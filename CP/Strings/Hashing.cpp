#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5, MODS = 2;
const array<int, MODS> mod = {1000003111, 1000003999};

array<int, MODS> p = {137, 277}, ip;
array<int, MODS> pw[N], ipw[N];

int fp(int b, int p, int mod) {
    int r = 1;
    while (p) {
        if (p & 1) {
            r = (1LL * r * b) % mod;
        }
        b = (1LL * b * b) % mod;
        p >>= 1;
    }
    return r;
}

// TODO DONT MISS CALL IT
void preCalc() {
    for (int j = 0; j < MODS; ++j) {
        ipw[0][j] = pw[0][j] = 1;
        ip[j] = fp(p[j], mod[j] - 2, mod[j]);
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < MODS; ++j) {
            pw[i][j] = (1LL * p[j] * pw[i - 1][j]) % mod[j];
            ipw[i][j] = (1LL * ip[j] * ipw[i - 1][j]) % mod[j];
        }
    }
}

struct Hashing {
    int n;
    vector<array<int, MODS> > hs, hr;

    Hashing() {
    }

    Hashing(string &s) {
        n = (int) s.size();
        hs.assign(n, array<int, MODS>{});
        hr.assign(n, array<int, MODS>{});

        // hash(abcd) = a*p^0 + b*p^1 + c*p^2 + d*p^3
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < MODS; j++) {
                hs[i][j] = ((i ? hs[i - 1][j] : 0) + (1LL * pw[i][j] * s[i]) % mod[j]) % mod[j];
            }
        }

        // rev_hash(abcd) = a*p^3 + b*p^2 + c*p^1 + d*p^0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < MODS; j++) {
                hr[i][j] = ((i ? hr[i - 1][j] : 0) + (1LL * pw[n - i - 1][j] * s[i]) % mod[j]) % mod[j];
            }
        }
    }

    // l, r 0-Based
    array<int, MODS> get_hash(int l, int r) {
        array<int, MODS> ret;
        for (int j = 0; j < MODS; j++) {
            ret[j] = ((hs[r][j] - (l ? hs[l - 1][j] : 0)) % mod[j] + mod[j]) % mod[j];
            ret[j] = (1LL * ret[j] * ipw[l][j]) % mod[j];
        }
        return ret;
    }

    array<int, MODS> get_rev_hash(int l, int r) {
        array<int, MODS> ret;
        for (int j = 0; j < MODS; j++) {
            ret[j] = ((hr[r][j] - (l ? hr[l - 1][j] : 0)) % mod[j] + mod[j]) % mod[j];
            ret[j] = (1LL * ret[j] * ipw[n - r + 1][j]) % mod[j];
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    preCalc();

    return 0;
}
