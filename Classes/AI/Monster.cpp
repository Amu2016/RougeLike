#include"Monster.h"
#include"Hero\Serber.h"
#include"Map\AStar.h"
#include"Map/Map2D.h"
#include"2D\Transformations.h"
#include"Layer\NextLevelLayer.h"

Monster* Monster::create() {
	Monster* sprite = new Monster();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Monster::init() {
	if (!Sprite::init()) return false;

	tileSize = MyTileMap::getInstance()->getTileSize();
	mapSize = MyTileMap::getInstance()->getMapLayerSize();
	winSize = Director::getInstance()->getWinSize();
	mapXXSize = MyTileMap::getInstance()->getMapSize();



	p_monster = Sprite::create();
	addChild(p_monster, 1);

	return true;	
}

void Monster::update(float delta) {

}

Vec2 Monster::getHeroPos() {
	return hero->getPosition();
}

bool Monster::beHurt(int damage) {
	if (getActionByTag(WARM_BEHURT_TAG)) {
		if (getActionByTag(WARM_BEHURT_TAG)->isDone()) {
			nowHp = nowHp - damage + mDefense;
			runBeHurtAnimate();
			b_IsBeHurt = true;
			return true;
		}
	}
	else {
		nowHp = nowHp - damage + mDefense;
		runBeHurtAnimate();
		b_IsBeHurt = true;
		return true;
	}
	return false;
}

bool Monster::isBeHurt() {
	if (b_IsBeHurt) {
		if (getActionByTag(WARM_BEHURT_TAG)) {
			if (getActionByTag(WARM_BEHURT_TAG)->isDone()) {
				b_IsBeHurt = false;
			}
			else
				return b_IsBeHurt;
		}
		b_IsBeHurt = false;
	}
	return b_IsBeHurt;
}

bool Monster::isDie() {
	if (nowHp > 0) return false;

	Gore* gore = Gore::create(goreType);

	auto size = p_vecWarm->size();

	gore->setPosition(getPosition());

	getParent()->addChild(gore, 0);

	auto iter = (*p_vecWarm).begin();

	while (iter != (*p_vecWarm).end()) {
		if (*iter == this)
			iter = (*p_vecWarm).erase(iter);
		else
			iter++;
	}

	if (size == 1) {
		auto nextLevelLayer = NextLevelLayer::create();
		nextLevelLayer->setPosition(Vec2(-getParent()->getPosition().x, -getParent()->getPosition().y));
		getParent()->addChild(nextLevelLayer, 2);
	}

	removeFromParent();

	return true;
}


bool Monster::isHaveCoollideFromHero() {
	auto pos = getPosition();
	auto heropos = hero->getPosition();

	auto disSqu = pos.distanceSquared(hero->getPosition());
	
	for (int i = tileSize.width / 2; i * i < disSqu - tileSize.width / 2; i += (tileSize.width / 2)) {
		Vec2 testPoint = Vec2(i, 0);
		
		Vec2 norVec = Vec2(hero->getPosition() - pos).getNormalized();

		Vec2 localPos = PointToWorldSpace(
			testPoint,
			norVec,
			norVec.getPerp(),
			pos
		);

		Vec2 testLocalPos = tileMapPosition(localPos, MyTileMap::getInstance()->getMap());
		
		if (tilesCollideKeys[testLocalPos]) {
			return true;
		}
	}
	return false;
}

void Monster::runBeHurtAnimate() {
	//auto scale1 = ScaleTo::create(rigidityTime/2, 0.7f, 0.8f, 1.0f);
	//auto scale2 = ScaleTo::create(rigidityTime/2, 1.0f);
	//auto scale3 = EaseElasticOut::create(scale2);
	//auto action = Sequence::create(scale1, scale2);

	auto a = Vec2(-vVelocity.x, -vVelocity.y).getNormalized()*repelDistance;

	auto move = MoveBy::create(rigidityTime, Vec2(-vVelocity.x, -vVelocity.y).getNormalized()*repelDistance);
	auto jump = JumpBy::create(rigidityTime, Vec2(0, 0), 5.0f, 1);

	//action->setTag(WARM_BEHURT_TAG);
	move->setTag(WARM_BEHURT_TAG);

	//p_monster->runAction(action);
	runAction(move);
	runAction(jump);
}

bool Monster::setPath() {
	AStar* aStar = new AStar();
	auto map = MyTileMap::getInstance()->getMap();


	aStar->setTraget(tileMapPosition(getPosition(), map),
		tileMapPosition(hero->getPosition(), map));

	if (!aStar->FindPath())
		return false;

	auto listPath = aStar->getPathList();

	path->clear();
	for (auto wayPoint : listPath) {
		auto a = tilePosToCenterPos(wayPoint, map);
		path->addWayPoint(tilePosToCenterPos(wayPoint, map));
	}

	path->setCurrWayPoint();

	return true;
}