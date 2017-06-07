#pragma once
#ifndef _StartLayer_H_
#define _StartLayer_H_
#include"cocos2d.h"
#include"stdafx.h"

//class GameLayer;

class StartLayer :public cocos2d::Layer {
public:
	virtual bool init();

	void startGame();

	CREATE_FUNC(StartLayer);

};

#endif // !_StartLayer_H_