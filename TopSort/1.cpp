#include <vector>
#include <queue>
#include <cstdio>

using namespace std;
void TopSort(vector<vector<int> > G, int n, int* inDegree) {
	/*
	*	param
	*	G：	邻接表
	*	n：	顶点数
	*	InDegree：	记录顶点的入度
	*/		
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 0; i < n; i++)
		if (inDegree[i] == 0)
			q.push(i);		//将所有入度为0的顶点入队
	while (!q.empty()) {
		int u = q.top();		//取队首顶点u
		printf("%d ", u); 
		q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];		//u的后继节点
			inDegree[v]--;			//v的入度减1
			if (inDegree[v] == 0)		//顶点v的入度减为0则入队
				q.push(v);
		}
	}
}
const int N = 100000;
int inDegree[N];
int main() {
	int n, m;
	int a, b;
	while (scanf("%d %d", &n, &m) != EOF) {
		vector<vector<int> > G(N);
		for (int i = 0; i != m; i++)
		{
			scanf("%d %d", &a, &b);
			G[a].push_back(b);

		}
		for (auto x : G) {
			for (auto y : x)
				inDegree[y]++;
		}

		TopSort(G, n, inDegree);

		printf("\n");
	}

	return 0;

}
