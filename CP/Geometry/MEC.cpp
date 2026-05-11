#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

T dist(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

T dist2(pt a, pt b) {
    return sqrt(dist(a, b));
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

pt perp(pt p) {
    return {-p.y, p.x};
}

// you can determine circle with 3 points
pt circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a; // consider coordinates relative to A
    // assert(cross(b, c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2.0L;
}

// a circle with minimum possible radius that contains all the n points, inside the circle or on its boundary
pair<pt, T> mec(vector<pt> &p) {
    if (p.empty()) {
        return make_pair(pt(0, 0), 0.0L);
    }

    shuffle(p.begin(), p.end(), mt19937(time(0)));

    pt center = p[0];
    T r = 0, EPS = 1e-8 + 1;
    for (int i = 0; i < p.size(); i++) {
        if (dist2(center, p[i]) > r * EPS) {
            center = p[i], r = 0;
            for (int j = 0; j < i; j++) {
                if (dist2(center, p[j]) > r * EPS) {
                    center = (p[i] + p[j]) / 2.0L;
                    r = dist2(center, p[i]);
                    for (int k = 0; k < j; k++) {
                        if (dist2(center, p[k]) > r * EPS) {
                            center = circumCenter(p[i], p[j], p[k]);
                            r = dist2(center, p[i]);
                        }
                    }
                }
            }
        }
    }
    return make_pair(center, r);
}
