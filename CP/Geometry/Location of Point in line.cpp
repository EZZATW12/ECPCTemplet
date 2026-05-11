#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

const long double EPS = 1e-9;

int sgn(T val) {
    if (val > EPS) return 1;
    if (val < -EPS) return -1;
    return 0;
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

// determine whether c is located on the left or right side of the line or if it touches the line when we are looking from a to b.
// determining the direction of the points (right -1, left 1, or on a line 0).
T orient(pt a, pt b, pt c) {
    return cross(b - a, c - a);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    T x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    T side = orient({x1, y1}, {x2, y2}, {x3, y3});
    if (sgn(side) == -1) {
        cout << "RIGHT\n";
    } else if (sgn(side) == 1) {
        cout << "LEFT\n";
    } else {
        cout << "TOUCH\n";
    }

    return 0;
}
