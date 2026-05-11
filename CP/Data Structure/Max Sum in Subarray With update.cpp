#include <bits/stdc++.h>
using namespace std;

struct node {
    long long mx, sum, pre, mn_suf;

    node() {
        mx = sum = pre = mn_suf = 0;
    }

    node(long long v) {
        sum = v, mx = pre = mn_suf = max(0LL, v);
    }
};

node neutral() {
    node ret;
    ret.sum = 0;
    ret.mx = ret.pre = ret.mn_suf = -1e18;
    return ret;
}

struct segtree {
    int sz;
    vector<node> t;

    segtree() {
    }

    segtree(int n) {
        sz = 1;
        while (sz < n) sz += sz;
        t.resize(2 * sz);
    }

    node combine(node a, node b) {
        node ret(0);
        ret.sum = a.sum + b.sum;
        ret.pre = max(a.pre, a.sum + b.pre);
        ret.mn_suf = max(b.mn_suf, a.mn_suf + b.sum);
        ret.mx = max({a.mx, b.mx, a.mn_suf + b.pre});
        return ret;
    }

    void build(int lx, int rx, int x, vector<long long> &arr) {
        if (lx == rx) {
            if (lx < (int) arr.size()) {
                t[x] = node(arr[lx]);
            }
            return;
        }
        int md = (lx + rx) / 2;
        build(lx, md, 2 * x, arr);
        build(md + 1, rx, 2 * x + 1, arr);
        t[x] = combine(t[2 * x], t[2 * x + 1]);
    }

    void build(vector<long long> &arr) {
        build(1, sz, 1, arr);
    }

    void set(int lx, int rx, int x, int idx, long long val) {
        if (lx == rx) {
            t[x] = node(val);
            return;
        }

        int md = (lx + rx) / 2;
        if (idx <= md) set(lx, md, 2 * x, idx, val);
        else set(md + 1, rx, 2 * x + 1, idx, val);

        t[x] = combine(t[2 * x], t[2 * x + 1]);
    }

    void set(int idx, long long val) {
        set(1, sz, 1, idx, val);
    }

    node query(int x, int lx, int rx, int l, int r) {
        if (r < lx || l > rx) return neutral();
        if (lx >= l && rx <= r) {
            return t[x];
        }
        int m = (lx + rx) >> 1;
        node a = query(2 * x, lx, m, l, r);
        node b = query(2 * x + 1, m + 1, rx, l, r);
        return combine(a, b);
    }

    node query(int l, int r) {
        return query(1, 1, sz, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    segtree seg(n);

    seg.build(arr);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            long long p, x;
            cin >> p >> x;
            seg.set(p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.query(l, r).mx << '\n';
        }
    }

    return 0;
}
