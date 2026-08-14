//
// Created by Ezzat on 6/22/2025.
//
using row = vector<ll>;
using Matrix = vector<row>;

Matrix mul(Matrix &a, Matrix &b) {
    int n = a.size(), m = a[0].size(), k = b[0].size();
    Matrix res(n, row(k));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int l = 0; l < m; ++l) {
                res[i][j] += (1ll * a[i][l] * b[l][j]) % mod;
                res[i][j] %= mod;
            }
        }
    }
    return res;
}

Matrix power(Matrix a, ll p) {
    int n = a.size();
    Matrix res(n, row(n));
    for (int i = 0; i < n; ++i)res[i][i] = 1;
    while (p) {
        if (p & 1) res = mul(res, a);
        a = mul(a, a), p >>= 1;
    }
    return res;
}