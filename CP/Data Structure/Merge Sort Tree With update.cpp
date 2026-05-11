#include <bits/stdc++.h>
using namespace std;

template<typename T>

struct mstree {
    int sz = 1;

    vector<T> a;
    vector<multiset<T> > t;

    mstree(int n) {
        while (sz < n) sz += sz;
        t.resize(2 * sz);
        a.assign(sz + 1, T());
    }

    void build(int x, int lx, int rx, vector<T> &v) {
        if (lx == rx) {
            if (lx < (int) v.size()) {
                t[x].insert(v[lx]);
                a[lx] = v[lx];
            }
            return;
        }

        int md = (lx + rx) >> 1;
        build(2 * x, lx, md, v);
        build(2 * x + 1, md + 1, rx, v);
        t[x].insert(t[2 * x].begin(), t[2 * x].end());
        t[x].insert(t[2 * x + 1].begin(), t[2 * x + 1].end());
    }

    void build(const vector<T> &v) {
        build(1, 1, sz, v);
    }

    // count of elements >= val in [l, r]
    int query(int x, int lx, int rx, int l, int r, T &val) {
        if (rx < l || lx > r) return 0;

        if (lx >= l && rx <= r) {
            auto it = t[x].lower_bound(val);
            return (int) distance(it, t[x].end()); // count how many elements are from it up to the end of the multiset
        }

        int md = (lx + rx) >> 1;
        return query(2 * x, lx, md, l, r, val) + query(2 * x + 1, md + 1, rx, l, r, val);
    }

    int query(int l, int r, T &val) {
        return query(1, 1, sz, l, r, val);
    }

    void update(int x, int lx, int rx, int pos, T &oldv, T &newv) {
        auto it = t[x].find(oldv);
        if (it != t[x].end()) {
            t[x].erase(it);
        }

        t[x].insert(newv);
        if (lx == rx) {
            a[pos] = newv;
            return;
        }

        int md = (lx + rx) >> 1;
        if (pos <= md) update(2 * x, lx, md, pos, oldv, newv);
        else update(2 * x + 1, md + 1, rx, pos, oldv, newv);
    }

    void update(int pos, T &newVal) {
        T oldVal = a[pos];
        update(1, 1, sz, pos, oldVal, newVal);
    }
};
