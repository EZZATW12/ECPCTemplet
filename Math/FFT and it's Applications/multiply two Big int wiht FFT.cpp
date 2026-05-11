#include <bits/stdc++.h>

using namespace std;
// Fast Fourier Transform (FFT)
// Time Complexity: O(N log N)
// Space Complexity: O(N)
namespace FFT {
    const double PI = acos(-1.0);

    // Lightweight custom complex struct to bypass std::complex overhead
    struct C {
        double x, y;

        C(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}

        inline C operator+(const C &o) const { return C(x + o.x, y + o.y); }

        inline C operator-(const C &o) const { return C(x - o.x, y - o.y); }

        inline C operator*(const C &o) const { return C(x * o.x - y * o.y, x * o.y + y * o.x); }

        inline C operator/(const double &d) const { return C(x / d, y / d); }
    };

    void fft(vector<C> &a, bool invert) {
        int n = a.size();
        // Bit-reversal permutation
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        // Iterative FFT
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            C wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                C w(1);
                for (int j = 0; j < len / 2; j++) {
                    C u = a[i + j];
                    C v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w = w * wlen;
                }
            }
        }

        if (invert) {
            for (C &x: a) x = x / n;
        }
    }

    // O(N log N) Black-Box Polynomial Multiplication
    // Returns the exact integer coefficients of A(x) * B(x)
    vector<long long> multiply(const vector<int> &a, const vector<int> &b) {
        if (a.empty() || b.empty()) return {};

        vector<C> fa(a.begin(), a.end());
        vector<C> fb(b.begin(), b.end());

        int n = 1;
        while (n < a.size() + b.size()) n <<= 1; // Pad to next power of 2
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++) {
            fa[i] = fa[i] * fb[i];
        }
        fft(fa, true);

        vector<long long> res(a.size() + b.size() - 1);
        for (int i = 0; i < res.size(); i++) {
            // round() is strictly necessary to fix floating-point inaccuracies
            res[i] = round(fa[i].x);
        }
        return res;
    }
}

string Big_int_multipler(const string &s1, const string &s2) {
    int n = s1.size(), m = s2.size();

    vector<int> poly1(n), poly2(m);
    for (int i = 0; i < n; ++i) {
        poly1[n - i - 1] = s1[i] - '0';
    }

    for (int i = 0; i < m; ++i) {
        poly2[m - i - 1] = s2[i] - '0';
    }

    vector<long long> ans = FFT::multiply(poly1, poly2);
    int k = ans.size();

    for (int i = 0; i < k - 1; ++i) {
        ans[i + 1] += ans[i] / 10;
        ans[i] = ans[i] % 10;
    }

    string final = to_string(ans[k - 1]);
    for (int i = k - 2; i >= 0; --i) {
        final += (char) (ans[i] + '0');
    }

    for (int i = 0; i < k; ++i) {
        if (final[i] != '0') return final.substr(i);
    }
    return "0";
}

string power_of_big_int(string s, int p) {
    string ans = "1";
    while (p) {
        if (p & 1) ans = Big_int_multipler(ans, s);
        s = Big_int_multipler(s, s);
        p >>= 1;
    }
    return ans;
}

void solve() {
    string a;
    int p;
    cin >> a >> p;
    cout << power_of_big_int(a, p);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}