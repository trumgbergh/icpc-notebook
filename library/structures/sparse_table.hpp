#include <bits/stdc++.h>
using namespace std;
template <class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        int n = (int)V.size();
        for (int pw = 1, k = 1; pw * 2 <= n; pw *= 2, ++k) {
            jmp.emplace_back(n - pw * 2 + 1);
            for (int j = 0; j < (int)jmp[k].size(); j++) {
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
        }
    }
    T query(int a, int b) {
        assert(a < b);  // or return inf if a == b
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
