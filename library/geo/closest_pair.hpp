#include "point.hpp"
#include <bits/stdc++.h>
using namespace std;

// Squared distance between the closest pair of points. Mutates a copy of pts
// (sorts it); pass by value.
template <typename T>
T closestPairSq(vector<Point<T>> pts) {
    int n = pts.size();
    sort(pts.begin(), pts.end(),
         [](const Point<T>& a, const Point<T>& b) { return a.x < b.x; });
    function<T(int, int)> rec = [&](int lo, int hi) -> T {
        if (hi - lo <= 1) return numeric_limits<T>::max();
        int mid = (lo + hi) / 2;
        T midX = pts[mid].x;
        T d = min(rec(lo, mid), rec(mid, hi));
        inplace_merge(
            pts.begin() + lo, pts.begin() + mid, pts.begin() + hi,
            [](const Point<T>& a, const Point<T>& b) { return a.y < b.y; });
        vector<Point<T>> strip;
        for (int i = lo; i < hi; i++) {
            T dx = pts[i].x - midX;
            if (dx * dx < d) strip.push_back(pts[i]);
        }
        for (int i = 0; i < (int)strip.size(); i++) {
            for (int j = i + 1; j < (int)strip.size(); j++) {
                T dy = strip[j].y - strip[i].y;
                if (dy * dy >= d) break;
                d = min(d, (strip[i] - strip[j]).abs2());
            }
        }
        return d;
    };
    return rec(0, n);
}
