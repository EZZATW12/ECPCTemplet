#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;

#define ll long long
struct PersistentSegTree {
    struct Node {
        int l = 0;
        int r = 0;
        ll sum = 0;
    };

    int n;                 // The size of the array/range
    vector<Node> tree;     // The pool of all nodes
    vector<int> roots;     // Stores the root index for each version

    // Constructor: Pre-allocates memory to prevent slow reallocations
    PersistentSegTree(int array_size, int expected_updates = 100005) {
        n = array_size;

        // Calculate max nodes: base tree + (updates * log2(n))
        // +1000 for safety padding
        int max_nodes = (n * 4) + (expected_updates * 20) + 1000;
        tree.reserve(max_nodes);

        // Push the implicitly 0 "null" node at index 0
        tree.push_back(Node());

        // Initialize version 0 with an empty tree (root = 0)
        roots.push_back(0);
    }

    // Helper to create a new node, copying an existing one if requested
    inline int newNode(int copy_idx = 0) {
        tree.push_back(tree[copy_idx]);
        return tree.size() - 1;
    }

    // Recursive Build
    int _build(int l, int r, const vector<int>& a) {
        int curr = newNode();
        if (l == r) {
            tree[curr].sum = a[l];
            return curr;
        }
        int mid = l + (r - l) / 2;
        tree[curr].l = _build(l, mid, a);
        tree[curr].r = _build(mid + 1, r, a);
        tree[curr].sum = tree[tree[curr].l].sum + tree[tree[curr].r].sum;
        return curr;
    }

    // Recursive Update
    int _update(int prev_root, int l, int r, int idx, ll val) {
        int curr = newNode(prev_root); // Path Copying
        if (l == r) {
            tree[curr].sum += val;
            return curr;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            tree[curr].l = _update(tree[prev_root].l, l, mid, idx, val);
        } else {
            tree[curr].r = _update(tree[prev_root].r, mid + 1, r, idx, val);
        }
        tree[curr].sum = tree[tree[curr].l].sum + tree[tree[curr].r].sum;
        return curr;
    }

    // Recursive Query
    ll _query(int root, int l, int r, int ql, int qr) {
        if (!root || ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[root].sum;

        int mid = l + (r - l) / 2;
        return _query(tree[root].l, l, mid, ql, qr) +
               _query(tree[root].r, mid + 1, r, ql, qr);
    }

    // --- Public API ---

    // Build the initial version (Version 0) from an array
    void build_initial(const vector<int>& a) {
        roots[0] = _build(1, n, a);
    }

    // Perform an update on a previous version and save it as a NEW version
    // Returns the ID of the newly created version
    int update(int target_version, int idx, ll val) {
        int new_root = _update(roots[target_version], 1, n, idx, val);
        roots.push_back(new_root);
        return roots.size() - 1;
    }

    // Copy a previous version exactly without making changes
    void copy_version(int target_version) {
        roots.push_back(roots[target_version]);
    }

    // Query a specific version for the sum in range [L, R]
    ll query(int version, int L, int R) {
        return _query(roots[version], 1, n, L, R);
    }

    // Get total number of versions currently stored
    int get_version_count() const {
        return roots.size() - 1;
    }
};