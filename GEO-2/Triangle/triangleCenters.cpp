
/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses sqrt, division, dot, cross, perp)
 * Requirements: Points A, B, C must form a non-degenerate triangle.
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

T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
pt prep(pt p) { return {-p.Y, p.X}; }
pt perp(pt p) { return {-p.Y, p.X}; }

struct line {
    pt v; T c;
    line(pt v, T c) : v(v), c(c) {}
    line(pt p, pt q) { v = q - p; c = cross(v, p); }
};

bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (sgn(d) == 0) return false; 
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

// Centroid (G): Intersection of medians = (A + B + C) / 3
pt centroid(pt a, pt b, pt c) {
    return (a + b + c) / (T)3.0;
}

// Incenter (I): Intersection of angle bisectors = (a*A + b*B + c*C) / (a + b + c)
pt incenter(pt a, pt b, pt c) {
    T la = abs(b - c);
    T lb = abs(c - a);
    T lc = abs(a - b);
    return (a * la + b * lb + c * lc) / (la + lb + lc);
}

// Incircle Radius (r) = Area / semiperimeter
T incircleRadius(pt a, pt b, pt c) {
    T la = abs(b - c), lb = abs(c - a), lc = abs(a - b);
    T s = (la + lb + lc) / 2.0;
    T area = abs(cross(b - a, c - a)) / 2.0;
    return area / s;
}

// Circumcenter (O): Intersection of perpendicular bisectors
pt circumcenter(pt a, pt b, pt c) {
    pt m1 = (a + b) / (T)2.0;
    pt m2 = (a + c) / (T)2.0;
    line l1(m1, m1 + perp(b - a));
    line l2(m2, m2 + perp(c - a));
    pt res;
    inter(l1, l2, res);
    return res;
}

// Circumcircle Radius (R) = (a * b * c) / (4 * Area)
T circumcircleRadius(pt a, pt b, pt c) {
    T la = abs(b - c), lb = abs(c - a), lc = abs(a - b);
    T area = abs(cross(b - a, c - a)) / 2.0;
    return (la * lb * lc) / (4.0 * area);
}

// Orthocenter (H): Intersection of altitudes = A + B + C - 2*O
pt orthocenter(pt a, pt b, pt c) {
    return a + b + c - (T)2.0 * circumcenter(a, b, c);
}

// Excenters (I_a, I_b, I_c): Opposite to vertices A, B, C respectively
pt excenterA(pt a, pt b, pt c) {
    T la = abs(b - c), lb = abs(c - a), lc = abs(a - b);
    return (-a * la + b * lb + c * lc) / (-la + lb + lc);
}

pt excenterB(pt a, pt b, pt c) {
    T la = abs(b - c), lb = abs(c - a), lc = abs(a - b);
    return (a * la - b * lb + c * lc) / (la - lb + lc);
}

pt excenterC(pt a, pt b, pt c) {
    T la = abs(b - c), lb = abs(c - a), lc = abs(a - b);
    return (a * la + b * lb - c * lc) / (la + lb - lc);
}

// Excircle Radii (r_a, r_b, r_c): r_a = Area / (s - a)
T excircleRadiusA(pt a, pt b, pt c) {
    T la = abs(b - c), lb = abs(c - a), lc = abs(a - b);
    T s = (la + lb + lc) / 2.0;
    T area = abs(cross(b - a, c - a)) / 2.0;
    return area / (s - la);
}

// Nine-point Center (N): Midpoint between Circumcenter (O) and Orthocenter (H)
pt ninePointCenter(pt a, pt b, pt c) {
    pt o = circumcenter(a, b, c);
    pt h = orthocenter(a, b, c);
    return (o + h) / (T)2.0;
}

// Nine-point Circle Radius = R / 2
T ninePointRadius(pt a, pt b, pt c) {
    return circumcircleRadius(a, b, c) / 2.0;
}
