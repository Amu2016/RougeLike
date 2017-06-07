#pragma once
#ifndef _GameLoadingLayer_H_
#define _GameLoadingLayer_H_

#include"cocos2d.h"
#include"stdafx.h"

class GameLoadingLayer :public cocos2d::LayerColor {
public:
	static GameLoadingLayer* GameLoadingLayer::create()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		GameLoadingLayer * layer = new (std::nothrow) GameLoadingLayer();
		if (layer && layer->initWithColor(Color4B::WHITE , visibleSize.width, visibleSize.height))
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

#endif // !_GameLoadingLayer_H_
