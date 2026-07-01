#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct segtree {
    int sz = 1;

    T neutral;

    vector<T> t;
    function<T(T, T)> combine;

    segtree(int n, T init, function<T(T, T)> com) {
        while (sz < n) sz += sz;
        combine = com;
        neutral = init;
        t.resize(2 * sz);
    }

    void pull(int x) {
        t[x] = combine(t[2 * x], t[2 * x + 1]);
    }

    void build(int x, int lx, int rx, vector<T> &v) {
        if (lx == rx) {
            //TODO 1-based
            if (lx < (int) v.size()) {
                t[x] = v[lx];
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(2 * x, lx, m, v);
        build(2 * x + 1, m + 1, rx, v);
        pull(x);
    }

    void build(vector<T> &v) {
        build(1, 1, sz, v);
    }

    void set(int lx, int rx, int x, int idx, T val) {
        if (lx == rx) {
            // TODO
            t[x] = val;
            return;
        }
        int m = (lx + rx) >> 1;
        if (idx <= m) {
            set(lx, m, 2 * x, idx, val);
        } else {
            set(m + 1, rx, 2 * x + 1, idx, val);
        }
        t[x] = combine(t[2 * x], t[2 * x + 1]);
    }

    void set(int idx, T val) {
        set(1, sz, 1, idx, val);
    }

    T query(int x, int lx, int rx, int l, int r) {
        if (rx < l || lx > r) return neutral;
        if (lx >= l && rx <= r) return t[x];
        int m = (lx + rx) >> 1;
        return combine(query(2 * x, lx, m, l, r), query(2 * x + 1, m + 1, rx, l, r));
    }

    T query(int l, int r) {
        return query(1, 1, sz, l, r);
    }
};

int main() {
    segtree<long long> seg(n + 1, 0, [](long long a, long long b) {
        return a + b;
    });

    return 0;
}
