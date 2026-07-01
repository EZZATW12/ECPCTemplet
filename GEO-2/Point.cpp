#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;

const T EPS = 1e-9;
const T PI = acos(-1.0);

#define X real()
#define Y imag()

// Returns 1 if positive, -1 if negative, 0 if strictly zero (within EPS)
int sgn(T val) {
    return (val > EPS) - (val < -EPS);
}

// --- BASIC VECTOR MATH ---
T dot(pt v, pt w) { return (conj(v) * w).real(); }
T cross(pt v, pt w) { return (conj(v) * w).imag(); }
T sq(pt p) { return dot(p, p); }

// Orientation: > 0 (left turn / CCW), < 0 (right turn / CW), == 0 (collinear)
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
bool isPerp(pt v, pt w) { return fabs(dot(v, w)) < EPS; }
pt prep(pt p) { return {-p.Y, p.X}; }

// --- TRANSFORMATIONS ---
pt translate(pt v, pt p) { return p + v; }
pt scale(pt c, T factor, pt p) { return c + (p - c) * factor; }
pt rot(pt p, pt c, T a) { return c + (p - c) * polar((T) 1.0, a); }
pt perp(pt p) { return {-p.Y, p.X}; } // 90 degree CCW rotation

// --- ANGLES ---
T angle(pt v, pt w) {
    return acos(clamp(dot(v, w) / abs(v) / abs(w), (T)-1.0, (T)1.0));
}
T orientedAngle(pt a, pt b, pt c) {
    T ampli = angle(b - a, c - a);
    return orient(a, b, c) > 0 ? ampli : 2 * PI - ampli;
}
T angleTravelled(pt a, pt b, pt c) {
    T ampli = angle(b - a, c - a);
    return orient(a, b, c) > 0 ? ampli : -ampli;
}
bool inAngle(pt a, pt b, pt c, pt p) {
    T abp = orient(a, b, p), acp = orient(a, c, p), abc = orient(a, b, c);
    if (abc < 0) swap(abp, acp);
    return (abp >= 0 && acp <= 0) ^ (abc < 0);
}