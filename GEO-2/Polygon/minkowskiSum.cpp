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

void reorderPolygon(vector<pt> &p) {
    int pos = 0;
    for (int i = 1; i < p.size(); i++) {
        if (p[i].Y < p[pos].Y || (sgn(p[i].Y - p[pos].Y) == 0 && p[i].X < p[pos].X)) pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

/**
 * Time Complexity: O(N + M)
 * Floating Point: No (integer-safe if pt is integer; uses cross and sgn)
 * Requirements: Both polygons must be convex.
 */
// a and b are convex polygons
// returns a convex hull of their minkowski sum
// min(a.size(), b.size()) >= 2
// https://cp-algorithms.com/geometry/minkowski.html
vector<pt> minkowskiSum(vector<pt> a, vector<pt> b) {
    reorderPolygon(a); reorderPolygon(b);
    int n = a.size(), m = b.size();
    int i = 0, j = 0;
    a.push_back(a[0]); a.push_back(a[1]);
    b.push_back(b[0]); b.push_back(b[1]);
    vector<pt> c;
    while (i < n || j < m) {
        c.push_back(a[i] + b[j]);
        T p_val = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
        if (sgn(p_val) >= 0) ++i;
        if (sgn(p_val) <= 0) ++j;
    }
    return c;
}

