#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

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

    // From direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {
    }

    // TODO
    // From equation ax + by - c = 0
    line(T a, T b, T c) : v(b, -a), c(-c) {
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

//  distance between segment [AB] and point P
T segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) {
            // if closest to projection
            return l.dist(p); // output distance to line
        }
    }
    return min(abs(p - a), abs(p - b)); // otherwise distance to A or B
}

// determining the direction of the points (right, left, or on a line).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
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

//  distance between two segments
T segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy)) return 0;
    return min({
        segPoint(a, b, c), segPoint(a, b, d),
        segPoint(c, d, a), segPoint(c, d, b)
    });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long double ax, ay, bx, by, cx, cy, dx, dy;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;

    cout << fixed << setprecision(15) << segSeg({ax, ay}, {bx, by}, {cx, cy}, {dx, dy}) << '\n';

    return 0;
}
