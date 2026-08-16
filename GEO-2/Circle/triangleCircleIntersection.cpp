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
 * Floating Point: Yes (uses sqrt, max, abs, acos, division, sq)
 * Requirements: None
 */
// returns the area of the intersection of the circle with center c and radius r
// and the triangle formed by the points c, a, b
T triangleCircleIntersection(pt c, T r, pt a, pt b) {
    T sd1 = sq(c - a), sd2 = sq(c - b);
    if(sd1 > sd2) { swap(a, b); swap(sd1, sd2); }
    T sd = sq(a - b);
    T d1 = sqrt(sd1), d2 = sqrt(sd2), d = sqrt(sd);
    T x = abs(sd2 - sd - sd1) / (2 * d);
    T h = sqrt(max((T)0.0, sd1 - x * x));
    if(r >= d2) return h * d / 2;
    T area = 0;
    if(sd + sd1 < sd2) {
        if(r < d1) area = r * r * (acos(h / d2) - acos(h / d1)) / 2;
        else {
            area = r * r * (acos(h / d2) - acos(h / r)) / 2;
            T y = sqrt(max((T)0.0, r * r - h * h));
            area += h * (y - x) / 2;
        }
    } 
    else {
        if(r < h) area = r * r * (acos(h / d2) + acos(h / d1)) / 2;
        else {
            area += r * r * (acos(h / d2) - acos(h / r)) / 2;
            T y = sqrt(max((T)0.0, r * r - h * h));
            area += h * y / 2;
            if(r < d1) {
                area += r * r * (acos(h / d1) - acos(h / r)) / 2;
                area += h * y / 2;
            } 
            else area += h * x / 2;
        }
    }
    return area;
}

