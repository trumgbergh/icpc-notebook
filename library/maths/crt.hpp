#include "euclid.h"

// Chinese Remainder Theorem: finds $x$ such that $x \equiv a \pmod m$ and
// $x \equiv b \pmod n$. Returns $(x, \text{lcm}(m,n))$, or $(-1,-1)$ if no
// solution exists ($m, n$ need not be coprime).
pair<int64_t, int64_t> crt(int64_t a, int64_t m, int64_t b, int64_t n) {
    if (n > m) swap(a, b), swap(m, n);
    int64_t x, y, g = euclid(m, n, x, y);
    if ((b - a) % g) return {-1, -1};
    int64_t mod = n / g;
    int64_t tmp = (b - a) / g % mod * x % mod;
    if (tmp < 0) tmp += mod;
    return {a + tmp * m, m / g * n};
}
