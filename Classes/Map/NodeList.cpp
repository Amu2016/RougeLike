#include"NodeList.h"

void NodeList::PrintList() {
	List* listNode = first->next;
	while (listNode != nullptr) {
		listNode = listNode->next;
	}
}

int NodeList::getLength() {
	List* listNode = first->next;
	int count = 0;
	while (listNode != nullptr) {
		listNode = listNode->next;
		count++;
	}
	return count;
}

void NodeList::Insert(MapNode& node) {
	List* list = new List;
	list->node = &node;
	List* listNode = first;
	while (listNode->next != nullptr) {
		if (listNode->next == nullptr) {
			listNode->next = list;
			return;
		}
		if (listNode->next->node->Val_F > node.Val_F) {
			list->next = listNode->next;
			listNode->next = list;
			return;
		}
		listNode = listNode->next;
	}
	listNode->next = list;
	listNode->next->next = nullptr;
}

void NodeList::Delete(MapNode& node) {
	MapNode* n = &node;
	List* ptr = first;
	while (ptr->next != nullptr) {
		MapNode* n1 = this->FirstNode();
		if (ptr->next->node == &node) {
			List* list = ptr->next;
			ptr->next = list->next;
			delete list;
			return;
		}
		ptr = ptr->next;
	}
}