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

T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
pt prep(pt p) { return {-p.Y, p.X}; }
pt perp(pt p) { return {-p.Y, p.X}; }

/**
 * Time Complexity: O(N)
 * Floating Point: Yes (uses sqrt to compute final diameter)
 * Requirements: Polygon must be convex. Points must be sorted in CCW order.
 */
// maximum distance from any point on the perimeter to another point on the perimeter
T diameter(const vector<pt> &p) {
    int n = (int)p.size();
    if (n == 1) return 0;
    if (n == 2) return abs(p[0] - p[1]);
    T ans = 0;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) {
            ans = max(ans, sq(p[i] - p[j]));
            j = (j + 1) % n;
        }
        ans = max(ans, sq(p[i] - p[j]));
        i++;
    }
    return sqrt(ans);
}

