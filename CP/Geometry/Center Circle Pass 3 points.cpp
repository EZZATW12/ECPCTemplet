#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

const long double EPS = 1e-9;

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

T dist(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

pt perp(pt p) {
    return {-p.y, p.x};
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

bool isColinear(pt a, pt b, pt c) {
    return fabs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) < EPS;
}

// you can determine circle with 3 points
// return center and radius
pair<pt, T> circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a; // consider coordinates relative to A
    assert(cross(b, c) != 0); // no circumcircle if A,B,C aligned
    return make_pair(a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2.0L,
                     abs(perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2.0L));
}
