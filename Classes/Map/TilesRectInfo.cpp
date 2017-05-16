#include"TilesRectInfo.h"

TilesRectInfo::TilesRectInfo() {
	tileMap = cocos2d::TMXTiledMap::create("Map/TilesInfo.tmx");
	TilessLayer = tileMap->getLayer("Tiles");

	auto sprite = TilessLayer->getTileAt(cocos2d::Vec2(7, 3));
	Stone_TilesRect = sprite->getTextureRect();

	sprite = TilessLayer->getTileAt(cocos2d::Vec2(1, 1));
	Corridor_TilesRect = sprite->getTextureRect();

	sprite = TilessLayer->getTileAt(cocos2d::Vec2(5, 3));
	Floor_TilesRect = sprite->getTextureRect();

	sprite = TilessLayer->getTileAt(cocos2d::Vec2(5, 5));
	Door_TilesRect = sprite->getTextureRect();

	sprite = TilessLayer->getTileAt(cocos2d::Vec2(5, 4));
	Unused_TilesRect = sprite->getTextureRect();

	sprite = TilessLayer->getTileAt(cocos2d::Vec2(5, 5));
	UpStairs_TilesRect = sprite->getTextureRect();

	sprite = TilessLayer->getTileAt(cocos2d::Vec2(5, 5));
	DownStairs_TilesRect = sprite->getTextureRect();
}

TilesRectInfo::TilesRectInfo(cocos2d::TMXTiledMap* tilemap) {
	tileMap = tilemap;
	TilessLayer = tileMap->getLayer("Tiles");
}