#pragma once
#ifndef _WarmState_H_
#define _WarmState_H_

#include"FSM\State.h"
#include"cocos2d.h"

class WarmMonster;

// wander
class WarmPatrol : public State<WarmMonster> {
public:
	static WarmPatrol* getInstance() {
		static WarmPatrol* warmPatrol = new WarmPatrol();
		return warmPatrol;
	}

	virtual void Enter(WarmMonster* warm);
	virtual void Execute(WarmMonster* warm);
	virtual void Exit(WarmMonster* warm);

private:
	WarmPatrol() {}

};

// seek
class WarmAttack : public State<WarmMonster> {
public:
	static WarmAttack* getInstance() {
		static WarmAttack* warmAttack = new WarmAttack();
		return warmAttack;
	}

	virtual void Enter(WarmMonster* warm);
	virtual void Execute(WarmMonster* warm);
	virtual void Exit(WarmMonster* warm);

private:
	WarmAttack() {}
};

// flee
class WarmFlee : public State<WarmMonster> {
public:
	static WarmFlee* getInstance() {
		static WarmFlee* warmFlee = new WarmFlee();
		return warmFlee;
	}

	virtual void Enter(WarmMonster* warm);
	virtual void Execute(WarmMonster* warm);
	virtual void Exit(WarmMonster* warm);

private:
	WarmFlee() {}
};



// be hurt
class BeHurt : public State<WarmMonster> {
public:
	static BeHurt* getInstance() {
		static BeHurt* beHurt = new BeHurt();
		return beHurt;
	}

	virtual void Enter(WarmMonster* warm);
	virtual void Execute(WarmMonster* warm);
	virtual void Exit(WarmMonster* warm);

private:
	BeHurt() {}
};


// xunlu
class PursuitByPath : public State<WarmMonster> {
public:
	static PursuitByPath* getInstance() {
		static PursuitByPath* pursuit = new PursuitByPath();
		return pursuit;
	}

	virtual void Enter(WarmMonster* warm);
	virtual void Execute(WarmMonster* warm);
	virtual void Exit(WarmMonster* warm);

private:
	PursuitByPath() {}
};



#endif // !_WarmState_H_
