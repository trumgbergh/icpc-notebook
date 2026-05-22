#include <bits/stdc++.h>
typedef int64_t i64;
i64 euclid(i64 a, i64 b, i64 &x, i64 &y) {
    if (!b) return x = 1, y = 0, a;
    i64 d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}
