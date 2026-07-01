#include <bits/stdc++.h>
using namespace std;

typedef double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T sq(pt p) {
    return p.x * p.x + p.y * p.y;
}

pt perp(pt p) {
    return {-p.y, p.x};
}

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

struct line {
    pt v;
    T c;

    // From direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {
    }

    // TODO
    // From equation ax + by - c = 0
    line(T a, T b, T c) : v({b, -a}), c(-c) {
    }

    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {
    }

    T side(pt p) {
        return cross(v, p) - c;
    }

    T dist(pt p) {
        return abs(side(p)) / abs(v);
    }

    line perpThrough(pt p) {
        return {p, p + perp(v)};
    }

    //  Sorting along a line
    bool cmpProj(pt p, pt q) {
        return dot(v, p) < dot(v, q);
    }

    //  translate a line l by vector t
    line translate(pt t) {
        return {v, c + cross(v, t)};
    }

    // s shifting line l to the left by a certain distance
    line shiftLeft(T dist) {
        return {v, c + dist * abs(v)};
    }

    pt proj(pt p) {
        return p - perp(v) * side(p) / sq(v);
    }

    pt refl(pt p) {
        return p - perp(v) * (T) 2.0 * side(p) / sq(v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    double x1, y1, a, b, c;
    cin >> x1 >> y1 >> a >> b >> c;

    line l(a, b, c);
    cout << fixed << setprecision(9) << l.dist({x1, y1}) << '\n';

    return 0;
}
