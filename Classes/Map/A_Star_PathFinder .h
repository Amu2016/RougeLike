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
	unsigned int Manhattan(const unsigned int x,const unsigned int y);			//�����پ���
	unsigned int Chebyshev(const unsigned int x, const unsigned int y);			//�Խ��߾���
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
				mapNode[i][j].flag = VIABLE;		//�ڵ�����
				break;
			case 'x':
				mapNode[i][j].flag = WALL;			//�ڵ�����
				break;
			case 's':
				mapNode[i][j].flag = STARTNODE;	//�ڵ�����
				Star_X = i;
				Star_Y = j;
				break;
			case 'd':
				mapNode[i][j].flag = TRAGETNODE;	//�ڵ�����
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
	if (node.flag == WALL || node.flag == INCLOSE || node.flag == STARTNODE)	//���ڵ� Ϊ ǽ  ����  ��closelist��  ������openlist
		return;																	//���� �ǳ�ʼ�ڵ�ʱ

	if (node.flag == TRAGETNODE) {		//�� �ڵ�Ϊ Ŀ��ڵ�ʱ
		node.father = father;
		return;
	}

	if (node.flag == INOPEN) {			//���ڵ��� openlist��ʱ
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
			openList->Delete(node);	//ɾ��node�����²���ʹ֮����
			openList->Insert(node);
		}
		return;
	}
	if (node.flag == VIABLE) {		//���ڵ�Ϊ�յ�  �Ҳ���openlist ���� closelist��
		node.flag = INOPEN;
		if (node.Pos_X != father->Pos_X&&node.Pos_Y != father->Pos_Y) {  //���ڵ��ڸ��ڵ�ĶԽ���λ��ʱ
			node.Val_G = father->Val_G + D2;
			node.Val_H = Manhattan(node.Pos_X, node.Pos_Y);
			node.Val_F = node.Val_G + node.Val_H;
			node.father = father;
			openList->Insert(node);
			return;
		}
		else {															//���ڵ��ڸ��ڵ����������ʱ
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

unsigned int AStarPathFinder::Manhattan(const unsigned int x, const unsigned int y) {//�����پ���
	return D*(MAX(x, Traget_X) - MIN(x, Traget_X) + MAX(y, Traget_Y) - MIN(y, Traget_Y));
}

unsigned int AStarPathFinder::Chebyshev(const unsigned int x, const unsigned int y) {//�Խ��߾���
	unsigned int dx = MAX(x, Traget_X) - (MIN(x, Traget_X));
	unsigned int dy = MAX(y, Traget_Y) - (MIN(y, Traget_Y));
	return D*(dx + dy) + (D2 - D)*MIN(dx, dy);
}

void AStarPathFinder::FindPath() {
	clock_t start = clock();
	openList->Insert(mapNode[Star_X][Star_Y]);	//��ʼ�����Open�б���
	while (true) {
		if (openList->IsNULL()) {			//��openlist Ϊ��ʱ  ˵��������ͼ��û��·�����Ե����յ�
			std::cout << " NO PATH  !!!!!";
			return;
		}
		MapNode* node = openList->FirstNode();	//���openlist�е� Fֵ ��С�ڵ�node
		int dx, dy;
		//openList->PrintList();			//��ӡopenlist ��Fֵ
		AddToCLoseList(*node);				//��openlist�е� Fֵ ��С�ڵ�node ��ӵ�closelist�� ����openlist��ɾ��
		for (int i = 0; i < 8; i++) {		//�����ڵ�node �˸�����Ľڵ�  ����ӵ�openlist��
			dx = node->Pos_X + Dir[i][0];
			dy = node->Pos_Y + Dir[i][1];
			if (dx < 0 || dy < 0 || dx >= LENGTH || dy >= WIDE)
				continue;
			AddToOpenList(node, mapNode[dx][dy]);
			if (mapNode[dx][dy].flag == TRAGETNODE)  //������������  while  ѭ��
				break;
		}
		if (mapNode[dx][dy].flag == TRAGETNODE)
			break;
	}

	clock_t end = clock();
	std::cout << "AStar_1 Run times :" << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
	
	MapNode* node = &(mapNode[Traget_X][Traget_Y]);
	while (node->father->flag != STARTNODE) {    // ���·��
		node = node->father;
		map[node->Pos_X][node->Pos_Y] = '@';
	}
	for (int i = 0; i < LENGTH; i++) {			//��ӡ����  ����·����� �ĵ�ͼ
		for (int j = 0; j < WIDE; j++)
			std::cout << map[i][j];
		std::cout << "\n";
	}
}

#endif A_Star_PathFinder_H