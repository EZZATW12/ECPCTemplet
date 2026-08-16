//
// Created by ezzat on 6/27/2026.
//
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

/**
 * Node structure for the Dynamic (Pointer-based) Segment Tree.
 *
 * WHAT IT DOES:
 * Instead of allocating a massive fixed-size array (which would cause a Memory Limit Exceeded
 * for ranges up to 1e18), this tree dynamically creates nodes only when they are needed.
 */
struct Node {
    ll val;         // The sum of the segment, modulo 1e9+7
    Node *left;     // Pointer to the left child
    Node *right;    // Pointer to the right child

    Node(ll v = 0) {
        val = v % mod;
        left = nullptr;
        right = nullptr;
    }
};

/**
 * PointerSegTree (Dynamic Segment Tree)
 *
 * WHAT IT DOES:
 * It maintains the sum of elements over an enormous array (default range 0 to 1e18).
 * It supports two main operations efficiently (O(log(max_v - min_v)) time complexity):
 * 1. Point Update: Add a value to a specific index.
 * 2. Range Query: Get the sum of all values within a specific range [L, R].
 */
struct PointerSegTree {
    Node *root;
    ll min_v, max_v; // The minimum and maximum possible indices for the tree

    // Constructor initializes the tree with an overall range [L, R].
    // Defaults to 0 to 1e18, making it highly suitable for massive index constraints.
    PointerSegTree(ll L = 0, ll R = 1e18) {
        root = new Node();
        min_v = L;
        max_v = R;
    }

    // Safely retrieves the value of a node.
    // Returns 0 if the node hasn't been created yet (saving memory for empty segments).
    ll get_val(Node *node) {
        return node ? node->val : 0;
    }

    // Recalculates the current node's value by summing its left and right children.
    void push_up(Node *node) {
        if (node) {
            node->val = (get_val(node->left) + get_val(node->right)) % mod;
        }
    }

    // Internal recursive update function.
    // It travels down to 'pos' and creates new nodes along the path if they don't exist.
    void update(Node *&u, ll l, ll r, ll pos, ll val) {
        if (!u) u = new Node(); // Dynamically allocate memory only when visited

        // Base case: we reached the exact position (leaf node)
        if (l == r) {
            val %= mod;
            // Point addition: Adds 'val' to the current element.
            // (If you need to strictly assign a value, change this to: u->val = val)
            u->val = (u->val + val) % mod;
            return;
        }

        ll mid = l + (r - l) / 2; // Prevents overflow when L and R are massive

        // Route the update to the left or right child depending on where 'pos' falls
        if (pos <= mid) update(u->left, l, mid, pos, val);
        else update(u->right, mid + 1, r, pos, val);

        // After updating the leaf, update this current node's sum
        push_up(u);
    }

    // HOW TO USE - Update:
    // Call this to add 'val' to the element located at index 'pos'.
    void update(ll pos, ll val) {
        update(root, min_v, max_v, pos, val);
    }

    // Internal recursive range sum query function.
    ll query(Node *u, ll l, ll r, ll ql, ll qr) {
        // Base case 1: If we hit a null pointer (empty segment) or are completely
        // out of bounds of the query [ql, qr], the sum is 0.
        if (!u || l > qr || r < ql) return 0;

        // Base case 2: If the current segment [l, r] is completely enveloped
        // by the query range [ql, qr], return the node's entire value.
        if (ql <= l && r <= qr) return u->val;

        ll mid = l + (r - l) / 2;

        // Recursively gather sums from the left and right halves
        ll left_sum = query(u->left, l, mid, ql, qr);
        ll right_sum = query(u->right, mid + 1, r, ql, qr);

        // Return combined sum modulo 1e9+7
        return (left_sum + right_sum) % mod;
    }

    // HOW TO USE - Query:
    // Call this to get the total sum of elements in the inclusive range [ql, qr].
    ll query(ll ql, ll qr) {
        return query(root, min_v, max_v, ql, qr);
    }
};

// =========================================================================
// EXAMPLE USAGE DEMONSTRATION
// =========================================================================
int main() {
    // 1. Initialize the segment tree over a massive range
    //    (e.g., from index 1 up to index 1,000,000,000,000)
    PointerSegTree tree(1, 1e12);

    // 2. Perform point additions: tree.update(index, value)
    tree.update(5, 100);       // Add 100 at index 5
    tree.update(1000000, 50);  // Add 50 at index 1,000,000
    tree.update(5, 20);        // Add 20 more to index 5 (Index 5 is now 120)

    // 3. Perform range queries: tree.query(left_index, right_index)
    cout << "Sum [1, 10]: " << tree.query(1, 10) << "\n";             // Expected: 120
    cout << "Sum [10, 1000000]: " << tree.query(10, 1000000) << "\n"; // Expected: 50
    cout << "Sum [1, 1000000]: " << tree.query(1, 1000000) << "\n";   // Expected: 170

    return 0;
}