#include"DungeonGenerator.h"

MyMap DungeonGenerator::Generate() {
	auto rng = RngT(seed);

	auto myMap = MyMap(xSize, ySize, Tiles::Unused);

	MakeDungeon(myMap, rng);

	return myMap;
}

int DungeonGenerator::GetRandomInt(RngT& rng, int min, int max)const {
	return std::uniform_int_distribution<int>(min, max)(rng);
}

Direction DungeonGenerator::GetRandomDirection(RngT& rng)const {
	return Direction(std::uniform_int_distribution<int>(0, 3)(rng));
}

bool DungeonGenerator::MakeCorridor(MyMap& map, RngT& rng, int x, int y, int maxLength, Direction direction)const {
	auto length = GetRandomInt(rng, MAP_MIN_CORRIDOR, maxLength);

	auto xstart = x;
	auto ystart = y;
	auto xend = x;
	auto yend = y;

	if (direction == Direction::North)
		ystart = y - length;
	else if (direction == Direction::East)
		xend = x + length;
	else if (direction == Direction::South)
		yend = y + length;
	else if (direction == Direction::West)
		xstart = x - length;

	if (!map.IsXInBounds(xstart) || !map.IsXInBounds(xend) || !map.IsYInBounds(ystart) || !map.IsYInBounds(yend))
		return false;

	if (!map.IsAreaUnused(xstart, ystart, xend, yend))
		return false;

	map.setCells(xstart, ystart, xend, yend, Tiles::Corridor);

	return true;
}

bool DungeonGenerator::MakeRoom(MyMap& map, RngT& rng, int x, int y, int xMaxLength, int yMaxLength, Direction direction)const {
	auto xLength = GetRandomInt(rng, MAP_MIN_WIDE, xMaxLength);
	auto yLength = GetRandomInt(rng, MAP_MIN_LENGTH, yMaxLength);

	auto xstart = x;
	auto ystart = y;
	auto xend = x;
	auto yend = y;

	if (direction == Direction::North) {
		ystart = y - yLength;
		xstart = x - xLength / 2;
		xend = x + (xLength + 1) / 2;
	}
	else if (direction == Direction::East) {
		ystart = y - yLength / 2;
		yend = y + (yLength + 1) / 2;
		xend = x + xLength;
	}
	else if (direction == Direction::South) {
		yend = y + yLength;
		xstart = x - xLength / 2;
		xend = x + (xLength + 1) / 2;
	}
	else if (direction == Direction::West) {
		ystart = y - yLength / 2;
		yend = y + (yLength + 1) / 2;
		xstart = x - xLength;
	}

	if (!map.IsXInBounds(xstart) || !map.IsXInBounds(xend) || !map.IsYInBounds(ystart) || !map.IsYInBounds(yend))
		return false;
	if (!map.IsAreaUnused(xstart, ystart, xend, yend))
		return false;

	map.setCells(xstart, ystart, xend, yend, Tiles::DirtWall);
	map.setCells(xstart + 1, ystart + 1, xend - 1, yend - 1, Tiles::DirtFloor);

	return true;
}

bool DungeonGenerator::MakeFeature(MyMap& map, RngT& rng, int x, int y, int xmod, int ymod, Direction direction)const {
	auto chance = GetRandomInt(rng, 0, 100);

	if (chance <= chanceRoom) {
		if (MakeRoom(map, rng, x + xmod, y + ymod, MAP_MAX_WIDE, MAP_MAX_LENGTH, direction)) {
			map.setCell(x, y, Tiles::Door);

			map.setCell(x + xmod, y + ymod, Tiles::DirtFloor);

			return true;
		}
		return false;
	}
	else {
		if (MakeCorridor(map, rng, x + xmod, y + ymod, MAP_MAX_CORRIDOR, direction)) {
			map.setCell(x, y, Tiles::Door);
			return true;
		}
		return false;
	}
}

bool DungeonGenerator::MakeFeature(MyMap& map, RngT& rng)const {
	auto tries = 0;
	auto maxTries = xSize * ySize;

	for (; tries != maxTries; tries++) {
		int x = GetRandomInt(rng, 1, xSize - 2);
		int y = GetRandomInt(rng, 1, ySize - 2);

		if (map.getCell(x, y) != Tiles::DirtWall && map.getCell(x, y) != Tiles::Corridor)
			continue;

		if (map.IsAdjacent(x, y, Tiles::Door))
			continue;

		if (map.getCell(x, y + 1) == Tiles::DirtFloor || map.getCell(x, y + 1) == Tiles::Corridor) {
			if (MakeFeature(map, rng, x, y, 0, -1, Direction::North))
				return true;
		}
		else if (map.getCell(x - 1, y) == Tiles::DirtFloor || map.getCell(x - 1, y) == Tiles::Corridor) {
			if (MakeFeature(map, rng, x, y, 1, 0, Direction::East))
				return true;
		}
		else if (map.getCell(x, y - 1) == Tiles::DirtFloor || map.getCell(x, y - 1) == Tiles::Corridor) {
			if (MakeFeature(map, rng, x, y, 0, 1, Direction::South))
				return true;
		}
		else if (map.getCell(x + 1, y) == Tiles::DirtFloor || map.getCell(x + 1, y) == Tiles::Corridor) {
			if (MakeFeature(map, rng, x, y, -1, 0, Direction::West))
				return true;
		}
	}
	return false;
}

bool DungeonGenerator::MakeStairs(MyMap& map, RngT& rng, Tiles tiles)const {
	auto tries = 0;
	auto maxTries = 10000;

	for (; tries != maxTries; tries++) {
		int x = GetRandomInt(rng, 1, xSize - 2);
		int y = GetRandomInt(rng, 1, ySize - 2);

		if (map.getCell(x, y) == Tiles::DirtWall || map.getCell(x, y) == Tiles::Corridor || map.getCell(x, y) == Tiles::Unused)
			continue;

		if (map.IsAdjacent(x, y, Tiles::Door))
			continue;
		if (map.IsAdjacent(x, y, Tiles::Unused))
			continue;
		if (map.IsAdjacent(x, y, Tiles::DirtWall))
			continue;

		map.setCell(x, y, tiles);

		return true;
	}
	return false;
}

bool DungeonGenerator::MakeDungeon(MyMap& map, RngT& rng)const {
	MakeRoom(map, rng, xSize / 2, ySize / 2, MAP_MAX_WIDE, MAP_MAX_LENGTH, GetRandomDirection(rng));

	for (auto features = 1; features != maxFeatures; features++) {
		if (!MakeFeature(map, rng)) {
			CCLOG("Unable to place more feature%d", features);
			break;
		}
	}

	if (!MakeStairs(map, rng, Tiles::UpStairs))
		CCLOG("Unable to place up stairs");

	if (!MakeStairs(map, rng, Tiles::DownStairs))

	return true;
}