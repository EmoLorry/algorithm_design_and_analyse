#include <vector>
#include <queue>
#include <cstdio>

using namespace std;
void TopSort(vector<vector<int> > G, int n, int* inDegree) {
	/*
	*	param
	*	G��	�ڽӱ�
	*	n��	������
	*	InDegree��	��¼��������
	*/		
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 0; i < n; i++)
		if (inDegree[i] == 0)
			q.push(i);		//���������Ϊ0�Ķ������
	while (!q.empty()) {
		int u = q.top();		//ȡ���׶���u
		printf("%d ", u); 
		q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			int v = G[u][i];		//u�ĺ�̽ڵ�
			inDegree[v]--;			//v����ȼ�1
			if (inDegree[v] == 0)		//����v����ȼ�Ϊ0�����
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
