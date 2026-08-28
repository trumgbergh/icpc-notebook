#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int a, b, cost;
};

const int64_t INF = (int64_t)1e18;

// dist[v] = INF if v is unreachable from s, -INF if v is reachable through a
// negative-weight cycle. Assumes V^2 * max|w_i| < 2^63.
vector<int64_t> bellmanFord(int n, int s, vector<Edge>& edges) {
    vector<int64_t> d(n, INF);
    d[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (Edge& e : edges) {
            if (d[e.a] < INF) d[e.b] = min(d[e.b], d[e.a] + (int64_t)e.cost);
        }
    }
    for (int i = 0; i < n; i++) {
        for (Edge& e : edges) {
            if (d[e.a] == -INF && d[e.b] != -INF) {
                d[e.b] = -INF;
            } else if (d[e.a] < INF && d[e.a] + (int64_t)e.cost < d[e.b]) {
                d[e.b] = -INF;
            }
        }
    }
    return d;
}
