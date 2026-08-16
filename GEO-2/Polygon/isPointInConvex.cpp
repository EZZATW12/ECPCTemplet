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
 * Time Complexity: O(log N)
 * Floating Point: No (integer-safe; uses orient and sgn)
 * Requirements: Polygon must be strictly convex.
 */
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int isPointInConvex(const vector<pt> &p, const pt& x) { // O(log n)
    int n = p.size(); assert(n >= 3);
    int a = sgn(orient(p[0], p[1], x)), b = sgn(orient(p[0], p[n - 1], x));
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (sgn(orient(p[0], p[mid], x)) >= 0) l = mid;
        else r = mid;
    }
    int k = sgn(orient(p[l], p[r], x));
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}

