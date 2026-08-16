/**
 * Time Complexity: O(N log N)
 * Floating Point: Yes (uses sqrt and abs to calculate minimum Euclidean distance)
 * Requirements: None
 */
#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;

const T EPS = 1e-9;
const T PI = acos(-1.0);

#define X real()
#define Y imag()

int sgn(T val) {
    return (val > EPS) - (val < -EPS);
}

T dot(pt v, pt w) { return (conj(v) * w).real(); }
T cross(pt v, pt w) { return (conj(v) * w).imag(); }
T sq(pt p) { return dot(p, p); }

// Returns {p1, p2} that are closest, and distance in min_dist out-parameter
pair<pt, pt> closestPairOfPoints(vector<pt> pts, T &min_dist) {
    int n = pts.size();
    assert(n >= 2);
    sort(pts.begin(), pts.end(), [](pt a, pt b) {
        if (abs(a.X - b.X) > EPS) return a.X < b.X;
        return a.Y < b.Y;
    });

    T d2 = 1e30;
    pair<pt, pt> best_pair;

    auto update = [&](pt p1, pt p2) {
        T dist_sq = sq(p1 - p2);
        if (dist_sq < d2) {
            d2 = dist_sq;
            best_pair = {p1, p2};
        }
    };

    auto cmpy = [](pt a, pt b) { return a.Y < b.Y; };

    function<void(int, int)> solve = [&](int l, int r) {
        if (r - l <= 3) {
            for (int i = l; i <= r; ++i) {
                for (int j = i + 1; j <= r; ++j) {
                    update(pts[i], pts[j]);
                }
            }
            sort(pts.begin() + l, pts.begin() + r + 1, cmpy);
            return;
        }

        int mid = (l + r) / 2;
        T midx = pts[mid].X;
        solve(l, mid);
        solve(mid + 1, r);

        vector<pt> temp(r - l + 1);
        merge(pts.begin() + l, pts.begin() + mid + 1, pts.begin() + mid + 1, pts.begin() + r + 1, temp.begin(), cmpy);
        copy(temp.begin(), temp.end(), pts.begin() + l);

        vector<pt> strip;
        for (int i = l; i <= r; ++i) {
            if (sq(pts[i].X - midx) < d2) {
                for (int j = (int)strip.size() - 1; j >= 0 && sq(pts[i].Y - strip[j].Y) < d2; --j) {
                    update(pts[i], strip[j]);
                }
                strip.push_back(pts[i]);
            }
        }
    };

    solve(0, n - 1);
    min_dist = sqrt(d2);
    return best_pair;
}
