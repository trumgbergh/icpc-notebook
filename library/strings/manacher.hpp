#include <bits/stdc++.h>
using namespace std;

// Returns vector p of size n, where p[i] is the radius
// of the longest odd palindrome centered at s[i].
// Total length of palindrome centered at s[i] is 2 * p[i] - 1.
vector<int> manacher_odd(string s) {
    int n = (int)s.length();
    s = "$" + s + "^";  // Out-of-bounds guard
    vector<int> p(n + 2);
    int l = 0;
    int r = 1;  // [l, r]: Furthest reaching palindrome boundary.
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            p[i] = min(r - i, p[l + (r - i)]);
        }
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
    ;
}

// Interleaves '#' to handle even palindromes.
// Returns a vector of size 2n + 1.
// Even indicies (0, 2, 4...): Centers at '#"
// Odd indicies(1, 3, 5...): Centers at original characters.
// Palindrome length in original string = res[i] - 1
vector<int> manacher(string s) {
    string t;
    for (auto c : s) {
        t += string("#") + c;
    }

    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}
