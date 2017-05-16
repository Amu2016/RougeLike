#pragma once
#ifndef _MonsterBehavior_H_
#define _MonsterBehavior_H_

#include"stdafx.h"
#include"MyRandom.h"
#include"Map\MyTileMap.h"
#include"2D\Transformations.h"
#include"Map\Map2D.h"

class WarmMonster;

class MonsterBehavior {
public:
	MonsterBehavior(WarmMonster* monster):
		tileMap(MyTileMap::getInstance()->getMap()),
		tilesCollideKeys(MyTileMap::getInstance()->getTilesCollideKeys()),
		seed(std::random_device()()),
		warm(monster),
		warmState(WarmState::WANDER),
		wanderJitter(30.0f),
		wanderRadius(120.0f),
		wanderDistance(130.0f)
	{
		rng = RngT(seed);
	}

	~MonsterBehavior();

	Vec2 Calculate();

	void setWarmState(WarmState state) { warmState = state; }
	WarmState getWarmState() { return warmState; }

	Vec2 Seek();

	Vec2 Seek(Vec2 vecPos);

	Vec2 Flee();

	Vec2 Arrive(Vec2 tragetPos);

	Vec2 Pursuit();

	Vec2 Evade();

	Vec2 Wander();

	Vec2 ObstacleAvoidance();

	Vec2 FollowPath();

	

private:
	TMXTiledMap* tileMap;
	//std::vector<Collide>& tilesCollideKeys;
	std::map<Vec2, bool> tilesCollideKeys;

	WarmMonster*	warm;
	int seed;
	RngT rng;

	WarmState warmState;

	//---------Wander-----------
	Vec2			wanderTarget;//徘徊的目标点
	float			wanderJitter;//每秒加到目标点的随机距离
	float			wanderRadius;//wander圈的半径
	float			wanderDistance;//wander圈在智能体前面的距离(一般大于半径)
	//--------------------------

	//----ObstacleAvoidance-----

	float			boxLength;
	float			boxHeight;

	//--------------------------


	Sprite* sprite;
};

#endif // !_MonsterBehavior_H_
