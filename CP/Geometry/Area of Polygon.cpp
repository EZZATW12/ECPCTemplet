#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

const T PI = acos(-1.0);

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

T areaPolygon(vector<pt> p) {
    T area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n-1
    }
    // if area >= 0, the points are ordered counter-clockwise else ordered clockwise
    return abs(area) / 2.0;
}

// calculates the area of a regular polygon when n is number of sides of the polygon and r is radius of the circumscribed circle (distance from center to a vertex)
T area_polygon(int n, T r) {
    return 0.5L * n * r * r * sin(2.0L * PI / n);
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

    cout << fixed << setprecision(9) << areaPolygon(p) << '\n';

    return 0;
}
