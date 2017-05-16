#pragma once
#ifndef _DungeonGenerator_H_
#define _DungeonGenerator_H_

#include"Map.h"
#include<random>
#include"stdafx.h"

class DungeonGenerator {
public:
	int seed;
	int xSize, ySize;
	int maxFeatures;
	int chanceRoom, chanceCorridor;

	DungeonGenerator() :
		seed(std::random_device()()),
		xSize(50), ySize(50),
		maxFeatures(100),
		chanceRoom(75), chanceCorridor(25) {}

	DungeonGenerator(int xsize, int ysize) :
		seed(std::random_device()()),
		xSize(xsize), ySize(ysize),
		maxFeatures(100),
		chanceRoom(75), chanceCorridor(25) {}

	MyMap Generate();

private:

	int GetRandomInt(RngT& rng, int min, int max)const;

	Direction GetRandomDirection(RngT& rng)const;

	bool MakeCorridor(MyMap& map, RngT& rng, int x, int y, int maxLength, Direction direction)const;

	bool MakeRoom(MyMap& map, RngT& rng, int x, int y, int xMaxLength, int yMaxLength, Direction direction)const;

	bool MakeFeature(MyMap& map, RngT& rng, int x, int y, int xmod, int ymod, Direction direction)const;

	bool MakeFeature(MyMap& map, RngT& rng)const;

	bool MakeStairs(MyMap& map, RngT& rng, Tiles tiles)const;

	bool MakeDungeon(MyMap& map, RngT& rng)const;
};

#endif // !_DungeonGenerator_H_
