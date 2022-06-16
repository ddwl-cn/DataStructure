#include<iostream>
#include<stack>
using namespace std;
/*
题目有时会要求使用非递归的方式进行二叉树的遍历
所以掌握非递归遍历是必要的
*/
typedef struct node {
	int data;
	node* lchild, * rchild;
}TreeNode, *Tree;
TreeNode* getNewNode(int data = 0) {
	TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
	t->lchild = t->rchild = NULL;
	t->data = data;
	return t;
}
// 非递归建树 按照左小右大建树
void build(Tree& tree, int data) {
	if (tree != NULL) {
		Tree p = tree, last = NULL;
		while (p != NULL) {
			last = p;

			if (p->data > data) p = p->lchild;
			else if (p->data < data) p = p->rchild;
			else return;
		}
		// 新的节点如果大于最后一个节点就放右子树 否则放左子树
		Tree newNode = getNewNode(data);

		if (last->data > data) 
			last->lchild = newNode;
		else 
			last->rchild = newNode;
	}
	else
		tree = getNewNode(data);
}
// 先序非递归
void PreOrder(Tree tree) {
	if (tree == NULL) return;
	// 使用栈来存放先前为完全访问的节点
	stack<TreeNode*> s;
	s.push(tree);
	while (!s.empty()) {
		// 访问栈顶元素
		tree = s.top();
		s.pop();
		printf("%d ", tree->data);
		// 应当优先将右孩子压入栈中 因为下一次取栈顶如果节点左孩子不为空应该是访问的左孩子
		// 右孩子不为空就入栈
		if (tree->rchild != NULL) {
			s.push(tree->rchild);
		}
		// 左孩子不为空就入栈
		if (tree->lchild != NULL) {
			s.push(tree->lchild);
		}

	}
}
// 中序非递归
void InOrder(Tree tree) {
	if (tree == NULL) return;
	stack<TreeNode*> s;
	s.push(tree);
	while (!s.empty()) {
		// 先把左子树全部压入栈中
		while (tree->lchild != NULL) {
			s.push(tree->lchild);
			tree = tree->lchild;
		}
		// 一棵树的左子树压完后就访问
		tree = s.top();
		s.pop();
		printf("%d ", tree->data);
		// 退回到父节点后向右走一步继续重复上述操作
		if (tree->rchild != NULL) {
			s.push(tree->rchild);
			tree = tree->rchild;
		}
	}
}
// 后序非递归
void PostOrder(Tree tree) {
	if (tree == NULL) return;
	stack<TreeNode*> s, res;
	s.push(tree);
	// 使用一个栈进行后序非递归遍历一般较为麻烦 而借助两个栈就可以巧妙的简化问题难度
	while (!s.empty()) {
		Tree temp = s.top();
		res.push(temp);
		s.pop();

		// 因为后序遍历根是最后访问的 所以左右子树都先进入s栈
		// s栈的作用就是先只遍历不访问 随后每次将从s栈顶取出的元素压入res栈即可
		if (temp->lchild != NULL) s.push(temp->lchild);
		if (temp->rchild != NULL) s.push(temp->rchild);

	}
	// 最后按顺序出栈就是后序遍历序列
	while (!res.empty()) {
		printf("%d ", res.top()->data);
		res.pop();
	}
}
int main() {
	Tree root = NULL;
	build(root, 5);
	build(root, 1);
	build(root, 10);
	build(root, 4);
	build(root, 8);
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	return 0;
}