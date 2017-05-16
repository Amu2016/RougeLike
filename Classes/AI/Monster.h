#pragma once
#ifndef _Monster_H_
#define _Monster_H_

#include"cocos2d.h"
#include"stdafx.h"
#include"MyRandom.h"
#include"Map\MyTileMap.h"
#include"UI\HpStrand.h"
#include"Varia\Gore.h"
#include"Map\Path.h"

USING_NS_CC;

class Serber;

class Monster : public Sprite {
public:
	Monster() {}
	Monster(Gore::GoreType goreType) :
		goreType(goreType),
		rng(RngT(std::random_device()())),
		mass(1.0f),
		maxSpeed(getRandomFloat(rng, 90.0f, 120.0f)),
		minSpeed(10.0f),
		maxForce(100.0f),
		maxTurnRate(10.0f),
		mAttack(5),
		mDefense(0),
		rigidityTime(0.5f),
		repelDistance(10.0f),
		b_IsBeHurt(false),
		path(new Path()),
		tilesCollideKeys(MyTileMap::getInstance()->getTilesCollideKeys())
	{
		vVelocity = Vec2(
			getRandomFloat(rng, -10.0f, 10.0f),
			getRandomFloat(rng, -10.0f, 10.0f));
		vHeading = vVelocity.getNormalized();
		vSide = vHeading.getPerp();
	}
	static Monster* create();
	virtual bool init();
	void SetTraget(Serber* sprite) { hero = sprite; }

	void setMonsterVec(std::vector<Monster*>* p_vec) { p_vecWarm = p_vec; }

	void update(float delta);

	Vec2 getVelocity() { return vVelocity; }
	Vec2 getHdading() { return vHeading; }
	Vec2 getSide() { return vSide; }

	Vec2 getHeroPos();

	Rect getMonsterBoundingBox() { return p_monster->getBoundingBox(); }

	bool beHurt(int damage);
	bool isBeHurt();

	bool isDie();

	bool isHaveCoollideFromHero();

	void runBeHurtAnimate();

	void setVVelocity(Vec2 vec) { vVelocity = vec; }

	int  getMaxHp() { return maxHp; }
	int getNowHp() { return nowHp; }
	int getFleeHp() { return fleeHp; }
	float getCordon() { return cordon; }
	float getMaxCordon() { return maxCordon; }

	float getSpeed() { return vVelocity.length(); }
	float getMass() { return mass; }
	float getMaxSpeed() { return maxSpeed; }
	float getMaxForce() { return maxForce; }
	float getMaxTurnRate() { return maxTurnRate; }

	Path* getPath() { return path; }
	bool setPath();
	void setPath(Path* p) { path->set(p); }
	void cleanPath() { path->clear(); }


	virtual ~Monster() {
		delete path;
	}

protected:
	Sprite* p_monster;

	Serber* hero;
	HpStrand* hpStrand;

	std::vector<Monster*>* p_vecWarm;

	std::map<Vec2, bool> tilesCollideKeys;

	Gore::GoreType goreType;

	Path* path;

	int maxHp;
	int nowHp;
	int fleeHp;
	int mAttack;
	int mDefense;

	float rigidityTime;
	float repelDistance;


	bool b_IsBeHurt;


	float cordon;
	float maxCordon;

	RngT rng;
	Size tileSize;
	Size mapSize;
	Size winSize;
	Size mapXXSize;

	Vec2 vVelocity;//速率 
	Vec2 vHeading;//标准化向量   实体朝向
	Vec2 vSide;//垂直于实体朝向向量

	float mass;
	float maxSpeed;//最大速度
	float minSpeed;
	float maxForce;//最大驱动力
	float maxTurnRate;//最大转向速率（弧度每秒）

	void setMaxHp(int hp) { maxHp = hp; }
	void setNowHp(int hp) { nowHp = hp; }
	void setFleeHp(int hp) { fleeHp = hp; }
	void setCordon(float cor) { cordon = cor; }
	void setMaxCordon(float maxcor) { maxCordon = maxcor; }

private:

};

#endif // !_Monster_H_
