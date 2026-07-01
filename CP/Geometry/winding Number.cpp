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

// The number of times the polygon wraps around this point
int windingNumber(vector<pt> p, pt a) {
    T ampli = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        ampli += angleTravelled(a, p[i], p[(i + 1) % n]);
    }
    return round(ampli / (2 * M_PI));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    return 0;
}
