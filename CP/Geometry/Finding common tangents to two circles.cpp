#include <bits/stdc++.h>
using namespace std;

typedef double T;
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

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

pt perp(pt p) {
    return {-p.y, p.x};
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

    // From equation ax + by = c
    line(T a, T b, T c) : v(b, -a), c(c) {
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

    T sqDist(pt p) {
        return side(p) * side(p) / (double) sq(v);
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

// finds 1 tangent between two circles assuming:
// first circle is centered at (0, 0) with radius r1
// second circle is centered at c with radius r2
void tangents(pt c, T r1, T r2, vector<line> &ans) {
    T r = r2 - r1, z = sq(c), d = z - r * r;
    if (d < -EPS || z < EPS) return;
    d = sqrt(max((T) 0.0, d));

    // compute coefficients (a, b, c) of line: ax + by = c
    T a = (c.x * r + c.y * d) / z;
    T b = (c.y * r - c.x * d) / z;
    T cc = r1;

    // convert (a, b, c) to line structure
    ans.emplace_back(a, b, cc);
}


// finds all common tangents between two circles
vector<line> tangents(pt ca, T ra, pt cb, T rb) {
    vector<line> ans;

    pt c = cb - ca;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            tangents(c, ra * i, rb * j, ans);
        }
    }

    for (line &l: ans) {
        l.c -= cross(l.v, ca);
    }
    return ans;
}