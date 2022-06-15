#include<iostream>
#include<queue>
#include<string>
using namespace std;
#define MAX_NODE 26
// 哈夫曼树节点定义
typedef struct TreeNode* HuffmanTree;
typedef struct TreeNode {
	char data;
	// 节点的权重
	double weight;
	// 子节点和父节点
	HuffmanTree lchild, rchild;

}HuffmanNode;
// 堆中存放的是节点的地址 
struct HuffmanPtr {
	HuffmanTree node;
	// 自定义小根堆
	bool operator<(const HuffmanPtr& t)const {
		return node->weight > (t.node)->weight;
	}
};
// 以字母表中26个字母编码为例
char codeArray[MAX_NODE] = {	'A', 'B', 'C', 'D', 'E',
								'F', 'G', 'H', 'I', 'J', 
								'K', 'L', 'M', 'N', 'O', 
								'P', 'Q', 'R', 'S', 'T', 
								'U', 'V', 'W', 'X', 'Y', 'Z'};
// 所占权重
double weightArray[MAX_NODE] = { 8.19, 1.47, 3.83, 3.91, 12.25,
								 2.26, 1.71, 4.57, 7.10, 0.14,
								 0.41, 3.77, 3.34, 7.06, 7.26,
								 2.89, 0.09, 6.85, 6.36, 9.41,
								 2.58, 1.09, 1.59, 0.21, 1.58, 0.08 };
// 每个字母对应的编码
string code[MAX_NODE];

// 分配新节点
HuffmanTree getNewNode(char data = '.', double weight = 0.0) {
	HuffmanTree node = (HuffmanTree)malloc(sizeof(HuffmanNode));
	if (node == NULL) exit(-1);
	node->data = data;
	node->weight = weight;
	node->lchild = node->rchild = NULL;
	return node;
}
// 生成哈夫曼树 (使用小根堆进行优化)
void HuffmanEncoding(HuffmanTree& tree) {
	// 注意堆中存放的是节点指针
	priority_queue<HuffmanPtr> heap;

	// 先把基本的几个节点放入堆中
	for (int i = 0; i < MAX_NODE; i++) {
		HuffmanTree t = getNewNode(codeArray[i], weightArray[i]);
		heap.push({ t });
	}
	// 直到堆中只剩下一个节点即为Huffman树的根
	while (heap.size() > 1) {
		// 每次拿出最小的两个节点
		HuffmanPtr p1 = heap.top();
		heap.pop();
		HuffmanPtr p2 = heap.top();
		heap.pop();

		// 新的节点
		HuffmanTree newNode = getNewNode();
		// 新节点的权重是子节点权重之和
		newNode->weight = (p1.node)->weight + (p2.node)->weight;
		newNode->lchild = p1.node;
		newNode->rchild = p2.node;
		// 再加入到堆中
		heap.push({ newNode });
	}
	// 最后堆顶剩的节点就是哈夫曼树的根节点
	tree = heap.top().node;
	heap.pop();
}
void dfs(HuffmanTree tree) {
	if (tree == NULL) return;
	printf("%c %.2llf\n", tree->data, tree->weight);
	dfs(tree->lchild);
	dfs(tree->rchild);
}
// 获得每个字母对应的编码
void getCode(HuffmanTree tree, string c) {
	if (tree->lchild == NULL && tree->rchild == NULL) {
		code[tree->data - 'A'] = c;
		return;
	}
	getCode(tree->lchild, c + '0');
	getCode(tree->rchild, c + '1');
}
int main() {

	HuffmanTree tree;
	HuffmanEncoding(tree);
	//dfs(tree);
	getCode(tree, "");
	char t = 'A';
	for (auto it : code)
		cout << t++ << ": " << it << '\n';
	return 0;
}