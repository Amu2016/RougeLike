#include"AStar.h"
#include"MyTileMap.h"

AStar::AStar() {

	OpenList = new BinaryHeap(2000);
	CloseList = new BinaryHeap(2000);

	auto mapData = MyTileMap::getInstance()->getMapdata();
	auto mapSize = MyTileMap::getInstance()->getMapSize();

	for (int y = 0; y != mapSize.height; y++) {
		for (int x = 0; x != mapSize.width; x++) {
			mapNode[y][x].Pos_X = y;
			mapNode[y][x].Pos_Y = x;
			mapNode[y][x].father = nullptr;
			switch (mapData[x + mapSize.width * y]) {
			case Tiles::Unused:
				mapNode[y][x].flag = WALL;
				break;
			case Tiles::DirtWall:
				mapNode[y][x].flag = WALL;
				break;
			case Tiles::DirtFloor:
				mapNode[y][x].flag = VIABLE;
				break;
			case Tiles::Corridor:
				mapNode[y][x].flag = VIABLE;
				break;
			case Tiles::Door:
				mapNode[y][x].flag = VIABLE;
				break;
			case Tiles::UpStairs:
				mapNode[y][x].flag = VIABLE;
				break;
			case Tiles::DownStairs:
				mapNode[y][x].flag = VIABLE;
				break;
			default:
				break;
			}
		}
	}

}

void AStar::setTraget(Vec2 startPos, Vec2 tragetPos) {
	mapNode[(int)startPos.y][(int)startPos.x].flag = STARTNODE;
	mapNode[(int)tragetPos.y][(int)tragetPos.x].flag = TRAGETNODE;
	Start_X = (int)startPos.y;
	Start_Y = (int)startPos.x;
	Traget_X = (int)tragetPos.y;
	Traget_Y = (int)tragetPos.x;
}

bool AStar::FindPath() {

	OpenList->insert(mapNode[Start_X][Start_Y]);
	
	if (OpenList->isEmpty()) {
		CCLOG("First　node  FindPath flase");
		return false;
	}

	while (true) {
		if (OpenList->isEmpty()) {
			CCLOG("FindPath flase");
			return false;
		}
		MapNode* node = OpenList->findMin();
		int dx, dy;
		//AddToCloseList(*node);
		if (node->flag == INOPEN)
			node->flag = INCLOSE;
		OpenList->deleteMin();
		CloseList->insert(*node);

		//OpenList->printHeap();

		if (HasWall(node->Pos_X, node->Pos_Y)) {
			// 只遍历 <上下左右> 四个方向
			for (int i = 1; i < 9; i += 2) {
				dx = node->Pos_X + Dirs[i][0];
				dy = node->Pos_Y + Dirs[i][1];

				if (dx < 0 || dy < 0 || dx >= LENGTH || dy >= WIDE)
					continue;

				AddToOpenList(node, mapNode[dx][dy]);

				if (mapNode[dx][dy].flag == TRAGETNODE)
					break;
			}
		}
		else {
			//遍历 八个方向
			for (int i = 0; i < 8; i++) {
				dx = node->Pos_X + Dir[i][0];
				dy = node->Pos_Y + Dir[i][1];
				if (dx < 0 || dy < 0 || dx >= LENGTH || dy >= WIDE)
					continue;
				AddToOpenList(node, mapNode[dx][dy]);

				if (mapNode[dx][dy].flag == TRAGETNODE)
					break;
			}
		}

		if (mapNode[dx][dy].flag == TRAGETNODE)
			break;
	}

	MapNode* node = &(mapNode[Traget_X][Traget_Y]);

	//while ((node->father->flag != STARTNODE)) {
	//	node = node->father;
	//	listPath.push_front(Vec2(node->Pos_Y, node->Pos_X));
	//}

	while ((node->flag != STARTNODE)) {
		listPath.push_front(Vec2(node->Pos_Y, node->Pos_X));

		if (node != findNextNode(node, Vec2(1, 0))) {
			node = findNextNode(node, Vec2(1, 0));
			continue;
		}
		if (node != findNextNode(node, Vec2(1, 1))) {
			node = findNextNode(node, Vec2(1, 1));
			continue;
		}
		if (node != findNextNode(node, Vec2(0, 1))) {
			node = findNextNode(node, Vec2(0, 1));
			continue;
		}
		if (node != findNextNode(node, Vec2(1, -1))) {
			node = findNextNode(node, Vec2(1, -1));
			continue;
		}
		if (node != findNextNode(node, Vec2(0, -1))) {
			node = findNextNode(node, Vec2(0, -1));
			continue;
		}
		if (node != findNextNode(node, Vec2(-1, -1))) {
			node = findNextNode(node, Vec2(-1, -1));
			continue;
		}
		if (node != findNextNode(node, Vec2(-1, 0))) {
			node = findNextNode(node, Vec2(-1, 0));
			continue;
		}
		if (node != findNextNode(node, Vec2(-1, 1))) {
			node = findNextNode(node, Vec2(-1, 1));
			continue;
		}
		node = node->father;
	}


	CCLOG("FindPath true%d", listPath.size());
	return true;
}

MapNode* AStar::findNextNode(MapNode* node, Vec2 dir) {
	if (node->flag == STARTNODE)
		return node;
	if (node->Pos_X + dir.x == node->father->Pos_X && node->Pos_Y + dir.y == node->father->Pos_Y) {
		MapNode* nodeNext = findNextNode(node->father, dir);
		if (nodeNext == node)
			return node;
		else
			return nodeNext;
	}
	return node;
}

void AStar::AddToOpenList(MapNode* father, MapNode& node) {
	if (node.flag == WALL || node.flag == INCLOSE || node.flag == STARTNODE)
		return;
	if (node.flag == TRAGETNODE) {
		node.father = father;
		return;
	}
	if (node.flag == INOPEN) {
		//return;
		size_t tempG = 0, tempF = 0;
		if (node.Pos_X != father->Pos_X && node.Pos_Y != father->Pos_Y) {
			tempG = father->Val_G + D2;
			tempF = tempG + node.Val_H;
		}
		else {
			tempG = father->Val_G + D;
			tempF = tempG + node.Val_H;
		}
		if (node.Val_G > tempG) {
			node.Val_G = tempG;
			node.Val_F = tempF;
			node.father = father;
			OpenList->decreaseVal(node.Key);
			//OpenList->printHeap();
		}
		return;
	}
	if (node.flag == VIABLE) {
		node.flag = INOPEN;
		if (node.Pos_X != father->Pos_X&&node.Pos_Y != father->Pos_Y) {
			node.Val_G = father->Val_G + D2;
			node.Val_H = Manhattan(node.Pos_X, node.Pos_Y);
			node.Val_F = node.Val_G + node.Val_H;
			node.father = father;
			OpenList->insert(node);
			//OpenList->printHeap();
			return;
		}
		else {
			node.Val_G = father->Val_G + D;
			node.Val_H = Manhattan(node.Pos_X, node.Pos_Y);
			node.Val_F = node.Val_G + node.Val_H;
			node.father = father;
			OpenList->insert(node);
			//OpenList->printHeap();
			return;
		}
	}
}

void AStar::AddToCloseList(MapNode& node) {
	node.flag = INCLOSE;
	OpenList->deleteMin();
	CloseList->insert(node);
}

bool AStar::HasWall(size_t x, size_t y) {
	for (int i = 1; i < 9; i += 2) {
		int tempX = x + Dirs[i][0];
		int tempY = y + Dirs[i][1];
		if (tempX < 0 || tempY < 0 || tempX >= LENGTH || tempY >= WIDE)
			continue;

		if (mapNode[tempX][tempY].flag == WALL)
			return true;
	}
	return false;
}

size_t AStar::Manhattan(const size_t x, const size_t y)const {
	return D*(MAX(x, Traget_X) - MIN(x, Traget_X) + MAX(y, Traget_Y) - MIN(y, Traget_Y));
}

size_t AStar::Chebyshev(const size_t x, const size_t y)const {
	size_t dx = MAX(x, Traget_X) - (MIN(x, Traget_X));
	size_t dy = MAX(y, Traget_Y) - (MIN(y, Traget_Y));
	return D*(dx + dy) + (D2 - D)*MIN(dx, dy);
}