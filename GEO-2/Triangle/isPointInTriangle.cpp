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
 * Floating Point: No (integer-safe, only uses cross product and sign checks)
 * Requirements: None
 */
// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int isPointInTriangle(pt a, pt b, pt c, pt p) {
    if (sgn(cross(b - a, c - a)) < 0) swap(b, c);
    int c1 = sgn(cross(b - a, p - a));
    int c2 = sgn(cross(c - b, p - b));
    int c3 = sgn(cross(a - c, p - c));
    if (c1 < 0 || c2 < 0 || c3 < 0) return 1;
    if (c1 + c2 + c3 != 3) return 0;
    return -1;
}

