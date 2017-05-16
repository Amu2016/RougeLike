#pragma once
#ifndef AStar_H
#define AStar_H

#include"stdafx.h"
#include<math.h>
#include"A_BirnaryHeap.h"
#include"NodeList.h"

class AStar {
public:
	AStar();
	~AStar() {
	
	}

	void setTraget(Vec2 startPos, Vec2 tragetPos);

	bool FindPath();

	std::list<Vec2> getPathList() { return listPath; }

private:
	BinaryHeap* OpenList;
	BinaryHeap* CloseList;
	MapNode mapNode[LENGTH][WIDE];
	char Map[LENGTH][WIDE];

	std::list<Vec2> listPath;

	size_t Start_X, Start_Y, Traget_X, Traget_Y;

	MapNode* findNextNode(MapNode* node,Vec2 dir);

	void AddToOpenList(MapNode* father, MapNode& node);
	void AddToCloseList(MapNode& node);
	bool HasWall(size_t x,size_t y);
	size_t Manhattan(const size_t x, const size_t y)const;
	size_t Chebyshev(const size_t x, const size_t y)const;
};



#endif AStar_H