#pragma once
#ifndef _Map2D_H_
#define _Map2D_H_
#include "stdafx.h"
#include"MyTileMap.h"

inline Vec2 tileMapPosition(Vec2 position, TMXTiledMap* tileMap) {
	//auto tileMap = MyTileMap::getInstance();
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return Vec2(x, y);
}

inline Vec2 tilePosToCenterPos(Vec2 position, TMXTiledMap* tileMap) {
	int x = position.x * tileMap->getTileSize().width + tileMap->getTileSize().width / 2;
	int y = tileMap->getMapSize().height * tileMap->getTileSize().height - 
		position.y * tileMap->getTileSize().height - tileMap->getTileSize().height / 2;
	return Vec2(x, y);
}

#endif // !_Map2D_H_
