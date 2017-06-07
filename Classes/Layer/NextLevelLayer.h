#pragma once
#ifndef _NextLevelLayer_H_
#define _NextLevelLayer_H_

#include"cocos2d.h"
#include"stdafx.h"

class NextLevelLayer :public cocos2d::LayerColor {
public:
	static NextLevelLayer* NextLevelLayer::create()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		NextLevelLayer * layer = new (std::nothrow) NextLevelLayer();
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

#endif // !_NextLevelLayer_H_
