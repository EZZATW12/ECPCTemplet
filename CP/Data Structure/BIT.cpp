#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT {
    int n;
    vector<T> bit; // TODO 1-Based

    BIT(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        bit.assign(n + 1, 0);
    }

    void build(const vector<T> &a) {
        for (int i = 1; i <= n; ++i) {
            bit[i] += a[i];
        }

        for (int i = 1; i <= n; ++i) {
            int j = i + (i & -i);
            if (j <= n) {
                bit[j] += bit[i];
            }
        }
    }

    void add(int idx, T delta) {
        while (idx <= n) {
            bit[idx] += delta;
            idx += idx & -idx;
        }
    }

    T sum(int idx) {
        T ret = 0;
        while (idx > 0) {
            ret += bit[idx];
            idx -= idx & -idx;
        }
        return ret;
    }

    T query(int l, int r) {
        if (r < l) return 0;
        return sum(r) - sum(l - 1);
    }

    // returns smallest index such that sum(i) >= k.
    int lower_bound(T k) {
        if (k <= 0) return 1;

        int pos = 0, bitMask = 1;
        while ((bitMask << 1) <= n) {
            bitMask <<= 1;
        }

        for (; bitMask; bitMask >>= 1) {
            int nxt = pos + bitMask;
            if (nxt <= n && bit[nxt] < k) {
                k -= bit[nxt];
                pos = nxt;
            }
        }
        return pos + 1;
    }
};