#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1e6 + 5;
const int p1 = 31, MOD1 = 1e9 + 7;
const int p2 = 39, MOD2 = 1e9 + 9;
int pow1[MAXLEN], pow2[MAXLEN];
bool is_precomputed = false;

void precompute_pow() {
    pow1[0] = 1;
    pow2[0] = 1;
    for (int i = 1; i < MAXLEN; i++) {
        pow1[i] = (1LL * pow1[i - 1] * p1) % MOD1;
        pow2[i] = (1LL * pow2[i - 1] * p2) % MOD2;
    }
    is_precomputed = true;
}

int modadd(int a, int b, int m) {
    int res = a + b;
    if (res >= m) res -= m;
    return res;
}
int modsub(int a, int b, int m) {
    int res = a - b;
    if (res < 0) res += m;
    return res;
}
int modmul(int a, int b, int m) {
    int64_t res = 1LL * a * b;
    return res % m;
}

struct HashPair {
    int n;
    vector<int> h1, h2;

    HashPair(string& s) : n(s.length()) {
        if (!is_precomputed) precompute_pow();

        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a' + 1;
            h1[i + 1] = modadd(modmul(h1[i], p1, MOD1), c, MOD1);
            h2[i + 1] = modadd(modmul(h2[i], p2, MOD2), c, MOD2);
        }
    }

    pair<int, int> calc(int l, int r) {
        int len = r - l + 1;
        int hash1 = modsub(h1[r], modmul(h1[l - 1], pow1[len], MOD1), MOD1);
        int hash2 = modsub(h2[r], modmul(h2[l - 1], pow2[len], MOD2), MOD2);
        return {hash1, hash2};
    }
};
