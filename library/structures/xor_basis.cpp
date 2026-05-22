#include <bits/stdc++.h>
using namespace std;
struct XORBasis {
    int bits;
    int size = 0;
    vector<long long> basis;

    // Pass 30 for standard integers, 62 for long long
    XORBasis(int max_bits = 62) : bits(max_bits) { basis.resize(bits, 0); }

    // Returns true if x was successfully inserted (linearly independent)
    bool insert(long long x) {
        for (int i = bits - 1; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = x;
                    size++;
                    return true;
                }
                x ^= basis[i];
            }
        }
        return false;  // x can already be represented by the basis
    }

    // Returns the maximum possible XOR sum using a subset
    long long max_xor() {
        long long res = 0;
        for (int i = bits - 1; i >= 0; i--) {
            if ((res ^ basis[i]) > res) {
                res ^= basis[i];
            }
        }
        return res;
    }

    // Returns the minimum possible non-zero XOR sum
    long long min_xor() {
        for (int i = 0; i < bits; i++) {
            if (basis[i]) return basis[i];
        }
        return 0;
    }

    // Checks if x can be represented as a XOR combination of elements
    bool can_represent(long long x) {
        for (int i = bits - 1; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (!basis[i]) return false;
                x ^= basis[i];
            }
        }
        return true;
    }

    // Returns the number of distinct subset XOR values possible: 2^size
    long long count_distinct() { return 1LL << size; }
};
