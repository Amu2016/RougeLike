#pragma once
#ifndef _GameLayer_H_
#define _GameLayer_H_

#include"cocos2d.h"
#include"cocostudio/CocoStudio.h"

#include"Map\DungeonGenerator.h"
#include"Map\MyTileMap.h"

#include"Hero\Serber.h"
#include"AI\WarmMonster.h"

USING_NS_CC;

class GameLayer :public cocos2d::Layer {
public:
	GameLayer() :
		rng(RngT(std::random_device()()))
	{}


	virtual bool init();

	void update(float delta);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);

	

	//void setUILayer(UILayer* ui) { uiLayer = ui; }



	inline Vec2 tileMapPosition(Vec2 position);
	inline Vec2 getChildWinPosition(float x, float y);
	inline void setViewCenter();


	Serber* getSerber() { return serber; }
	Vec2 getHeroPos() { return serber->getPosition(); }




	inline void layerMoveUp();
	inline void layerMoveDown();
	inline void layerMoveLeft();
	inline void layerMoveRight();


	CREATE_FUNC(GameLayer);

private:
	RngT rng;
	//UILayer* uiLayer;

	std::vector<Monster*> vecWarm;


	TMXTiledMap* tileMap;
	TMXLayer* background;
	TMXLayer* collide;

	Size mapSize;
	Size winSize;

	Serber* serber;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;


};

#endif // !_GameLayer_H_
