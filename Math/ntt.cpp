const int G = 3;
const int mod = 998244353;

ll w_1[25], w[25];

ll binpow(ll a, ll b, ll m = mod)
{
    a %= m;
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
ll inverse(ll a, ll m = mod)
{
    return binpow(a, m - 2);
}
void ntt(vector<ll>&a, bool inv = false)
{
    int n = (int)a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2, lg = 1; len <= n; len <<= 1, lg++)
    {
        ll wlen = inv ? w_1[lg] : w[lg];
        for (int i = 0; i < n; i += len) {
            ll W = 1;
            for (int j = 0; j < len / 2; ++j) {
                ll u = a[i + j], v = a[i + j + len / 2] * W % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + len / 2] = (u - v + mod) % mod;
                W = W * wlen % mod;
            }
        }
    }
    if (inv) {
        ll n_1 = inverse(n);
        for (int i = 0; i < n; ++i)
            a[i] = a[i] * n_1 % mod;
    }
}

void init() {
    int h;

    for (h = 0; h <= 20; h++) {
        w[h] = binpow(3, (mod - 1) >> h);
        w_1[h] = binpow(3, mod - 1 - ((mod - 1) >> h));
    }
}