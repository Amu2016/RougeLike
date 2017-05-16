#pragma once
#ifndef _GameLoadingLayer_H_
#define _GameLoadingLayer_H_

#include"cocos2d.h"
#include"stdafx.h"

class GameLoadingLayer :public cocos2d::Layer {
public:
	virtual bool init();

	void startGame(float delta);

	CREATE_FUNC(GameLoadingLayer);

};

#endif // !_GameLoadingLayer_H_
