#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

pt perp(pt p) {
    return {-p.y, p.x};
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

struct line {
    pt v;
    T c;

    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {
    }

    T side(pt p) {
        return cross(v, p) - c;
    }

    T dist(pt p) {
        return abs(side(p)) / abs(v);
    }

    //  Sorting along a line
    bool cmpProj(pt p, pt q) {
        return dot(v, p) < dot(v, q);
    }
};

void reorder_polygon(vector<pt> &p) {
    int pos = 0;
    for (int i = 1; i < p.size(); i++) {
        if (p[i].y < p[pos].y || (p[i].y == p[pos].y && p[i].x < p[pos].x)) {
            pos = i;
        }
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}

// computes the Minkowski sum of two convex polygons p and q
// p must be counter clockwise
vector<pt> minkowski(vector<pt> p, vector<pt> q) {
    // the first vertex must be the lowest
    reorder_polygon(p);
    reorder_polygon(q);

    // we must ensure cyclic indexing
    p.push_back(p[0]);
    p.push_back(p[1]);
    q.push_back(q[0]);
    q.push_back(q[1]);

    vector<pt> ret;
    int i = 0, j = 0;
    while (i < p.size() - 2 || j < q.size() - 2) {
        ret.push_back(p[i] + q[j]);
        auto cros = cross(p[i + 1] - p[i], q[j + 1] - q[j]);
        i += (cros >= 0 && i < p.size() - 2);
        j += (cros <= 0 && j < q.size() - 2);
    }
    return ret;
}

// true if P at least as high as A (blue part)
bool above(pt a, pt p) {
    return p.y >= a.y;
}

// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

//  checks if a point P lies on the disk of diameter [AB].
bool inDisk(pt a, pt b, pt p) {
    return dot(a - p, b - p) <= 0;
}

// check if a point P lies on segment [AB].
bool onSegment(pt a, pt b, pt p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict) {
    if (p.size() < 3) return false;
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1;
}

// check if point is inside a convex polygon (O(log n))
bool point_in_convex_polygon(pt p, const vector<pt> &poly) {
    pt origin = poly[0];

    int l = 1, r = (int) poly.size() - 2, ret = 1;
    while (l <= r) {
        int md = (l + r) / 2;
        if (orient(origin, poly[md], p) >= 1) {
            ret = md;
            l = md + 1;
        } else {
            r = md - 1;
        }
    }
    return inPolygon({origin, poly[ret], poly[ret + 1]}, p, false);
}

//  distance between segment [AB] and point P
T segPoint(pt p, pt a, pt b) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) {
            // if closest to projection
            return l.dist(p); // output distance to line
        }
    }
    return min(abs(p - a), abs(p - b)); // otherwise distance to A or B
}

// distance between two polygons (or simply checking whether they intersect)
pair<bool, T> polygons_intersection_distance(vector<pt> p, vector<pt> q) {
    // reflect q for Minkowski method
    // any point in Minkowski become ((xp - xq), (yp - yq))
    // dist is sqrt((xp - xq)^2 + (yp - yq)^2)
    // min dist is min(sqrt(x^2, y^2)) from Minkowski Sum
    vector<pt> negq = q;
    for (auto &v: negq) {
        v = {-v.x, -v.y};
    }

    // compute Minkowski Sum
    vector<pt> sum_poly = minkowski(p, negq);

    // check if origin (0,0) is inside sumPoly
    bool intersect = point_in_convex_polygon({0, 0}, sum_poly);
    if (intersect) {
        return make_pair(true, 0.0);
    }

    // if not intersecting, compute minimum distance to origin
    T mn_dist = 1e18;
    for (int i = 0; i < sum_poly.size(); i++) {
        pt a = sum_poly[i];
        pt b = sum_poly[(i + 1) % sum_poly.size()];
        mn_dist = min(mn_dist, segPoint({0, 0}, a, b));
    }
    return make_pair(false, mn_dist);
}

int main() {
    vector<pt> p = {{0, 0}, {2, 0}, {2, 2}, {0, 2}}; // square
    vector<pt> q = {{3, 1}, {4, 0}, {4, 2}}; // triangle

    auto [intersect, dist] = polygons_intersection_distance(p, q);

    if (intersect) {
        cout << "Polygons intersect\n";
    } else {
        cout << "Polygons do NOT intersect, distance " << dist << "\n";
    }
}