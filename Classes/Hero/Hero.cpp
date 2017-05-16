#include"Hero.h"
#include"Layer\UILayer.h"
#include"HeroState.h"

float Hero::speed = 200;
bool Hero::KeyDown = false;

Hero* Hero::create() {
	Hero* sprite = new Hero();
	if (sprite && sprite->init())
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Hero::init() {
	if (!Sprite::init()) return false;

	heroDirVec = Vec2(0, 0);

	p_hero = Sprite::create();
	addChild(p_hero, 1);
	
	hpStrand = HpStrand::create(maxHp);
	addChild(hpStrand, 2);
	hpStrand->setPosition(Vec2(0, 20));
	hpStrand->setScaleX(0.9f);
	hpStrand->setScaleY(0.5f);



	stateMachine = new StateMachine<Hero>(this);
	stateMachine->setCurrentState(Wake::getInstance());


	scheduleUpdate();

	return true;
}

void Hero::update(float delta) {

	stateMachine->update(delta);

}

void Hero::beHurt(int damage, Vec2 vec) {
	if (getActionByTag(HERP_BEHURTJUMP_TAG)) {
		if (getActionByTag(HERP_BEHURTJUMP_TAG)->isDone()) {
			nowHp = nowHp - damage + mDefense;
			runBeHurtAnimate(vec);
		}
	}
	else {
		nowHp = nowHp - damage + mDefense;
		runBeHurtAnimate(vec);
	}
}

void Hero::runBeHurtAnimate(Vec2 vec) {
	//auto scale1 = ScaleTo::create(rigidityTime/2, 0.7f, 0.8f, 1.0f);
	//auto scale2 = ScaleTo::create(rigidityTime/2, 1.0f);
	//auto scale3 = EaseElasticOut::create(scale2);
	//auto action = Sequence::create(scale1, scale2);

	auto move = MoveBy::create(rigidityTime, vec.getNormalized()*repelDistance);
	auto jump = JumpBy::create(rigidityTime, Vec2(0, 0), 5.0f, 1);

	//action->setTag(WARM_BEHURT_TAG);
	move->setTag(HERP_BEHURTMOVE_TAG);
	jump->setTag(HERP_BEHURTJUMP_TAG);

	//p_monster->runAction(action);
	runAction(move);
	runAction(jump);
}


