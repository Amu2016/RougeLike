#pragma once
#ifndef _Hero_H_
#define _Hero_H_

#include"stdafx.h"
#include"cocos2d.h"
#include"Map\MyTileMap.h"
#include"UI\HpStrand.h"
#include"FSM\StateMachine.h"

USING_NS_CC;

class Monster;

class Hero :public Sprite {
public:

	Hero() :
		heroDir(HeroDir::UP),
		heroState(HeroState::STAND),
		maxTime(3000),
		normalSpeed(100),
		maxHp(100),
		nowHp(100),
		mAttack(10),
		mDefense(0),
		rigidityTime(0.5f),
		repelDistance(10.0f)
	{}

	static Hero* create();

	virtual bool init();

	void update(float delta);

	Sprite* getHeroSprite() { return p_hero; }

	HeroDir getHeroDir() { return heroDir; }

	void setHeroDir(HeroDir herodir) { heroDir = herodir; }

	void setMonsterVec(std::vector<Monster*>* p_vec) { p_vecWarm = p_vec; }

	float getSpeed()const { return speed; }

	void setSpeed(float sp) { speed = sp; }

	float getMaxTime()const { return maxTime; }

	void beHurt(int damage, Vec2 vec);
	void runBeHurtAnimate(Vec2 vec);

protected:
	Sprite* p_hero;
	HpStrand* hpStrand;


	static float speed;
	const float maxTime;
	const float normalSpeed;
	int maxHp;
	int nowHp;
	int mAttack;
	int mDefense;

	float rigidityTime;
	float repelDistance;



	std::vector<Monster*>* p_vecWarm;

	
	
	static bool KeyDown;

	HeroDir heroDir;
	HeroState heroState;

	StateMachine<Hero>* stateMachine;


	Vec2 heroDirVec;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	struct Nature {
		int maxHp;
		int nowHp;


	};


private:

};

#endif // !_Hero_H_
