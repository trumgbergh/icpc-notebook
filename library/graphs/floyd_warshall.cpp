#include <bits/stdc++.h>
using namespace std;
const long long inf = 1LL << 62;
void floydWarshall(vector<vector<long long>>& m) {
    int n = (int)m.size();
    for (int i = 0; i < n; i++) m[i][i] = min(m[i][i], 0LL);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (m[i][k] != inf && m[k][j] != inf) {
                    auto newDist = max(m[i][k] + m[k][j], -inf);
                    m[i][j] = min(m[i][j], newDist);
                }
            }
        }
    }
    for (int k = 0; k < n; k++) {
        if (m[k][k] >= 0) continue;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
            }
        }
    }
}
