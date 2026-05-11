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

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

pt perp(pt p) {
    return {-p.y, p.x};
}

// find intersection points of two circles
int circleCircle(pt o1, T r1, pt o2, T r2, pair<pt, pt> &out) {
    pt d = o2 - o1;
    T d2 = sq(d);
    if (!sgn(d2)) {
        // concentric circles
        assert(r1 != r2);
        return 0;
    }

    T pd = (d2 + r1 * r1 - r2 * r2) / 2; // = |O_1P| * d
    T h2 = r1 * r1 - pd * pd / d2; // = h^2
    if (sgn(h2) != -1) {
        pt p = o1 + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
        // if 1 intersection h = 0
        out = {p - h, p + h};
    }
    return 1 + sgn(h2); // number of intersection points
}