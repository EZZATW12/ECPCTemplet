#define rep(aa, bb, cc) for(int aa = bb; aa < cc;aa++)
#define sz(a) (int)a.size()
template<int MOD>
struct FWHT {
    int fast(int b, int e) {
        int res = 1;
        for(;e;e>>=1,b=1ll*b*b%MOD)
            if(e & 1)
                res = 1ll * res * b % MOD;
        return res;
    }
    inline int add(int x, int y) {
        return x + y - (x + y >= MOD? MOD : 0);
    }
    inline int sub(int x, int y) {
        return x - y + (x - y < 0? MOD : 0);
    }
    void FST(vi& a, bool inv) {
        for (int n = sz(a), step = 1; step < n; step *= 2) {
            for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
                    int &u = a[j], &v = a[j + step]; tie(u, v) =
                    //  inv ? pii(sub(v,u), u) : pii(v, add(u,v)); // AND
                    //  inv ? pii(v, sub(u,v)) : pii(add(u,v), u); // OR /// include-line
                        pair<ll,ll>(add(u,v), sub(u,v));           // XOR /// include-line
                }
        }
         if (inv) {
            int divisor = fast(sz(a), MOD - 2);
            for (int& x : a) x = 1ll * x * divisor % MOD; // XOR only /// include-line
         }
    }
    vi conv(vi a, vi b) {
        FST(a, 0); FST(b, 0);
        rep(i,0,sz(a)) a[i] = 1ll * a[i] * b[i] % MOD;
        FST(a, 1); return a;
    }
};
