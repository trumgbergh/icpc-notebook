#include <bits/stdc++.h>
using namespace std;

const int M = 58;  // TODO: BLOCK SIZE
struct Info {
    int l = 0, r = 0, t = 0, i = 0;
    friend constexpr bool operator<(const Info& a, const Info& b) {
        if (a.l / M != b.l / M) {
            return a.l / M < b.l / M;
        }
        if (a.r / M != b.r / M) {
            return a.r / M < b.r / M;
        }
        return a.t < b.t;
    }
};

/*
vector<tuple<int, int, int, int>> qry;
vector<int> ans(qry.size());
for (auto [x, y, t, i] : qry) {
    while (l < x) del(l++);
    while (l > x) add(--l);
    while (r < y) add(++r);
    while (r > y) del(r--);
    while (cur < t) modify(x, y, cur++);
    while (cur > t) modify(x, y, --cur);
    ans[i] = query();
}
*/
