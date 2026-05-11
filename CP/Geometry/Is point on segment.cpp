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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long double px, py, sx, sy, ex, ey;
    cin >> px >> py >> sx >> sy >> ex >> ey;

    cout << (onSegment({sx, sy}, {ex, ey}, {px, py}) ? "YES\n" : "NO\n");

    return 0;
}
