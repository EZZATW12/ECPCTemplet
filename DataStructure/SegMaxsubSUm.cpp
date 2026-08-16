struct item {
    long long seg, pref, suf, sum;
};

struct segtree {
    int size;
    vector<item> v;

    item merge(item a, item b) {
        return {
                max({a.seg, b.seg, a.suf + b.pref}),
                max(a.pref, a.sum + b.pref),
                max(b.suf, b.sum + a.suf),
                a.sum + b.sum
        };
    }

    // FIXED: The sum of an empty segment is 0.
    item NEUTRAL_ELEMENT = {0, 0, 0, 0}; // todo

    item single(long long u) {
        if (u > 0)
            return {u, u, u, u};
        else
            return {0, 0, 0, u};
    };

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        v.assign(2 * size, NEUTRAL_ELEMENT); // assign is safer than resize here
    }

    void set(int idx, long long val, int x, int lx, int rx) {
        if (rx - lx == 1) {
            v[x] = single(val);
            return;
        }
        int m = (lx + rx) >> 1;
        if (idx < m) {
            set(idx, val, 2 * x + 1, lx, m);
        } else {
            set(idx, val, 2 * x + 2, m, rx);
        }
        v[x] = merge(v[2 * x + 1], v[2 * x + 2]);
    }

    void set(int idx, long long val) {
        set(idx, val, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx) {
        if (lx >= l && rx <= r) return v[x];
        if (rx <= l || lx >= r) return NEUTRAL_ELEMENT;

        int m = (lx + rx) >> 1;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    long long calc(int l, int r) {
        // Query interval is [l, r). If your queries are [l, r] inclusive, 
        // you must call calc(l, r + 1) in your main function!
        return calc(l, r, 0, 0, size).seg;
    }
};