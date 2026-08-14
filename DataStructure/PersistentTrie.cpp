#include <vector>

using namespace std;

// K is the maximum number of bits (Use 30 for numbers up to 10^9, or 15 for 10^4)
template <int K = 30>
struct PersistentTrie {
    struct Node {
        int nxt[2];
        int max_time;
    };

    vector<Node> trie;
    vector<int> roots;

    PersistentTrie() {
        // Initialize Node 0 as the "null" node
        // Its max_time is -1, meaning it will never satisfy a valid range query >= l
        trie.push_back({{0, 0}, -1});
        roots.push_back(0); // roots[0] is the empty trie before any insertions
    }

    // Insert 'val' at index 'time'.
    // Note: It is assumed that 'time' starts at 1 and increases sequentially.
    void insert(int val, int time) {
        int prev_u = roots.back();
        int curr_u = trie.size();
        roots.push_back(curr_u);

        // Create the new root node copying the previous version's children
        trie.push_back({trie[prev_u].nxt[0], trie[prev_u].nxt[1], time});

        for (int i = K - 1; i >= 0; --i) {
            int bit = (val >> i) & 1;
            int new_node = trie.size();
            int next_prev_u = trie[prev_u].nxt[bit];

            // Create the new intermediate node
            trie.push_back({trie[next_prev_u].nxt[0], trie[next_prev_u].nxt[1], time});

            // Link it to our current path
            trie[curr_u].nxt[bit] = new_node;

            curr_u = new_node;
            prev_u = next_prev_u;
        }
    }

    // Get maximum (x ^ A[j]) for j in [l, r]
    int get_max_xor(int x, int l, int r) {
        if (l > r || r >= roots.size()) return -1; // Invalid range safeguard
        int u = roots[r];
        if (trie[u].max_time < l) return -1; // No valid elements in the queried range

        int ans = 0;
        for (int i = K - 1; i >= 0; --i) {
            int bit = (x >> i) & 1;
            int target = bit ^ 1; // To maximize XOR, we want the opposite bit

            if (trie[trie[u].nxt[target]].max_time >= l) {
                ans |= (1 << i);
                u = trie[u].nxt[target];
            } else {
                u = trie[u].nxt[1 - target]; // Forced to take the same bit
            }
        }
        return ans;
    }

    // Get minimum (x ^ A[j]) for j in [l, r]
    int get_min_xor(int x, int l, int r) {
        if (l > r || r >= roots.size()) return -1;
        int u = roots[r];
        if (trie[u].max_time < l) return -1;

        int ans = 0;
        for (int i = K - 1; i >= 0; --i) {
            int bit = (x >> i) & 1;
            int target = bit; // To minimize XOR, we want the exact same bit

            if (trie[trie[u].nxt[target]].max_time >= l) {
                // Match found, the XOR at this bit is 0, so we don't add to 'ans'
                u = trie[u].nxt[target];
            } else {
                // Forced to take the opposite bit, adding to the XOR sum
                ans |= (1 << i);
                u = trie[u].nxt[1 - target];
            }
        }
        return ans;
    }
};