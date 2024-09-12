#include <queue>
#include <cstdio>
using namespace std;

const int N = 100000;
const int M = 500000; 
int inDegree[N];


//������
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};
//�ڽ�����ָ������

void TopSort(ListNode* G[]) {
	/*
	*	param
	*	G��	�ڽ�����
	*	n��	������
	*	InDegree��	��¼��������
	*/
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 0; i!= N; i++)
		if (!inDegree[i])
			q.push(i);	
				//���������Ϊ0�Ķ������
	while (!q.empty()) {
		int u = q.top();		//ȡ���ȶ��׶���u
		printf("%d ", u);
		q.pop();
		ListNode* tmp = G[u];
		while (tmp) {
			int v = tmp->val;		//u�ĺ�̽ڵ�
			inDegree[v]--;			//v����ȼ�1
			tmp = tmp->next;
			if (!inDegree[v])		//����v����ȼ�Ϊ0�����
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
			tmp->next = ptrArrayhead[a]; // ���½ڵ�ָ��ǰ�ڽ������ͷ�ڵ�
			ptrArrayhead[a] = tmp; // �����ڽ������ͷ�ڵ�Ϊ�½ڵ�
		}
		TopSort(ptrArrayhead);
		printf("\n");
		

	}
	return 0;
}
