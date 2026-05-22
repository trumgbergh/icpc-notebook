#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int n, m, time;
    vector<unordered_map<int, int>> adj;
    vector<int> num, low;
    vector<bool> isCut;
    vector<pair<int, int>> bridges;

    Graph(int n, int m)
        : adj(n), time(0), num(n, 0), low(n, 0), isCut(n, false) {}

    void addEdge(int u, int v) {
        adj[u][v]++;
        adj[v][u]++;
    }

    void dfs(int u, int p) {
        int nChild = 0;
        num[u] = low[u] = ++time;
        for (auto &e : adj[u]) {
            int v = e.first;
            if (v == p) continue;
            ++nChild;
            if (num[v])
                low[u] = min(low[u], num[v]);
            else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if ((p == -1 && nChild >= 2) || p != -1 && low[v] >= num[u]) {
                    isCut[u] = true;
                }
                if (low[v] >= num[v] && e.second == 1) {
                    bridges.emplace_back(u, v);
                }
            }
        }
    }
};
