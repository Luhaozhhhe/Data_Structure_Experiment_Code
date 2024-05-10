#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int N = 100;
vector<int> g[N];
int start, theEnd;
int reach[N], visit[N];
int m, n;
int len;

bool bfs(int v, int label) {
	len = 1;
	queue<int> q;
	reach[v] = label;
	q.push(v);
	while (!q.empty()) {
		int w = q.front();
		q.pop();
		if (w == theEnd) {
			break;
		}
		int u;
		for (int i = 0; i < g[w].size(); i++) {
			u = g[w][i];
			if (!visit[u]) {
				len++;
				reach[u] = w;
				visit[u] = 1;
				q.push(u);
			}
		}
	}
	if (len == 1) {
		return false;
	}
	return true;
}

bool findpath_bfs(int Start, int End) {
	reach[1] = Start;
	len = 1;
	theEnd = End;
	fill(visit, visit + n, 0);
	if (Start == End || bfs(Start, 1)) {
		reach[0] = 0;
		return true;
	}
	return false;

}

void show_bfs(int x) {
	if (x == start) {
		cout << x << " ";
		return;
	}
	show_bfs(reach[x]);
	cout << x << " ";
	reach[0]++;
}

int main() {//test for the code
	cout << "please input V and E " << endl;
	cin >> n >> m;
	int u, v;
	cout << "input every E's number" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);

	}
	cout << "please input the begin and the end" << endl;
	cin >> start >> theEnd;
	if (findpath_bfs(start, theEnd)) {
		cout << "the bfs path is:" ;
		show_bfs(theEnd);
		cout << endl;
		cout << "the length of the bfs:" << reach[0] << endl;
	}
	return 0;
}