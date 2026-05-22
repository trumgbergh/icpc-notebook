#include <bits/stdc++.h>
template <typename T>
// Simple primality test
bool isPrime(T x) {
    for (T d = 2; d * d <= x; d++) {
        if (x % d == 0) return false;
    }
    return true;
}
