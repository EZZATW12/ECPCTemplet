#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;

const T EPS = 1e-9;
const T PI = acos(-1.0);

#define X real()
#define Y imag()

/**
 * Returns 1 if val > EPS, -1 if val < -EPS, and 0 if strictly zero (within EPS).
 */
int sgn(T val) {
    return (val > EPS) - (val < -EPS);
}

// --- BASIC VECTOR MATH ---

/**
 * Computes dot product of 2D vectors v and w: v.X * w.X + v.Y * w.Y
 */
T dot(pt v, pt w) { return (conj(v) * w).real(); }

/**
 * Computes 2D cross product of vectors v and w: v.X * w.Y - v.Y * w.X
 * Positive if w is counter-clockwise (left) of v.
 */
T cross(pt v, pt w) { return (conj(v) * w).imag(); }

/**
 * Computes squared magnitude of vector p: |p|^2 = p.X^2 + p.Y^2
 */
T sq(pt p) { return dot(p, p); }

/**
 * Orientation of triple (a, b, c): cross product of (b - a) and (c - a)
 * Returns > 0 for CCW (left turn), < 0 for CW (right turn), == 0 for collinear points.
 */
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

/**
 * Checks if vectors v and w are perpendicular (|dot(v, w)| < EPS).
 */
bool isPerp(pt v, pt w) { return fabs(dot(v, w)) < EPS; }

/**
 * Returns 90-degree counter-clockwise perpendicular vector (-p.Y, p.X).
 */
pt prep(pt p) { return {-p.Y, p.X}; }

/**
 * Returns 90-degree counter-clockwise perpendicular vector (-p.Y, p.X).
 */
pt perp(pt p) { return {-p.Y, p.X}; }

// --- TRANSFORMATIONS ---

/**
 * Translates point p by translation vector v.
 */
pt translate(pt v, pt p) { return p + v; }

/**
 * Scales point p relative to center c by scaling factor.
 */
pt scale(pt c, T factor, pt p) { return c + (p - c) * factor; }

/**
 * Rotates point p counter-clockwise around center c by angle a (in radians).
 */
pt rot(pt p, pt c, T a) { return c + (p - c) * polar((T) 1.0, a); }

// --- ANGLES ---

/**
 * Unoriented angle between vectors v and w in radians, range [0, PI].
 */
T angle(pt v, pt w) {
    return acos(clamp(dot(v, w) / abs(v) / abs(w), (T)-1.0, (T)1.0));
}

/**
 * Oriented angle angle(BAC) around vertex a in radians, range [0, 2*PI).
 */
T orientedAngle(pt a, pt b, pt c) {
    T ampli = angle(b - a, c - a);
    return orient(a, b, c) > 0 ? ampli : 2 * PI - ampli;
}

/**
 * Signed angle turned moving from vector (b - a) to (c - a).
 * Positive for CCW turn, negative for CW turn.
 */
T angleTravelled(pt a, pt b, pt c) {
    T ampli = angle(b - a, c - a);
    return orient(a, b, c) > 0 ? ampli : -ampli;
}

/**
 * Checks if point p lies inside the angular region defined by angle BAC.
 */
bool inAngle(pt a, pt b, pt c, pt p) {
    T abp = orient(a, b, p), acp = orient(a, c, p), abc = orient(a, b, c);
    if (abc < 0) swap(abp, acp);
    return (abp >= 0 && acp <= 0) ^ (abc < 0);
}
