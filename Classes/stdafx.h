#pragma once
#ifndef STDAFX_H
#define STDAFX_H

#include"cocos2d.h"
#include"math.h"
#include<random>

typedef std::mt19937 RngT;

#define PI 3.14159265359f

USING_NS_CC;


#define MAPTILESIZE 32.0f


//-----------------------------

#define WIDE 50		//地图横向
#define LENGTH 50	//地图纵向
#define D 10		//横向移动代价
#define D2 14		//对角移动代价

//   节点属性
//		空	   墙  OpenList内 CloseList内  开始节点   目标节点
enum { VIABLE, WALL, INOPEN, INCLOSE, STARTNODE, TRAGETNODE };
//0      1      2  
//3      S      4
//5      6      7
static const int Dir[8][2] = { { -1,-1 },{ -1,0 },{ -1,1 },{ 0,-1 },{ 0,1 },{ 1,-1 },{ 1,0 },{ 1,1 } };

static const int Dirs[9][2] = { { -1,-1 },{ -1,0 },{ -1,1 },{ 0,-1 },{ 0,0 } ,{ 0,1 },{ 1,-1 },{ 1,0 },{ 1,1 } };

struct MapNode {
	size_t Val_F = 0;	//F=G+H	初始点  经过  节点 到目标节点的估价函数
	size_t Pos_X;	//节点的X坐标
	size_t Pos_Y;	//节点的Y坐标
	size_t Val_G = 0;	//初始点带节点的实际代价
	size_t Val_H = 0;	//节点到目标节点的估计代价
	size_t flag = VIABLE;
	MapNode* father;	//父节点
	size_t Key = 0;			//在heap中的key值
};

//-----------------------------


//-----------------------------

#define MAP_MAX_WIDE 12
#define MAP_MAX_LENGTH 14
#define MAP_MIN_WIDE 5
#define MAP_MIN_LENGTH 6

#define MAP_MAX_CORRIDOR 7
#define MAP_MIN_CORRIDOR 2


enum class Tiles {
	Unused,		//未使用
	DirtWall,	//墙
	DirtFloor,	//地板
	Corridor,	//
	Door,		//门
	UpStairs,	//
	DownStairs	//
};

enum class Direction {
	North,
	South,
	East,
	West
};

//-------------------------



//-----------------------

#define HERO_STAND_FLAG 1
#define HERO_WAKE_FLAG 2
#define HERO_MOVE_FLAG 3
#define HERO_FIGHT_FLAG 4

#define HERO_UPSTAND_TAG 1
#define HERO_DOWNSTAND_TAG 2
#define HERO_LEFTSTAND_TAG 3
#define HERO_RIGHTSTAND_TAG 4

#define HERO_UPWAKE_TAG 11
#define HERO_DOWNWAKE_TAG 12
#define HERO_LEFTWAKE_TAG 13
#define HERO_RIGHTWAKE_TAG 14

#define HERO_UPMOVE_TAG 21
#define HERO_DOWNMOVE_TAG 22
#define HERO_LEFTMOVE_TAG 23
#define HERO_RIGHTMOVE_TAG 24

#define HERO_UPFIGHT_TAG 31
#define HERO_DOWNFIGHT_TAG 32
#define HERO_LEFTFIGHT_TAG 33
#define HERO_RIGHTFIGHT_TAG 34

#define HERP_BEHURTMOVE_TAG 80
#define HERP_BEHURTJUMP_TAG  81

enum class HeroDir {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class HeroState {
	WAKE,
	STAND,
	FIGHT
};

enum class HeroEvent {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FIGHT,
	SKILL_1,
	SKILL_2,
	SKILL_3
};

enum class HeroMoveDir {
	STAND,
	UPMOVE,
	DOWNMOVE,
	LEFTMOVE,
	RIGHTMOVE
};





//-----------------------------


//-----------------------

#define GAMELAYER_UPMOVE_TAG 101
#define GAMELAYER_DOWNMOVE_TAG 102
#define GAMELAYER_LEFTMOVE_TAG 103
#define GAMELAYER_RIGHTMOVE_TAG 104





//----------------------



//----------------------
#define WARM_CALM_TAG 201
#define WARM_ANGER_TAG 202


#define WARM_BEHURT_TAG 300


enum class WarmState {
	SEEK,
	FLEE,
	WANDER,
	BEHURT,
	PURSUITBYPATH
};

//-------------------

//-------------------

#define MinDetectionBoxLength 30

struct  Collide{
	Collide(Vec2 pos, bool tag) :
		Pos(pos),
		Tag(tag) {}
	Vec2 Pos;
	bool Tag;
};

//-------------------
#endif STDAFX_H