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

/**
 * 2D Line representation defined by direction vector v and offset constant c (cross(v, p) = c).
 */
struct line {
    pt v; T c;

    line(pt v, T c) : v(v), c(c) {}
    line(T a, T b, T _c) { v = {b, -a}; c = _c; }
    line(pt p, pt q) { v = q - p; c = cross(v, p); }

    // Evaluates side of point p wrt line (> 0 left, < 0 right, 0 on line)
    T side(pt p) { return cross(v, p) - c; }
    
    // Perpendicular distance from point p to line
    T dist(pt p) { return abs(side(p)) / abs(v); }
    
    // Compares projections of points p and q along line direction vector v
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
    
    // Translates line by vector t
    line translate(pt t) { return {v, c + cross(v, t)}; }
    
    // Squared perpendicular distance from point p to line
    double sqDist(pt p) { return side(p) * side(p) / sq(v); }
    
    // Perpendicular line passing through point p
    line prepThrought(pt p) { return {p, p + prep(v)}; }
    
    // Shifts line parallel to itself to the left by dist
    line shiftLeft(T dist) { return {v, c + dist * abs(v)}; }
    
    // Orthogonal projection of point p onto line
    pt proj(pt p) { return p - prep(v) * side(p) / sq(v); }
    
    // Reflection of point p across line
    pt refl(pt p) { return p - prep(v) * (T) 2.0 * side(p) / sq(v); }
};

/**
 * Computes intersection point of non-parallel lines l1 and l2. Returns true if unique intersection exists.
 */
bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (sgn(d) == 0) return false; 
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

/**
 * Angle bisector line between non-parallel lines l1 and l2 (interior if interior=true, exterior otherwise).
 */
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); 
    T sign = interior ? 1 : -1;
    return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
            l2.c / abs(l2.v) + l1.c / abs(l1.c) * sign};
}

/**
 * Checks if point p lies inside or on the boundary of the disk with diameter AB.
 */
bool inDisk(pt a, pt b, pt p) { return sgn(dot(a - p, b - p)) <= 0; }

/**
 * Checks if point p lies on segment AB.
 */
bool onSegment(pt a, pt b, pt p) { return sgn(orient(a, b, p)) == 0 && inDisk(a, b, p); }

/**
 * Checks for proper (non-endpoint) intersection of segment AB and segment CD.
 */
bool properInter(pt a, pt b, pt c, pt d, pt &inter) {
    T oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    if (oa * ob < 0 && oc * od < 0) {
        T s = oa / (oa - ob);
        inter = a + s * (b - a);
        return true;
    }
    return false;
}

/**
 * Minimum distance from point p to line segment AB.
 */
T segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p); 
    }
    return min(abs(p - a), abs(p - b)); 
}

/**
 * Minimum distance between segment AB and segment CD.
 */
T segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy)) return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d), segPoint(c, d, a), segPoint(c, d, b)});
}

/**
 * Returns set of intersection points between segment AB and segment CD.
 */
set<pair<T, T>> inters(pt a, pt b, pt c, pt d) {
    set<pair<T, T>> s; pt out;
    if (a == c || a == d) s.insert({a.X, a.Y});
    if (b == c || b == d) s.insert({b.X, b.Y});
    if (s.size()) return s;
    if (properInter(a, b, c, d, out)) return {{out.X, out.Y}};
    if (onSegment(c, d, a)) s.insert({a.X, a.Y});
    if (onSegment(c, d, b)) s.insert({b.X, b.Y});
    if (onSegment(a, b, c)) s.insert({c.X, c.Y});
    if (onSegment(a, b, d)) s.insert({d.X, d.Y});
    return s;
}
