#include <queue>
#include <cstdio>
using namespace std;

//链表结点
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
	*	G：	邻接链表
	*	n：	顶点数
	*	InDegree：	记录顶点的入度
	*/
    MinHeapPriorityQueue q(10000);
	for (int i = 0; i != n; i++)
		if (!inDegree[i])
			q.push(i);		//将所有入度为0的顶点入队
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
const int N = 100000;
const int M = 500000;
int inDegree[N];

int main() {
	int n, m;
	int a, b;

	while (scanf("%d %d", &n, &m) != EOF) {
		ListNode* ptrArrayhead[N] = { nullptr };//邻接链表指针索引
		for (int i = 0; i != M; i++)
		{
			scanf("%d %d", &a, &b);
			inDegree[b]++;
			ListNode* tmp = new ListNode(b);
			// 将新节点加入到对应顶点的邻接链表中
			tmp->next = ptrArrayhead[a]; // 将新节点指向当前邻接链表的头节点
			ptrArrayhead[a] = tmp; // 更新邻接链表的头节点为新节点
		}

		TopSort(ptrArrayhead, N, inDegree);

		printf("\n");


	}
	return 0;
}