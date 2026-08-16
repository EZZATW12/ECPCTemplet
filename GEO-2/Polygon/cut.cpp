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

int isParallel(pt a, pt b, pt c, pt d) {
    T k = fabs(cross(b - a, d - c));
    if (k < EPS) {
        if (fabs(cross(a - b, a - c)) < EPS && fabs(cross(c - d, c - a)) < EPS) return 2;
        else return 1;
    }
    else return 0;
}

/**
 * Time Complexity: O(N)
 * Floating Point: Yes (computes segment intersection using inter, which requires floats)
 * Requirements: None
 */
// returns a vector with the vertices of a polygon with everything
// to the left of the line going from a to b cut away.
vector<pt> cut(const vector<pt> &p, pt a, pt b) {
    vector<pt> ans;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        T c1 = cross(b - a, p[i] - a);
        T c2 = cross(b - a, p[(i + 1) % n] - a);
        if (sgn(c1) >= 0) ans.push_back(p[i]);
        if (sgn(c1 * c2) < 0) {
            if (!isParallel(p[i], p[(i + 1) % n], a, b)) {
                pt tmp; 
                inter(line(p[i], p[(i + 1) % n]), line(a, b), tmp);
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}

