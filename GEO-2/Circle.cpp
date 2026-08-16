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
 * Orthogonal projection of point p onto line through points a and b.
 */
pt proj(pt a, pt b, pt p) {
    pt v = b - a;
    return a + v * dot(v, p - a) / sq(v);
}

/**
 * Intersection of line through points a and b with circle centered at c with radius r.
 * Outputs intersection points in p1 and p2.
 * Returns: 0 if no intersection, 1 if line is tangent, 2 if line intersects at 2 points.
 */
int circleLineInter(pt c, T r, pt a, pt b, pt &p1, pt &p2) {
    pt p = proj(a, b, c); 
    T d = abs(p - c); 

    if (sgn(d - r) > 0) return 0; 
    if (sgn(d - r) == 0) { p1 = p2 = p; return 1; }

    T offset = sqrt(max((T) 0.0, r * r - d * d));
    pt v = (b - a) / abs(b - a); 

    p1 = p + v * offset;
    p2 = p - v * offset;
    return 2;
}

/**
 * Intersection of two circles (c1, r1) and (c2, r2). Outputs intersection points in p1 and p2.
 * Returns: 0 if disjoint/nested, 1 if tangent, 2 if 2 intersection points, -1 if circles are identical.
 */
int circleCircleInter(pt c1, T r1, pt c2, T r2, pt &p1, pt &p2) {
    T d = abs(c2 - c1);

    if (sgn(d - (r1 + r2)) > 0 || sgn(d - abs(r1 - r2)) < 0) return 0;
    if (sgn(d) == 0 && sgn(r1 - r2) == 0) return -1;

    T a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
    T h = sqrt(max((T) 0.0, r1 * r1 - a * a));
    pt p = c1 + (c2 - c1) * (a / d);
    pt perpP = perp(c2 - c1) * (h / d);

    p1 = p + perpP;
    p2 = p - perpP;

    return sgn(h) == 0 ? 1 : 2;
}
