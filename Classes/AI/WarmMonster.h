#pragma once
#ifndef _WarmMonster_H_
#define _WarmMonster_H_

#include"Monster.h"
#include"FSM\StateMachine.h"

class MonsterBehavior;

class WarmMonster : public Monster {
public:
	static WarmMonster* create();
	virtual bool init();

	void update(float delta);

	inline void updatePosition(float delta);

	bool attackUpdate();

	inline void WanderPatrol();
	
	bool isFlee();
	bool isSeek();
	bool isWander();
	
	StateMachine<WarmMonster>* getStateMachine() { return stateMachine; }
	MonsterBehavior* getBehavior() { return behavior; }


	inline void initAnimation();

	void runCalmAnimate();
	void runAngerAnimate();
	void stopCalmAnimate();
	void stopAngerAnimate();

	~WarmMonster();

private:

	StateMachine<WarmMonster>* stateMachine;
	MonsterBehavior* behavior;


	WarmMonster();
	
};

#endif // !_WarmMonster_H_
