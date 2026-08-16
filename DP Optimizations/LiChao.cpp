#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll OO = 1e18 + 5;   // Represents infinity. Used as a baseline for minimum queries.
const ll maxN = 1e6 + 5;  // The maximum x-coordinate range the tree will cover [0, maxN-1].
// Since this is a sparse tree, you could safely increase this to 1e9 or 1e18.

/**
 * Represents a single linear function: y = m*x + c
 */
struct Line {
    ll m, c;
    // Default constructor creates a line at "infinity" (used for empty nodes)
    Line() : m(0), c(OO) {}
    Line(ll m, ll c) : m(m), c(c) {}
};

// Evaluates the y-value of line 'l' at a specific x-coordinate
ll sub(ll x, Line l) {
    return x * l.m + l.c;
}

/**
 * Sparse Li Chao Tree Node
 * Maintains the line that gives the minimum value at the midpoint of its range.
 */
struct node {
    Line line;           // The line that is optimal at the midpoint of this node's range
    node *left, *right;  // Pointers to the left and right halves of the domain

    node() {
        left = right = NULL;
    }

    node(ll m, ll c) {
        line = Line(m, c);
        left = right = NULL;
    }

    // Lazily creates child nodes only if we traverse down to them
    void extend(int l, int r) {
        if (left == NULL && l != r) {
            left = new node();
            right = new node();
        }
    }

    // Core insertion logic (O(log(range)))
    void add(Line toAdd, int l, int r) {
        assert(l <= r);
        int mid = (l + r) / 2;

        // Base case: We reached a single coordinate (leaf node)
        if (l == r) {
            if (sub(l, toAdd) < sub(l, line))
                swap(toAdd, line); // Keep the one that gives the smaller y
            return;
        }

        extend(l, r); // Ensure children exist before pushing down

        // Standard Li Chao Tree logic:
        // 1. Ensure 'line' has the smaller slope (for consistency in pushing down)
        if(toAdd.m < line.m)
            swap(toAdd, line);

        // 2. Compare the lines at the right half of the range.
        // If 'toAdd' is better on the right, push the old 'line' left and keep 'toAdd'.
        // Otherwise, push 'toAdd' right.
        if(sub(mid+1, line) < sub(mid+1, toAdd))
            left->add(toAdd, l, mid);
        else{
            swap(line, toAdd);
            right->add(toAdd, mid+1, r);
        }
    }

    // Helper to add a line over the default domain [0, maxN-1]
    void add(Line toAdd) {
        add(toAdd, 0, maxN-1);
    }

    // Core query logic (O(log(range)))
    // Finds the minimum y-value at coordinate x among all lines stored.
    ll query(ll x, int l, int r) {
        int mid = (l + r) / 2;

        // If we hit a leaf or an empty node, just evaluate the line here
        if (l == r || left == NULL)
            return sub(x, line);

        extend(l, r);

        // Take the minimum of the line at the current node and the line in the relevant child
        if (x <= mid)
            return min(sub(x, line), left->query(x, l, mid));
        else
            return min(sub(x, line), right->query(x, mid+1, r));
    }

    // Helper to query over the default domain [0, maxN-1]
    ll query(ll x) {
        return query(x, 0, maxN-1);
    }

    // IMPORTANT: Recursively deletes the tree to prevent Memory Leaks.
    // Always call this at the end of a test case!
    void clear() {
        if (left != NULL) {
            left->clear();
            right->clear();
        }
        delete this;
    }
};

// =========================================================================
// EXAMPLE USAGE DEMONSTRATION
// =========================================================================
int main() {
    // ---------------------------------------------------------
    // SCENARIO 1: Querying for the MINIMUM (Default Behavior)
    // ---------------------------------------------------------
    node* min_tree = new node(); // Create the root of the tree

    // Add lines: y = -2x + 10, y = 1x + 2
    min_tree->add(Line(-2, 10));
    min_tree->add(Line(1, 2));

    // Query at x = 2
    // Line 1: -2(2) + 10 = 6
    // Line 2: 1(2) + 2 = 4   <-- Minimum
    cout << "Min at x=2: " << min_tree->query(2) << "\n";

    // Memory Cleanup
    min_tree->clear();


    // ---------------------------------------------------------
    // SCENARIO 2: Querying for the MAXIMUM (The Negation Trick)
    // ---------------------------------------------------------
    node* max_tree = new node();

    // We want to add lines: y = -2x + 10, y = 1x + 2
    // RULE: To find the max, add the NEGATED slope and NEGATED intercept.
    // Original: y = -2x + 10  -> Negated: y = 2x - 10
    // Original: y = 1x + 2    -> Negated: y = -1x - 2
    max_tree->add(Line(-(-2), -(10)));
    max_tree->add(Line(-(1), -(2)));

    // Query at x = 2
    // RULE: Negate the answer!
    // Line 1 (actual): -2(2) + 10 = 6  <-- Maximum
    // Line 2 (actual): 1(2) + 2 = 4
    ll max_ans = -(max_tree->query(2));
    cout << "Max at x=2: " << max_ans << "\n";

    // Memory Cleanup
    max_tree->clear();

    return 0;
}