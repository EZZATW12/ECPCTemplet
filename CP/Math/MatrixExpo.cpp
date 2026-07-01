#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7, matrix_size = 2;

struct matrix {
    vector<vector<long long> > mat;

    matrix() {
        mat.assign(matrix_size, vector<long long>(matrix_size));
    }

    matrix friend operator *(const matrix &a, const matrix &b) {
        matrix c;
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                c.mat[i][j] = 0;
                for (int u = 0; u < matrix_size; u++) {
                    c.mat[i][j] += (a.mat[i][u] * b.mat[u][j]) % mod;
                    c.mat[i][j] %= mod;
                }
            }
        }
        return c;
    }

    matrix friend operator +(const matrix &a, const matrix &b) {
        matrix c;
        for (int i = 0; i < matrix_size; i++) {
            for (int j = 0; j < matrix_size; j++) {
                c.mat[i][j] = (a.mat[i][j] + b.mat[i][j]) % mod;
                c.mat[i][j] %= mod;
            }
        }
        return c;
    }
};

matrix fp(matrix b, long long p) {
    matrix r;
    for (int i = 0; i < matrix_size; i++) {
        r.mat[i][i] = 1;
    }
    while (p) {
        if (p & 1) r = r * b;
        b = b * b;
        p >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto mul = [&](vector<int> &dp, matrix &mat) {
        vector<int> new_dp(matrix_size);
        for (int r = 0; r < matrix_size; r++) {
            const auto &row = mat.mat[r];
            for (int c = 0; c < matrix_size; c++) {
                new_dp[c] = (new_dp[c] + 1LL * dp[r] * row[c]) % mod;
            }
        }
        return new_dp;
    };

    return 0;
}
