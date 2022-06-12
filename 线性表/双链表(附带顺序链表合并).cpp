#include<stdio.h>
#include<stdlib.h>

// 节点定义
typedef struct ListNode {
	int data;
	struct ListNode* next;
	struct ListNode* pre;
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
	// 初始化头尾指针
	L.head->data = 0;
	L.head->next = NULL;
	L.head->pre = NULL;
	L.tail->data = 0;
	L.tail->next = NULL;
	L.tail->pre = NULL;
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
	
	// 桥接新节点 相比单链表需要同时更新pre指针
	newNode->data = data;
	newNode->next = temp;
	newNode->pre = cur;
	if(temp != NULL) temp->pre = newNode;
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
	temp->next->pre = cur;
	// 释放空间
	free(temp);
	return true;
}
// 正着遍历一遍 倒着遍历一遍
void travel(List L) {
	if (L.head != NULL) {
		NodePtr cur = L.head;
		while (cur->next != NULL) {
			cur = cur->next;
			printf("%d ", cur->data);
		}
		printf("\n");
		cur = L.tail;
		while (cur->pre != NULL) {
			printf("%d ", cur->data);
			cur = cur->pre;
		}
	}
}
// 合并两个顺序链表
void merge(List a, List b, List& c) {

	NodePtr pa = a.head, pb = b.head;

	while (pa->next != NULL && pb->next!= NULL) {
		// 先插小的
		if (pa->next->data < pb->next->data) {
			insert(c, pa->next->data, c.length);
			pa = pa->next;
		}
		else {
			insert(c, pb->next->data, c.length);
			pb = pb->next;
		}
	}
	while (pa->next != NULL) {
		insert(c, pa->next->data, c.length);
		pa = pa->next;
	}
	while (pb->next != NULL) {
		insert(c, pb->next->data, c.length);
		pb = pb->next;
	}
}
int main() {
	//List L;
	//// 手动初始化
	//init(L);
	//insert(L, 1, L.length);
	//insert(L, 2, L.length);
	//insert(L, 3, L.length);
	//insert(L, 4, L.length);
	//insert(L, 5, L.length);
	//erase(L, 4);
	//travel(L);
	// 合并两个顺序链表
	List a, b, c;
	init(a), init(b), init(c);
	insert(a, 0, a.length), insert(a, 2, a.length), insert(a, 4, a.length), insert(a, 6, a.length);
	insert(b, 1, b.length), insert(b, 3, b.length), insert(b, 5, b.length), insert(b, 7, b.length);
	merge(a, b, c);

	//输出合并后的序列的 正序和倒序
	travel(c);
	return 0;
}