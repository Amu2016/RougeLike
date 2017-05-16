#pragma once
#ifndef _JoyStick_H_
#define _JoyStick_H_

#include "cocos2d.h"
#include <cmath>
#include"stdafx.h"
using namespace cocos2d;

class Serber;

class JoyStick : public Sprite
{
public:

	static JoyStick* getInstance() {
		static JoyStick* joyStick = JoyStick::create();
		return joyStick;
	}

	HeroMoveDir getHeroDir();

	void setHero(Serber* h) { hero = h; }

private:
	//static JoyStick* joyStick;

	Serber* hero;

	static JoyStick* create();

	JoyStick() {}
	virtual ~JoyStick(void);

	//中心摇杆精灵
	Sprite* centerPoint;


	//限制摇杆移动事件的频率
	int yhCount = 0;
	//方向盘半径
	float rRange;
	//中心摇杆离方向盘原点距离的横坐标
	float vx;
	//中心摇杆离方向盘原点距离的纵坐标
	float vy;
	//获取矩形区域
	Rect getRect();
	//判断触摸点位置的方法
	bool containsTouchLocation(Touch* touch);
	//初始化摇杆位置及获取半径
	void calCenter();
	//计算中心摇杆在纹理图的坐标方法
	void calCenterPosition(float tx, float ty);

	//每次精灵进入时被回调
	virtual void onEnter();
	//每次精灵退出时被回调
	virtual void onExit();
	//开始单点触控事件的处理方法
	bool onTouchBegan(Touch* touch, Event* event);
	//单点触控移动事件的处理方法
	void onTouchMoved(Touch* touch, Event* event);
	//单点触控结束事件的处理方法
	void onTouchEnded(Touch* touch, Event* event);
};


#endif
