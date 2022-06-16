#include<iostream>
#include<list>
#include<stack>
using namespace std;
#define MAX_V 500
#define INF 0x3f3f3f3f
// 除了计算最短路 还记录了路径
// 邻接表存图
int G[MAX_V + 1][MAX_V + 1];
int n, m;
int dis[MAX_V + 1];
bool vis[MAX_V + 1];
// 用来记录路径
int path[MAX_V + 1];
void Dijkstra(int s) {
	for (int i = 0; i <= n; i++) {
		vis[i] = 0;
		dis[i] = G[s][i];
		// 初始化都指向0
		path[i] = 0;
		if (dis[i] != INF) path[i] = s;
	}
	dis[s] = 0;
	vis[s] = 1;
	for (int i = 1; i < n; i++) {
		int v = 0;
		int minimum = INF;
		// 找到能够到达且没被访问过的点中的最短的一个
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && (v == 0 || minimum > dis[j])) {
				v = j;
				minimum = dis[j];
			}
		}
		//if (v == 0) break;
		vis[v] = 1;
		
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dis[j] > dis[v] + G[v][j]) {
				dis[j] = dis[v] + G[v][j];
				// 更新距离时同时更新路径
				path[j] = v;
			}
		}
	}
}
// 打印到达某一点的路径
void printPath(int i) {
	// 倒着追溯父节点并存放到栈中 随后出栈即可得到正序路径
	stack<int> p;
	cout << "到达节点 " << i << " 所经过的路径如下：";
	int index = i;
	p.push(index);
	while (path[index] != 0) {
		p.push(path[index]);
		index = path[index];
	}
	while (!p.empty()) {
		cout << p.top();
		if (p.size() != 1) cout << " -> ";
		p.pop();
	}
	cout << "\n\n";
}
int main() {
	memset(G, INF, sizeof(G));
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		G[x][y] = w;
	}
	Dijkstra(1);

	for (int i = 1; i <= n; i++) {
		cout << "节点 1 到节点 "<< i << " 的最小代价为：" << dis[i] << '\n';
		printPath(i);
	}

	return 0;
}
/*
5 7
1 2 1
1 3 5
2 3 2
2 5 4
3 4 4
4 5 3
5 4 3
*/