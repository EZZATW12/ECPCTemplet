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
 * Floating Point: Yes (uses fabs, EPS, and division)
 * Requirements: Rays must not be collinear.
 */
bool rayRayIntersection(pt as, pt ad, pt bs, pt bd) {
    T dx = bs.X - as.X, dy = bs.Y - as.Y;
    T det = bd.X * ad.Y - bd.Y * ad.X;
    if (fabs(det) < EPS) return 0;
    T u = (dy * bd.X - dx * bd.Y) / det;
    T v = (dy * ad.X - dx * ad.Y) / det;
    if (sgn(u) >= 0 && sgn(v) >= 0) return 1;
    else return 0;
}

