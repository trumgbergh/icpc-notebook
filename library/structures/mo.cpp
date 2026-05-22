#include <bits/stdc++.h>
using namespace std;

int64_t order(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg = -1;
    if (x < hpow) {
        if (y < hpow)
            seg = 0;
        else
            seg = 3;
    } else {
        if (y < hpow)
            seg = 1;
        else
            seg = 2;
    }

    seg = (seg + rotate) & 3;
    int rotateD[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow);
    int ny = y & (y ^ hpow);
    int nrot = (rotate + rotateD[seg]) & 3;
    int64_t sz = 1LL << (2 * pow - 2);
    int64_t ans = seg * sz;
    int64_t add = order(nx, ny, pow - 1, nrot);
    if (seg == 1 || seg == 2)
        ans += add;
    else
        ans += (sz - add - 1);
    return ans;
}

struct Query {
    int l, r, id;
    Query(int l_, int r_, int id_) : l(l_), r(r_), id(id_) {}
    bool operator<(const Query& o) const {
        return order(l, r, 21, 0) < order(o.l, o.r, 21, 0);
    }
};
