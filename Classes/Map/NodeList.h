#pragma once
#ifndef NodeList_H
#define NodeList_H

#include"stdafx.h"

struct List {
	MapNode* node;
	List* next;
};

class NodeList {
public:
	NodeList() {
		first = new List;
		first->next = nullptr;
	};
	virtual ~NodeList() {};
public:
	void PrintList();
	bool IsNULL() {				//列表是否为空
		if (first->next == nullptr)
			return true;
		return false;
	};
	int getLength();			//列表长度
	void Insert(MapNode& node);
	void Delete(MapNode& node);
	MapNode* FirstNode() {
		return first->next->node;
	};
private:
	List* first;
};

#endif NodeList_H