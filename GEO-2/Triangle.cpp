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
 * Area of triangle with base b and height h.
 */
long double triangleAreaBH(long double b, long double h) { return b * h / 2; }

/**
 * Area of triangle given side lengths a, b and included angle t (in radians).
 */
long double triangleArea2sidesAngle(long double a, long double b, long double t) {
    return fabs(a * b * sin(t) / 2);
}

/**
 * Area of triangle given two angles t1, t2 (in radians) and included side length s.
 */
long double triangleArea2anglesSide(long double t1, long double t2, long double s) {
    return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}

/**
 * Area of triangle using Heron's formula given side lengths a, b, c.
 */
long double triangleArea3sides(long double a, long double b, long double c) {
    long double s((a + b + c) / 2);
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

/**
 * Area of triangle formed by 3 Cartesian points a, b, c.
 */
long double triangleArea3points(const pt& a, const pt& b, const pt& c) {
    return fabs(cross(a,b) + cross(b,c) + cross(c,a)) / 2;
}
