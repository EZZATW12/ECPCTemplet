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

int segLineRelation(pt a, pt b, pt c, pt d) {
    T p = orient(c, d, a);
    T q = orient(c, d, b);
    if (sgn(p) == 0 && sgn(q) == 0) return 2;
    else if (p * q < 0) return 1;
    else return 0;
}

/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses division)
 * Requirements: Segment and line must not be collinear.
 */
bool segLineIntersection(pt a, pt b, pt c, pt d, pt &ans) {
    int k = segLineRelation(a, b, c, d);
    assert(k != 2);
    if (k) {
        T d_val = cross(b - a, d - c);
        if (sgn(d_val) != 0) {
            ans = a + (b - a) * (cross(c - a, d - c) / d_val);
        }
    }
    return k;
}

