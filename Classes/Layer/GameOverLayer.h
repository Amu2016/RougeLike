#pragma once
#ifndef _GameOverLayer_H_
#define _GameOverLayer_H_

#include"cocos2d.h"
#include"stdafx.h"

class GameOverLayer :public cocos2d::LayerColor {
public:
	static GameOverLayer* GameOverLayer::create()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		GameOverLayer * layer = new (std::nothrow) GameOverLayer();
		if (layer && layer->initWithColor(Color4B::WHITE, visibleSize.width, visibleSize.height))
		{
			layer->init();
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}

	virtual bool init();

	void startGame(float delta);

	//CREATE_FUNC(GameLoadingLayer);

};

#endif // !_GameOverLayer_H_
