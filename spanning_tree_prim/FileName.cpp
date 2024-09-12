#include <cstdio>
#include <algorithm>

using namespace std;
struct _prim {
    int to; // 到达的顶点
    int w; // 权重

    // 默认构造函数
    _prim() : to(0), w(0) {}
    _prim(int v, int w) : to(v), w(w) {}
};
struct ListNode {
    int to;
    int w;
    ListNode* next;
    ListNode(int x, int y) : to(x), w(y), next(NULL) {}
};

class MinHeapPriorityQueue {
private:
    _prim* heap;
    int capacity;
    int size;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent].w > heap[index].w) { // Compare in the opposite direction for Min Heap
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

        if (left < size && heap[left].w < heap[smallest].w) // Compare in the opposite direction for Min Heap
            smallest = left;
        if (right < size && heap[right].w < heap[smallest].w) // Compare in the opposite direction for Min Heap
            smallest = right;

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeapPriorityQueue(int capacity) : capacity(capacity), size(0) {
        heap = new _prim[capacity]{};
    }

    ~MinHeapPriorityQueue() {
        delete[] heap;
    }

    bool empty() const {
        return size == 0;
    }

    void push(_prim value) {
        heap[size] = value;
        heapifyUp(size);
        ++size;
    }

    _prim top() const {
        return heap[0];
    }

    void pop() {
        heap[0] = heap[size - 1];
        --size;
        heapifyDown(0);
    }
};



int prim(ListNode* arr[], int N) {
    int* is_in_MST_i = new int[N] {};
    int* Distance_i_to_tree = new int[N];
    std::fill(Distance_i_to_tree, Distance_i_to_tree + N, 1000);

    MinHeapPriorityQueue pq(500000);
    int start = 0;
    pq.push(_prim(0, 0));

    int sum = 0;
    while (!pq.empty()) {
        int add = pq.top().to;
        pq.pop();
        is_in_MST_i[add] = 1;

        ListNode* temp = arr[add];
        while (temp) {
            int v = temp->to;
            int w = temp->w;
            if (!is_in_MST_i[v] && Distance_i_to_tree[v] > w) {
                Distance_i_to_tree[v] = w;
                pq.push(_prim(v, Distance_i_to_tree[v]));
            }
            temp = temp->next;
        }
    }
    for (int i = 1; i < N; ++i) {
        sum += Distance_i_to_tree[i];
    }

    return sum;
}
const int N1 = 1000;
const int N2 = 10000;

int main() {
    FILE* inputFile, * outputFile;
    if (fopen_s(&inputFile, "caizihuan_luorui.txt", "r") != 0) {
        printf("Error: Unable to open input file.\n");
        return 1;
    }
    if (fopen_s(&outputFile, "output.txt", "w") != 0) {
        printf("Error: Unable to open output file.\n");
        return 1;
    }

    int n, m;
    int a, b, w;
    while (fscanf_s(inputFile, "%d %d", &n, &m) != EOF) {
        if (n == N1) {
            ListNode* ptrArrayheadN1[N1] = { NULL };
            for (int i = 0; i != m; i++)
            {
                fscanf_s(inputFile, "%d %d %d", &a, &b, &w);
                ListNode* tmpa = new ListNode(b, w);
                tmpa->next = ptrArrayheadN1[a]; // 将新节点指向当前邻接链表的头节点
                ptrArrayheadN1[a] = tmpa; // 更新邻接链表的头节点为新节点
                ListNode* tmpb = new ListNode(a, w);
                tmpb->next = ptrArrayheadN1[b];
                ptrArrayheadN1[b] = tmpb;
            }

            int minspanningtree = prim(ptrArrayheadN1, N1);
            fprintf(outputFile, "%d\n", minspanningtree);
        }
        else {
            ListNode* ptrArrayheadN2[N2] = { NULL };
            for (int i = 0; i != m; i++)
            {
                fscanf_s(inputFile, "%d %d %d", &a, &b, &w);
                ListNode* tmpa = new ListNode(b, w);
                tmpa->next = ptrArrayheadN2[a]; // 将新节点指向当前邻接链表的头节点
                ptrArrayheadN2[a] = tmpa; // 更新邻接链表的头节点为新节点
                ListNode* tmpb = new ListNode(a, w);
                tmpb->next = ptrArrayheadN2[b];
                ptrArrayheadN2[b] = tmpb;
            }
            int minspanningtree = prim(ptrArrayheadN2, N2);
            fprintf(outputFile, "%d\n", minspanningtree);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}