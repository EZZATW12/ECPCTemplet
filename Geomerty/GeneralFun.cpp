#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define EPS 1e-9
#define PI acos(-1)
typedef double T;
typedef complex<T> pt;

#define x real()
#define y imag()

// transformations
// abs(point) -> get the len of the vector
// arg(point) -> get the angle of the vector
T sq(pt p) { // get squere of vector
    return p.x * p.x + p.y * p.y;
}

int sgn(T val) {
    if (val > EPS) return 1;
    if (val < -EPS) return -1;
    return 0;
}

int dcmp(const ld &a, const ld &b) {
    if (fabs(a - b) < EPS)
        return 0;

    return (a > b ? 1 : -1);
}

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

bool isPerp(pt a, pt b) { // check if the vector is perpendicular
    return fabs(dot(a, b)) < EPS;
}

pt Perp(pt a) { // get the perpendicular of vector
    return {-a.y, a.x};
}

//////////////// TRASFORMATIONS ////////////////////////
pt translate(pt v, pt p) {
    return p + v; // translate p base on vector v
}

pt scale(pt c, double factor, pt p) {
    return c + (p - c) * factor;  // To scale an object by a certain ratio & around a center c
}

pt rot(pt p, double a, pt c) { // rotate point around center c by angle a
    pt ret = p - c;
    pt rotat = {cos(a), sin(a)};
    return c + ret * rotat;
}

pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
    return fp + (r - p) * (fq - fp) / (q - p);
    // if have point p and tarns fp and point q and trans fq and point r so get the fr
}

/////////////// Angles //////////////////////////
T Angle(pt v, pt w) {
    //  a.b = |a | * | b | *cos(angle)->cos(angle) = (a.b) /(|a | * | b |) -> angle = acos((a.b) /( | a | * | b |))
    return acos(clamp(dot(v, w) / abs(v) / abs(w), (T) -1.0, (T) 1.0));

}

T orient(pt a, pt b, pt c) {
    /*
        orient(A, B, C) is positive if when going from A to B to
        C we turn left, negative if we turn right, and zero if A, B, C are collinear
     */
    return cross(b - a, c - a);
}

T orientedAngle(pt a, pt b, pt c) { // the angle when go from a to b then c
    ld ampli = Angle(b - a, c - a);
    if (orient(a, b, c) > 0) return ampli;
    else return 2 * PI - ampli;
}

T angleTravelled(pt a, pt b, pt c) {
    ld ampli = Angle(b - a, c - a);
    if (orient(a, b, c) > 0) return ampli;
    else return -ampli;
}

//check p in between angle(bac) counter clockwise
bool inAngle(pt a, pt b, pt c, pt p) {
    T abp = orient(a, b, p), acp = orient(a, c, p), abc = orient(a, b, c);
    if (abc < 0) swap(abp, acp);
    return (abp >= 0 && acp <= 0) ^ (abc < 0);
}

bool isConvex(vector<pt> p) {
    // check if the polygon is convex or not by check the sign of it's oriented Angle
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

///////////////////////////////////////  Line  ////////////////////////////////////////////////////////////////
struct line {
    pt v;
    T c;

    // From direction vector v and offset c
    line(pt _v, T _c) {
        v = _v, c = _c;
    }

    // From equation ax+by=c
    line(T a, T b, T _c) {
        v = {b, -a};
        c = _c;
    }

    // From points P and Q
    line(pt p, pt q) {
        v = q - p;
        c = cross(v, p);
    }

    T side(pt p) {
        return cross(v, p) - c;
    }

    ld dist(pt p) { // get the dist from p to the proj of p in the line
        return abs(side(p)) / abs(v);
    }

    double sqDist(pt p) {// get the sq dist from p to the proj of p in the line
        return side(p) * side(p) / (T) sq(v);
    }

    line prepThrought(pt p) {
        // get the line that throught in p and perp of p
        return {p, p + Perp(p)};
    }

    bool cmpProj(pt p, pt q) { // to sort point base on it's proj in the line
        return dot(v, p) < dot(v, q);
    }

    line translate(pt t) { // translate the line by vector t
        return {v, c + cross(v, t)};
    }

    line shiftLeft(T dist) {// shiftLeft the line by dist
        return {v, c + dist * abs(v)};
    }

    pt proj(pt p) { // get the proj of the point p in the line
        return p - Perp(v) * side(p) / sq(v);
    }

    pt refl(pt p) {// get the refl of the point p in the line
        return p - Perp(v) * (T) 2.0 * side(p) / sq(v);
    }
};

bool inter(line l1, line l2, pt &out) {
    // get the intersect point of line1 and line2
    T d = cross(l1.v, l2.v);
    if (fabs(d) < EPS) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
    return true;
}

line bisector(line l1, line l2, bool interior) {
    // get the line that divide the inter of two line
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    T sign = interior ? 1 : -1;
    return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
            l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign};
}


///////////////////////////// Segmant //////////////////////////////////////////
bool inDisk(pt a, pt b, pt p) {
    // checks if a point P lies on the disk of diameter [AB]
    return dot(a - p, b - p) <= EPS;
}

bool onSegment(pt a, pt b, pt p) {
    // check that point p on the segmant [ab]
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    // get the prop intersect of two segments
    double oa = orient(c, d, a),
            ob = orient(c, d, b),
            oc = orient(a, b, c),
            od = orient(a, b, d);
    // Proper intersection exists iff opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

set<pair<ld, ld>> inters(pt a, pt b, pt c, pt d) {
    // get all intersect of to segments
    set<pair<ld, ld>> s;
    pt out;
    if (a == c || a == d) {
        s.insert(make_pair(a.x, a.y));
    }
    if (b == c || b == d) {
        s.insert(make_pair(b.x, b.y));
    }
    if (s.size()) return s;

    if (properInter(a, b, c, d, out)) return {make_pair(out.x, out.y)};
    if (onSegment(c, d, a)) s.insert(make_pair(a.x, a.y));
    if (onSegment(c, d, b)) s.insert(make_pair(b.x, b.y));
    if (onSegment(a, b, c)) s.insert(make_pair(c.x, c.y));
    if (onSegment(a, b, d)) s.insert(make_pair(d.x, d.y));

    return s;
}

double seg_Point_Dist(pt a, pt b, pt p) {
    // get the dist from point to Segment
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) // if closest toprojection
            return l.dist(p); // output distance to line
    }
    return min(abs(p - a), abs(p - b)); // otherwise distance to A or B
}

double seg_Seg_Dist(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy))
        return 0;
    return min({seg_Point_Dist(a, b, c), seg_Point_Dist(a, b, d),
                seg_Point_Dist(c, d, a), seg_Point_Dist(c, d, b)});
}

//////////////////// Polygons ////////////////////////////////////////////////////////////
double areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

double areaPolygon(vector<pt> p) {
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n-1
    }
    return abs(area) / 2.0;
}

// true if P at least as high as A (blue part)
bool above(pt a, pt p) {
    return p.y >= a.y;
}

// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    // check point is on polygon or not
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}

bool sameLine(const line &L1, const line &L2) {
    // Recover (a,b,c) from v and c:
    // v = (-b, a)  => a = v.imag(), b = -v.real()
    ld a1 = imag(L1.v);
    ld b1 = -real(L1.v);
    ld c1 = L1.c;
    ld a2 = imag(L2.v);
    ld b2 = -real(L2.v);
    ld c2 = L2.c;

    // Check proportionality: (a1,b1,c1) ~ (a2,b2,c2)
    // i.e. a1*b2 == a2*b1,  a1*c2 == a2*c1,  b1*c2 == b2*c1
    if (fabsl(a1 * b2 - a2 * b1) > EPS) return false;
    if (fabsl(a1 * c2 - a2 * c1) > EPS) return false;
    if (fabsl(b1 * c2 - b2 * c1) > EPS) return false;
    return true;
}

}

int main() {


}
