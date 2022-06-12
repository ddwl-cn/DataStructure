#include<stdio.h>
#include<stdlib.h>

// 节点定义
typedef struct ListNode {
	int data;
	struct ListNode* next;
}Node, *NodePtr;
// 循环链表定义
struct List {
	Node* head;
	int length;
};


// 初始化头结点
bool init(List& L) {
	// 头尾指针开始在一起
	L.head = (NodePtr)malloc(sizeof(Node));

	if (L.head == NULL) exit(-1);

	L.head->data = 0;
	// 头结点开始指向自己
	L.head->next = L.head;
	L.length = 0;
	return true;
}

// 插入操作 插入到最后后一个位置
bool insert(List& L, int data) {
	
	// 遍历链表到合适位置
	NodePtr cur = L.head, newNode = NULL;
	while (cur->next != L.head) cur = cur->next;
	// 记录下当前节点的下一个节点

	newNode = (NodePtr)malloc(sizeof(Node));
	if (newNode == NULL) exit(-1);
	
	// 桥接新节点
	newNode->data = data;
	newNode->next = L.head;
	cur->next = newNode;
	L.length++;
	return true;
}
// 删除操作 删除指定位置的节点 (也可以改写成删除指定元素)
bool erase(List& L, int pos) {
	if (pos <= 0 || pos > L.length) exit(-1);

	NodePtr cur = L.head, temp = NULL;
	int cnt = 0;
	while (cnt + 1 != pos) cur = cur->next, cnt++;

	temp = cur->next;
	// 越过要删除的节点
	cur->next = temp->next;
	// 释放空间
	free(temp);
	return true;
}
void travel(List L) {
	if (L.head != NULL) {
		NodePtr cur = L.head;
		while (cur->next != L.head) {
			cur = cur->next;
			printf("%d ", cur->data);
		}
	}
}
int main() {
	List L;
	// 手动初始化
	init(L);
	insert(L, 1);
	insert(L, 2);
	insert(L, 3);
	insert(L, 4);
	insert(L, 5);
	erase(L, 4);
	travel(L);
	return 0;
}