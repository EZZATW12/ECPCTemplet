//
// Created by ezzat on 6/27/2026.
//

/* =========================================================================
 * Pointer-Based (Dynamic) Segment Tree with Lazy Propagation
 * =========================================================================
 *
 * WHAT IT IS:
 * A Segment Tree that allocates nodes only when they are needed.
 * Standard segment trees require O(N) memory, which fails if your coordinate
 * range is massive (e.g., 1 to 10^18). This dynamic tree uses pointers to
 * achieve O(Q log(MAX_RANGE)) time and memory complexity for Q queries.
 *
 * CAPABILITIES:
 * - Range Updates: Add a value 'val' to all elements in range [ql, qr].
 * - Range Queries: Get the sum of elements in range [ql, qr].
 * - All operations are done modulo a global 'mod' variable.
 *
 * HOW TO USE IT:
 * 1. Define 'll' and 'mod' globally before this struct:
 *    typedef long long ll;
 *    const ll mod = 1e9 + 7;
 *
 * 2. Instantiate the tree with your minimum and maximum possible coordinates:
 *    PointerSegTree tree(1, 1e18); // Example: range from 1 to 10^18
 *
 * 3. Update a range [ql, qr] by adding 'val':
 *    tree.update(2, 10, 5); // Adds 5 to all indices from 2 to 10
 *
 * 4. Query the sum of a range [ql, qr]:
 *    ll sum = tree.query(4, 15); // Gets sum of indices from 4 to 15, modulo 'mod'
 * ========================================================================= */

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

    // Constructor: Initializes the segment tree with a given coordinate range [L, R].
    // Defaults to [0, 10^18] if no arguments are provided.
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

        // Dynamically create children if they don't exist yet
        if (!node->left) node->left = new Node();
        if (!node->right) node->right = new Node();

        ll mid = l + (r - l) / 2;
        ll lz = node->lazy;

        // Safely calculate lengths with modulo to prevent overflow
        ll len_left = (mid - l + 1) % mod;
        ll len_right = (r - mid) % mod;

        // Apply lazy value to left child
        node->left->val = (node->left->val + (lz * len_left) % mod) % mod;
        node->left->lazy = (node->left->lazy + lz) % mod;

        // Apply lazy value to right child
        node->right->val = (node->right->val + (lz * len_right) % mod) % mod;
        node->right->lazy = (node->right->lazy + lz) % mod;

        // Clear current node's lazy flag
        node->lazy = 0;
    }

    // Internal recursive update function
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

    // PUBLIC API: Add 'val' to all indices in the inclusive range [ql, qr]
    void update(ll ql, ll qr, ll val) {
        update(root, min_v, max_v, ql, qr, val);
    }

    // Internal recursive query function
    ll query(Node *u, ll l, ll r, ll ql, ll qr) {
        if (!u || l > qr || r < ql) return 0;

        if (ql <= l && r <= qr) return u->val;

        push_down(u, l, r);
        ll mid = l + (r - l) / 2;

        ll left_sum = query(u->left, l, mid, ql, qr);
        ll right_sum = query(u->right, mid + 1, r, ql, qr);

        return (left_sum + right_sum) % mod;
    }

    // PUBLIC API: Get the sum of elements in the inclusive range [ql, qr]
    ll query(ll ql, ll qr) {
        return query(root, min_v, max_v, ql, qr);
    }
};