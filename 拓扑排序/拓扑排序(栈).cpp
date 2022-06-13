#include<iostream>
#include<stack>
#include<list>
#include<vector>
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
// 拓扑排序 如果顶点全部正常输出说明图是无环图 否则说明有环
bool TopSort(list<int> G[], node n[], int v) {
	stack<int> s;
	// 已排序节点个数
	int cnt = 0;
	// 入度为0的入栈
	for (int i = 1; i <= v; i++) {
		if (n[i].in == 0) {
			s.push(i);
			cnt++;
		}
	}

	while (!s.empty()) {
		int index = s.top();
		s.pop();
		// 与他相连的节点入度均 -1
		for (auto it : G[index]) {
			n[it].in--;
			// 如果入度 -1 后为 0 就入栈
			if (n[it].in == 0) {
				s.push(it);
				cnt++;
			}
		}
	}
	return cnt == v;
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