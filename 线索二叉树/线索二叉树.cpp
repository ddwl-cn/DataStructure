#include<stdio.h>
#include<stdlib.h>
/*
线索化二叉树的复习大致就是前、中、后序的线索化及其对应的遍历了
其中前序、中序线索化遍历比较类似，后序则相对较为特殊需要使用到父亲节点和一个临时指针用来记录上一个访问的节点
*/
typedef struct TreeNode{
	int data;
	struct TreeNode *lchild, *rchild, *parent;
	int ltag, rtag;
}Node, *NodePtr;

// 线索化时的中间节点 因为是全局变量所以在每次构建线索二叉树后记得要再赋值为NULL
NodePtr pre = NULL;
bool build(NodePtr& tree, int data, NodePtr lastNode) {
	if (tree == NULL) {
		// 为新节点分配空间
		tree = (NodePtr)malloc(sizeof(Node));
		if (tree == NULL) return false;

		tree->data = data;
		tree->lchild = NULL;
		tree->rchild = NULL;
		tree->parent = lastNode;
		tree->ltag = 0;
		tree->rtag = 0;
		return true;
	}
	// 按照排序树的方式构建二叉树
	if (data < tree->data)
		build(tree->lchild, data, tree);
	else
		build(tree->rchild, data, tree);
	return true;
}
// 前、中、后遍历
void InOrder(NodePtr tree) {
	if (tree != NULL) {
		InOrder(tree->lchild);
		printf("%d ", tree->data);
		InOrder(tree->rchild);
	}
}
void PreOrder(NodePtr tree) {
	if (tree != NULL) {
		printf("%d ", tree->data);
		PreOrder(tree->lchild);
		PreOrder(tree->rchild);
	}
}
void PostOrder(NodePtr tree) {
	if (tree != NULL) {
		PostOrder(tree->lchild);
		PostOrder(tree->rchild);
		printf("%d ", tree->data);
	}
}
// 构建中序线索二叉树 刚开始pre指针为 NULL
void getThreadInOrder(NodePtr tree) {
	if (tree != NULL) {
		getThreadInOrder(tree->lchild);
		// 如果该节点的左节点为空 将左孩子指向前驱节点
		if (tree->lchild == NULL) {
			tree->lchild = pre;
			tree->ltag = 1;
		}
		// 如果该节点前驱节点右节点为空 就设置前驱节点的后继节点为当前节点
		if (pre != NULL && pre->rchild == NULL) {
			pre->rchild = tree;
 			pre->rtag = 1;
		}
		pre = tree;
		getThreadInOrder(tree->rchild);
	}
}
// 遍历中序线索化二叉树
void travelThreadInOrder(NodePtr tree) {
	if (tree != NULL) {
		if (tree->lchild == NULL) printf("%d ", tree->data);
		else {
			tree = tree->lchild;
			while (tree != NULL) {
				// 如果有左标记是0 一直按照中序遍历顺序向左走
				while (tree->ltag == 0) tree = tree->lchild;
				// 走到左标记为1是第一个可以访问的节点 直接输出
				printf("%d ", tree->data);
				// 如果有右标记是1 且右孩子不指向根节点 说明右孩子是线索 直接访问右孩子并输出
				while (tree->rtag == 1 && tree->rchild != NULL) {
					tree = tree->rchild;

					printf("%d ", tree->data);
				}
				// 线索走完后继续按照中序遍历顺序向右走一步 之后重复上述操作
				tree = tree->rchild;
			}
		}

	}
}
// 构建先序线索二叉树
void getThreadPreOrder(NodePtr tree) {
	if (tree != NULL) {
		if (tree->lchild == NULL) {
			tree->lchild = pre;
			tree->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL) {
			pre->rchild = tree;
			pre->rtag = 1;
		}
		pre = tree;
		// 左孩子已经存放了前驱节点 不再是空 所以不再递归左树
		if(tree->ltag == 0)
			getThreadPreOrder(tree->lchild);
		getThreadPreOrder(tree->rchild);
	}
}
// 遍历先序线索化二叉树
void travelThreadPreOrder(NodePtr tree) {
	while (tree != NULL) {
		// 先序访问到就遍历
		// 向左走直到左标签非零
		while (tree->ltag == 0) {
			printf("%d ", tree->data);
			tree = tree->lchild;
		}
		printf("%d ", tree->data);
		// 如果右子树是线索就直接访问
		while (tree->rtag == 1 && tree->rchild != NULL) {
			tree = tree->rchild;
			printf("%d ", tree->data);
		}

		tree = tree->rchild;
	}
}
// 构建后序线索二叉树
void getThreadPostOrder(NodePtr tree) {
	if (tree != NULL) {
		getThreadPostOrder(tree->lchild);
		getThreadPostOrder(tree->rchild);
		if (tree->lchild == NULL) {
			tree->lchild = pre;
			tree->ltag = 1;
		}
		if (pre != NULL && pre->rchild == NULL) {
			pre->rchild = tree;
			pre->rtag = 1;
		}
		pre = tree;
	}
}
// 后序线索树的遍历需要借助父亲指针 比较特殊
void travelThreadPostOrder(NodePtr tree) {
	NodePtr root = tree;
	if (tree != NULL) {
		// 先走到最左边
		while (tree != NULL && tree->ltag == 0) tree = tree->lchild;
		// 用来保留前一次访问的节点
		NodePtr temp = NULL;
		// 启动大循环
		while (tree != NULL) {
			// 如果当前节点有后继线索 就按照后继线索走
			if (tree->rtag == 1) {
				printf("%d ", tree->data);
				temp = tree;
				tree = tree->rchild;
			}
			else {
				// 如果当前节点的有子树恰好是上一次访问过的 就打印输出当前节点
				// 因为后序遍历时 父节点一定是其右节点的后继 此时节点的左右一定已经遍历完了
				if (tree->rchild == temp) {
					printf("%d ", tree->data);
					// 如果这个节点就是根节点那就退出 如果先前已经设置根节点的父节点为空了可以不退出
					// if (tree == root) return;
					temp = tree;
					tree = tree->parent;
				}
				else {
					// 说明刚遍历完根节点的左子树需要对右子树进行相同操作
					tree = tree->rchild;
					while (tree != NULL && tree->ltag == 0) tree = tree->lchild;
				}
			}
		}
	}
}

int main() {
	srand(0);
	NodePtr tree = NULL;
	// 手动构建树 当然也可以随机数构建
	build(tree, 10, NULL);
	build(tree, 5, NULL);
	build(tree, 12, NULL);
	build(tree, 50, NULL);
	build(tree, 7, NULL);
	build(tree, 17, NULL);
	build(tree, 107, NULL);
	build(tree, 77, NULL);
	build(tree, 89, NULL);
	//printf("中序遍历：");
	//InOrder(tree);
	//printf("先序遍历：");
	//PreOrder(tree);
	printf("后序遍历：");
	PostOrder(tree);
	printf("\n");

	pre = NULL;

	//getThreadInOrder(tree);
	//printf("中序线索遍历：");
	//travelThreadInOrder(tree);

	//getThreadPreOrder(tree);
	//printf("先序线索遍历：");
	//travelThreadPreOrder(tree);

	getThreadPostOrder(tree);
	printf("后序线索遍历：");
	travelThreadPostOrder(tree);

	return 0;
}