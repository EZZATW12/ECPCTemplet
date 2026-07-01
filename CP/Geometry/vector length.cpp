#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T dist(pt p, pt p2) {
    T dx = abs(p.x - p2.x), dy = abs(p.y - p2.y);
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long double x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    cout << fixed << setprecision(15) << dist({x1, y1}, {x2, y2}) << '\n';

    return 0;
}
