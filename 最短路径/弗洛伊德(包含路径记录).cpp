#include<iostream>
using namespace std;
#define MAX_V 500
#define INF 0x3f3f3f3f
int G[MAX_V + 1][MAX_V + 1];
// 记录路径
int path[MAX_V + 1][MAX_V + 1];
int n, m;
// 弗洛伊德算法用于计算多源最短路径
void Floyd() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			// k是中间节点 如果
			for (int k = 1; k <= n; k++) {
				if (G[i][j] > G[i][k] + G[k][j]) {
					G[i][j] = G[i][k] + G[k][j];
					path[i][j] = k;
				}
			}
		}
	}
}
// 打印从起点到终点的最短路径
void getPath(int s, int e) {
	if (s == e) return;
	if (path[s][e] == 0) {
		cout << s << " -> ";
		return;
	}
	getPath(s, path[s][e]);
	getPath(path[s][e], e);
}
void printPath(int s, int e) {
	getPath(s, e);
	// 终点单独打印
	cout << e;
}
int main() {
	cin >> n >> m;
	memset(G, INF, sizeof(G));
	memset(path, 0, sizeof(path));
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		G[x][y] = w;
	}
	Floyd();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << G[i][j] << ' ';
		}
		cout << '\n';
	}

	printPath(1, 3);
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