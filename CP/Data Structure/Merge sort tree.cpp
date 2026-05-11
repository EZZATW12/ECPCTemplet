template<typename T>
struct mstree {
    int sz = 1;

    //TODO
    T neutral = 0;

    vector<vector<T> > t;

    mstree(int n) {
        while (sz < n) sz += sz;
        t.resize(2 * sz);
    }

    T combine(T a, T b) {
        //TODO
        return a + b;
    }

    void pull(int x) {
        t[x] = combine(t[2 * x], t[2 * x + 1]);
    }

    void build(int x, int lx, int rx, vector<T> &v) {
        if (lx == rx) {
            //TODO 1-based
            if (lx <= (int) (v.size())) {
                t[x].push_back(v[lx]);
            }
            return;
        }
        int m = (lx + rx) >> 1;
        build(2 * x, lx, m, v);
        build(2 * x + 1, m + 1, rx, v);
        t[x].resize(rx - lx + 1);
        merge(t[2 * x].begin(), t[2 * x].end(), t[2 * x + 1].begin(), t[2 * x + 1].end(), t[x].begin());
    }

    void build(vector<T> &v) {
        // assert(v.size() == sz);
        build(1, 1, sz, v);
    }

    // count of elements >= x and <= y
    // return upper_bound(t[x].begin(), t[x].end(), y) - lower_bound(t[x].begin(), t[x].end(), qx);

    // count of elements <= x in this node's range
    // return upper_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();

    // count of elements >= x in this node's range
    // return t[x].end() - lower_bound(t[x].begin(), t[x].end(), val);

    // count of elements < x in this node's range
    // lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();

    // count of elements > x in this node's range
    // tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), x);

    T query(int x, int lx, int rx, int l, int r, int val) {
        if (rx < l || lx > r) return neutral;
        if (lx >= l && rx <= r) {
            //TODO
            return t[x].end() - lower_bound(t[x].begin(), t[x].end(), val);
        }
        int m = (lx + rx) >> 1;
        return combine(query(2 * x, lx, m, l, r, val), query(2 * x + 1, m + 1, rx, l, r, val));
    }

    T query(int l, int r, int x) {
        // assert(l <= r && l >= 1 && r <= sz);
        return query(1, 1, sz, l, r, x);
    }
};
