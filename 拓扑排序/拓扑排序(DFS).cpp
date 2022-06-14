#include<iostream>
#include<list>
using namespace std;
// 顶点个数
#define MAX_V 500
struct node {
	// 入度 出度
	int in, out;
	node(int in = 0, int out = 0) {
		this->in = in;
		this->out = out;
	}
};

// dfs判断是否有环 图、标记数组、起点、是否有环
void dfs(list<int> G[], int vis[], int s, bool &flag) {
	if (flag) return;

	for (auto it : G[s]) {
		// 如果搜索时遇到环路直接退出
		if (vis[it] == 1) {
			flag = 1;
			return;
		}
		// 本次深搜中被访问过暂时标记为1
		vis[it] = 1;
		dfs(G, vis, it, flag);
		// 回溯
		vis[it] = 0;

	}
}
bool TopSort(list<int> G[], node n[], int v) {
	int vis[MAX_V+1];
	memset(vis, 0, sizeof vis);

	bool flag = 0;
	for (int i = 1; i <= v; i++) {
		// 从入度为0的节点开始搜索
		if (n[i].in == 0) {
			vis[i] = 1;
			dfs(G, vis, i, flag);
			vis[i] = 0;
		}
		if (flag) return 0;
	}
	return 1;
}
int main() {
	// 邻接表 存放图
	list<int> G[MAX_V + 1];
	// 对应编号的节点节点信息
	node n[MAX_V + 1];
	int v, m;
	// 顶点个数 边的条数
	cin >> v >> m;
	for (int i = 1; i <= m; i++) {
		// 图是无向图 节点编号按数字顺序标号
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);

		n[x].out++; 
		n[y].in++;
	}
	cout<<TopSort(G, n, v);

	return 0;
}
/*
有环图示例
6 6
4 1
5 1
1 6
1 2
2 3
3 1

无环图示例
6 5
4 1
5 1
1 6
1 2
2 3
*/