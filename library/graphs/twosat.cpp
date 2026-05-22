#include <bits/stdc++.h>
using namespace std;

struct TwoSat {
    int N;
    vector<vector<int>> gr;
    vector<int> values;  // 0 = false, 1 = true
    TwoSat(int n = 0) : N(n), gr(2 * n) {}
    int addVar() {
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }
    void orClause(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f ^ 1].emplace_back(j);
        gr[j ^ 1].emplace_back(f);
    }
    void must(int x) { orClause(x, x); }
    void xorClause(int f, int j) {
        orClause(f, j);
        orClause(~f, ~j);
    }
    void nandClause(int f, int j) {
        orClause(f, j);
        orClause(~f, ~j);
    }
    void implies(int f, int j) { orClause(~f, j); }
    void atMostOne(const vector<int>& li) {
        if ((int)li.size() <= 1) return;
        int cur = ~li[0];
        for (int i = 2; i < (int)li.size(); i++) {
            int next = addVar();
            orClause(cur, ~li[i]);
            orClause(cur, next);
            orClause(~li[i], next);
            cur = ~next;
        }
        orClause(cur, ~li[1]);
    }
    vector<int> val, comp, z;
    int time = 0;
    int dfs(int i) {
        int low = val[i] = ++time;
        int x;
        z.emplace_back(i);
        for (int e : gr[i])
            if (!comp[e]) low = min(low, val[e] ?: dfs(e));
        if (low == val[i]) do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1) values[x >> 1] = !(x & 1);
            } while (x != i);
        return val[i] = low;
    }
    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for (int i = 0; i < 2 * N; i++)
            if (!comp[i]) dfs(i);
        for (int i = 0; i < N; i++)
            if (comp[2 * i] == comp[2 * i + 1]) return 0;
        return 1;
    }
};
