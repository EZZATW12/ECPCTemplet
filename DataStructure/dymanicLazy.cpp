//
// Created by ezzat on 6/27/2026.
//
struct Node {
    ll val;
    ll lazy;
    Node *left;
    Node *right;

    Node(ll v = 0) {
        val = v % mod;
        lazy = 0;
        left = nullptr;
        right = nullptr;
    }
};

struct PointerSegTree {
    Node *root;
    ll min_v, max_v;

    PointerSegTree(ll L = 0, ll R = 1e18) {
        root = new Node();
        min_v = L;
        max_v = R;
    }

    ll get_val(Node *node) {
        return node ? node->val : 0;
    }

    void push_up(Node *node) {
        if (node) {
            node->val = (get_val(node->left) + get_val(node->right)) % mod;
        }
    }

    void push_down(Node *node, ll l, ll r) {
        if (!node || node->lazy == 0 || l == r) return;

        if (!node->left) node->left = new Node();
        if (!node->right) node->right = new Node();

        ll mid = l + (r - l) / 2;
        ll lz = node->lazy;

        // Safely calculate lengths with modulo to prevent overflow
        ll len_left = (mid - l + 1) % mod;
        ll len_right = (r - mid) % mod;

        node->left->val = (node->left->val + (lz * len_left) % mod) % mod;
        node->left->lazy = (node->left->lazy + lz) % mod;

        node->right->val = (node->right->val + (lz * len_right) % mod) % mod;
        node->right->lazy = (node->right->lazy + lz) % mod;

        node->lazy = 0;
    }

    void update(Node *&u, ll l, ll r, ll ql, ll qr, ll val) {
        if (!u) u = new Node();

        if (ql <= l && r <= qr) {
            ll len = (r - l + 1) % mod;
            val %= mod;
            u->val = (u->val + (val * len) % mod) % mod;
            u->lazy = (u->lazy + val) % mod;
            return;
        }

        push_down(u, l, r);
        ll mid = l + (r - l) / 2;

        if (ql <= mid) update(u->left, l, mid, ql, qr, val);
        if (qr > mid) update(u->right, mid + 1, r, ql, qr, val);

        push_up(u);
    }

    void update(ll ql, ll qr, ll val) {
        update(root, min_v, max_v, ql, qr, val);
    }

    ll query(Node *u, ll l, ll r, ll ql, ll qr) {
        if (!u || l > qr || r < ql) return 0;

        if (ql <= l && r <= qr) return u->val;

        push_down(u, l, r);
        ll mid = l + (r - l) / 2;

        ll left_sum = query(u->left, l, mid, ql, qr);
        ll right_sum = query(u->right, mid + 1, r, ql, qr);

        return (left_sum + right_sum) % mod;
    }

    ll query(ll ql, ll qr) {
        return query(root, min_v, max_v, ql, qr);
    }
};