#include<iostream>
#include<list>
using namespace std;
#define MAX_V 500
#define INF 0x3f3f3f3f
// 使用链表存图
int G[MAX_V + 1][MAX_V + 1];
// 点个数 边个数
int n, m;
// 普利姆最小生成树 返回最少代价
int prim(int s) {
	int dis[MAX_V + 1];
	int vis[MAX_V + 1];
	int index = s, sum = 0;
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; i++) dis[i] = G[s][i];
	dis[s] = 0;
	vis[s] = 1;
	// 遍历n-1次即可
	for (int i = 1; i < n; i++) {
		int minimum = INF;
		// 遍历找与集合紧挨的最短边
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dis[j] < minimum) {
				minimum = dis[j];
				index = j;
			}
		}

		vis[index] = 1;
		sum += minimum;
		// 如果新加入的节点能够使得dis中边的长度更短就更新
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dis[j] > G[index][j]) {
				dis[j] = G[index][j];
			}
		}

	}
	return sum;
}

int main() {
	cin >> n >> m;
	memset(G, INF, sizeof G);
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		// 这里采用无向图的形式
		G[y][x] = G[x][y] = w;
	}
	cout << prim(1);

}
/*
5 7
1 2 1
1 3 1
2 3 3
3 4 2
2 4 1
2 5 5
1 5 5
*/