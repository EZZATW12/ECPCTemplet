#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct segtree {
    int sz = 1;

    T neutral;

    vector<T> t, lazy;
    function<T(T, T)> combine;

    segtree(int n, T init, function<T(T, T)> com) {
        while (sz < n) sz += sz;
        combine = com;
        neutral = init;
        t.resize(2 * sz);
        lazy.resize(2 * sz);
    }

    void pull(int x) {
        t[x] = combine(t[2 * x], t[2 * x + 1]);
    }

    void push(int x, int lx, int rx) {
        if (!lazy[x]) return;
        //TODO
        t[x] += lazy[x];
        if (lx != rx) {
            lazy[2 * x] += lazy[x];
            lazy[2 * x + 1] += lazy[x];
        }
        lazy[x] = 0;
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

    void update(int x, int lx, int rx, int l, int r, T val) {
        push(x, lx, rx);
        if (lx > r || rx < l) return;
        if (lx >= l && rx <= r) {
            lazy[x] += val;
            push(x, lx, rx);
            return;
        }
        int m = (lx + rx) >> 1;
        update(2 * x, lx, m, l, r, val);
        update(2 * x + 1, m + 1, rx, l, r, val);
        pull(x);
    }

    void update(int l, int r, T val) {
        update(1, 1, sz, l, r, val);
    }

    T query(int x, int lx, int rx, int l, int r) {
        push(x, lx, rx);
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    segtree<long long> mn(n + 1, LLONG_MAX, [](long long a, long long b) {
        return min(a, b);
    });
    mn.build(arr);


    return 0;
}
