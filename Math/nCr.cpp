int  fact[N], inv[N], pw[N];

int fp(int b, int p) {
    int r = 1;
    while (p) {
        if (p & 1) r = (1ll * r * b) % mod;
        b = (1ll * b * b) % mod;
        p >>= 1;
    }
    return r;
}

void preCalc() {
    pw[0] = fact[0] = inv[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (1ll * fact[i - 1] * i) % mod;
        inv[i] = fp(fact[i], mod - 2);
        pw[i] = pw[i - 1] + pw[i - 1];
        if (pw[i] >= mod) pw[i] -= mod;
    }
}

int ncr(int n, int r) {
    assert(n >= r && r >= 0);
    return 1ll * (1ll * fact[n] * inv[r] % mod) * inv[n - r] % mod;
}
