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
 * Computes area of polygon p using Shoelace formula.
 */
T areaPolygon(const vector<pt> &p) {
    T area = 0.0; int n = p.size();
    for (int i = 0; i < n; i++) area += cross(p[i], p[(i + 1) % n]); 
    return abs(area) / 2.0;
}

// Helper function checking if point p is at or above horizontal level of a
bool above(pt a, pt p) { return p.Y >= a.Y; }

// Helper function testing ray crossing for point-in-polygon test
bool crossesRay(pt a, pt p, pt q) {
    return (above(a, q) - above(a, p)) * sgn(orient(a, p, q)) > 0;
}

/**
 * Point-in-polygon ray casting test.
 * Returns true if point a is strictly inside polygon p (or on boundary if strict=false).
 */
bool inPolygon(const vector<pt> &p, pt a, bool strict = true) {
    int numCrossings = 0; int n = p.size();
    for (int i = 0; i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a)) return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; 
}

/**
 * Computes convex hull of point set p using Andrew's Monotone Chain algorithm in O(N log N).
 */
vector<pt> convexHull(vector<pt> p) {
    int n = p.size(), k = 0;
    if (n <= 2) return p;
    vector<pt> h(2 * n);

    sort(p.begin(), p.end(), [](pt a, pt b) {
        if (abs(a.X - b.X) > EPS) return a.X < b.X;
        return a.Y < b.Y - EPS;
    });

    for (int i = 0; i < n; ++i) {
        while (k >= 2 && sgn(orient(h[k - 2], h[k - 1], p[i])) <= 0) k--;
        h[k++] = p[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && sgn(orient(h[k - 2], h[k - 1], p[i])) <= 0) k--;
        h[k++] = p[i];
    }
    h.resize(k - 1); 
    return h;
}

/**
 * Returns number of integer lattice points on segment between (x1, y1) and (x2, y2), inclusive.
 */
int segmentLatticePointsCount(int x1, int y1, int x2, int y2) {
    return abs(__gcd(x1 - x2, y1 - y2)) + 1;
}
