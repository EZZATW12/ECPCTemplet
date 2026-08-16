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
 * Floating Point: No (integer-safe; uses sgn)
 * Requirements: None
 */
// rotate the polygon such that the (bottom, left)-most point is at the first position
void reorderPolygon(vector<pt> &p) {
    int pos = 0;
    for (int i = 1; i < p.size(); i++) {
        if (p[i].Y < p[pos].Y || (sgn(p[i].Y - p[pos].Y) == 0 && p[i].X < p[pos].X)) pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

