//
// Created by ezzat on 6/27/2026.
//
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

struct Node {
    ll val;
    Node *left;
    Node *right;

    Node(ll v = 0) {
        val = v % mod;
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

    void update(Node *&u, ll l, ll r, ll pos, ll val) {
        if (!u) u = new Node();

        if (l == r) {
            val %= mod;
            // Assuming addition update. Change to u->val = val if assignment is needed.
            u->val = (u->val + val) % mod;
            return;
        }

        ll mid = l + (r - l) / 2;

        if (pos <= mid) update(u->left, l, mid, pos, val);
        else update(u->right, mid + 1, r, pos, val);

        push_up(u);
    }

    void update(ll pos, ll val) {
        update(root, min_v, max_v, pos, val);
    }

    ll query(Node *u, ll l, ll r, ll ql, ll qr) {
        // If we hit a null pointer or are completely out of bounds, sum is 0
        if (!u || l > qr || r < ql) return 0;

        // If the current segment is completely inside the query range
        if (ql <= l && r <= qr) return u->val;

        ll mid = l + (r - l) / 2;

        ll left_sum = query(u->left, l, mid, ql, qr);
        ll right_sum = query(u->right, mid + 1, r, ql, qr);

        return (left_sum + right_sum) % mod;
    }

    ll query(ll ql, ll qr) {
        return query(root, min_v, max_v, ql, qr);
    }
};