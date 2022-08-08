#include<iostream>
#include<algorithm>
#include<malloc.h>
#include<assert.h>
using namespace std;
#define HEAP_MAXSIZE 500
#define FindParent(child)  (child & 1) == 0 ? ((child - 1) >> 1) : (child >> 1)

struct Heap {
	int* data;
	int size;
	int capacity;
};
// 假设是大顶堆
void init(Heap* heap) {
	heap->data = new int[HEAP_MAXSIZE];
	if (heap->data == NULL) {
		assert(0);
		return;
	}
	heap->size = 0;
	heap->capacity = HEAP_MAXSIZE;
}
// 扩容
void resize(Heap* heap) {
	assert(heap);
	int* newData = new int[heap->capacity * 2];
	if (newData == NULL) {
		assert(0);
		return;
	}
	for (int i = 0; i < heap->size; i++) {
		newData[i] = heap->data[i];
	}
	heap->capacity *= 2;
	delete[] heap->data;

	heap->data = newData;
}
// 插入时用于调整
void AdjustUp(Heap* heap, int parent) {
	assert(heap);
	int child = parent;
	parent = FindParent(child);
	while (child > 0) {
		// 如果父节点小于子节点 就交换
		if (heap->data[parent] < heap->data[child]) {
			swap(heap->data[parent], heap->data[child]);
		}
		else return;
		// 向上调整
		child = parent;
		parent = FindParent(child);
	}

}
// 删除、排序时用于调整
void AdjustDown(Heap* heap, int parent) {
	assert(heap);
	int child = (parent << 1) + 1;
	while (child < heap->size) {
		// 找到孩子中较大的一个
		if (child + 1 < heap->size && heap->data[child] < heap->data[child + 1]) {
			child += 1;
		}
		// 如果父节点小于最大的子节点 就交换
		if (heap->data[parent] < heap->data[child]) {
			swap(heap->data[parent], heap->data[child]);
		}
		else return;
		// 向下调整
		parent = child;
		child = (parent << 1) + 1;
	}
}
void insert(Heap* heap, int data) {
	assert(heap);
	// 容量满了 先扩容
	if (heap->size >= heap->capacity)
		resize(heap);

	heap->data[heap->size] = data;
	AdjustUp(heap, heap->size);
	heap->size += 1;
}
void Delete(Heap* heap) {
	assert(heap);
	if (heap->size == 0) {
		assert(0);
		return;
	}
	heap->size -= 1;
	swap(heap->data[0], heap->data[heap->size]);
	AdjustDown(heap, 0);
}
void HeapSort(Heap* heap) {
	assert(heap);
	int size = heap->size;
	for (int i = 0; i < size - 1; i++) {
		swap(heap->data[0], heap->data[size - i - 1]);
		// 此处heap->size需要减一因为随后的AdjustDown需要调整的是大小为heap->size - 1的堆
		heap->size--;
		AdjustDown(heap, 0);
	}
	// 排序完再改回来
	heap->size = size;
}
int main() {
	Heap heap;
	init(&heap);
	insert(&heap, 1);
	insert(&heap, 2);
	insert(&heap, 3);
	insert(&heap, 4);
	insert(&heap, 5);
	insert(&heap, 15);
	insert(&heap, 56);
	insert(&heap, 55);
	insert(&heap, 58);
	Delete(&heap);
	for (int i = 0; i < heap.size; i++) {
		cout << heap.data[i] << ' ';
	}
	putchar(10);

	HeapSort(&heap);

	putchar(10);
	for (int i = 0; i < heap.size; i++) {
		cout << heap.data[i] << ' ';
	}

	return 0;
}