#include <bits/stdc++.h>
using namespace std;

template<typename T>

struct segtree {
    int sz = 1;

    // TODO
    T neutral = 0;

    segtree() {
    }

    vector<T> t;

    segtree(int n, T init) {
        sz = n;
        t.resize(2 * sz);
        neutral = init;
    }

    T combine(T a, T b) {
        // TODO
        return a + b;
    }

    void build(vector<T> &v) {
        assert(sz == (int)v.size());
        for (int i = 0; i < sz; i++) t[sz + i] = v[i];
        for (int i = sz - 1; i >= 0; i--) {
            t[i] = combine(t[2 * i], t[2 * i + 1]);
        }
    }

    void update(int idx, T val) {
        assert(idx >= 1 && idx <= sz);
        t[idx + sz - 1] += val;
        for (idx += sz - 1; idx > 1; idx >>= 1) {
            t[idx >> 1] = combine(t[idx], t[idx ^ 1]);
        }
    }

    T query(int l, int r) {
        T ret = neutral;
        for (l += sz - 1, r += sz - 1; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) ret = combine(ret, t[l++]);
            if (~r & 1) ret = combine(ret, t[r--]);
        }
        return ret;
    }
};
