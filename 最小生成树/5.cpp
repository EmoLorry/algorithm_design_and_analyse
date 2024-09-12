#include <algorithm>
#include <cstdio>

using namespace std;
int father[10000];
int Rank[10000];
int edgeindex[500000];
int weight[500000];
int from[500000];
int to[500000];
void Array_quickSort(int low, int high) {
    if (low < high) {
        int pivot = weight[high]; // 选择最后一个元素作为pivot
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (weight[j] < pivot) {
                i++;
                swap(weight[i],weight[j]);
                swap(edgeindex[i], edgeindex[j]);
            }
        }
        swap(weight[i + 1], weight[high]);
        swap(edgeindex[i + 1], edgeindex[high]);
        int pi = i + 1;

        Array_quickSort(low, pi - 1);
        Array_quickSort(pi + 1, high);
    }
}

int findFather(int x) {
  if(father[x]!=x)
     father[x]=findFather(father[x]);
  return father[x];
}

void Union(int a, int b) {
    int faA = findFather(a);
    int faB = findFather(b);
            if (Rank[faA] > Rank[faB]) {
                father[faB] = faA;
            } else if (Rank[faA] < Rank[faB]) {
                father[faA] = faB;
            } else {
                father[faB] = faA;
                Rank[faA]++;
            }
}
void init(int n) {
    for (int i =n-1; i >= 0; i--)
        father[i] = i;
        
    Rank[10000]={0};
}
int Kruskal(int n) {
    init(n);
    Array_quickSort(0, 499999); // Sorting edges by increasing weight
    int mst_cost = 0;
    int count = 0;
    for (int i = 0;count!= n-1; ++i) {
        int Index = edgeindex[i];
        if (findFather(from[Index]) != findFather(to[Index])) {
            Union(from[Index], to[Index]);
            mst_cost += weight[i];
            count += 1;
        }
    }
    return mst_cost;
}

int main() {
    int m, n;
    int a, b, w;

    while (scanf("%d %d", &n, &m) != EOF) {
        int count =m;
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &w);
            edgeindex[i] = i;
            weight[i] = w;
            from[i] = a;
            to[i] = b;
        }

        int result = Kruskal(n);
        printf("%d\n", result);
    }

    return 0;
}
