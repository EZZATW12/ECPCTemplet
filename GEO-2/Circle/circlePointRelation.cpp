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
 * Floating Point: Yes (uses abs for distance, sgn)
 * Requirements: None
 */
// 0 if outside, 1 if on circumference, 2 if inside circle
int circlePointRelation(pt p, T r, pt b) {
    T d = abs(p - b);
    if (sgn(d - r) < 0) return 2;
    if (sgn(d - r) == 0) return 1;
    return 0;
}

