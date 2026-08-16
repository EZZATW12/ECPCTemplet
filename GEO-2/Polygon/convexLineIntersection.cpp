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

/**
 * Time Complexity: O(log N)
 * Floating Point: No (strictly integer-safe operations like orient and cross product)
 * Requirements: Polygon must be convex. Top vertex of the polygon must be provided.
 */
// given a convex polygon p, and a line ab and the top vertex of the polygon
// returns the intersection of the line with the polygon
// it returns the indices of the edges of the polygon that are intersected by the line
// so if it returns i, then the line intersects the edge (p[i], p[(i + 1) % n])
array<int, 2> convexLineIntersection(const vector<pt> &p, pt a, pt b, int top) {
    int end_a = extremeVertex(p, perp(a - b), top);
    int end_b = extremeVertex(p, perp(b - a), top);
    auto cmp_l = [&](int i) { return sgn(orient(a, p[i], b)); };
    if (cmp_l(end_a) < 0 || cmp_l(end_b) > 0)
        return {-1, -1}; // no intersection
    array<int, 2> res;
    for (int i = 0; i < 2; i++) {
        int lo = end_b, hi = end_a, n = p.size();
        while ((lo + 1) % n != hi) {
            int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
            (cmp_l(m) == cmp_l(end_b) ? lo : hi) = m;
        }
        res[i] = (lo + !cmp_l(hi)) % n;
        swap(end_a, end_b);
    }
    if (res[0] == res[1]) return {res[0], -1}; // touches the vertex res[0]
    if (!cmp_l(res[0]) && !cmp_l(res[1])) 
        switch ((res[0] - res[1] + (int)p.size() + 1) % p.size()) {
            case 0: return {res[0], res[0]}; // touches the edge (res[0], res[0] + 1)
            case 2: return {res[1], res[1]}; // touches the edge (res[1], res[1] + 1)
        }
    return res; 
}

