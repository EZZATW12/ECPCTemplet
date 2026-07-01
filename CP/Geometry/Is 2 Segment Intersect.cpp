#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

// determining the direction of the points (right, left, or on a line).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

//  checks if a point P lies on the disk of diameter [AB].
bool inDisk(pt a, pt b, pt p) {
    return dot(a - p, b - p) <= 0;
}

// check if a point P lies on segment [AB].
bool onSegment(pt a, pt b, pt p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

// Returns true if segments two intersect
bool segmentsIntersect(pt p1, pt q1, pt p2, pt q2) {
    T o1 = orient(p1, q1, p2);
    T o2 = orient(p1, q1, q2);
    T o3 = orient(p2, q2, p1);
    T o4 = orient(p2, q2, q1);

    // General Case: They intersect if the ends of one are on opposite sides of the other.
    if (o1 * o2 < 0 && o3 * o4 < 0) {
        return true;
    }

    if (o1 == 0 && onSegment(p1, q1, p2)) return true;
    if (o2 == 0 && onSegment(p1, q1, q2)) return true;
    if (o3 == 0 && onSegment(p2, q2, p1)) return true;
    if (o4 == 0 && onSegment(p2, q2, q1)) return true;

    return false;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    T x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    cout << (segmentsIntersect({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}) ? "YES" : "NO") << '\n';

    return 0;
}
