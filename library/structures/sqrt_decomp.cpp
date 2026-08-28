#include <bits/stdc++.h>
using namespace std;
struct SqrtDecomp {
    int n, blockSize, numBlocks;
    vector<int64_t> a, blockSum, blockLazy;

    SqrtDecomp(vector<int64_t>& a_) : n(a_.size()), a(a_) {
        blockSize = max(1, (int)sqrt(n));
        numBlocks = (n + blockSize - 1) / blockSize;
        blockSum.assign(numBlocks, 0);
        blockLazy.assign(numBlocks, 0);
        for (int i = 0; i < n; i++) blockSum[i / blockSize] += a[i];
    }

    void update(int l, int r, int64_t val) {  // a[i] += val for l <= i < r
        for (int i = l; i < r;) {
            int b = i / blockSize;
            int blockEnd = min(r, (b + 1) * blockSize);
            if (i == b * blockSize && blockEnd == (b + 1) * blockSize) {
                blockLazy[b] += val;
                blockSum[b] += val * blockSize;
                i = blockEnd;
            } else {
                a[i] += val;
                blockSum[b] += val;
                i++;
            }
        }
    }

    int64_t query(int l, int r) {  // sum of a[i] for l <= i < r
        int64_t res = 0;
        for (int i = l; i < r;) {
            int b = i / blockSize;
            int blockEnd = min(r, (b + 1) * blockSize);
            if (i == b * blockSize && blockEnd == (b + 1) * blockSize) {
                res += blockSum[b];
                i = blockEnd;
            } else {
                res += a[i] + blockLazy[b];
                i++;
            }
        }
        return res;
    }
};
