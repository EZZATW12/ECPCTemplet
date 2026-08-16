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
 * Time Complexity: O(1)
 * Floating Point: No (integer safe)
 * Requirements: None
 */
// 0 if do not intersect, 1 if proper intersect, 2 if segment intersect collinear
int segLineRelation(pt a, pt b, pt c, pt d) {
    T p = orient(c, d, a);
    T q = orient(c, d, b);
    if (sgn(p) == 0 && sgn(q) == 0) return 2;
    else if (p * q < 0) return 1;
    else return 0;
}

