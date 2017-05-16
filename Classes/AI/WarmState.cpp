#include"WarmState.h"
#include"WarmMonster.h"
#include"MonsterBehavior.h"
#include"Hero\Serber.h"


//--------------------------------

void WarmPatrol::Enter(WarmMonster* warm) {
	//CCLOG("WarmPatrol Enter");
	warm->getBehavior()->setWarmState(WarmState::WANDER);
}

void WarmPatrol::Execute(WarmMonster* warm) {
	//CCLOG("WarmPatrol Execute");

	if (warm->isBeHurt()) {
		warm->getStateMachine()->changeState(BeHurt::getInstance());
	}


	if (warm->isFlee()) {
		warm->getStateMachine()->changeState(WarmFlee::getInstance());
	}
	if (warm->isSeek()) {
		if(warm->isHaveCoollideFromHero())
			if(warm->setPath())
			warm->getStateMachine()->changeState(PursuitByPath::getInstance());
		else
			warm->getStateMachine()->changeState(WarmAttack::getInstance());
		warm->stopCalmAnimate();
		warm->runAngerAnimate();
	}
}

void WarmPatrol::Exit(WarmMonster* warm) {
	//CCLOG("WarmPatrol Exit");
	//warm->stopCalmAnimate();
}

//------------------------------------


//--------------------------------

void WarmAttack::Enter(WarmMonster* warm) {
	CCLOG("WarmAttack Enter");
	warm->getBehavior()->setWarmState(WarmState::SEEK);
}

void WarmAttack::Execute(WarmMonster* warm) {

	if (warm->isBeHurt()) {
		warm->getStateMachine()->changeState(BeHurt::getInstance());
	}

	warm->attackUpdate();


	if (warm->isFlee()) {
		warm->getStateMachine()->changeState(WarmFlee::getInstance());
		warm->runCalmAnimate();
	}
	if (warm->isWander()) {
		warm->getStateMachine()->changeState(WarmPatrol::getInstance());
		warm->runCalmAnimate();
	}

	if (warm->isHaveCoollideFromHero())
		if (warm->setPath())
			warm->getStateMachine()->changeState(PursuitByPath::getInstance());
}

void WarmAttack::Exit(WarmMonster* warm) {
	CCLOG("WarmAttack Exit");
	warm->stopAngerAnimate();
}

//------------------------------------

void WarmFlee::Enter(WarmMonster* warm) {
	//CCLOG("WarmFlee Enter");
	warm->getBehavior()->setWarmState(WarmState::FLEE);
}

void WarmFlee::Execute(WarmMonster* warm) {
	if (warm->isBeHurt()) {
		warm->getStateMachine()->changeState(BeHurt::getInstance());
	}

	if (warm->isWander()) {
		warm->getStateMachine()->changeState(WarmPatrol::getInstance());
	}
}

void WarmFlee::Exit(WarmMonster* warm) {
	//CCLOG("WarmFlee Exit");
}

//------------------------------------


//------------------------------------

void BeHurt::Enter(WarmMonster* warm) {
	CCLOG("BeHurt Enter");
	warm->getBehavior()->setWarmState(WarmState::BEHURT);
	warm->setVVelocity(Vec2(0.0f, 0.0f));
}

void BeHurt::Execute(WarmMonster* warm) {

	if (warm->isBeHurt())
		return;

	if (warm->isFlee()) {
		warm->getStateMachine()->changeState(WarmFlee::getInstance());
		warm->runCalmAnimate();
	}
	if (warm->isWander()) {
		warm->getStateMachine()->changeState(WarmPatrol::getInstance());
	}
	if (warm->isSeek()) {
		if (warm->isHaveCoollideFromHero())
			warm->getStateMachine()->changeState(PursuitByPath::getInstance());
		else
			warm->getStateMachine()->changeState(WarmAttack::getInstance());
		warm->stopCalmAnimate();
		warm->runAngerAnimate();
	}
}

void BeHurt::Exit(WarmMonster* warm) {
	CCLOG("BeHurt Exit");
}

//------------------------------------


//------------------------------------

void PursuitByPath::Enter(WarmMonster* warm) {
	CCLOG("PursuitByPath Enter");
	warm->getBehavior()->setWarmState(WarmState::PURSUITBYPATH);
}

void PursuitByPath::Execute(WarmMonster* warm) {
	if (warm->isBeHurt())
		return;

	if (warm->isFlee()) {
		warm->getStateMachine()->changeState(WarmFlee::getInstance());
		warm->runCalmAnimate();
	}
	if (warm->isWander()) {
		warm->getStateMachine()->changeState(WarmPatrol::getInstance());

	}

	if (!warm->isHaveCoollideFromHero())
		warm->getStateMachine()->changeState(WarmAttack::getInstance());
}

void PursuitByPath::Exit(WarmMonster* warm) {
	CCLOG("PursuitByPath Exit");
	warm->cleanPath();
	warm->stopAngerAnimate();
}

//------------------------------------
