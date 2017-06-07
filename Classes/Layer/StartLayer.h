#pragma once
#ifndef _StartLayer_H_
#define _StartLayer_H_
#include"cocos2d.h"
#include"stdafx.h"

//class GameLayer;

class StartLayer :public cocos2d::LayerColor {
public:

	static StartLayer* StartLayer::create()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		StartLayer * layer = new (std::nothrow) StartLayer();
		if (layer && layer->initWithColor(Color4B::RED, visibleSize.width, visibleSize.height))
		{
			layer->init();
			layer->autorelease();
			return layer;
		}
		CC_SAFE_DELETE(layer);
		return nullptr;
	}
	virtual bool init();

	void startGame();

	//CREATE_FUNC(StartLayer);

};

#endif // !_StartLayer_H_