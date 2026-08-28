#include <bits/stdc++.h>
using namespace std;

struct KMP {
    string pattern;
    int n;
    vector<int> pi;
    vector<vector<int>> aut;

    KMP(const string& s = "") {
        if (!s.empty()) init(s);
    }

    void init(const string& s) {
        pattern = s;
        n = s.length();
        pi.clear();
        aut.clear();
    }

    // 1. Builds only the pi array. O(N)
    void build_pi() {
        if (n == 0) return;
        pi.assign(n, 0);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && pattern[i] != pattern[j]) {
                j = pi[j - 1];
            }
            if (pattern[i] == pattern[j]) {
                j++;
            }
            pi[i] = j;
        }
    }

    // 2. Builds the 2D DFA. O(N * ALPHABET_SIZE)
    void build_automaton(int nchar = 26, char base = 'a') {
        if (pi.empty()) build_pi();  // Safety net

        aut.assign(n + 1, vector<int>(nchar, 0));
        for (int state = 0; state <= n; state++) {
            for (int c = 0; c < nchar; c++) {
                if (state > 0 && c != (pattern[state] - base)) {
                    aut[state][c] = aut[pi[state - 1]][c];
                } else {
                    if (state < n && c == (pattern[state] - base)) {
                        aut[state][c] = state + 1;
                    } else {
                        aut[state][c] =
                            (state == 0) ? 0 : aut[pi[state - 1]][c];
                    }
                }
            }
        }
    }
};
