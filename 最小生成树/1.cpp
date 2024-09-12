#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// 边的结构体，包括目标节点和权重
struct Edge {
    int target;
    int weight;
    Edge(int t, int w) : target(t), weight(w) {}
};

// 邻接列表表示的图
class Graph {
public:
    int V; // 节点数
    vector<vector<Edge>> adjList; // 邻接列表

    Graph(int V) : V(V) {
        adjList.resize(V);
    }

    // 添加边
    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight);
    }
};

// Prim算法求最小生成树
int primMST(Graph& graph) {
    vector<bool> inMST(graph.V, false); // 是否已在最小生成树中
    vector<int> key(graph.V, numeric_limits<int>::max()); // 节点的键值，表示到最小生成树的最小距离
    vector<int> parent(graph.V, -1); // 最小生成树中每个节点的父节点
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 优先队列，按键值排序

    // 选择第一个节点为起始点
    int src = 0;
    key[src] = 0;
    pq.push(make_pair(0, src));

    // Prim算法迭代
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true; // 将节点加入最小生成树

        // 更新与u相邻的节点的键值
        for (const auto& edge : graph.adjList[u]) {
            int v = edge.target;
            int weight = edge.weight;
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // 计算最小生成树的权重和
    int minWeight = 0;
    for (int i = 1; i < graph.V; ++i) {
        minWeight += key[i];
    }

    return minWeight;
}

int main() {
    int n;//顶 点 数(1000/10000)
    int m;//边数int m;(500000)
    int a, b, v;//a-b表示一条无向边，编号范围为{0，1，..，n-1}
    while (scanf("%d %d", &n, &m) != EOF) {
        //如果是全局变量，记得清空上一轮数据!!!!
        Graph graph(n);
        for (int i = 0; i < m; i++)
        {
            scanf("%d %d %d", &a, &b, &v); // 添加无向边 a - b，及其权重v
            graph.addEdge(a, b, v);
        }
        //算法运行，将最小生成树的最小权重和结果存在result中result =
        int result = primMST(graph);
        printf("%d\n", result);
    }
    return 0;
}