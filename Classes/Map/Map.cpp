#include"Map.h"

//USING_NS_CC;

void MyMap::init() {
	tmxMap = cocos2d::TMXTiledMap::create("Map/Map.tmx");
	background = tmxMap->getLayer("background");
	collide = tmxMap->getLayer("collide");
}

cocos2d::TMXTiledMap* MyMap::getTilesMap() {
	return tmxMap;
}

Size MyMap::getMapSize() {
	return Size(tmxMap->getMapSize().width*tmxMap->getTileSize().width,
		tmxMap->getMapSize().height*tmxMap->getTileSize().height);
}

void MyMap::setCell(int x, int y, Tiles celltype) {
	data[x + xSize * y] = celltype;
}

Tiles MyMap::getCell(int x, int y)const {
	return data[x + xSize * y];
}

void MyMap::setCells(int xStart, int yStart, int xEnd, int yEnd, Tiles celltype) {
	for (int y = yStart; y != yEnd + 1; y++)
		for (int x = xStart; x != xEnd + 1; x++)
			setCell(x, y, celltype);
}

bool MyMap::IsXInBounds(int x)const {
	return x >= 0 && x < xSize;
}

bool MyMap::IsYInBounds(int y)const {
	return y >= 0 && y < ySize;
}

bool MyMap::IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd)const {
	for (int y = yStart; y != yEnd + 1; y++)
		for (int x = xStart; x != xEnd + 1; x++)
			if (getCell(x, y) != Tiles::Unused)
				return false;
	return true;
}

bool MyMap::IsAdjacent(int x, int y, Tiles tiles)const {
	return
		getCell(x - 1, y) == tiles || getCell(x + 1, y) == tiles ||
		getCell(x, y - 1) == tiles || getCell(x, y - 1) == tiles;
}

void MyMap::DrowMap(){
	for (int y = 0; y != ySize; y++) {
		for (int x = 0; x != xSize; x++) {
			auto sprite = background->getTileAt(cocos2d::Vec2(x, y));
			switch (getCell(x, y))
			{
			case Tiles::Unused:
				sprite->setTextureRect(tilesRectInfo.getUnusedRect());
				tilesCollideKeys.insert(std::pair<Vec2,bool>(Vec2(x, y), true));

				collideKeys.insert(std::pair<Vec2, bool>(toWorldPosition(Vec2(x, y)), true));

				collider.push_back(Collide(toWorldPosition(Vec2(x, y)), false));
				break;
			case Tiles::DirtWall:
				sprite->setTextureRect(tilesRectInfo.getStoneTilesRect());
				tilesCollideKeys.insert(std::pair<Vec2, bool>(Vec2(x, y), true));

				collideKeys.insert(std::pair<Vec2, bool>(toWorldPosition(Vec2(x, y)), true));
				collider.push_back(Collide(toWorldPosition(Vec2(x, y)), false));
				break;
			case Tiles::DirtFloor:
				sprite->setTextureRect(tilesRectInfo.getFloorRect());
				tilesCollideKeys.insert(std::pair<Vec2, bool>(Vec2(x, y), false));

				collideKeys.insert(std::pair<Vec2, bool>(toWorldPosition(Vec2(x, y)), false));
				break;
			case Tiles::Corridor:
				sprite->setTextureRect(tilesRectInfo.getCorridorRect());
				tilesCollideKeys.insert(std::pair<Vec2, bool>(Vec2(x, y), false));

				collideKeys.insert(std::pair<Vec2, bool>(toWorldPosition(Vec2(x, y)), false));
				break;
			case Tiles::Door:
				sprite->setTextureRect(tilesRectInfo.getDoorRect());
				tilesCollideKeys.insert(std::pair<Vec2, bool>(Vec2(x, y), false));

				collideKeys.insert(std::pair<Vec2, bool>(toWorldPosition(Vec2(x, y)), false));
				break;
			case Tiles::UpStairs:
				heroPosition = cocos2d::Vec2(x, y);
				break;
			case Tiles::DownStairs:
				
				break;
			default:
				break;
			}
			if (x == 0 || y == 0 || x == xSize - 1 || y == ySize - 1) {
				sprite->setTextureRect(tilesRectInfo.getStoneTilesRect());
				tilesCollideKeys.insert(std::pair<Vec2, bool>(Vec2(x, y), true));

				collideKeys.insert(std::pair<Vec2, bool>(toWorldPosition(Vec2(x, y)), true));
				collider.push_back(Collide(toWorldPosition(Vec2(x, y)), false));
			}
			sprite->getTexture()->setAntiAliasTexParameters();
		}
		auto a = 1;
	}
}

inline Vec2 MyMap::tileMapPosition(Vec2 position) {
	int x = position.x / tmxMap->getTileSize().width;
	int y = ((tmxMap->getMapSize().height * tmxMap->getTileSize().height) - position.y) / tmxMap->getTileSize().height;
	return Vec2(x, y);
}

inline Vec2 MyMap::toWorldPosition(Vec2 position) {
	int x = position.x * tmxMap->getTileSize().width + tmxMap->getTileSize().width / 2;
	int y = tmxMap->getMapSize().height * tmxMap->getTileSize().height - position.y * tmxMap->getTileSize().height
		- tmxMap->getTileSize().height / 2;
	return Vec2(x, y);
}