#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-9;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    long double px, py, a, b, c;
    cin >> px >> py >> a >> b >> c;

    long double eq = px * a + py * b + c;

    cout << (abs(eq) < EPS ? "YES" : "NO") << '\n';

    return 0;
}
