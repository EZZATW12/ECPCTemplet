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

/**
 * Time Complexity: O(log N)
 * Floating Point: No (integer-safe; pointPolyTangent is integer-safe)
 * Requirements: Polygon must be convex. Point must lie strictly outside the polygon.
 */
// (ccw, cw) tangents from a point that is outside this convex polygon
// returns indexes of the points
// ccw means the tangent from Q to that point is in the same direction as the polygon ccw direction
pair<int, int> tangentsFromPointToPolygon(const vector<pt> &p, pt Q){
    int ccw = pointPolyTangent(p, Q, 1, 0, (int)p.size() - 1).second;
    int cw = pointPolyTangent(p, Q, -1, 0, (int)p.size() - 1).second;
    return make_pair(ccw, cw);
}

