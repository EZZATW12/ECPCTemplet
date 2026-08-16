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

bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (sgn(d) == 0) return false; 
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
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
 * Time Complexity: Expected O(N)
 * Floating Point: Yes (uses division, abs, perp, sgn)
 * Requirements: None
 */
// given n points, find the minimum enclosing circle of the points
// call convex_hull() before this for faster solution
// expected O(n)
pair<pt, T> minimumEnclosingCircle(vector<pt> &p) {
    random_shuffle(p.begin(), p.end());
    int n = p.size();
    pt c = p[0];
    T r = 0;
    for (int i = 1; i < n; i++) {
        if (sgn(abs(c - p[i]) - r) > 0) {
            c = p[i];
            r = 0;
            for (int j = 0; j < i; j++) {
                if (sgn(abs(c - p[j]) - r) > 0) {
                    c = (p[i] + p[j]) / (T)2.0;
                    r = abs(p[i] - p[j]) / 2.0;
                    for (int k = 0; k < j; k++) {
                        if (sgn(abs(c - p[k]) - r) > 0) {
                            pt temp1, temp2;
                            circleCircleInter(p[i], r, p[j], r, temp1, temp2); // this would be getCircle
                            // wait, circumcircle of triangle is easier
                            pt b = (p[i] + p[j]) / (T)2.0;
                            pt c_mid = (p[i] + p[k]) / (T)2.0;
                            line l1(b, b + perp(p[i] - p[j]));
                            line l2(c_mid, c_mid + perp(p[i] - p[k]));
                            inter(l1, l2, c);
                            r = abs(p[i] - c);
                        }
                    }
                }
            }
        }
    }
    return {c, r};
}

