//
// Created by Ezzat on 6/2/2025.
//
struct BIT {
    vector <ll> tree;

    BIT(int _n = N) {
        tree.resize(_n + 2);
    }

    ll get(int k) {
        ll ret = 0;
        for (int i = ++k; i >= 1; i -= i & -i) {
            ret += tree[i];
        }
        return ans;
    }

    void update(int k, ll v) {
        for (int i = ++k; i < N; i += i & -i) {
            tree[i] += v;
        }
    }
    ll query(int l, int r) {
        return get(r) - get(l - 1);
    }

    // binary search for first prefix with sum x
    int BS(ll x) {
        int pos = 0;
        for (int sz = (1 << __lg(tree.size())); sz > 0 && x; sz >>= 1) {
            if (pos + sz < tree.size() && tree[pos + sz] < x) {
                x -= tree[pos + sz];
                pos += sz;
            }
        }
        return pos + 1;
    }
};