#include <bits/stdc++.h>

using namespace std;

// Properties:
// - component graph is a DAG
// - traversed graph always has the same sccs
// - each component is sorted in topological order
struct Graph {
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> adj_t;
    vector<int> mark, order, leader;
    vector<vector<int>> components;
    Graph(int n_) : n(n_), adj(n), adj_t(n), mark(n), leader(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj_t[v].push_back(u);
    }

    void dfsForward(int u) {
        mark[u] = 1;
        for (int v : adj[u]) {
            if (mark[v] == 0) dfsForward(v);
        }
        order.push_back(u);
    }

    void dfsBackward(int u, int p) {
        mark[u] = 2;
        leader[u] = p;
        for (int v : adj_t[u]) {
            if (mark[v] == 1) dfsBackward(v, p);
        }
        components.back().push_back(u);
    }

    vector<vector<int>> scc() {  // Kosaraju's algorithm
        fill(mark.begin(), mark.end(), 0);
        for (int u = 0; u < n; u++) {
            if (mark[u] == 0) dfsForward(u);
        }
        reverse(order.begin(), order.end());
        for (int u : order) {
            if (mark[u] != 1) continue;
            components.emplace_back();
            dfsBackward(u, u);
        }
        return components;
    }
};
