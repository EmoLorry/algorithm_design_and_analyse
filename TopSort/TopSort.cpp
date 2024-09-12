#include <queue>
#include <cstdio>
using namespace std;

const int N = 100000;

//链表结点
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};


struct GraphNode {
	int inDegree;
	ListNode* head;
	GraphNode() : inDegree(0), head(nullptr) {}
};


void TopSort(GraphNode* G[]) {
	/*
	*	param
	*	G：	邻接表
	*	n：	顶点数
	*	InDegree：	记录顶点的入度
	*/
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 0; i!= N; i++)
		if (!G[i]->inDegree)
			q.push(i);		//将所有入度为0的顶点入队
	while (!q.empty()) {
		int u = q.top();		//取队首顶点u
		printf("%d ", u);
		q.pop();
		ListNode* tmp = G[u]->head;
		while (tmp) {
			int v = tmp->val;		//u的后继节点
			G[v]->inDegree--;			//v的入度减1
			tmp = tmp->next;
			if (!G[v]->inDegree)		//顶点v的入度减为0则入队
				q.push(v);
		}
	}
}

int main() {
	int n, m;
	int a, b;

	while (scanf("%d %d", &n, &m) != EOF) {
		GraphNode* ptrArrayhead[N];//邻接链表指针索引
		for (int i = 0; i < N; ++i) {
			ptrArrayhead[i] = new GraphNode();
		}

		for (int i = 0; i != N; i++)
		{
			scanf("%d %d", &a, &b);
			ListNode* tmp = new ListNode(b);
			ptrArrayhead[b]->inDegree++;
			
			// 将新节点加入到对应顶点的邻接链表中
			tmp->next = ptrArrayhead[a]->head; // 将新节点指向当前邻接链表的头节点
			ptrArrayhead[a]->head = tmp; // 更新邻接链表的头节点为新节点
		}

		TopSort(ptrArrayhead);

		printf("\n");
		

	}
	return 0;
}
