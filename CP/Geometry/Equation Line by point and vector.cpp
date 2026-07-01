#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long double xp, yp, vx, vy;
    cin >> xp >> yp >> vx >> vy;

    cout << fixed << setprecision(15) << vx << ' ' << vy << ' ' << -(vx * xp + vy * yp) << '\n';

    return 0;
}
