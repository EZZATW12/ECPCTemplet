// Lattice points are points on a grid whose coordinates are integers, like: (0,0), (2,3), (-1,5)
// They are usually divided into two types:
// 1) Boundary Lattice Points (B)
// Points with integer coordinates that lie on the edges of the polygon.
// 2) Interior Lattice Points (I)
// Points with integer coordinates that lie strictly inside the polygon (not on edges).

#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

T areaPolygon(vector<pt> p) {
    T area = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n-1
    }
    return abs(area);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n;
    cin >> n;

    vector<pt> p(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        p[i] = pt(a, b);
    }

    T area = areaPolygon(p), B = 0;

    // Pick Theorem -> area = I + (B / 2) - 1
    // Can you use Pick's theorem? If a polygon has all its vertices at integer coordinates (like (0,0), (3,2), (-1,4), etc.), then it is called a lattice polygon.
    for (int i = 0; i < n; i++) {
        pt p1 = p[i], p2 = p[(i + 1) % n];
        // the number of lattice points on a segment is gcd(|dx|, |dy|) + 1 including 2 points of segment
        B += gcd(abs(p1.x - p2.x), abs(p1.y - p2.y));
    }

    T two_I = area - B + 2, I = two_I / 2;
    cout << I << ' ' << B << '\n';

    return 0;
}
