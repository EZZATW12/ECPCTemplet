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

struct line {
    pt v; T c;

    line(pt v, T c) : v(v), c(c) {}
    line(T a, T b, T _c) { v = {b, -a}; c = _c; }
    line(pt p, pt q) { v = q - p; c = cross(v, p); }

    T side(pt p) { return cross(v, p) - c; }
    T dist(pt p) { return abs(side(p)) / abs(v); }
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
    line translate(pt t) { return {v, c + cross(v, t)}; }
    double sqDist(pt p) { return side(p) * side(p) / sq(v); }
    line prepThrought(pt p) { return {p, p + prep(v)}; }
    line shiftLeft(T dist) { return {v, c + dist * abs(v)}; }
    pt proj(pt p) { return p - prep(v) * side(p) / sq(v); }
    pt refl(pt p) { return p - prep(v) * (T) 2.0 * side(p) / sq(v); }
};

T distFromPointToRay(pt a, pt b, pt c) {
    b = a + b;
    T r = dot(c - a, b - a);
    if (r < 0.0) return abs(c - a);
    
    line l(a, b);
    return l.dist(c);
}

bool rayRayIntersection(pt as, pt ad, pt bs, pt bd) {
    T dx = bs.X - as.X, dy = bs.Y - as.Y;
    T det = bd.X * ad.Y - bd.Y * ad.X;
    if (fabs(det) < EPS) return 0;
    T u = (dy * bd.X - dx * bd.Y) / det;
    T v = (dy * ad.X - dx * ad.Y) / det;
    if (sgn(u) >= 0 && sgn(v) >= 0) return 1;
    else return 0;
}

/**
 * Time Complexity: O(1)
 * Floating Point: Yes (returns 0.0, calls floating-point dependent functions)
 * Requirements: None
 */
T rayRayDistance(pt as, pt ad, pt bs, pt bd) {
    if (rayRayIntersection(as, ad, bs, bd)) return 0.0;
    T ans = distFromPointToRay(as, ad, bs);
    ans = min(ans, distFromPointToRay(bs, bd, as));
    return ans;
}

