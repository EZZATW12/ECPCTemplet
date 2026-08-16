#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;

const T EPS = 1e-9;
const T PI = acos(-1.0);

#define X real()
#define Y imag()

int sgn(T val) {
    return (val > EPS) - (val < -EPS);
}

T dot(pt v, pt w) { return (conj(v) * w).real(); }
T cross(pt v, pt w) { return (conj(v) * w).imag(); }
T sq(pt p) { return dot(p, p); }

T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
pt prep(pt p) { return {-p.Y, p.X}; }
pt perp(pt p) { return {-p.Y, p.X}; }

bool half(pt p) {
    return p.Y > 0.0 || (p.Y == 0.0 && p.X < 0.0);
}

/**
 * Time Complexity: O(N log N)
 * Floating Point: No (integer-safe, uses cross product and squared distances)
 * Requirements: None
 */
void polarSort(vector<pt> &v) {
    sort(v.begin(), v.end(), [](pt a, pt b) {
        return make_tuple(half(a), 0.0, sq(a)) < make_tuple(half(b), cross(a, b), sq(b));
    });
}

void polarSort(vector<pt> &v, pt o) {
    sort(v.begin(), v.end(), [&](pt a, pt b) {
        return make_tuple(half(a - o), 0.0, sq(a - o)) < make_tuple(half(b - o), cross(a - o, b - o), sq(b - o));
    });
}

