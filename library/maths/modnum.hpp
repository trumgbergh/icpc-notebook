#include "euclid.h"

const i64 mod = 17;  // change to something else
struct Mod {
    i64 x;
    Mod(i64 xx) : x(xx) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
    Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
    Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
    Mod operator/(Mod b) { return *this * invert(b); }
    Mod invert(Mod a) {
        i64 x, y, g = euclid(a.x, mod, x, y);
        assert(g == 1);
        return Mod((x + mod) % mod);
    }
    Mod operator^(i64 e) {
        if (!e) return Mod(1);
        Mod r = *this ^ (e / 2);
        r = r * r;
        return e & 1 ? *this * r : r;
    }
};
