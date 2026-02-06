//
// Created by Ezzat on 6/2/2025.
//
struct BIT {
    vector<long long> tree;

    BIT(int _n = N) {
        tree.resize(_n + 2);
    }

    long long get(int k) {
        long long ret = 0;
        for (int i = ++k; i >= 1; i -= i & -i) {
            ret += tree[i];
        }
        return ret;
    }

    void update(int k, long long v) {
        for (int i = ++k; i < tree.size(); i += i & -i) {
            tree[i] += v;
        }
    }

    long long query(int l, int r) {
        return get(r) - get(l - 1);
    }

    // binary search for first prefix with sum x
    long long BS(long long x) {
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