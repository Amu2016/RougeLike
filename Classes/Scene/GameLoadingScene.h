#pragma once
#ifndef _GameLoadingScene_H_
#define _GameLoadingScene_H_

#include"cocos2d.h"
USING_NS_CC;

class GameLoadingScene : public cocos2d::Layer{
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLoadingScene);
};

#endif // !_GameLoadingScene_H_
