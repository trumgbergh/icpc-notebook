#include <bits/stdc++.h>
using namespace std;

// Flattens a tree via DFS entry/exit times so subtree ranges become
// contiguous, and (combined with LCA) point-update / root-to-node / a-to-b
// path sums become O(log N) Fenwick tree queries. subtreeSum() shows the
// simpler point-update + range-query variant for subtree-only queries.
struct EulerTour {
    int n, timer = 0;
    vector<vector<int>> adj;
    vector<int> tin, tout;
    vector<int64_t> cur, bit, bitSub;

    EulerTour(int n_)
        : n(n_),
          adj(n_),
          tin(n_),
          tout(n_),
          cur(n_, 0),
          bit(n_ + 2, 0),
          bitSub(n_ + 1, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p) {
        tin[u] = timer++;
        for (int v : adj[u])
            if (v != p) dfs(v, u);
        tout[u] = timer - 1;
    }

    void bitAdd(int i, int64_t d) {
        for (i++; i <= n + 1; i += i & (-i)) bit[i] += d;
    }
    int64_t bitQuery(int i) {  // prefix sum [0, i]
        int64_t s = 0;
        for (i++; i > 0; i -= i & (-i)) s += bit[i];
        return s;
    }

    void bitSubAdd(int i, int64_t d) {
        for (i++; i <= n; i += i & (-i)) bitSub[i] += d;
    }
    int64_t bitSubQuery(int i) {  // prefix sum [0, i]
        int64_t s = 0;
        for (i++; i > 0; i -= i & (-i)) s += bitSub[i];
        return s;
    }

    // Sets node v's value (starts at 0); call once per node after dfs() to
    // set initial values, or again later to update.
    void update(int v, int64_t newVal) {
        int64_t delta = newVal - cur[v];
        cur[v] = newVal;
        bitAdd(tin[v], delta);
        bitAdd(tout[v] + 1, -delta);
        bitSubAdd(tin[v], delta);
    }

    // Sum of values on the path from the root to v (inclusive).
    int64_t pathFromRoot(int v) { return bitQuery(tin[v]); }

    // Sum of values on the path from a to b; lca must be lca(a, b).
    int64_t pathSum(int a, int b, int lca) {
        return pathFromRoot(a) + pathFromRoot(b) - 2 * pathFromRoot(lca) +
               cur[lca];
    }

    // Sum of values in the subtree of v (inclusive).
    int64_t subtreeSum(int v) {
        return bitSubQuery(tout[v]) - bitSubQuery(tin[v] - 1);
    }
};
