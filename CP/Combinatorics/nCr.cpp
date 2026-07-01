#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
vector<long long> fact(N + 5), inv(N + 5);

long long fp(long long b, long long p) {
    long long res = 1;
    while (p) {
        if (p & 1) {
            res = (1LL * res * b) % mod;
        }
        b = (1LL * b * b) % mod;
        p >>= 1;
    }
    return res;
}

void preCalc() {
    fact[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (1LL * i * fact[i - 1]) % mod;
        inv[i] = fp(fact[i], mod - 2);
    }
}

long long nCr(long long n, long long r) {
    if (r > n) return 0;
    return (1LL * ((1LL * fact[n] * inv[r]) % mod) * inv[n - r]) % mod;
}


// n up to 1e10 and r up to 1e5
int nCr(int n, int r) {
    long long ret = 1;
    for (int i = 0; i < r; ++i) {
        ret = ret * ((n - i) % mod) % mod;
    }
    ret *= inv[r];
    ret %= mod;
    return ret;
}

// without mod
long long nCr(long long n, long long r) {
    long long ans = 1;
    for (int i = 1; i <= r; ++i) {
        ans = ans * (n - r + i) / i;
    }
    return ans;
}