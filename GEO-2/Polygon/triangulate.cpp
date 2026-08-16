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

int isPointInTriangle(pt a, pt b, pt c, pt p) {
    if (sgn(cross(b - a, c - a)) < 0) swap(b, c);
    int c1 = sgn(cross(b - a, p - a));
    int c2 = sgn(cross(c - b, p - b));
    int c3 = sgn(cross(a - c, p - c));
    if (c1 < 0 || c2 < 0 || c3 < 0) return 1;
    if (c1 + c2 + c3 != 3) return 0;
    return -1;
}

/**
 * Time Complexity: O(N^3)
 * Floating Point: No (integer-safe; relies on orient and isPointInTriangle)
 * Requirements: None
 */
// ear decomposition, O(n^3) but faster
vector<vector<pt>> triangulate(vector<pt> p) {
    vector<vector<pt>> v;
    while (p.size() >= 3) {
        for (int i = 0, n = p.size(); i < n; i++) {
            int pre = i == 0 ? n - 1 : i - 1;
            int nxt = i == n - 1 ? 0 : i + 1;
            int ori = sgn(orient(p[pre], p[i], p[nxt])); 
            if (ori < 0) { 
                int ok = 1;
                for (int j = 0; j < n; j++) {
                    if (j == i || j == pre || j == nxt) continue;
                    if (isPointInTriangle(p[pre], p[i], p[nxt], p[j]) < 1) { 
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    v.push_back({p[pre], p[i], p[nxt]});
                    p.erase(p.begin() + i);
                    break;
                }
            }
        }
    }
    return v;
}

