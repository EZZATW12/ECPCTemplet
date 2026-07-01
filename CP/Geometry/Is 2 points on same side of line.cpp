#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-9;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

int sgn(T val) {
    if (val > EPS) return 1;
    if (val < -EPS) return -1;
    return 0;
}

bool sameSide(pt p1, pt p2, T a, T b, T c) {
    T eq1 = a * p1.x + b * p1.y + c, eq2 = a * p2.x + b * p2.y + c;
    return (sgn(eq1 * eq2) >= 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    T x1, y1, x2, y2, a, b, c;
    cin >> x1 >> y1 >> x2 >> y2 >> a >> b >> c;

    cout << (sameSide({x1, y1}, {x2, y2}, a, b, c) ? "YES" : "NO") << '\n';

    return 0;
}
