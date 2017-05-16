#pragma once
#ifndef A_BinaryHeap_H
#define A_BinaryHeap_H

#include"stdafx.h"
#include<vector>
class BinaryHeap {
public:
	explicit BinaryHeap(int capacity = 100) :
		currentSize(0)
	{ 
		heap.resize(capacity + 1);
	}
	explicit BinaryHeap(const std::vector<MapNode*>& items) :
		heap(items.size() + 10), 
		currentSize(items.size()) 
	{
		for (size_t i = 0; i < items.size(); i++)
			heap[i + 1] = items[i];
		buildHeap();
	}
	~BinaryHeap() {};

	void buildHeap();

	bool isEmpty()const {
		if (currentSize > 0) return false;
		return true;
	}
	MapNode* findMin()const { return heap[1]; }

	void insert(MapNode& node);
	void deleteMin();
	void deleteMin(MapNode& minNode);
	void decreaseVal(size_t key);
	void printHeap();

private:
	size_t currentSize;
	std::vector<MapNode*> heap;

	void percolateDown(size_t hold);
};



#endif A_BinaryHeap_H