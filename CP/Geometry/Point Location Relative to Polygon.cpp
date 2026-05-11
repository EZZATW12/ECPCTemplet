#include <bits/stdc++.h>
using namespace std;

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

// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

// true if P at least as high as A (blue part)
bool above(pt a, pt p) {
    return p.y >= a.y;
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
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;

    vector<pt> p(n);
    for (int i = 0; i < n; i++) {
        T a, b;
        cin >> a >> b;
        p[i] = pt(a, b);
    }

    T px, py;
    cin >> px >> py;

    bool ok = inPolygon(p, {px, py}, true), ok2 = inPolygon(p, {px, py}, false);
    if (ok && ok2) {
        cout << "INSIDE\n";
    } else if (!ok && !ok2) {
        cout << "OUTSIDE\n";
    } else {
        cout << "BOUNDARY\n";
    }

    return 0;
}
