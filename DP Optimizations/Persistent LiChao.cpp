#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll OO = 1e18 + 5;

struct Line {
    ll m, c;
    Line() : m(0), c(OO) {} // Default line is "infinity"
    Line(ll m, ll c) : m(m), c(c) {}
};

ll sub(ll x, Line l) {
    return x * l.m + l.c;
}

struct PersistentLiChao {
    struct Node {
        int lc, rc;     // Indices of the left and right children
        Line line;      // The line responsible for this range
        Node() : lc(0), rc(0), line(Line()) {}
    };

    vector<Node> tree;
    ll minX, maxX;

    // Initializes the tree with the domain range [minX, maxX]
    PersistentLiChao(ll min_x = -1e9, ll max_x = 1e9) {
        minX = min_x;
        maxX = max_x;
        // tree[0] acts as the "null" or "empty" node
        tree.push_back(Node());
    }

    // Creates a new clone of an existing node to maintain persistence
    int copy_node(int u) {
        tree.push_back(tree[u]);
        return tree.size() - 1; // Return the index of the newly pushed node
    }

    // Internal recursive add function
    int add(int u, Line toAdd, ll l, ll r) {
        int cur = copy_node(u); // Always work on a new copy
        ll mid = l + (r - l) / 2;

        bool left_better = (sub(l, toAdd) < sub(l, tree[cur].line));
        bool mid_better = (sub(mid, toAdd) < sub(mid, tree[cur].line));

        // The line that is better at the midpoint becomes the new default for this segment
        if (mid_better) {
            swap(tree[cur].line, toAdd);
        }

        if (l == r) return cur; // Reached a leaf, stop recursion

        // If lines intersect, push the "loser" down to the child where it might still win
        if (left_better != mid_better) {
            tree[cur].lc = add(tree[cur].lc, toAdd, l, mid);
        } else {
            tree[cur].rc = add(tree[cur].rc, toAdd, mid + 1, r);
        }
        return cur;
    }

    // Call this to add a line to a specific version of the tree
    // Returns the root index of the NEW version of the tree
    int add(int root_version, ll m, ll c) {
        return add(root_version, Line(m, c), minX, maxX);
    }

    // Internal recursive query function
    ll query(int u, ll x, ll l, ll r) {
        if (!u) return OO; // If node doesn't exist, return infinity

        ll res = sub(x, tree[u].line);
        if (l == r) return res;

        ll mid = l + (r - l) / 2;
        if (x <= mid)
            return min(res, query(tree[u].lc, x, l, mid));
        else
            return min(res, query(tree[u].rc, x, mid + 1, r));
    }

    // Call this to find the minimum y at x, searching inside a specific tree version
    ll query(int root_version, ll x) {
        return query(root_version, x, minX, maxX);
    }

    // Call this between testcases to reset all memory
    void clear() {
        tree.assign(1, Node()); // Keeps only the empty 0-th node
    }
};



int main() {
    // 1. Create the data structure
    PersistentLiChao lct(-1e9, 1e9);

    // 2. Keep track of your roots.
    // Version 0 is an empty tree (root index 0)
    vector<int> roots;
    roots.push_back(0);

    // Update 1: Add line y = -2x + 10 to Version 0 -> Creates Version 1
    int root_v1 = lct.add(roots[0], -2, 10);
    roots.push_back(root_v1);

    // Update 2: Add line y = x + 2 to Version 1 -> Creates Version 2
    int root_v2 = lct.add(roots[1], 1, 2);
    roots.push_back(root_v2);

    // --- Time Travel Queries ---

    // Query at x = 4, but only using lines that existed in Version 1
    // (Only y = -2x + 10 exists here)
    // Result: -2(4) + 10 = 2
    cout << "Min at x=4 in V1: " << lct.query(roots[1], 4) << "\n";

    // Query at x = 4 using the latest lines (Version 2)
    // (y = -2x + 10 gives 2)
    // (y = x + 2 gives 6) -> Minimum is still 2
    cout << "Min at x=4 in V2: " << lct.query(roots[2], 4) << "\n";

    // Query at x = 0 using Version 2
    // (y = -2(0) + 10 = 10)
    // (y = 0 + 2 = 2) -> Minimum is 2
    cout << "Min at x=0 in V2: " << lct.query(roots[2], 0) << "\n";

    // 3. Clear memory before the next test case
    lct.clear();
    roots.clear();

    return 0;
}