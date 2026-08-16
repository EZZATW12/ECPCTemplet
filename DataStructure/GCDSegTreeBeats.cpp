#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 2e18;

struct GCDSegTree {
    struct Node {
        ll sum;
        ll mx, mn;
        ll lcm;
        ll lazy_set; // -1 means no pending lazy update
    };

    int n;
    vector<Node> tree;

    GCDSegTree(const vector<ll>& a) {
        n = a.size();
        tree.assign(4 * n + 5, {0, 0, 0, 1, -1});
        if (n > 0) build(1, 0, n - 1, a);
    }

private:
    // Helper to safely calculate LCM without Integer Overflow
    ll safe_lcm(ll a, ll b) {
        if (a == INF || b == INF) return INF;
        ll g = std::gcd(a, b);
        // If (a / g) * b exceeds INF, cap it at INF
        if ((INF / b) < (a / g)) return INF;
        return (a / g) * b;
    }

    void push_up(int u) {
        int lc = u << 1, rc = u << 1 | 1;
        tree[u].sum = tree[lc].sum + tree[rc].sum;
        tree[u].mx = max(tree[lc].mx, tree[rc].mx);
        tree[u].mn = min(tree[lc].mn, tree[rc].mn);
        tree[u].lcm = safe_lcm(tree[lc].lcm, tree[rc].lcm);
    }

    void apply_set(int u, int l, int r, ll v) {
        if (!u) return;
        tree[u].sum = v * (r - l + 1);
        tree[u].mx = v;
        tree[u].mn = v;
        tree[u].lcm = v;
        tree[u].lazy_set = v;
    }

    void push_down(int u, int l, int r) {
        if (tree[u].lazy_set != -1) {
            int mid = l + (r - l) / 2;
            apply_set(u << 1, l, mid, tree[u].lazy_set);
            apply_set(u << 1 | 1, mid + 1, r, tree[u].lazy_set);
            tree[u].lazy_set = -1;
        }
    }

    void build(int u, int l, int r, const vector<ll>& a) {
        if (l == r) {
            tree[u].sum = tree[u].mx = tree[u].mn = tree[u].lcm = a[l];
            tree[u].lazy_set = -1;
            return;
        }
        int mid = l + (r - l) / 2;
        build(u << 1, l, mid, a);
        build(u << 1 | 1, mid + 1, r, a);
        push_up(u);
    }

    void update_gcd(int u, int l, int r, int ql, int qr, ll x) {
        if (ql <= l && r <= qr) {
            // Break Condition: The update 'x' is a multiple of all elements here.
            // Meaning gcd(A[i], x) = A[i]. Nothing changes!
            if (tree[u].lcm != INF && x % tree[u].lcm == 0) return;

            // Tag Condition: All elements in this segment are exactly the same number.
            if (tree[u].mx == tree[u].mn) {
                apply_set(u, l, r, std::gcd(tree[u].mx, x));
                return;
            }
        }
        push_down(u, l, r);
        int mid = l + (r - l) / 2;
        if (ql <= mid) update_gcd(u << 1, l, mid, ql, qr, x);
        if (qr > mid) update_gcd(u << 1 | 1, mid + 1, r, ql, qr, x);
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
    // --- PUBLIC BLACK BOX FUNCTIONS ---

    // Applies A[i] = gcd(A[i], x) to all elements in range [l, r]
    void range_gcd(int l, int r, ll x) {
        if (l <= r && l >= 0 && r < n)
            update_gcd(1, 0, n - 1, l, r, x);
    }

    // Returns the total sum of elements in range [l, r]
    ll get_sum(int l, int r) {
        if (l <= r && l >= 0 && r < n)
            return query_sum(1, 0, n - 1, l, r);
        return 0;
    }
};

// =========================================================================
// EXAMPLE USAGE
// =========================================================================
int main() {
    // Array: {4, 6, 8, 12, 15}
    vector<ll> arr = {4, 6, 8, 12, 15};
    GCDSegTree st(arr);

    cout << "Initial Sum: " << st.get_sum(0, 4) << "\n"; // 45

    // Apply gcd(A[i], 6) to indices [1, 3] (Values: 6, 8, 12)
    // gcd(6,6)=6, gcd(8,6)=2, gcd(12,6)=6
    // Array becomes: {4, 6, 2, 6, 15}
    st.range_gcd(1, 3, 6);

    cout << "Sum after Range GCD: " << st.get_sum(0, 4) << "\n"; // 33

    return 0;
}