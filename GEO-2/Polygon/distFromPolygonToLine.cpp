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

int extremeVertex(const vector<pt> &p, const pt &z, const int top) {
    int n = p.size();
    if (n == 1) return 0;
    T ans = dot(p[0], z); int id = 0;
    if (dot(p[top], z) > ans) { ans = dot(p[top], z); id = top; }
    int l = 1, r = top - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (dot(p[mid + 1], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    if (dot(p[l], z) > ans) { ans = dot(p[l], z); id = l; }
    l = top + 1, r = n - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (dot(p[(mid + 1) % n], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    l %= n;
    if (dot(p[l], z) > ans) { ans = dot(p[l], z); id = l; }
    return id;
}

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

/**
 * Time Complexity: O(log N)
 * Floating Point: Yes (returns floating point distance via line.dist and literal 0.0)
 * Requirements: Polygon must be convex. Top upper right vertex must be provided.
 */
// minimum distance from convex polygon p to line ab
// returns 0 is it intersects with the polygon
// top - upper right vertex
T distFromPolygonToLine(const vector<pt> &p, pt a, pt b, int top) { //O(log n)
    pt orth = perp(b - a);
    if (sgn(orient(a, b, p[0])) > 0) orth = perp(a - b);
    int id = extremeVertex(p, orth, top);
    if (dot(p[id] - a, orth) > 0) return 0.0; 
    line l(a, b);
    return l.dist(p[id]); 
}

