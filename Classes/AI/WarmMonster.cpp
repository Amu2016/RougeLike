#include"WarmMonster.h"
#include"MonsterBehavior.h"
#include"WarmState.h"
#include"Hero\Serber.h"

WarmMonster::WarmMonster() :
	Monster(Gore::GoreType::Warm),
	behavior(new MonsterBehavior(this))
{}

WarmMonster::~WarmMonster() {
	delete stateMachine;
	delete behavior;
}

WarmMonster* WarmMonster::create() {
	WarmMonster* sprite = new WarmMonster();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool WarmMonster::init() {
	if (!Monster::init()) return false;

	initAnimation();

	runCalmAnimate();

	p_monster->setScale(0.2f);
	//setRotation(100);

	setMaxHp(50);
	setNowHp(50);
	setFleeHp(30);
	setCordon(300);
	setMaxCordon(300);

	//------------------------

	hpStrand = HpStrand::create(maxHp);
	addChild(hpStrand, 2);
	hpStrand->setPosition(Vec2(0, 25));
	hpStrand->setScaleX(0.9f);
	hpStrand->setScaleY(0.5f);

	//---------------------

	stateMachine = new StateMachine<WarmMonster>(this);	
	stateMachine->setCurrentState(WarmPatrol::getInstance());
	behavior->setWarmState(WarmState::WANDER);
	//stateMachine->setGlobalState();


	//--------------------

	//----------------
	scheduleUpdate();
	//----------------

	return true;
}

void WarmMonster::update(float delta) {
	stateMachine->update(delta);
	updatePosition(delta);
	hpStrand->updateHp(nowHp);
}

inline void WarmMonster::updatePosition(float delta) {

	Vec2 force = behavior->Calculate();

	Vec2 accelerartion = force / mass;


	//Vec2 changeV = accelerartion * delta;
	//CCLOG("changeV    %f   %f", changeV.x, changeV.y);

	vVelocity += accelerartion * delta;

	if (vVelocity.length() > maxSpeed) {
		vVelocity.normalize();
		vVelocity *= maxSpeed;
	}
	//if (vVelocity.length() < minSpeed) {
	//	vVelocity.normalize();
	//	vVelocity *= minSpeed;
	//}

	Vec2 newposition = getPosition() + vVelocity * delta;



	if (newposition.x > mapSize.width)
		newposition -= Vec2(mapSize.width, 0);
	if (newposition.x < 0)
		newposition += Vec2(mapSize.width, 0);

	if (newposition.y > mapSize.height)
		newposition -= Vec2(0, mapSize.height);
	if (newposition.y < 0)
		newposition += Vec2(0, mapSize.height);

	setPosition(newposition);

	if (vVelocity.length() > 0.000001f) {
		vHeading = vVelocity.getNormalized();
		vSide = vHeading.getPerp();
	}
	
	p_monster->setRotation(-(CC_RADIANS_TO_DEGREES(vHeading.getAngle()) + 90.0f));
		

	//auto a = behavior->ObstacleAvoidance();
	//auto b = behavior->Wander();
	//CCLOG("ObstacleAvoidance::  %f   %f", a.x, a.y);
	//CCLOG("Wander::  %f   %f", b.x, b.y);

	//float rotate = CC_RADIANS_TO_DEGREES(vHeading.getAngle());
	//char* log1 = new char[50];
	//sprintf(log1, "%f\40%f\40%f\40%f", vVelocity.x*delta, vVelocity.y*delta, vVelocity.length(), rotate);
	//CCLOG(log1);
	//char* log2 = new char[30];
	//sprintf(log2, "%f%f", newposition.x, newposition.y);
	//CCLOG(log2);
}

bool WarmMonster::attackUpdate() {

	if (Rect(getPosition() + Vec2(p_monster->getBoundingBox().size.width / 6, 
		p_monster->getBoundingBox().size.height / 6),
		p_monster->getBoundingBox().size * 2 / 3).intersectsRect(
		Rect(hero->getPosition() + Vec2(hero->getHeroSprite()->getBoundingBox().size.width / 6,
			hero->getHeroSprite()->getBoundingBox().size.height / 6),
			Size(hero->getHeroSprite()->getBoundingBox().size.width * 2 / 3,
				hero->getHeroSprite()->getBoundingBox().size.height * 2 / 3)))) {
		hero->beHurt(mAttack, vVelocity);
		return true;
	}
	return false;
}

inline void WarmMonster::WanderPatrol() {

}

bool WarmMonster::isFlee() { return nowHp < fleeHp; }
bool WarmMonster::isSeek() { return getPosition().distanceSquared(hero->getPosition()) < (cordon * cordon); }
bool WarmMonster::isWander() { return getPosition().distanceSquared(hero->getPosition()) > (maxCordon * maxCordon); }


inline void WarmMonster::initAnimation() {
	auto Warm_Calm = Animation::create();
	for (int i = 1; i < 4; i++)
		Warm_Calm->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("NPC_4_0%d.png", i)));

	Warm_Calm->setDelayPerUnit(1.0f / 10.0f);
	Warm_Calm->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(Warm_Calm, "Warm_Calm");

	auto Warm_Anger = Animation::create();
	for (int i = 4; i < 7; i++)
		Warm_Anger->addSpriteFrame(SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("NPC_4_0%d.png", i)));

	Warm_Anger->setDelayPerUnit(1.0f / 10.0f);
	Warm_Anger->setRestoreOriginalFrame(true);
	AnimationCache::getInstance()->addAnimation(Warm_Anger, "Warm_Anger");
}

void WarmMonster::runCalmAnimate() {
	auto calm = Animate::create(AnimationCache::getInstance()->getAnimation("Warm_Calm"));
	auto repeatanimate = RepeatForever::create(calm);
	repeatanimate->setTag(WARM_CALM_TAG);

	p_monster->runAction(repeatanimate);
}

void WarmMonster::runAngerAnimate() {
	auto anger = Animate::create(AnimationCache::getInstance()->getAnimation("Warm_Anger"));
	auto repeatanimate = RepeatForever::create(anger);
	repeatanimate->setTag(WARM_ANGER_TAG);

	p_monster->runAction(repeatanimate);
}

void WarmMonster::stopCalmAnimate() {
	p_monster->stopActionByTag(WARM_CALM_TAG);
}

void WarmMonster::stopAngerAnimate() {
	p_monster->stopActionByTag(WARM_ANGER_TAG);
}