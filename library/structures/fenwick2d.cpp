#include "fenwick.cpp"

struct FT2 {
    vector<vector<int>> ys;
    vector<FT> ft;
    FT2(int limx) : ys(limx) {}
    void fakeUpdate(int x, int y) {
        for (; x < (int)ys.size(); x |= x + 1) ys[x].push_back(y);
    }
    void init() {
        for (vector<int>& v : ys)
            sort(v.begin(), v.end()), ft.emplace_back(v.size());
    }
    int ind(int x, int y) {
        return (int)(lower_bound(ys[x].begin(), ys[x].end(), y) -
                     ys[x].begin());
    }
    void update(int x, int y, int64_t dif) {
        for (; x < (int)ys.size(); x |= x + 1) ft[x].update(ind(x, y), dif);
    }
    int64_t query(int x, int y) {
        int64_t sum = 0;
        for (; x; x &= x - 1) sum += ft[x - 1].query(ind(x - 1, y));
        return sum;
    }
};
