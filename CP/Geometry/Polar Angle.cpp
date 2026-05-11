#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    double a, b;
    cin >> a >> b;

    // atan2(y, x)
    // from origin
    // if not origin atan(dy, dx)
    double angle = atan2(b, a);
    if (angle < 0) angle += 2 * acos(-1.0);
    cout << fixed << setprecision(10) << angle;

    return 0;
}
