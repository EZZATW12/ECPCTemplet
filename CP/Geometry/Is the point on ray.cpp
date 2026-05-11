#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-9;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

bool isPointOnRay(pt p, pt s, pt e) {
    pt sp = p - s;
    pt se = e - s;

    bool same_dir_vector = abs(cross(se, sp)) < EPS; // vector se must be in the same direction as vector sp.
    bool same_dir_ray = dot(se, sp) >= -EPS; // The point must be in the same direction as the ray.

    return (same_dir_vector && same_dir_ray);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long double px, py, sx, sy, ex, ey;
    cin >> px >> py >> sx >> sy >> ex >> ey;

    pt p = {px, py}, s = {sx, sy}, e = {ex, ey};

    cout << (isPointOnRay(p, s, e) ? "YES" : "NO") << '\n';

    return 0;
}
