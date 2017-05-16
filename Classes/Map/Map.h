#pragma once
#ifndef _Map_H_
#define _Map_H_

#include<iostream>
#include<vector>
#include"cocos2d.h"
#include"TilesRectInfo.h"
#include"stdafx.h"


class MyMap {
public:
	MyMap() : xSize(0), ySize(0), data() {
		init();
	}
	MyMap(int x, int y, Tiles value = Tiles::Unused) :
		xSize(x), ySize(y),
		data(x*y, value) {
		init();
	}

	void init();
	cocos2d::TMXTiledMap* getTilesMap();

	Size getMapSize();
	std::vector<Tiles> getMapData() {
		return data;
	}

	std::map<Vec2, bool> getTilesCollideKeys(){
		return tilesCollideKeys;
	}
	std::map<Vec2, bool>& getCollideKeys() {
		return collideKeys;
	}
	std::vector<Collide>& getCollidePos() {
		return collider;
	}

	cocos2d::Vec2 getHeroPosition() {
		return heroPosition;
	}


	void setCell(int x, int y, Tiles celltype);
	Tiles getCell(int x, int y) const;
	void setCells(int xStart, int yStart, int xEnd, int yEnd, Tiles celltype);

	bool IsXInBounds(int x)const;
	bool IsYInBounds(int y)const;

	bool IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd)const;

	bool IsAdjacent(int x, int y, Tiles Tiles)const;

	void DrowMap();

	inline Vec2 tileMapPosition(Vec2 position);

	inline Vec2 toWorldPosition(Vec2 position);

private:
	int xSize, ySize;
	std::vector<Tiles> data;
	std::map<Vec2, bool> tilesCollideKeys;
	std::map<Vec2, bool> collideKeys;
	std::vector<Collide> collider;

	cocos2d::TMXTiledMap* tmxMap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* collide;
	cocos2d::Vec2 heroPosition;



	TilesRectInfo tilesRectInfo;
};

#endif // !_Map_H_
