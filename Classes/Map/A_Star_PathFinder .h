#pragma once
#ifndef A_Star_PathFinder_H
#define A_Star_PathFinder_H


#include"stdafx.h"
#include"NodeList.h"
#include<math.h>

class AStarPathFinder {
public:
	AStarPathFinder() {};
	AStarPathFinder(const char map[][WIDE]);
	virtual ~AStarPathFinder() {};
public:
	void AddToOpenList(MapNode* father, MapNode& node);
	void AddToCLoseList(MapNode& node);
	unsigned int Manhattan(const unsigned int x,const unsigned int y);			//曼华顿距离
	unsigned int Chebyshev(const unsigned int x, const unsigned int y);			//对角线距离
	void FindPath();
private:
	NodeList* openList;
	NodeList* closeList;
	MapNode mapNode[LENGTH][WIDE];//
	char map[LENGTH][WIDE];
	unsigned int Star_X, Star_Y, Traget_X, Traget_Y;
};

AStarPathFinder::AStarPathFinder(const char map[][WIDE]) {

	openList = new NodeList;
	closeList = new NodeList;

	for (int i = 0; i < LENGTH; i++) {
		for (int j = 0; j < WIDE; j++) {
			this->map[i][j] = map[i][j];

			mapNode[i][j].Pos_X = i;
			mapNode[i][j].Pos_Y = j;
			mapNode[i][j].father = nullptr;
			switch (map[i][j])
			{
			case '.':
				mapNode[i][j].flag = VIABLE;		//节点属性
				break;
			case 'x':
				mapNode[i][j].flag = WALL;			//节点属性
				break;
			case 's':
				mapNode[i][j].flag = STARTNODE;	//节点属性
				Star_X = i;
				Star_Y = j;
				break;
			case 'd':
				mapNode[i][j].flag = TRAGETNODE;	//节点属性
				Traget_X = i;
				Traget_Y = j;
				break;
			default:
				break;
			}
		}
	}
}

void AStarPathFinder::AddToOpenList(MapNode* father, MapNode& node) {
	if (node.flag == WALL || node.flag == INCLOSE || node.flag == STARTNODE)	//当节点 为 墙  或者  在closelist中  或者在openlist
		return;																	//或者 是初始节点时

	if (node.flag == TRAGETNODE) {		//当 节点为 目标节点时
		node.father = father;
		return;
	}

	if (node.flag == INOPEN) {			//当节点在 openlist中时
		//return;
		unsigned int TempG = 0, TempF = 0;
		if (node.Pos_X != father->Pos_X && node.Pos_Y != father->Pos_Y) {
			TempG = father->Val_G + D2;
			TempF = TempG + node.Val_H;
		}
		else {
			TempG = father->Val_G + D;
			TempF = TempG + node.Val_H;
		}
		if (node.Val_G > TempG) {
			node.Val_G = TempG;
			node.Val_F = TempF;
			node.father = father;
			openList->Delete(node);	//删除node后重新插入使之有序
			openList->Insert(node);
		}
		return;
	}
	if (node.flag == VIABLE) {		//当节点为空地  且不在openlist 或者 closelist中
		node.flag = INOPEN;
		if (node.Pos_X != father->Pos_X&&node.Pos_Y != father->Pos_Y) {  //当节点在父节点的对角线位置时
			node.Val_G = father->Val_G + D2;
			node.Val_H = Manhattan(node.Pos_X, node.Pos_Y);
			node.Val_F = node.Val_G + node.Val_H;
			node.father = father;
			openList->Insert(node);
			return;
		}
		else {															//当节点在父节点的上下左右时
			node.Val_G = father->Val_G + D;
			node.Val_H = Manhattan(node.Pos_X, node.Pos_Y);
			node.Val_F = node.Val_G + node.Val_H;
			node.father = father;
			openList->Insert(node);
			return;
		}
	}
}

void AStarPathFinder::AddToCLoseList(MapNode& node) {
	if (node.flag == INOPEN)
		node.flag = INCLOSE;
	openList->Delete(node);
	closeList->Insert(node);
}

unsigned int AStarPathFinder::Manhattan(const unsigned int x, const unsigned int y) {//曼华顿距离
	return D*(MAX(x, Traget_X) - MIN(x, Traget_X) + MAX(y, Traget_Y) - MIN(y, Traget_Y));
}

unsigned int AStarPathFinder::Chebyshev(const unsigned int x, const unsigned int y) {//对角线距离
	unsigned int dx = MAX(x, Traget_X) - (MIN(x, Traget_X));
	unsigned int dy = MAX(y, Traget_Y) - (MIN(y, Traget_Y));
	return D*(dx + dy) + (D2 - D)*MIN(dx, dy);
}

void AStarPathFinder::FindPath() {
	clock_t start = clock();
	openList->Insert(mapNode[Star_X][Star_Y]);	//起始点加入Open列表中
	while (true) {
		if (openList->IsNULL()) {			//当openlist 为空时  说明遍历地图后没右路径可以到达终点
			std::cout << " NO PATH  !!!!!";
			return;
		}
		MapNode* node = openList->FirstNode();	//获得openlist中的 F值 最小节点node
		int dx, dy;
		//openList->PrintList();			//打印openlist 的F值
		AddToCLoseList(*node);				//把openlist中的 F值 最小节点node 添加到closelist中 并从openlist中删除
		for (int i = 0; i < 8; i++) {		//遍历节点node 八个方向的节点  并添加到openlist中
			dx = node->Pos_X + Dir[i][0];
			dy = node->Pos_Y + Dir[i][1];
			if (dx < 0 || dy < 0 || dx >= LENGTH || dy >= WIDE)
				continue;
			AddToOpenList(node, mapNode[dx][dy]);
			if (mapNode[dx][dy].flag == TRAGETNODE)  //连续两次跳出  while  循环
				break;
		}
		if (mapNode[dx][dy].flag == TRAGETNODE)
			break;
	}

	clock_t end = clock();
	std::cout << "AStar_1 Run times :" << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
	
	MapNode* node = &(mapNode[Traget_X][Traget_Y]);
	while (node->father->flag != STARTNODE) {    // 标记路径
		node = node->father;
		map[node->Pos_X][node->Pos_Y] = '@';
	}
	for (int i = 0; i < LENGTH; i++) {			//打印出右  最优路径标记 的地图
		for (int j = 0; j < WIDE; j++)
			std::cout << map[i][j];
		std::cout << "\n";
	}
}

#endif A_Star_PathFinder_H