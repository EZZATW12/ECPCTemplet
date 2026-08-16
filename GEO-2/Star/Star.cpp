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
 * Floating Point: Yes (uses PI, sin, tan, and floating-point arithmetic)
 * Requirements: None
 */
struct Star {
    int n;    // number of sides of the star
    T r;      // radius of the circumcircle
    Star(int _n, T _r) {
        n = _n;
        r = _r;
    }

    T area() {
        T theta = PI / n;
        T s = 2 * r * sin(theta);
        T R = 0.5 * s / tan(theta);
        T a = 0.5 * n * s * R;
        T a2 = 0.25 * s * s / tan(1.5 * theta);
        return a - n * a2;
    }
};

