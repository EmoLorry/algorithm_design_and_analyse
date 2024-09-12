#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N = 4;
const int M = 500000;
int father[10000];
int index[M];
int weight[M];
int from[M];
int to[M];
void Array_quickSort(int low, int high) {
    if (low < high) {
        int pivot = weight[high]; // 选择最后一个元素作为pivot
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (weight[j] < pivot) {
                i++;
                swap(weight[i],weight[j]);
                swap(index[i], index[j]);
            }
        }
        swap(weight[i + 1], weight[high]);
        swap(index[i + 1], index[high]);
        int pi = i + 1;

        Array_quickSort(low, pi - 1);
        Array_quickSort(pi + 1, high);
    }
}

int findFather(int x,int* father) {
    int a = x;
  //  cout << a << endl;
    for (int i = 0; i != 4; i++)
        cout << father[i] << " *";
    while (x != father[x]) { 
        x = father[x]; }
        
    while (a != father[a]) {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}
void Union(int a, int b, int* father) {
    int faA = findFather(a,father);
    int faB = findFather(b,father);
    if (faA != faB)
        father[faA] = faB;
}
void init(int n,int* father) {
    for (int i =n-1; i >= 0; i--)
        father[i] = i;
}
int Kruskal(int n) {
    int* father = new int[n];
    init(n, father);
    Array_quickSort(0, 3); // Sorting edges by increasing weight
    int mst_cost = 0;
    int count = 0;
    for (int i = 0; i != 4; ++i) {
        if (count == n - 1)
            break;
        int Index = index[i];

        if (findFather(from[Index], father) != findFather(to[Index], father)) {
            Union(from[Index], to[Index], father);
            mst_cost += weight[i];
            count += 1;
        }
    }
    return mst_cost;
}

int main() {
    int m, n;
    int a, b, w;

    while (scanf_s("%d %d", &n, &m) != EOF) {
        
        for (int i = 0; i < m; i++) {
            scanf_s("%d %d %d", &a, &b, &w);
            index[i] = i;
            weight[i] = w;
            from[i] = a;
            to[i] = b;
        }

        int result = Kruskal(n);
        printf("%d\n", result);
    }

    return 0;
}