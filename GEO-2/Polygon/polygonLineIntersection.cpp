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

/**
 * Time Complexity: O(N log N)
 * Floating Point: Yes (uses division, EPS, and abs)
 * Requirements: None
 */
// not necessarily convex, boundary is included in the intersection
// returns total intersected length
// it returns the sum of the lengths of the portions of the line that are inside the polygon
T polygonLineIntersection(vector<pt> p, pt a, pt b) {
    int n = p.size();
    p.push_back(p[0]);
    line l(a, b);
    T ans = 0.0;
    vector< pair<T, int> > vec;
    for (int i = 0; i < n; i++) {
        int s1 = sgn(orient(a, b, p[i]));
        int s2 = sgn(orient(a, b, p[i + 1]));
        if (s1 == s2) continue;
        line t(p[i], p[i + 1]);
        pt inter_pt = (t.v * l.c - l.v * t.c) / cross(l.v, t.v);
        T tmp = dot(inter_pt, l.v);
        int f;
        if (s1 > s2) f = s1 && s2 ? 2 : 1;
        else f = s1 && s2 ? -2 : -1;
        vec.push_back(make_pair((f > 0 ? tmp - EPS : tmp + EPS), f)); // keep eps very small
    }
    sort(vec.begin(), vec.end());
    for (int i = 0, j = 0; i + 1 < (int)vec.size(); i++){
        j += vec[i].second;
        if (j) ans += vec[i + 1].first - vec[i].first; 
    }
    ans = ans / abs(l.v);
    p.pop_back();
    return ans;
}

