#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T dot(pt v, pt w) {
    return v.x * w.x + v.y * w.y;
}

double angle(pt v, pt w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    double a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << fixed << setprecision(9) << angle({a, b}, {c, d}) << '\n';

    return 0;
}
