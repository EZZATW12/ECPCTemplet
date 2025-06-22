//
// Created by Ezzat on 6/22/2025.
//
const int M = 2;

int mul(const ll &a,const ll&b){
    return (a % mod + mod) * (b % mod + mod) % mod;
}

int add(const ll &a,const ll&b){
    return (a + b + 2 * mod)%mod;
}

typedef array<array<int,M>,M> matrix;

matrix operator*(const matrix &lhs, const matrix &rhs) {
    matrix ret{};
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            for (int k = 0; k < M; ++k)
                ret[i][k] = add(ret[i][k], mul(lhs[i][j],rhs[j][k]));
    return ret;
}

matrix Identity(int n) {
    matrix ret={};
    for (int i = 0; i < n; ++i) {
        ret[i][i] = 1;
    }
    return ret;
}

matrix mat_power(matrix x, ll p) {
    matrix res = Identity(x.size());
    while (p) {
        if (p & 1) res = (res * x);
        x = (x * x);
        p >>= 1;
    }
    return res;
}