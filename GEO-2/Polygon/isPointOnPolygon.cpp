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

bool inDisk(pt a, pt b, pt p) { return sgn(dot(a - p, b - p)) <= 0; }
bool onSegment(pt a, pt b, pt p) { return sgn(orient(a, b, p)) == 0 && inDisk(a, b, p); }

/**
 * Time Complexity: O(N)
 * Floating Point: No (integer-safe assuming onSegment is integer-safe)
 * Requirements: None
 */
bool isPointOnPolygon(const vector<pt> &p, const pt& z) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], z)) return 1;
    }
    return 0;
}

