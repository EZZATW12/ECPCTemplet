#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int pw[N], ipw[N], mod_inv, mod;

int phi(int n) {
    int ret = n;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            ret -= ret / i;
        }
    }
    if (n > 1) ret -= ret / n;
    return ret;
}

long long fp(long long b, long long p) {
    long long res = 1;
    while (p) {
        if (p & 1) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        p >>= 1;
    }
    return res;
}

void preClc() {
    mod_inv = phi(mod) - 1;
    pw[0] = ipw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = (10LL * pw[i - 1]) % mod;
        ipw[i] = fp(pw[i], mod_inv);
    }
}
