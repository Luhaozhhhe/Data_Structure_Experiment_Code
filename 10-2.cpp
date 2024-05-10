#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
int n, m, label;
int vis[N], flag[N];
vector<int> g[N];
void dfs(int x, int reach[], int label)
{// 深度优先搜索. reach[i] 用来标记所有邻接于顶点v的可到达的顶点
	reach[x] = 1;
	flag[x] = label;
	for (int i = 0; i < g[x].size(); i++)
	{
		int y = g[x][i];
		if (reach[y] == 0)// y 是一个没有到达的顶点
		{
			// 深度优先搜索递归方法
			dfs(y, reach, label);
		}
	}
}
int lablecomponents(int c[])
{// 给无向图的构件做标记
	// 返回构件的个数
	// 令 c[i] 是顶点 i 的构件号
	// 确定是一个无向图
	fill(c, c + n + 1, 0);
	label = 0;
	for (int i = 1; i <= n; i++)
	{
		if (c[i] == 0)// 顶点 i 未到达
		{// 顶点 i 是一个新构件
			dfs(i, c, label); // 给新构件做标记 
			label++;
		}
	}
	return label;
}
int main() {
	cout << "please input the V and the E:" << endl;
	cin >> n >> m;
	cout << "please input every E's number:" << endl;
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	lablecomponents(vis);
	cout << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (flag[i] == flag[j] && i != j)
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	return 0;
}