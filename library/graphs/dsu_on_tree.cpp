#include <bits/stdc++.h>
using namespace std;

// Small-to-large merging (DSU on tree). vec[v] ends up holding every vertex
// in the subtree of v; cnt[c] holds the count of color c among vertices
// currently merged into the node being processed.
struct DsuOnTree {
    int n;
    vector<vector<int>> adj;
    vector<int> color, sz, cnt;
    vector<vector<int>> vec;

    DsuOnTree(vector<vector<int>> adj_, vector<int> color_)
        : n(adj_.size()),
          adj(adj_),
          color(color_),
          sz(n),
          cnt(*max_element(color.begin(), color.end()) + 1, 0),
          vec(n) {
        dfsSz(0, -1);
        dfs(0, -1, false);
    }

    void dfsSz(int v, int p) {
        sz[v] = 1;
        for (int u : adj[v]) {
            if (u == p) continue;
            dfsSz(u, v);
            sz[v] += sz[u];
        }
    }

    void dfs(int v, int p, bool keep) {
        int mx = -1, bigChild = -1;
        for (int u : adj[v]) {
            if (u != p && mx < sz[u]) mx = sz[u], bigChild = u;
        }
        for (int u : adj[v]) {
            if (u != p && u != bigChild) dfs(u, v, false);
        }
        if (bigChild != -1) {
            dfs(bigChild, v, true);
            swap(vec[v], vec[bigChild]);
        }
        vec[v].push_back(v);
        cnt[color[v]]++;
        for (int u : adj[v]) {
            if (u != p && u != bigChild) {
                for (int x : vec[u]) {
                    cnt[color[x]]++;
                    vec[v].push_back(x);
                }
            }
        }
        // cnt[c] = number of vertices in subtree(v) colored c -- answer
        // queries for v here.
        if (!keep) {
            for (int x : vec[v]) cnt[color[x]]--;
        }
    }
};
