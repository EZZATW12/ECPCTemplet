#include <bits/stdc++.h>

using namespace std;

namespace FWHT {
    const int MOD = 998244353; // Change as needed

    // Modular exponentiation for inverse computation
    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    // Core FWHT function
    // type: 0 = XOR, 1 = AND, 2 = OR
    void fwht(vector<int> &a, int type, bool inv) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    int u = a[i + j];
                    int v = a[i + len + j];

                    if (type == 0) { // XOR
                        a[i + j] = (u + v >= MOD ? u + v - MOD : u + v);
                        a[i + len + j] = (u - v < 0 ? u - v + MOD : u - v);
                    } else if (type == 1) { // AND
                        if (!inv) {
                            a[i + j] = (u + v >= MOD ? u + v - MOD : u + v);
                        } else {
                            a[i + j] = (u - v < 0 ? u - v + MOD : u - v);
                        }
                    } else if (type == 2) { // OR
                        if (!inv) {
                            a[i + len + j] = (u + v >= MOD ? u + v - MOD : u + v);
                        } else {
                            a[i + len + j] = (v - u < 0 ? v - u + MOD : v - u);
                        }
                    }
                }
            }
        }

        // Scale down for Inverse XOR Transform
        if (type == 0 && inv) {
            long long invN = power(n, MOD - 2);
            for (int i = 0; i < n; i++) {
                a[i] = (1LL * a[i] * invN) % MOD;
            }
        }
    }

    // Wrapper for Convolutions
    // Automatically pads arrays to the next power of 2
    vector<int> convolute(vector<int> a, vector<int> b, int type) {
        int sz = max(a.size(), b.size());
        int n = 1;
        while (n < sz) n <<= 1;

        a.resize(n, 0);
        b.resize(n, 0);

        fwht(a, type, false);
        fwht(b, type, false);

        for (int i = 0; i < n; i++) {
            a[i] = (1LL * a[i] * b[i]) % MOD;
        }

        fwht(a, type, true);
        return a;
    }
}