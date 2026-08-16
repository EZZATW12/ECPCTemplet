#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 2e18;

struct SegTreeBeats {
    struct Node {
        ll sum;
        ll max1, max2, max_c;
        ll min1, min2, min_c;
        ll lazy_add;
    };

    int n;
    vector<Node> tree;

    SegTreeBeats(const vector<ll>& a) {
        n = a.size();
        tree.assign(4 * n + 5, {0, -INF, -INF, 0, INF, INF, 0, 0});
        if (n > 0) build(1, 0, n - 1, a);
    }

private:
    void push_up(int u) {
        int lc = u << 1, rc = u << 1 | 1;
        tree[u].sum = tree[lc].sum + tree[rc].sum;

        // Merge Maxes
        if (tree[lc].max1 == tree[rc].max1) {
            tree[u].max1 = tree[lc].max1;
            tree[u].max_c = tree[lc].max_c + tree[rc].max_c;
            tree[u].max2 = max(tree[lc].max2, tree[rc].max2);
        } else if (tree[lc].max1 > tree[rc].max1) {
            tree[u].max1 = tree[lc].max1;
            tree[u].max_c = tree[lc].max_c;
            tree[u].max2 = max(tree[lc].max2, tree[rc].max1);
        } else {
            tree[u].max1 = tree[rc].max1;
            tree[u].max_c = tree[rc].max_c;
            tree[u].max2 = max(tree[lc].max1, tree[rc].max2);
        }

        // Merge Mins
        if (tree[lc].min1 == tree[rc].min1) {
            tree[u].min1 = tree[lc].min1;
            tree[u].min_c = tree[lc].min_c + tree[rc].min_c;
            tree[u].min2 = min(tree[lc].min2, tree[rc].min2);
        } else if (tree[lc].min1 < tree[rc].min1) {
            tree[u].min1 = tree[lc].min1;
            tree[u].min_c = tree[lc].min_c;
            tree[u].min2 = min(tree[lc].min2, tree[rc].min1);
        } else {
            tree[u].min1 = tree[rc].min1;
            tree[u].min_c = tree[rc].min_c;
            tree[u].min2 = min(tree[lc].min1, tree[rc].min2);
        }
    }

    void apply_add(int u, int l, int r, ll v) {
        if (!u) return;
        tree[u].sum += v * (r - l + 1);
        tree[u].max1 += v;
        if (tree[u].max2 != -INF) tree[u].max2 += v;
        tree[u].min1 += v;
        if (tree[u].min2 != INF) tree[u].min2 += v;
        tree[u].lazy_add += v;
    }

    void apply_chmin(int u, ll v) {
        if (!u || tree[u].max1 <= v) return;
        tree[u].sum -= (tree[u].max1 - v) * tree[u].max_c;

        // If the max was also acting as the min/min2, update those too!
        if (tree[u].min1 == tree[u].max1) tree[u].min1 = v;
        else if (tree[u].min2 == tree[u].max1) tree[u].min2 = v;

        tree[u].max1 = v;
    }

    void apply_chmax(int u, ll v) {
        if (!u || tree[u].min1 >= v) return;
        tree[u].sum += (v - tree[u].min1) * tree[u].min_c;

        // If the min was also acting as the max/max2, update those too!
        if (tree[u].max1 == tree[u].min1) tree[u].max1 = v;
        else if (tree[u].max2 == tree[u].min1) tree[u].max2 = v;

        tree[u].min1 = v;
    }

    void push_down(int u, int l, int r) {
        int mid = l + (r - l) / 2;
        int lc = u << 1, rc = u << 1 | 1;

        if (tree[u].lazy_add != 0) {
            apply_add(lc, l, mid, tree[u].lazy_add);
            apply_add(rc, mid + 1, r, tree[u].lazy_add);
            tree[u].lazy_add = 0;
        }

        // Push limits down
        apply_chmin(lc, tree[u].max1);
        apply_chmin(rc, tree[u].max1);
        apply_chmax(lc, tree[u].min1);
        apply_chmax(rc, tree[u].min1);
    }

    void build(int u, int l, int r, const vector<ll>& a) {
        if (l == r) {
            tree[u].sum = tree[u].max1 = tree[u].min1 = a[l];
            tree[u].max_c = tree[u].min_c = 1;
            tree[u].max2 = -INF;
            tree[u].min2 = INF;
            tree[u].lazy_add = 0;
            return;
        }
        int mid = l + (r - l) / 2;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        push_up(u);
    }

    void update_chmax(int u, int l, int r, int ql, int qr, ll v) {
        if (tree[u].min1 >= v) return; // Break Condition
        if (ql <= l && r <= qr && tree[u].min2 > v) { // Tag Condition
            apply_chmax(u, v);
            return;
        }
        push_down(u, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) update_chmax(u << 1, l, mid, ql, qr, v);
        if (qr > mid) update_chmax(u << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(u);
    }

    // (update_chmin and update_add follow the exact same logic structure, omitted from private for brevity but included in full code logic mentally. Just replicate the chmin/add logic from earlier but use the new push_down)

    void update_chmin(int u, int l, int r, int ql, int qr, ll v) {
        if (tree[u].max1 <= v) return;
        if (ql <= l && r <= qr && tree[u].max2 < v) {
            apply_chmin(u, v);
            return;
        }
        push_down(u, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) update_chmin(u << 1, l, mid, ql, qr, v);
        if (qr > mid) update_chmin(u << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(u);
    }

    void update_add(int u, int l, int r, int ql, int qr, ll v) {
        if (ql <= l && r <= qr) {
            apply_add(u, l, r, v);
            return;
        }
        push_down(u, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) update_add(u << 1, l, mid, ql, qr, v);
        if (qr > mid) update_add(u << 1 | 1, mid + 1, r, ql, qr, v);
        push_up(u);
    }

    ll query_sum(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[u].sum;
        push_down(u, l, r);
        int mid = l + (r - l) / 2;
        ll res = 0;
        if (ql <= mid) res += query_sum(u << 1, l, mid, ql, qr);
        if (qr > mid) res += query_sum(u << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }

public:
    // Apply A[i] = max(A[i], v)
    void chmax(int l, int r, ll v) {
        if (l <= r && l >= 0 && r < n) update_chmax(1, 0, n - 1, l, r, v);
    }

    // Apply A[i] = min(A[i], v)
    void chmin(int l, int r, ll v) {
        if (l <= r && l >= 0 && r < n) update_chmin(1, 0, n - 1, l, r, v);
    }

    // Add v to A[i]
    void add(int l, int r, ll v) {
        if (l <= r && l >= 0 && r < n) update_add(1, 0, n - 1, l, r, v);
    }

    ll get_sum(int l, int r) {
        if (l <= r && l >= 0 && r < n) return query_sum(1, 0, n - 1, l, r);
        return 0;
    }
};

// =========================================================================
// EXAMPLE USAGE
// =========================================================================
int main() {
    vector<ll> arr = {1, 2, 3, 4, 5};
    SegTreeBeats st(arr);

    // Array: {1, 2, 3, 4, 5}, Sum = 15
    cout << "Initial Sum: " << st.get_sum(0, 4) << "\n";

    // Apply chmax(3) to indices [0, 4]
    // Values less than 3 become 3.
    // Array becomes: {3, 3, 3, 4, 5}
    st.chmax(0, 4, 3);

    // Sum = 3 + 3 + 3 + 4 + 5 = 18
    cout << "Sum after chmax(3): " << st.get_sum(0, 4) << "\n";

    // Add 10 to everything
    // Array becomes: {13, 13, 13, 14, 15}
    st.add(0, 4, 10);

    // Apply chmin(13)
    // Values greater than 13 become 13.
    // Array becomes: {13, 13, 13, 13, 13}
    st.chmin(0, 4, 13);

    // Sum = 13 * 5 = 65
    cout << "Sum after add and chmin: " << st.get_sum(0, 4) << "\n";

    return 0;
}