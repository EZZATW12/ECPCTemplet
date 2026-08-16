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

pt proj(pt a, pt b, pt p) {
    pt v = b - a;
    return a + v * dot(v, p - a) / sq(v);
}

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

/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses division, sgn, abs)
 * Requirements: None
 */
// requires circleCircleInter from Circle.cpp
// returns two circle c1, c2 through points a, b and of radius r
// 0 if there is no such circle, 1 if one circle, 2 if two circle
int getCircle(pt a, pt b, T r, pt &c1, pt &c2) {
    int t = circleCircleInter(a, r, b, r, c1, c2);
    if (t == -1) t = 0; // if infinite intersections, return 0 for this context
    return t;
}

// returns two circle c1, c2 which is tangent to line u,  goes through
// point q and has radius r1; 0 for no circle, 1 if c1 = c2 , 2 if c1 != c2
int getCircle(line u, pt q, T r1, pt &c1, pt &c2) {
    T d = u.dist(q);
    if (sgn(d - r1 * 2.0) > 0) return 0;
    if (sgn(d) == 0) {
        c1 = q + perp(u.v) / abs(u.v) * r1;
        c2 = q - perp(u.v) / abs(u.v) * r1;
        return 2;
    }
    line u1 = u.shiftLeft(r1);
    line u2 = u.shiftLeft(-r1);
    pt p1_tmp, p2_tmp;
    int t = circleLineInter(q, r1, u1.v + u1.proj(pt(0,0)), u1.proj(pt(0,0)), p1_tmp, p2_tmp); // we need two points on u1
    if (!t) {
        t = circleLineInter(q, r1, u2.v + u2.proj(pt(0,0)), u2.proj(pt(0,0)), p1_tmp, p2_tmp);
    }
    c1 = p1_tmp;
    if (t == 1) {
        c2 = c1;
        return 1;
    }
    c2 = p2_tmp;
    return 2;
}

