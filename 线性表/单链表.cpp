#include<stdio.h>
#include<stdlib.h>

// 节点定义
typedef struct ListNode {
	int data;
	struct ListNode* next;
}Node, *NodePtr;
// 单链表定义
struct List {
	Node* head;
	Node* tail;
	int length;
};


// 初始化头结点
bool init(List& L) {
	// 头尾指针开始在一起
	L.tail = L.head = (NodePtr)malloc(sizeof(Node));

	if (L.head == NULL) exit(-1);

	L.head->data = 0;
	L.head->next = NULL;
	L.tail->data = 0;
	L.tail->next = NULL;
	L.length = 0;
	return true;
}

// 插入操作 插入到指定位置的后一个位置
bool insert(List& L, int data, int pos) {
	// 位置不合法退出程序
	if (pos < 0 || pos > L.length) exit(-1);
	// 遍历链表到合适位置
	NodePtr cur = L.head, temp = NULL, newNode = NULL;
	int cnt = 0;
	while (cnt != pos) cur = cur->next, cnt++;
	// 记录下当前节点的下一个节点
	temp = cur->next;

	newNode = (NodePtr)malloc(sizeof(Node));
	if (newNode == NULL) exit(-1);
	
	// 桥接新节点
	newNode->data = data;
	newNode->next = temp;
	cur->next = newNode;
	// 如果插入节点是在末尾插入的 尾指针要改变
	if(newNode->next == NULL) L.tail = newNode;
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
		while (cur->next != NULL) {
			cur = cur->next;
			printf("%d ", cur->data);
		}
	}
}
int main() {
	List L;
	// 手动初始化
	init(L);
	insert(L, 1, L.length);
	insert(L, 2, L.length);
	insert(L, 3, L.length);
	insert(L, 4, L.length);
	insert(L, 5, L.length);
	erase(L, 4);
	travel(L);
	return 0;
}