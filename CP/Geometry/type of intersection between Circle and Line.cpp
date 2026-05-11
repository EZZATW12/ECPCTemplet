#include <bits/stdc++.h>
using namespace std;

typedef double T;
typedef complex<T> pt;
#define x real()
#define y imag()

const long double EPS = 1e-9;

int sgn(T val) {
    if (val > EPS) return 1;
    if (val < -EPS) return -1;
    return 0;
}

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

    // From direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {
    }

    // From equation ax + by = c
    line(T a, T b, T c) : v(b, -a), c(c) {
    }

    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {
    }

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

// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

// The center of the circle passing through three points
pt circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a; // consider coordinates relative to A
    assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2.0;
}

// Points of intersection of a line with a circle in the plane and return type of intersection
int circleLine(pt o, double r, line l, pair<pt, pt> &out) {
    T h2 = r * r - l.sqDist(o);
    if (h2 >= 0) {
        // the line touches the circle
        pt p = l.proj(o); // point P
        pt h = l.v * sqrt(h2) / abs(l.v); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    return 0;
}
