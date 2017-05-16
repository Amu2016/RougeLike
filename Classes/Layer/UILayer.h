#pragma once
#ifndef _UILayer_H_
#define _UILayer_H_

#include"cocos2d.h"
#include"stdafx.h"
#include"UI\JoyStick.h"

//class GameLayer;

class UILayer :public cocos2d::Layer {
public:
	virtual bool init();

	void update(float delta);

	void updateHero(float delta);

	JoyStick* getJoyStick() { return joyStick; }

	//void setGameLayer(GameLayer* layer) { gameLayer = layer; }

	CREATE_FUNC(UILayer);


private:
	//GameLayer* gameLayer;

	JoyStick* joyStick;
};

#endif // !_UILayer_H_
