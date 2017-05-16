#pragma once
#ifndef _HEROSTATE_H_
#define _HEROSTATE_H_

#include"FSM\State.h"

class Hero;

//Wake
class Wake : public State<Hero> {
public:
	static Wake* getInstance() {
		static Wake* wake = new Wake();
		return wake;
	}

	virtual void Enter(Hero* hero);
	virtual void Execute(Hero* hero);
	virtual void Exit(Hero* hero);

private:
	Wake() {}

};


//Stand
class Stand : public State<Hero> {
public:
	static Stand* getInstance() {
		static Stand* stand = new Stand();
		return stand;
	}

	virtual void Enter(Hero* hero);
	virtual void Execute(Hero* hero);
	virtual void Exit(Hero* hero);

private:
	Stand() {}

};


//Fight
class Fight : public State<Hero> {
public:
	static Fight* getInstance() {
		static Fight* fight = new Fight();
		return fight;
	}

	virtual void Enter(Hero* hero);
	virtual void Execute(Hero* hero);
	virtual void Exit(Hero* hero);

private:
	Fight() {}

};

#endif // !_HEROSTATE_H_
