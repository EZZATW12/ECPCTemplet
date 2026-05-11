#include <bits/stdc++.h>

using namespace std;

// Arbitrary Modulo Polynomial Multiplication (MTT)
// Safely multiplies polynomials under ANY modulo (e.g., 1e9+7)
// Time Complexity: O(N log N)
namespace MTT {
    const double PI = acos(-1.0);

    // Ultra-lightweight complex number to bypass std::complex overhead
    struct C {
        double x, y;

        C(double _x = 0, double _y = 0) : x(_x), y(_y) {}

        inline C operator+(const C &o) const { return C(x + o.x, y + o.y); }

        inline C operator-(const C &o) const { return C(x - o.x, y - o.y); }

        inline C operator*(const C &o) const { return C(x * o.x - y * o.y, x * o.y + y * o.x); }

        inline C operator/(const double &d) const { return C(x / d, y / d); }

        inline C conj() const { return C(x, -y); }
    };

    void fft(vector<C> &a) {
        int n = a.size(), L = 31 - __builtin_clz(n);

        // Static caching: roots of unity are precomputed ONCE across all test cases
        static vector<C> R(2, C(1, 0)), rt(2, C(1, 0));
        for (static int k = 2; k < n; k *= 2) {
            R.resize(n);
            rt.resize(n);
            double ang = PI / k;
            C x(cos(ang), sin(ang));
            for (int i = k; i < 2 * k; i++) {
                rt[i] = R[i] = (i & 1) ? R[i / 2] * x : R[i / 2];
            }
        }

        vector<int> rev(n);
        for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | ((i & 1) << L)) / 2;
        for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);

        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    C z = rt[j + k] * a[i + j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }

    // O(N log N) - Returns A(x) * B(x) % MOD
    vector<long long> multiply(const vector<long long> &a, const vector<long long> &b, long long mod) {
        if (a.empty() || b.empty()) return {};

        vector<long long> res(a.size() + b.size() - 1);
        int n = 1;
        while (n < res.size()) n <<= 1;

        int cut = sqrt(mod);
        vector<C> L(n), R(n), outs(n), outl(n);

        // Split coefficients into (big * cut + small)
        for (size_t i = 0; i < a.size(); i++) L[i] = C(a[i] / cut, a[i] % cut);
        for (size_t i = 0; i < b.size(); i++) R[i] = C(b[i] / cut, b[i] % cut);

        fft(L);
        fft(R);

        // Extract 4 convolutions from 2 FFTs using conjugate symmetry
        for (int i = 0; i < n; i++) {
            int j = (n - i) & (n - 1);
            C out_l_j = (L[i] + L[j].conj()) * R[i] / (2.0 * n);
            C L_sub = L[i] - L[j].conj();
            C mult = L_sub * R[i] / (2.0 * n);

            outs[j] = C(mult.y, -mult.x); // mathematically equivalent to: mult / 1i
            outl[j] = out_l_j;
        }

        fft(outl);
        fft(outs);

        for (size_t i = 0; i < res.size(); i++) {
            long long av = round(outl[i].x);
            long long cv = round(outs[i].y);
            long long bv = round(outl[i].y) + round(outs[i].x);

            av %= mod;
            bv %= mod;
            cv %= mod;

            res[i] = ((av * cut % mod) * cut % mod + bv * cut % mod + cv) % mod;
            if (res[i] < 0) res[i] += mod;
        }
        return res;
    }
}
// Calculates the exact number of ways to form every subset sum
// Uses a priority queue to always multiply the smallest polynomials first (Huffman-style merge)
vector<long long> count_subset_sums(const vector<int>& coins, long long mod) {
    // Custom comparator so the priority queue puts the smallest vectors at the top
    auto cmp = [](const vector<long long>& a, const vector<long long>& b) {
        return a.size() > b.size();
    };
    priority_queue<vector<long long>, vector<vector<long long>>, decltype(cmp)> pq(cmp);

    // Step 1: Create the base polynomial (1 + x^v) for every coin
    for (int coin : coins) {
        vector<long long> poly(coin + 1, 0);
        poly[0] = 1;    // The choice to NOT pick the coin (x^0)
        poly[coin] = 1; // The choice TO pick the coin (x^v)
        pq.push(poly);
    }

    // Step 2: Divide and Conquer Merge
    while (pq.size() > 1) {
        vector<long long> A = pq.top(); pq.pop();
        vector<long long> B = pq.top(); pq.pop();

        // Multiply them using the MTT/FFT template
        vector<long long> C = MTT::multiply(A, B, mod);

        pq.push(C);
    }

    // Step 3: The final remaining polynomial contains all our answers
    return pq.top();
}
void solve() {
    long long MOD = 1e9 + 7;

    // Example: (2x + 1000000000) * (3x + 5)
    vector<long long> A = {1000000000, 2};
    vector<long long> B = {5, 3};

    vector<long long> C = MTT::multiply(A, B, MOD);

    // Print the coefficients modulo 1e9+7
    for (long long x: C) cout << x << " ";
}