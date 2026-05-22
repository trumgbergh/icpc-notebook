#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int a, b, cost;
};

int n, m, s;
vector<Edge> edges;
const int INF = 1e9 + 7;
void bellman_ford() {
    vector<int> d(n, INF);
    d[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (Edge e : edges) {
            if (d[e.a] < INF) d[e.b] = min(d[e.b], d[e.a] + e.cost);
        }
    }
}
