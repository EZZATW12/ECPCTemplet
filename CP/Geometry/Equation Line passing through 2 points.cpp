#include <bits/stdc++.h>
using namespace std;

typedef long double T;
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
    pt v; // Direction vector of the line
    T c;  // Cross-product constant: cross(v, P) = c for any point P on the line

    // 1. Construct from raw direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}

    // 2. Construct from standard equation: ax + by - c = 0
    // (Note: Fixed the c(-c) bug. For ax + by = c, the struct's 'c' is just 'c')
    line(T a, T b, T c) : v({b, -a}), c(c) {}

    // 3. Construct from two points P and Q
    // Direction is Q - P, offset is calculated using cross product of v and P
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

    // 4. Determines which side of the line point P is on
    // Returns > 0 for Left, < 0 for Right, 0 if perfectly collinear
    T side(pt p) {
        return cross(v, p) - c;
    }

    // 5. Shortest absolute distance from point P to the infinite line
    T dist(pt p) {
        return abs(side(p)) / abs(v);
    }

    // 6. Returns a new line perpendicular to this one, passing through point P
    line perpThrough(pt p) {
        return {p, p + perp(v)};
    }

    // 7. Used for sorting points. Compares the projection of P and Q onto the line.
    // Returns true if P comes before Q when traveling along the line's direction v.
    bool cmpProj(pt p, pt q) {
        return dot(v, p) < dot(v, q);
    }

    // 8. Translates the entire line by a 2D shift vector 't'
    line translate(pt t) {
        return {v, c + cross(v, t)};
    }

    // 9. Shifts the line parallel to itself to the left by a scalar 'dist'
    line shiftLeft(T dist) {
        return {v, c + dist * abs(v)};
    }

    // 10. Orthogonal projection: "Drops" point P perfectly onto the line
    pt proj(pt p) {
        return p - perp(v) * side(p) / sq(v);
    }

    // 11. Reflection: Treats the line as a mirror and reflects point P across it
    pt refl(pt p) {
        return p - perp(v) * (T) 2.0 * side(p) / sq(v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    line l({x1, y1}, {x2, y2});

    cout << fixed << setprecision(15) << l.v.imag() << ' ' << -l.v.real() << ' ' << l.c << '\n';

    return 0;
}
