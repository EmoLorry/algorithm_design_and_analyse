#include <queue>
#include <cstdio>
using namespace std;

const int N = 100000;

//������
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
	*	G��	�ڽӱ�
	*	n��	������
	*	InDegree��	��¼��������
	*/
	priority_queue<int, vector<int>, greater<int>> q;
	for (int i = 0; i!= N; i++)
		if (!G[i]->inDegree)
			q.push(i);		//���������Ϊ0�Ķ������
	while (!q.empty()) {
		int u = q.top();		//ȡ���׶���u
		printf("%d ", u);
		q.pop();
		ListNode* tmp = G[u]->head;
		while (tmp) {
			int v = tmp->val;		//u�ĺ�̽ڵ�
			G[v]->inDegree--;			//v����ȼ�1
			tmp = tmp->next;
			if (!G[v]->inDegree)		//����v����ȼ�Ϊ0�����
				q.push(v);
		}
	}
}

int main() {
	int n, m;
	int a, b;

	while (scanf("%d %d", &n, &m) != EOF) {
		GraphNode* ptrArrayhead[N];//�ڽ�����ָ������
		for (int i = 0; i < N; ++i) {
			ptrArrayhead[i] = new GraphNode();
		}

		for (int i = 0; i != N; i++)
		{
			scanf("%d %d", &a, &b);
			ListNode* tmp = new ListNode(b);
			ptrArrayhead[b]->inDegree++;
			
			// ���½ڵ���뵽��Ӧ������ڽ�������
			tmp->next = ptrArrayhead[a]->head; // ���½ڵ�ָ��ǰ�ڽ������ͷ�ڵ�
			ptrArrayhead[a]->head = tmp; // �����ڽ������ͷ�ڵ�Ϊ�½ڵ�
		}

		TopSort(ptrArrayhead);

		printf("\n");
		

	}
	return 0;
}
