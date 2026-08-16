#include <vector>
#include <array>

using namespace std;
typedef long long ll;

struct trie {
    vector<array<int, 3>> tree;
    int len;
    int total_elements;

    trie() {
        // [0] = left child (bit 0), [1] = right child (bit 1), [2] = count of elements
        tree.push_back({-1, -1, 0});
        len = 0;
        total_elements = 0;
    }

    // Unified insert/delete: delta = 1 to add, delta = -1 to remove
    void update(int val, int delta = 1) {
        int idx = 0;
        total_elements += delta;
        for (int i = 30; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (tree[idx][bit] == -1) {
                tree.push_back({-1, -1, 0});
                tree[idx][bit] = ++len;
            }
            idx = tree[idx][bit];
            tree[idx][2] += delta; // Update the count for the prefix
        }
    }

    // Number of val in trie such that (val ^ x) < k
    ll count_less(int x, int k) {
        ll ans = 0;
        int idx = 0;
        for (int i = 30; i >= 0; --i) {
            int bx = (x >> i) & 1;
            int bk = (k >> i) & 1;
            if (bk == 1) {
                // If k's bit is 1, a 0 in (val ^ x) is strictly smaller.
                // We add all elements that result in a 0 bit.
                if (tree[idx][bx] != -1) {
                    ans += tree[tree[idx][bx]][2];
                }
                // To keep checking, (val ^ x)'s bit must be 1 (matching k's bit)
                if (tree[idx][bx ^ 1] != -1 && tree[tree[idx][bx ^ 1]][2] > 0) {
                    idx = tree[idx][bx ^ 1];
                } else break;
            } else {
                // If k's bit is 0, (val ^ x)'s bit MUST be 0 to not exceed k
                if (tree[idx][bx] != -1 && tree[tree[idx][bx]][2] > 0) {
                    idx = tree[idx][bx];
                } else break;
            }
        }
        return ans;
    }

    // Number of val in trie such that (val ^ x) > k
    ll count_greater(int x, int k) {
        ll ans = 0;
        int idx = 0;
        for (int i = 30; i >= 0; --i) {
            int bx = (x >> i) & 1;
            int bk = (k >> i) & 1;
            if (bk == 0) {
                // If k's bit is 0, a 1 in (val ^ x) is strictly greater.
                // We add all elements that result in a 1 bit.
                if (tree[idx][bx ^ 1] != -1) {
                    ans += tree[tree[idx][bx ^ 1]][2];
                }
                // To keep checking, (val ^ x)'s bit must be 0 (matching k's bit)
                if (tree[idx][bx] != -1 && tree[tree[idx][bx]][2] > 0) {
                    idx = tree[idx][bx];
                } else break;
            } else {
                // If k's bit is 1, (val ^ x)'s bit MUST be 1 to not fall below k
                if (tree[idx][bx ^ 1] != -1 && tree[tree[idx][bx ^ 1]][2] > 0) {
                    idx = tree[idx][bx ^ 1];
                } else break;
            }
        }
        return ans;
    }

    // Maximum value of (val ^ x) for val in the trie
    ll max_xor(int x) {
        if (total_elements == 0) return -1; // Safety check for empty trie

        ll ans = 0;
        int idx = 0;
        for (int i = 30; i >= 0; --i) {
            int bx = (x >> i) & 1;
            int desired = bx ^ 1; // We want the opposite bit to maximize XOR

            if (tree[idx][desired] != -1 && tree[tree[idx][desired]][2] > 0) {
                ans |= (1LL << i);
                idx = tree[idx][desired];
            } else {
                // Forced to take the same bit (XOR results in 0 here)
                idx = tree[idx][desired ^ 1];
            }
        }
        return ans;
    }

    // Minimum value of (val ^ x) for val in the trie
    ll min_xor(int x) {
        if (total_elements == 0) return -1; // Safety check for empty trie

        ll ans = 0;
        int idx = 0;
        for (int i = 30; i >= 0; --i) {
            int bx = (x >> i) & 1;
            int desired = bx; // We want the same bit to minimize XOR

            if (tree[idx][desired] != -1 && tree[tree[idx][desired]][2] > 0) {
                // We matched the bit successfully (XOR results in 0 here)
                idx = tree[idx][desired];
            } else {
                // Forced to take the opposite bit
                ans |= (1LL << i);
                idx = tree[idx][desired ^ 1];
            }
        }
        return ans;
    }
};