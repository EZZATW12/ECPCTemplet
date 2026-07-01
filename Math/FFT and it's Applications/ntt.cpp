const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.


ll modpow(ll b, ll e) {
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1) ans = ans * b % mod;
    return ans;
}

// Primitive Root of the mod of form 2^a * b + 1
int generator() {
    vector<int> fact;
    int phi = mod - 1, n = phi;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back(n);

    for (int res = 2; res <= mod; ++res) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= modpow(res, phi / fact[i]) != 1;
        if (ok) return res;
    }
    return -1;
}

#include <bits/stdc++.h>

using namespace std;

namespace NTT {
    const int MOD = 998244353;
    const int G = 3; // Primitive root for 998244353

    // Fast modular exponentiation
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

    // Modular inverse
    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

    // In-place Number Theoretic Transform
    void ntt(vector<long long> &a, bool invert) {
        int n = a.size();

        // Bit-reversal permutation
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        // Cooley-Tukey iterative butterfly
        for (int len = 2; len <= n; len <<= 1) {
            long long wlen = power(G, (MOD - 1) / len);
            if (invert) wlen = modInverse(wlen);

            for (int i = 0; i < n; i += len) {
                long long w = 1;
                for (int j = 0; j < len / 2; j++) {
                    long long u = a[i + j];
                    long long v = (a[i + j + len / 2] * w) % MOD;

                    // Optimized modulo arithmetic for the inner loop
                    a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                    a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                    w = (w * wlen) % MOD;
                }
            }
        }

        // Scale for inverse transform
        if (invert) {
            long long n_inv = modInverse(n);
            for (long long &x: a) x = (x * n_inv) % MOD;
        }
    }

    // Black Box Polynomial Multiplication
    vector<long long> multiply(const vector<long long> &a, const vector<long long> &b) {
        if (a.empty() || b.empty()) return {};

        // Calculate the exact mathematical size of the resulting polynomial
        int expected_size = a.size() + b.size() - 1;

        vector<long long> fa(a.begin(), a.end()), fb(b.begin(), b.end());

        int n = 1;
        // Find the nearest power of 2 bounded by the expected size
        while (n < expected_size) n <<= 1;

        fa.resize(n, 0);
        fb.resize(n, 0);

        ntt(fa, false);
        ntt(fb, false);

        for (int i = 0; i < n; i++) {
            fa[i] = (fa[i] * fb[i]) % MOD;
        }

        ntt(fa, true);

        // Resize to exactly N + M - 1 to strip only the padding added for the power of 2
        fa.resize(expected_size);

        return fa;
    }
} // namespace NTT
vector<long long> pw(vector<long long> b, int p) {
    vector<long long> ans(1, 1);
    while (p) {
        if (p & 1) ans = NTT::multiply(ans, b);
        b = NTT::multiply(b, b);
        p >>= 1;
    }
    return ans;
}

ll CRT(ll a, ll m1, ll b, ll m2) {
    __int128 m = m1 * m2;
    ll ans = a * m2 % m * modpow(m2, m1 - 2, m1) % m + m1 * b % m * modpow(m1, m2 - 2, m2) % m;
    return ans % m;
}


/*

int mod, root, desired_mod = 1000000007;
const int mod1 = 167772161;
const int mod2 = 469762049;
const int mod3 = 754974721;
const int root1 = 3;
const int root2 = 3;
const int root3 = 11;

int CRT(int a, int b, int c, int m1, int m2, int m3) {
    __int128 M = (__int128)m1*m2*m3;
    ll M1 = (ll)m2*m3;
    ll M2 = (ll)m1*m3;
    ll M3 = (ll)m2*m1;

    int M_1 = modpow(M1%m1, m1 - 2, m1);
    int M_2 = modpow(M2%m2, m2 - 2, m2);
    int M_3 = modpow(M3%m3, m3 - 2, m3);

    __int128 ans = (__int128)a*M1*M_1;
    ans += (__int128)b*M2*M_2;
    ans += (__int128)c*M3*M_3;

    return (ans % M) % desired_mod;
}