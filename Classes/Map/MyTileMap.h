#pragma once
#ifndef _MyTileMap_H_
#define _MyTileMap_H_

#include"DungeonGenerator.h"
#include"cocos2d.h"

class MyTileMap {
public:
	static MyTileMap* getInstance() {
		if (!myTileMap) {
			myTileMap = new MyTileMap();
		}
		return myTileMap;
	}

	TMXTiledMap* getMap() {
		if (!tileMap) {
			DungeonGenerator generator = DungeonGenerator(50, 50);
			map = generator.Generate();
			map.DrowMap();
			tileMap = map.getTilesMap();
			mapData = map.getMapData();
			tilesCollideKeys = map.getTilesCollideKeys();
			collideKeys = map.getCollideKeys();
			collider = map.getCollidePos();
		}
		return tileMap;
	}

	TMXTiledMap* getNewMap() {
		DungeonGenerator generator = DungeonGenerator(50, 50);
		map = generator.Generate();
		map.DrowMap();
		tileMap = map.getTilesMap();
		mapData = map.getMapData();
		tilesCollideKeys = map.getTilesCollideKeys();
		collideKeys = map.getCollideKeys();
		collider = map.getCollidePos();

		return tileMap;
	}

	Size getMapLayerSize() {
		return Size(tileMap->getMapSize().width*tileMap->getTileSize().width,
			tileMap->getMapSize().height*tileMap->getTileSize().height);
	}

	Size getMapSize() {
		return tileMap->getMapSize();
	}

	Size getTileSize() {
		return Size(tileMap->getTileSize().width,
			tileMap->getTileSize().height);
	}

	std::vector<Tiles>& getMapdata() {
		return mapData;
	}

	std::map<Vec2, bool>& getTilesCollideKeys() {
		return tilesCollideKeys;
	}

	std::map<Vec2, bool>& getCollideKeys() {
		return collideKeys;
	}

	std::vector<Collide>& getCollidePos() {
		return collider;
	}

	cocos2d::Vec2 getHeroPosition() {
		return map.getHeroPosition();
	}


private:
	static MyTileMap* myTileMap;

	TMXTiledMap* tileMap;
	
	MyMap map;

	std::vector<Tiles> mapData;
	std::map<Vec2, bool> tilesCollideKeys;
	std::map<Vec2, bool> collideKeys;
	std::vector<Collide> collider;
	cocos2d::Vec2 heroPosition;

	MyTileMap() :
		tileMap(nullptr) {}
};


#endif // !_MyTileMap_H_
