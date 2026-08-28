#include <bits/stdc++.h>
using namespace std;
const int64_t INF = LLONG_MAX;
bool Q = false;

struct Line {
    int64_t k;
    int64_t m;
    mutable int64_t p;

    bool operator<(const Line& o) const {
        if (Q) return p < o.p;
        return k < o.k;
    }
};

struct LineContainer : multiset<Line, less<>> {
    int64_t div(int64_t a, int64_t b) { return a / b - ((a ^ b) < 0 && a % b); }

    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = INF;
            return false;
        }

        if (x->k == y->k) {
            if (x->m > y->m)
                x->p = INF;
            else
                x->p = -INF;
        } else
            x->p = div(y->m - x->m, x->k - y->k);

        return x->p >= y->p;
    }

    void add(int64_t k, int64_t m) {
        auto z = insert({-k, -m, 0});
        auto y = z++;
        auto x = y;

        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));

        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }

    // Query the max of k * x + m over all inserted lines.
    int64_t query(int64_t x) {
        assert(!empty());

        Q = true;
        auto l = *lower_bound({0, 0, x});
        Q = false;

        return -(l.k * x + l.m);
    }
};
