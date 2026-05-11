#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

double angle(pt v, pt w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

// amplitude travelled around point A, from P to Q
double angleTravelled(pt a, pt p, pt q) {
    T ampli = angle(p - a, q - a);
    if (orient(a, p, q) > 0) return ampli;
    else return -ampli;
}

bool half(pt p) {
    // true if in blue half
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

//  checks if a point P lies on the disk of diameter [AB].
bool inDisk(pt a, pt b, pt p) {
    return dot(a - p, b - p) <= 0;
}

// check if a point P lies on segment [AB].
bool onSegment(pt a, pt b, pt p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

struct anglle {
    pt d;
    int t = 0; // direction and number of full turns

    // Turn 180 degrees counter-clockwise
    anglle t180() {
        return {d * (-1LL), t + half(d)};
    }

    // Turn 360 degrees counter-clockwise (full turn)
    anglle t360() {
        return {d, t + 1};
    }
};

bool operator<(anglle a, anglle b) {
    return make_tuple(a.t, half(a.d), 0) < make_tuple(b.t, half(b.d), cross(a.d, b.d));
}

anglle moveTo(anglle a, pt newD) {
    // check that segment [DD'] doesn't go through the origin
    assert(!onSegment(a.d, newD, {0,0}));
    anglle b{newD, a.t};
    if (a.t180() < b) // if b more than half a turn bigger
        b.t--; //decrease b by a full turn
    if (b.t180() < a) // if b more than half a turn smaller
        b.t++; //  increase b by a full turn
    return b;
}

int windingNumber2(vector<pt> p, pt a) {
    anglle a{p.back()}; // start at last vertex
    for (pt d: p) {
        a = moveTo(a, d); // move to first vertex, second, etc.
    }
    return a.t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    return 0;
}
