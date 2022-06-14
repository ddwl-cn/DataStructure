#include<iostream>
using namespace std;
#define MAX_E 500
#define INF 0x3f3f3f3f
struct edge {
	int from, to;
	int weight;
}E[MAX_E << 1 + 1];
int n, m;
// 并查集 用来查询边所在的集合
int fa[MAX_E + 1];
int find(int x) {
	/*
	* 等价于
	* if (fa[x] == x) return x;
	* return (fa[x] = find(fa[x]));
	*/
	return (x == fa[x] ? x : (fa[x] = find(fa[x])));
}
// 合并集合
void merge(int x, int y) {
	fa[find(x)] = find(y);
}
int kruskal() {
	int sum = 0;
	int vis[MAX_E << 1 + 1];
	memset(vis, 0, sizeof vis);
	// 初始化并查集
	for (int i = 1; i <= n; i++) fa[i] = i;
	// 找够n-1条边为止
	for (int i = 1; i < n;) {
		// 遍历寻找最短边
		int minium = INF;
		int index = 0;
		for (int j = 1; j <= (m << 1); j++) {
			if (!vis[j] && E[j].weight < minium) {
				minium = E[j].weight;
				index = j;
			}
		}
		vis[index] = 1;

		// 最短边的两端不在同一个集合 就可以合并
		if (find(E[index].from) != find(E[index].to)) {
			merge(E[index].from, E[index].to);
			sum += E[index].weight;
			i++;
		}

	}
	return sum;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		E[i].from = x;
		E[i].to = y;
		E[i].weight = w;

		E[m + i].from = y;
		E[m + i].to = x;
		E[m + i].weight = w;
	}
	cout << kruskal();
	return 0;
}
/*
5 7
1 2 8
1 3 1
2 3 3
3 4 2
2 4 1
2 5 5
1 5 5
*/

