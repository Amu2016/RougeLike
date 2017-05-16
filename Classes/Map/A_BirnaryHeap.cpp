#include"A_BirnaryHeap.h"
int a = 0;

void BinaryHeap::buildHeap() {
	for (size_t i = currentSize / 2; i > 0; i--)
		percolateDown(i);
}

void BinaryHeap::insert(MapNode& node) {
	if (currentSize == heap.size() - 1)
		heap.resize(heap.size() * 2);

	size_t hole = ++currentSize;
	//std::cout << ++a <<":"<<currentSize << " ";

	//�˴�  <=  ��Ϊ�� ���²���ڵ�  ���ȱ����
	for (size_t father = 0; hole > 1 && heap[hole / 2]->Val_F > node.Val_F; hole = father) {
		father = hole / 2;
		heap[hole] = heap[father];
		heap[father]->Key = hole;
	}
	heap[hole] = &node;
	heap[hole]->Key = hole;
}

void BinaryHeap::deleteMin() {
	if (isEmpty())
		return;
	heap[1]->Key = 0;
	heap[1] = heap[currentSize--];
	heap[currentSize + 1] = nullptr;
	if (!isEmpty())
		percolateDown(1);
}

void BinaryHeap::deleteMin(MapNode& minNode) {
	if (isEmpty())
		return;
	heap[1]->Key = 0;
	minNode = *heap[1];
	heap[1] = heap[currentSize--];
	percolateDown(1);
}

void BinaryHeap::decreaseVal(size_t key) {
	MapNode* node = heap[key];

	size_t hole = key;

	//�˴� < ���� <=  ��Ϊ�� ���ϸ� �ڵ��ӳٱ����
	for (size_t father = 0; hole > 1 && heap[hole / 2]->Val_F > node->Val_F; hole = father) {
		father = hole / 2;
		heap[hole] = heap[father];
		heap[father]->Key = hole;
	}
	heap[hole] = node;
	heap[hole]->Key = hole;
}
	
void BinaryHeap::percolateDown(size_t hole) {
	size_t child;
	MapNode* tempNode = heap[hole];
	for (; hole * 2 <= currentSize; hole = child) {
		child = hole * 2;
		if (child != currentSize && heap[child]->Val_F > heap[child + 1]->Val_F)
			child++;
		if (heap[child]->Val_F < tempNode->Val_F) {
			heap[hole] = heap[child];
			heap[child]->Key = hole;
		}
		else
			break;
	}
	heap[hole] = tempNode;
	heap[hole]->Key = hole;
	//printHeap();
}

void BinaryHeap::printHeap() {
}