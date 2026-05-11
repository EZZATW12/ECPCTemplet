// cross product will be positive if the rotation from v to w is performed counter-clockwise and negative otherwise
// so for two vectors that are "close" in angle (within 180 deg) the sign of the cross product correctly tells which has the larger angle.
// but if two vectors are more than 180 deg apart, the cross is no longer sufficient
// to avoid this ambiguity we partition vectors into two groups (halves) by angle, typically:
// "Blue half" = angles in (0,pi] (upper half-plane, plus the negative x-axis),
// and "Other half" = angles in (-pi,0] (lower half-plane, plus positive x-axis).
// if two vectors point exactly in the same direction, cross(v, w) == 0
// sort will leave them in arbitrary relative order (sq)

#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

T cross(pt v, pt w, pt origin = {0, 0}) {
    return (v.x - origin.x) * (w.y - origin.y) - (v.y - origin.y) * (w.x - origin.x);
}

// true if in blue half
bool half(pt p, pt origin = {0, 0}) {
    T dx = p.x - origin.x, dy = p.y - origin.y;
    assert(dx != 0 || dy != 0); // (0, 0) has no angle
    // TODO
    return dy > 0 || (dy == 0 && dx < 0); // or dx > 0
}

// around origin
void polarSort(vector<pt> &v) {
    sort(v.begin(), v.end(), [](const pt &v, const pt &w) {
        // TODO
        if (half(v) != half(w)) {
            // or half(v) > half(w) depending on which half first
            return half(v) < half(w);
        }
        if (cross(v, w) != 0) {
            return cross(v, w) > 0;
        }
        return sq(v) < sq(w);
    });
}

void polarSortAround(pt o, vector<pt> &v) {
    sort(v.begin(), v.end(), [o](const pt &v, const pt &w) {
        // TODO
        if (half(v, o) != half(w, o)) {
            // or half(v) > half(w) depending on which half first
            return half(v, o) < half(w, o);
        }
        if (cross(v, w, o) != 0) {
            return cross(v, w, o) > 0;
        }
        return sq(v - o) < sq(w - o);
    });
}

// sort by atan2(x, y)
// sort the points in counterclockwise order that starts from the half line x <= 0, y = 0
// start from the 3rd quadrant and end at the 2nd quadrant
void sort_argument(vector<pt> &v) {
    // atan2(y, x)
    sort(v.begin(), v.end(), [&](pt a, pt b) {
        return atan2l(a.y, a.x) < atan2l(b.y, b.x);
    });
}

// sort points counter-clockwise around center
void sort_ccw(vector<pt> &v) {
    pt center(0, 0);
    for (auto p: v) {
        center += p;
    }
    center /= (int) v.size();

    sort(v.begin(), v.end(), [&](pt a, pt b) {
        T ang1 = atan2l(a.y - center.y, a.x - center.x);
        T ang2 = atan2l(b.y - center.y, b.x - center.x);
        return ang1 < ang2;
    });
}
