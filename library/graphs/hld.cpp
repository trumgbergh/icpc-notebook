#include "../structures/lazytree.cpp"
#include <bits/stdc++.h>
using namespace std;
template <bool VALS_EDGES>
struct HLD {
    int N, tim = 0;
    vector<vector<int>> adj;
    vector<int> par, siz, rt, pos;
    Node* tree;
    HLD(vector<vector<int>> adj_)
        : N((int)adj_.size()),
          adj(adj_),
          par(N, -1),
          siz(N, 1),
          rt(N),
          pos(N),
          tree(new Node(0, N)) {
        dfsSz(0);
        dfsHld(0);
    }
    void dfsSz(int v) {
        for (int& u : adj[v]) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), v));
            par[u] = v;
            dfsSz(u);
            siz[v] += siz[u];
            if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
        }
    }
    void dfsHld(int v) {
        pos[v] = tim++;
        for (int u : adj[v]) {
            rt[u] = (u == adj[v][0] ? rt[v] : u);
            dfsHld(u);
        }
    }
    template <class B>
    void process(int u, int v, B op) {
        for (;; v = par[rt[v]]) {
            if (pos[u] > pos[v]) swap(u, v);
            if (rt[u] == rt[v]) break;
            op(pos[rt[v]], pos[v] + 1);
        }
        op(pos[u] + VALS_EDGES, pos[v] + 1);
    }
    void modifyPath(int u, int v, int val) {
        process(u, v, [&](int l, int r) { tree->add(l, r, val); });
    }
    int queryPath(int u, int v) {  // Modify depending on problem
        int res = -1e9;
        process(u, v, [&](int l, int r) { res = max(res, tree->query(l, r)); });
        return res;
    }
    int querySubtree(int v) {  // modifySubtree is similar
        return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
    }
};
