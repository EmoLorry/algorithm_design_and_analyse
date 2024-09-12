#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 10000; // 最大节点数
const int MAXE = 500000; // 最大边数

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int f = 0, int t = 0, int w = 0) : from(f), to(t), weight(w) {}
};

bool compareEdge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class UnionFind {
private:
    int parent[MAXN];
    int rank[MAXN];

public:
    UnionFind(int size) {
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int kruskal(int n, Edge edges[], int m) {
    int count = 0;
    UnionFind uf(n);
    sort(edges, edges + m, compareEdge); // Sorting edges by increasing weight
    int mst_cost = 0;
    for (int i = 0; count != n-1; i++) {
        if (uf.find(edges[i].from) != uf.find(edges[i].to)) {
            uf.unionSets(edges[i].from, edges[i].to);
            mst_cost += edges[i].weight;
            count++;
        }
    }
    return mst_cost;
}

int main() {
    int m, n;
    int a, b, w;

    Edge edges[MAXE]; // 静态数组存储边

    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &w);
            edges[i] = Edge(a, b, w);
        }
      printf(
        int result = kruskal(n, edges, m);
  "%d\n", result);
    }

    return 0;
}
