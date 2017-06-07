#include"MonsterBehavior.h"
#include"WarmMonster.h"

//std::map<Vec2, bool> MonsterBehavior::tilesCollideKeys = MyTileMap::getInstance()->getCollideKeys();

MonsterBehavior::~MonsterBehavior() {}

Vec2 MonsterBehavior::Calculate() {
	Vec2 force = Vec2(0.0f, 0.0f);

	switch (warmState)
	{
	case WarmState::FLEE:
		force = Flee();
		force += ObstacleAvoidance();
		break;
	case WarmState::SEEK:
		force = Seek();
		force += ObstacleAvoidance();
		break;
	case WarmState::WANDER:
		force = Wander();
		force += ObstacleAvoidance();
		break;
	case WarmState::BEHURT:
		break;
	case WarmState::PURSUITBYPATH:
		force = FollowPath();
		//force += ObstacleAvoidance();
		break;
	default:
		break;
	}
	return force;
}

Vec2 MonsterBehavior::Seek() {

	Vec2 DesiredVelocity = (warm->getHeroPos() - warm->getPosition()).getNormalized() 
							* warm->getMaxSpeed();

	return (DesiredVelocity - warm->getVelocity());
}

Vec2 MonsterBehavior::Seek(Vec2 vecPos) {
	Vec2 DesiredVelocity = (vecPos - warm->getPosition()).getNormalized()
		* warm->getMaxSpeed() * 2;

	return (DesiredVelocity - warm->getVelocity());
}

Vec2 MonsterBehavior::Flee(){
	Vec2 DesiredVelocity = (warm->getPosition() - warm->getHeroPos()).getNormalized()
		* warm->getMaxSpeed();

	return (DesiredVelocity - warm->getVelocity());
}

Vec2 MonsterBehavior::Arrive(Vec2 tragetPos) {
	Vec2 toTraget = tragetPos - warm->getPosition();

	float dist = toTraget.length();

	if (dist > 0) {
		float decelerationWeaker = 0.3f;

		float speed = dist / (3 * decelerationWeaker);

		speed = MIN(speed, warm->getMaxSpeed());

		Vec2 desiredVelocity = toTraget * speed / dist;

		return (desiredVelocity - warm->getVelocity());
	}
	return Vec2(0, 0);
}

//Vec2 MonsterBehavior::Pursuit() {
//
//}
//
//Vec2 MonsterBehavior::Evade() {
//
//}

Vec2 MonsterBehavior::FollowPath() {
	//
	//如果  到达后   继续执行这个函数    warm->getPath()->setNextWayPoint();  会出错，   溢出 list
	//
	if (warm->getPath()->currentWayPoint().distanceSquared(warm->getPosition()) < 5 * 5) {
		if (warm->getPath()->Finished())
			Arrive(warm->getPath()->currentWayPoint());
		else
			warm->getPath()->setNextWayPoint();
	}

	if (!warm->getPath()->Finished())
		return Arrive(warm->getPath()->currentWayPoint());
	//else
	//	return Arrive(warm->getPath()->currentWayPoint());
}

Vec2 MonsterBehavior::Wander() {
	wanderTarget += Vec2(randomClamped(rng)*wanderJitter,
						 randomClamped(rng)*wanderJitter);
	wanderTarget.normalize();
	wanderTarget *= wanderRadius;
	
	Vec2 targetLocal = wanderTarget + Vec2(wanderDistance, 0);
	Vec2 targetParent = PointToWorldSpace(
		targetLocal,
		warm->getHdading(),
		warm->getSide(),
		warm->getPosition()
	);

	Vec2 a = warm->getPosition();


	return targetParent - warm->getPosition();
}

Vec2 MonsterBehavior::ObstacleAvoidance() {

	Vec2 warmPos = warm->getPosition();

	boxLength = MinDetectionBoxLength +
		(warm->getSpeed() / warm->getMaxSpeed()) * MinDetectionBoxLength;

	boxHeight = MAPTILESIZE + warm->getMonsterBoundingBox().size.height*2/3;

	Vec2 obs = Vec2(0, 0);
	float disToObs = boxLength * boxLength;

	Vec2 LocalPosOfClosestObstacle;
	bool isHaveCollide = false;


	for (int i = 0; i <= boxLength + 29; i += 30) {
		if (boxLength - i > 0 && i - boxLength < 30)
			i = boxLength;
		for (int j = -boxHeight; j <= boxHeight + 29; j += 30) {
			if (j > 0&& j - boxHeight > 0 && j - boxHeight < 30)
				j = boxHeight;
			Vec2 localPos = PointToWorldSpace(
				Vec2(i, j) ,
				warm->getHdading(),
				warm->getSide(),
				warm->getPosition()
			);
			Vec2 pos = tileMapPosition(localPos, tileMap);
			if (tilesCollideKeys[pos]) {
				Vec2 collidePos = tilePosToCenterPos(pos, tileMap);
				float ip = warmPos.distanceSquared(collidePos);

				if (ip < disToObs) {
					disToObs = ip;
					LocalPosOfClosestObstacle = PointToLocalSpace(collidePos,
						warm->getHdading(),
						warm->getSide(),
						warm->getPosition()
					);
					isHaveCollide = true;
				}
			}
			
		}
	}

	Vec2 SteeringForce;

	if (isHaveCollide) {
		float multiplier = 20 + ((boxLength - LocalPosOfClosestObstacle.x) / boxLength) * 5;
		SteeringForce.y = (MAPTILESIZE - LocalPosOfClosestObstacle.y) * multiplier;

		float BrakingWeight = 50;
		SteeringForce.x = -(boxLength - LocalPosOfClosestObstacle.x) * BrakingWeight;
	}

	//CCLOG("changeV    %f   %f", SteeringForce.x, SteeringForce.y);

	return VectorToWorldSpace(
		SteeringForce,
		warm->getHdading(),
		warm->getSide());
}