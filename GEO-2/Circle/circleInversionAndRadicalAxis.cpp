/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses division, sq, sqrt, perp)
 * Requirements: Center must not be equal to point p for inversion. Circles must not be concentric for radical axis.
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
pt perp(pt p) { return {-p.Y, p.X}; }

struct line {
    pt v; T c;
    line(pt v, T c) : v(v), c(c) {}
    line(pt p, pt q) { v = q - p; c = cross(v, p); }
};

// Power of point p with respect to circle (c, r): d^2 - r^2
// > 0 outside, == 0 on circle, < 0 inside
T powerOfPoint(pt center, T r, pt p) {
    return sq(p - center) - r * r;
}

// Inversion of point p across circle centered at 'c' with radius 'r'
// p' = c + (p - c) * r^2 / |p - c|^2
pt invertPoint(pt c, T r, pt p) {
    assert(sgn(abs(p - c)) != 0);
    return c + (p - c) * (r * r / sq(p - c));
}

// Inversion of a circle (c, r) across another circle (inv_c, inv_r)
// Returns pair<center, radius> of the inverted circle (assuming circle does not pass through inv_c)
pair<pt, T> invertCircle(pt inv_c, T inv_r, pt c, T r) {
    T d = abs(c - inv_c);
    assert(sgn(d - r) != 0); // circle must not pass through inversion center
    pt p1 = c + (c - inv_c) / d * r;
    pt p2 = c - (c - inv_c) / d * r;
    pt p1_inv = invertPoint(inv_c, inv_r, p1);
    pt p2_inv = invertPoint(inv_c, inv_r, p2);
    pt new_c = (p1_inv + p2_inv) / (T)2.0;
    T new_r = abs(p1_inv - p2_inv) / (T)2.0;
    return {new_c, new_r};
}

// Radical Axis of two circles (c1, r1) and (c2, r2)
// Line of points p having equal power wrt both circles: sq(p - c1) - r1^2 = sq(p - c2) - r2^2
line radicalAxis(pt c1, T r1, pt c2, T r2) {
    assert(c1 != c2);
    T d2 = sq(c2 - c1);
    T d = sqrt(d2);
    // Distance from c1 to foot of perpendicular from radical axis onto c1-c2 line
    T x = (d2 + r1 * r1 - r2 * r2) / (2.0 * d);
    pt foot = c1 + (c2 - c1) / d * x;
    return line(foot, foot + perp(c2 - c1));
}
