#include <queue>
#include <cstdio>
using namespace std;

//������
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};
class MinHeapPriorityQueue {
private:
    int* heap;
    int capacity;
    int size;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] > heap[index]) { // Compare in the opposite direction for Min Heap
                std::swap(heap[parent], heap[index]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left] < heap[smallest]) // Compare in the opposite direction for Min Heap
            smallest = left;
        if (right < size && heap[right] < heap[smallest]) // Compare in the opposite direction for Min Heap
            smallest = right;

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeapPriorityQueue(int capacity) : capacity(capacity), size(0) {
        heap = new int[capacity];
    }

    ~MinHeapPriorityQueue() {
        delete[] heap;
    }

    bool empty() const {
        return size == 0;
    }

    void push(int value) {
        heap[size] = value;
        heapifyUp(size);
        ++size;
    }

    int top() const {
        return heap[0];
    }

    void pop() {
        heap[0] = heap[size - 1];
        --size;
        heapifyDown(0);
    }
};

void TopSort(ListNode* G[], int n, int* inDegree) {
	/*
	*	param
	*	G��	�ڽ�����
	*	n��	������
	*	InDegree��	��¼��������
	*/
    MinHeapPriorityQueue q(10000);
	for (int i = 0; i != n; i++)
		if (!inDegree[i])
			q.push(i);		//���������Ϊ0�Ķ������
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
const int N = 100000;
const int M = 500000;
int inDegree[N];

int main() {
	int n, m;
	int a, b;

	while (scanf("%d %d", &n, &m) != EOF) {
		ListNode* ptrArrayhead[N] = { nullptr };//�ڽ�����ָ������
		for (int i = 0; i != M; i++)
		{
			scanf("%d %d", &a, &b);
			inDegree[b]++;
			ListNode* tmp = new ListNode(b);
			// ���½ڵ���뵽��Ӧ������ڽ�������
			tmp->next = ptrArrayhead[a]; // ���½ڵ�ָ��ǰ�ڽ������ͷ�ڵ�
			ptrArrayhead[a] = tmp; // �����ڽ������ͷ�ڵ�Ϊ�½ڵ�
		}

		TopSort(ptrArrayhead, N, inDegree);

		printf("\n");


	}
	return 0;
}