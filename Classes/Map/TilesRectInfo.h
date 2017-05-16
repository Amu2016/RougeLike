#pragma once
#ifndef _TilesRectInfo_H_
#define _TilesRectInfo_H_

#include"cocos2d.h"

class TilesRectInfo {
public:
	TilesRectInfo();
	TilesRectInfo(cocos2d::TMXTiledMap* tileMap);

	cocos2d::Rect getStoneTilesRect() { return Stone_TilesRect; }
	cocos2d::Rect getCorridorRect() { return Corridor_TilesRect; }
	cocos2d::Rect getFloorRect() { return Floor_TilesRect; }
	cocos2d::Rect getDoorRect() { return Door_TilesRect; }
	cocos2d::Rect getUnusedRect() { return Unused_TilesRect; }
	cocos2d::Rect getUpStairsRect() { return UpStairs_TilesRect; }
	cocos2d::Rect getDownStairsRect() { return DownStairs_TilesRect; }


private:
	cocos2d::TMXTiledMap* tileMap;
	cocos2d::TMXLayer* TilessLayer;

	cocos2d::Rect Stone_TilesRect;
	cocos2d::Rect Corridor_TilesRect;
	cocos2d::Rect Floor_TilesRect;
	cocos2d::Rect Door_TilesRect;
	cocos2d::Rect Unused_TilesRect;
	cocos2d::Rect UpStairs_TilesRect;
	cocos2d::Rect DownStairs_TilesRect;
};


#endif // !_TilesRectInfo_H_
