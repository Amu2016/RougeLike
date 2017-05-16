#pragma once
#ifndef _Map2D_H_
#define _Map2D_H_
#include "stdafx.h"
#include"MyTileMap.h"

auto tileMap = 

inline Vec2 tileMapPosition(Vec2 position) {
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return Vec2(x, y);
}

#endif // !_Map2D_H_
