#include <queue>
#include <cstdio>
using namespace std;

const int N = 100000;
const int M = 500000; 
int inDegree[N];


//链表结点
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};
//邻接链表指针索引

void TopSort(ListNode* G[]) {
	/*
	*	param
	*	G：	邻接链表
	*	n：	顶点数
	*	InDegree：	记录顶点的入度
	*/
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 0; i!= N; i++)
		if (!inDegree[i])
			q.push(i);	
				//将所有入度为0的顶点入队
	while (!q.empty()) {
		int u = q.top();		//取优先队首顶点u
		printf("%d ", u);
		q.pop();
		ListNode* tmp = G[u];
		while (tmp) {
			int v = tmp->val;		//u的后继节点
			inDegree[v]--;			//v的入度减1
			tmp = tmp->next;
			if (!inDegree[v])		//顶点v的入度减为0则入队
				q.push(v);
		}
	}
}

int main() {
	int n, m;
	int a, b;

	while (scanf("%d %d", &n, &m) != EOF) {
	ListNode* ptrArrayhead[N] = { nullptr };
		for (int i = 0; i != M; i++)
		{
			scanf("%d %d", &a, &b);
			inDegree[b]++;
			ListNode* tmp = new ListNode(b);
			tmp->next = ptrArrayhead[a]; // 将新节点指向当前邻接链表的头节点
			ptrArrayhead[a] = tmp; // 更新邻接链表的头节点为新节点
		}
		TopSort(ptrArrayhead);
		printf("\n");
		

	}
	return 0;
}
