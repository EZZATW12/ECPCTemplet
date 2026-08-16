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
 * Floating Point: Yes (uses division, sqrt, sgn)
 * Requirements: rp != rq
 */
// returns the center and radius of the circle such that for all points w on the circumference of the circle
// dist(w, a) : dist(w, b) = rp : rq
// rp != rq
// https://en.wikipedia.org/wiki/Circles_of_Apollonius
pair<pt, T> getApolloniusCircle(pt p, pt q, T rp, T rq) {
    rq *= rq;
    rp *= rp;
    T a = rq - rp;
    assert(sgn(a));
    T g = rq * p.X - rp * q.X; g /= a;
    T h = rq * p.Y - rp * q.Y; h /= a;
    T c = rq * p.X * p.X - rp * q.X * q.X + rq * p.Y * p.Y - rp * q.Y * q.Y;
    c /= a;
    pt o(g, h);
    T r = g * g + h * h - c;
    r = sqrt(r);
    return {o, r};
}

