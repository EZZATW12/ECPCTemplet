#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

const long double EPS = 1e-9;

int sgn(T val) {
    // positive number
    if (val > EPS) return 1;
    // negative number
    if (val < -EPS) return -1;
    // 0
    return 0;
}

// TODO if (0, 0) not ORIGIN
// will be positive if the rotation from a to b is performed counter-clockwise and negative otherwise
// so for two vectors that are "close" in angle (within 180 deg) the sign of the cross product correctly tells which has the larger angle.
T cross(pt v, pt w, pt origin = {0, 0}) {
    return (v.x - origin.x) * (w.y - origin.y) - (v.y - origin.y) * (w.x - origin.x);
}

// the dot product is positive if the angle between them is acute, negative if it is obtuse and it equals zero if they are orthogonal.
T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

void sort_points(vector<pt> &v) {
    sort(v.begin(), v.end(), [](pt &a, pt &b) {
        return sgn(fabs(a.x - b.x)) ? a.x < b.x : a.y < b.y;
    });
}

// erase(unique) with double
void unique(vector<pt> &v) {
    auto cmp_eq = [](pt &a, pt &b) {
        return abs(a.x - b.x) < EPS && abs(a.y - b.y) < EPS;
    };
    v.erase(unique(v.begin(), v.end(), cmp_eq), v.end());
}

bool is_int(T factor) {
    return (fabsl(factor - roundl(factor)) < 1e-5);
}

const double PI = acos(-1.0);

// Convert radians to degrees
double radToDeg(double rad) {
    return rad * 180.0 / PI;
}

// Convert degrees to radians
double degToRad(double deg) {
    return deg * PI / 180.0;
}

// returns the angle (in radians) between the positive x-axis and the point (x, y)
double angle(pt p) {
    return atan2l(p.y, p.x);
}

bool equal(T a, T b) {
    return (abs(a - b) < EPS);
}

T dist(pt a, pt b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

pt translate(pt v, pt p) {
    return p + v;
}

pt scale(pt c, T factor, pt p) {
    return c + (p - c) * factor;
}

// rotate vector v by angle c by radian
pt rotate(pt v, T c) {
    return {v.x * cos(c) - v.y * sin(c), v.x * sin(c) + v.y * cos(c)};
}

pt rot(pt p, T a) {
    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

pt perp(pt p) {
    return {-p.y, p.x};
}

pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
    return fp + (r - p) * (fq - fp) / (q - p);
}

bool isPerp(pt v, pt w) {
    return dot(v, w) == 0;
}

double angle(pt v, pt w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a,b,c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {
    return (orient(a, b, c) >= 0 ? angle(b - a, c - a) : 2 * M_PI - angle(b - a, c - a));
}

bool half(pt p) {
    // true if in blue half
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

// around origin
void polarSort(vector<pt> &v) {
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w));
    });
}

// around point o
void polarSortAround(pt o, vector<pt> &v) {
    sort(v.begin(), v.end(), [o](pt v, pt w) {
        return make_tuple(half(v - o), 0) < make_tuple(half(w - o), cross(v - o, w - o));
    });
}

struct line {
    pt v;
    T c;

    // From direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {
    }

    // From equation ax + by = c
    line(T a, T b, T c) : v(b, -a), c(c) {
    }

    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {
    }

    // Determine the direction of a point relative to a straight line
    T side(pt p) {
        return cross(v, p) - c;
    }

    T dist(pt p) {
        return abs(side(p)) / abs(v);
    }

    T sqDist(pt p) {
        return side(p) * side(p) / (double) sq(v);
    }

    line perpThrough(pt p) {
        return {p, p + perp(v)};
    }

    //  Sorting along a line
    bool cmpProj(pt p, pt q) {
        return dot(v, p) < dot(v, q);
    }

    //  translate a line l by vector t
    line translate(pt t) {
        return {v, c + cross(v, t)};
    }

    // s shifting line l to the left by a certain distance
    line shiftLeft(T dist) {
        return {v, c + dist * abs(v)};
    }

    pt proj(pt p) {
        return p - perp(v) * side(p) / sq(v);
    }

    pt refl(pt p) {
        return p - perp(v) * (T) 2.0 * side(p) / sq(v);
    }
};

//  intersection point between two lines l1 and l2
bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d;
    return true;
}

//  An angle bisector of two (non-parallel) lines l1 and l2 is a line that forms equal angles with l1 and l2.
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0);
    T sign = interior ? 1 : -1;
    return {
        l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
        l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign
    };
}

//  checks if a point P lies on the disk of diameter [AB].
bool inDisk(pt a, pt b, pt p) {
    return dot(a - p, b - p) <= 0;
}

// check if a point P lies on segment [AB].
bool onSegment(pt a, pt b, pt p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

//  intersection between two segments
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    // Proper intersection exists if opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

// To create sets of points we need a comparison function
struct cmpX {
    bool operator()(pt a, pt b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};

set<pt, cmpX> inters(pt a, pt b, pt c, pt d) {
    pt out;
    if (properInter(a, b, c, d, out)) return {out};
    set<pt, cmpX> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return s;
}

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

// if strict true, returns false when A is on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1;
}

int main() {
    return 0;
}
