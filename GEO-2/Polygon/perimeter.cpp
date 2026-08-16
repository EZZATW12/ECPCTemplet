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
 * Time Complexity: O(N)
 * Floating Point: Yes (uses abs to compute Euclidean distance, which relies on sqrt)
 * Requirements: None
 */
T perimeter(const vector<pt> &p) {
    T ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += abs(p[i] - p[(i + 1) % n]);
    return ans;
}

