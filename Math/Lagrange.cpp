struct LagrangePoly {
    vector<long long> y, den;
    void build(vector<long long> _a){
        //f(i) = _a[i]
        //f(x) has degree of y.size() - 1
        y = _a;
        den.resize(y.size());
        int n = (int) y.size();
        for (int i = 0; i < n; i++) {
            y[i] = (y[i] % MOD + MOD) % MOD;
            den[i] = inv[n - i - 1] * inv[i] % MOD;
            if ((n - i - 1) % 2 == 1) {
                den[i] = (MOD - den[i]) % MOD;
            }
        }
    }

    ll getVal(ll x) {
        int n = (int) y.size();
        x %= MOD;
        if (x < n) {
            return y[(int) x];
        }
        //O(N^2)
        /*long long ans = 0;
        for(int i = 0; i < n; i++) {
            long long cur = den[i];
            for(int j = 0; j < n; j++) {
                if(i == j) { continue; }
                cur = cur * (x - y[i] + MOD) % MOD;
            }
            ans = (ans + cur) % MOD;
        }
        return ans;*/
        // O(N)
        std::vector<long long> l, r;
        l.resize(n);
        l[0] = 1;
        for (int i = 1; i < n; i++) {
            l[i] = l[i - 1] * (x - (i - 1) + MOD) % MOD;
        }
        r.resize(n);
        r[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            r[i] = r[i + 1] * (x - (i + 1) + MOD) % MOD;
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long coef = l[i] * r[i] % MOD;
            ans = (ans + coef * y[i] % MOD * den[i]) % MOD;
        }
        return ans;
    }

};
