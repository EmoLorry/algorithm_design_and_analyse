#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

bool compareEdge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int size) : parent(size), rank(size, 0) {
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
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

int kruskal(int n, vector<Edge>& edges) {
    UnionFind uf(n);
    sort(edges.begin(), edges.end(), compareEdge); // Sorting edges by increasing weight
    int mst_cost = 0;
    for (const Edge& edge : edges) {
        if (uf.find(edge.from) != uf.find(edge.to)) {
            uf.unionSets(edge.from, edge.to);
            mst_cost += edge.weight;
        }
    }
    return mst_cost;
}

int main() {
    int m, n;
    int a, b, w;

    while (scanf("%d %d", &n, &m) != EOF) {
        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &w);
            edges.emplace_back(a, b, w);
        }

        int result = kruskal(n, edges);
        printf("%d\n", result);
    }

    return 0;
}
