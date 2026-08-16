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
 * Floating Point: Yes (uses fabs and EPS)
 * Requirements: None
 */
// 0 if not parallel, 1 if parallel, 2 if collinear
int isParallel(pt a, pt b, pt c, pt d) {
    T k = fabs(cross(b - a, d - c));
    if (k < EPS) {
        if (fabs(cross(a - b, a - c)) < EPS && fabs(cross(c - d, c - a)) < EPS) return 2;
        else return 1;
    }
    else return 0;
}

