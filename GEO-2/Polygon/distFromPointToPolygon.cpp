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

T segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p); 
    }
    return min(abs(p - a), abs(p - b)); 
}

pair<pt, int> pointPolyTangent(const vector<pt> &p, pt Q, int dir, int l, int r) {
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        bool pvs = sgn(orient(Q, p[mid], p[mid - 1])) != -dir;
        bool nxt = sgn(orient(Q, p[mid], p[mid + 1])) != -dir;
        if (pvs && nxt) return {p[mid], mid};
        if (!(pvs || nxt)) {
            auto p1 = pointPolyTangent(p, Q, dir, mid + 1, r);
            auto p2 = pointPolyTangent(p, Q, dir, l, mid - 1);
            return sgn(orient(Q, p1.first, p2.first)) == dir ? p1 : p2;
        }
        if (!pvs) {
            if (sgn(orient(Q, p[mid], p[l])) == dir)  r = mid - 1;
            else if (sgn(orient(Q, p[l], p[r])) == dir) r = mid - 1;
            else l = mid + 1;
        }
        if (!nxt) {
            if (sgn(orient(Q, p[mid], p[l])) == dir)  l = mid + 1;
            else if (sgn(orient(Q, p[l], p[r])) == dir) r = mid - 1;
            else l = mid + 1;
        }
    }
    pair<pt, int> ret = {p[l], l};
    for (int i = l + 1; i <= r; i++) ret = sgn(orient(Q, ret.first, p[i])) != dir ? make_pair(p[i], i) : ret;
    return ret;
}

pair<int, int> tangentsFromPointToPolygon(const vector<pt> &p, pt Q){
    int ccw = pointPolyTangent(p, Q, 1, 0, (int)p.size() - 1).second;
    int cw = pointPolyTangent(p, Q, -1, 0, (int)p.size() - 1).second;
    return make_pair(ccw, cw);
}

/**
 * Time Complexity: O(log N)
 * Floating Point: Yes (uses double literals 1e100, sqrt, and segPoint)
 * Requirements: Polygon must be convex. Point must lie strictly outside the polygon.
 */
// minimum distance from a point to a convex polygon
// it assumes point lie strictly outside the polygon
T distFromPointToPolygon(const vector<pt> &p, pt z) {
    T ans = 1e100;
    int n = p.size();
    if (n <= 3) {
        for(int i = 0; i < n; i++) ans = min(ans, segPoint(p[i], p[(i + 1) % n], z));
        return ans;
    }
    auto [r, l] = tangentsFromPointToPolygon(p, z);
    if(l > r) r += n;
    while (l < r) {
        int mid = (l + r) >> 1;
        T left = sq(p[mid % n] - z), right = sq(p[(mid + 1) % n] - z);
        ans = min({ans, left, right});
        if(left < right) r = mid;
        else l = mid + 1;
    }
    ans = sqrt(ans);
    ans = min(ans, segPoint(p[l % n], p[(l + 1) % n], z));
    ans = min(ans, segPoint(p[l % n], p[(l - 1 + n) % n], z));
    return ans;
}

