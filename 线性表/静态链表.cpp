#include<stdio.h>
#include<stdlib.h>
#define MAX_LIST_SIZE 50
typedef struct {
	int data;
	int next;
}List;
void init(List L[]) {
	for (int i = 0; i < MAX_LIST_SIZE; i++) {
		L[i].data = L[i].next = -1;
	}
}
bool insert(List L[], int data) {
	int i = 1;
	// 找到一个空闲位置
	while (L[i].data != -1) i++;

	if (i >= MAX_LIST_SIZE) exit(-1);

	// 找到先前的尾巴
	int j = 0;
	while (L[j].next != -1) j = L[j].next;

	L[j].next = i;
	L[i].data = data;
}
// 删除第i个元素
bool erase(List L[], int pos) {
	if (pos <= 0 || pos >= MAX_LIST_SIZE) exit(-1);
	
	// 找到待删除位置的前一个元素
	int i = 0, cnt = 0;
	while (cnt + 1 != pos && i != -1) i = L[i].next, cnt++;
	// 要删除的位置大于当前存放的个数
	if (i == -1) exit(-1);
	int index = L[i].next;
	L[i].next = L[L[i].next].next;
	L[index].data = -1;
	L[index].next = -1;
	return true;
}

void travel(List L[]) {
	int i = 0;
	while (L[i].next != -1) {
		i = L[i].next;
		printf("%d ", L[i].data);
	}
}

int main() {
	List L[MAX_LIST_SIZE];
	init(L);
	
	insert(L, 1);
	insert(L, 2);
	insert(L, 3);
	insert(L, 4);
	insert(L, 5);
	erase(L, 3);
	erase(L, 1);
	erase(L, 1);
	travel(L);

	return 0;
}