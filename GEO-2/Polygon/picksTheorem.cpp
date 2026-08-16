/**
 * Time Complexity: O(N)
 * Floating Point: No for boundary & interior points, Yes for exact area
 * Requirements: Polygon coordinates must be integers.
 */
#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;

const T EPS = 1e-9;
const T PI = acos(-1.0);

#define X real()
#define Y imag()

T cross(pt v, pt w) { return (conj(v) * w).imag(); }

// Count of lattice points strictly on segment between integer points (x1, y1) and (x2, y2), inclusive of endpoints
long long segmentLatticePoints(long long x1, long long y1, long long x2, long long y2) {
    return std::gcd(std::abs(x1 - x2), std::abs(y1 - y2)) + 1;
}

// Boundary lattice points count B for a polygon with integer vertices
long long boundaryLatticePoints(const vector<pt> &p) {
    int n = p.size();
    long long B = 0;
    for (int i = 0; i < n; i++) {
        long long x1 = llround(p[i].X), y1 = llround(p[i].Y);
        long long x2 = llround(p[(i + 1) % n].X), y2 = llround(p[(i + 1) % n].Y);
        B += std::gcd(std::abs(x1 - x2), std::abs(y1 - y2));
    }
    return B;
}

// Pick's Theorem: Area = I + B/2 - 1
// Returns interior lattice points count I = (2*Area - B + 2) / 2
long long interiorLatticePoints(const vector<pt> &p) {
    int n = p.size();
    long long twice_area = 0;
    for (int i = 0; i < n; i++) {
        long long x1 = llround(p[i].X), y1 = llround(p[i].Y);
        long long x2 = llround(p[(i + 1) % n].X), y2 = llround(p[(i + 1) % n].Y);
        twice_area += (x1 * y2 - x2 * y1);
    }
    twice_area = std::abs(twice_area);
    long long B = boundaryLatticePoints(p);
    return (twice_area - B + 2) / 2;
}
