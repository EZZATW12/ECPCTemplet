//
// Created by ezzat on 6/29/2026.
//
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

#define ll long long
#define ld long double
#define EPS 1e-9
#define PI acos(-1)
typedef long double T;
typedef complex<T> pt;

#define x real()
#define y imag()

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

T orient(pt a, pt b, pt c) {
    /*
        orient(A, B, C) is positive if when going from A to B to
        C we turn left, negative if we turn right, and zero if A, B, C are collinear
     */
    return cross(b - a, c - a);
}

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