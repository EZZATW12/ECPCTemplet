#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

const long double EPS = 1e-9;

int sgn(T val) {
    if (val > EPS) return 1;
    if (val < -EPS) return -1;
    return 0;
}

T dist(pt a, pt b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

pt perp(pt p) {
    return {-p.y, p.x};
}

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
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

    pt proj(pt p) {
        return p - perp(v) * side(p) / sq(v);
    }

    //  Sorting along a line
    bool cmpProj(pt p, pt q) {
        return dot(v, p) < dot(v, q);
    }
};

// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

//  checks if a point P lies on the disk of diameter [AB].
bool inDisk(pt a, pt b, pt p) {
    return sgn(dot(a - p, b - p)) <= 0;
}

// check if a point P lies on segment [AB].
bool onSegment(pt a, pt b, pt p) {
    return sgn(orient(a, b, p)) == 0 && inDisk(a, b, p);
}

// intersection strictly inside segments (not endpoints)
// if the intersection occurs at any of the endpoints a, b, c, d, it is not considered proper, but an endpoint intersection.
bool properInter(pt a, pt b, pt c, pt d, pt &inter) {
    T oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        T s = oa / (oa - ob);
        inter = a + s * (b - a);
        return true;
    }
    return false;
}

// find all intersection points between 2 segments
vector<pt> segmentsIntersectPoint(pt a, pt b, pt c, pt d) {
    // check proper intersection (inside segments)
    pt p;
    if (properInter(a, b, c, d, p)) {
        return {p};
    }

    // check endpoints on the other segment
    vector<pt> pts;
    if (onSegment(c, d, a)) pts.push_back(a);
    if (onSegment(c, d, b)) pts.push_back(b);
    if (onSegment(a, b, c)) pts.push_back(c);
    if (onSegment(a, b, d)) pts.push_back(d);

    // sort lexicographically (x first, then y)
    sort(pts.begin(), pts.end(), [](pt a, pt b) {
        if (sgn(abs(a.x - b.x))) return a.x < b.x;
        return a.y < b.y;
    });

    // remove duplicates
    pts.resize(unique(pts.begin(), pts.end()) - pts.begin());

    return pts;
}

void interSegLine(line l, pt a, pt b, vector<pt> &out) {
    out = segmentsIntersectPoint(a, b, l.proj(a), l.proj(b));
}