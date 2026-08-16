#include <vector>

using namespace std;

// K is the maximum number of bits (Use 30 for numbers up to 10^9, or 15 for 10^4)
template <int K = 30>
struct PersistentTrie {
    struct Node {
        int nxt[2];
        int max_time;
        int count; // Added: Tracks number of elements in this subtree
    };

    vector<Node> trie;
    vector<int> roots;

    PersistentTrie() {
        // Initialize Node 0 as the "null" node with count 0
        trie.push_back({{0, 0}, -1, 0});
        roots.push_back(0);
    }

    void insert(int val, int time) {
        int prev_u = roots.back();
        int curr_u = trie.size();
        roots.push_back(curr_u);

        // Create root node, incrementing the count from the previous version
        trie.push_back({trie[prev_u].nxt[0], trie[prev_u].nxt[1], time, trie[prev_u].count + 1});

        for (int i = K - 1; i >= 0; --i) {
            int bit = (val >> i) & 1;
            int new_node = trie.size();
            int next_prev_u = trie[prev_u].nxt[bit];

            // Create intermediate node, incrementing the count
            trie.push_back({trie[next_prev_u].nxt[0], trie[next_prev_u].nxt[1], time, trie[next_prev_u].count + 1});

            trie[curr_u].nxt[bit] = new_node;

            curr_u = new_node;
            prev_u = next_prev_u;
        }
    }

    // Number of elements j in [l, r] such that (A[j] ^ x) < k
    int get_count_less_xor(int x, int k, int l, int r) {
        if (l > r || r >= roots.size() || l < 1) return 0;

        int u = roots[r];
        int v = roots[l - 1]; // Use the (l-1)-th version to subtract out of range elements
        int ans = 0;

        for (int i = K - 1; i >= 0; --i) {
            int bx = (x >> i) & 1;
            int bk = (k >> i) & 1;

            if (bk == 1) {
                // To get a bit 0, target must be equal to bx (bx ^ target = 0)
                int target = bx;
                ans += trie[trie[u].nxt[target]].count - trie[trie[v].nxt[target]].count;

                // Move forward forcing bit 1 to keep comparing with k
                u = trie[u].nxt[bx ^ 1];
                v = trie[v].nxt[bx ^ 1];
            } else {
                // k's bit is 0, we must force a 0 to not exceed k
                u = trie[u].nxt[bx];
                v = trie[v].nxt[bx];
            }
        }
        return ans;
    }

    // Number of elements j in [l, r] such that (A[j] ^ x) > k
    int get_count_greater_xor(int x, int k, int l, int r) {
        if (l > r || r >= roots.size() || l < 1) return 0;

        int u = roots[r];
        int v = roots[l - 1];
        int ans = 0;

        for (int i = K - 1; i >= 0; --i) {
            int bx = (x >> i) & 1;
            int bk = (k >> i) & 1;

            if (bk == 0) {
                // To get a bit 1, target must be opposite of bx (bx ^ target = 1)
                int target = bx ^ 1;
                ans += trie[trie[u].nxt[target]].count - trie[trie[v].nxt[target]].count;

                // Move forward forcing bit 0 to keep comparing with k
                u = trie[u].nxt[bx];
                v = trie[v].nxt[bx];
            } else {
                // k's bit is 1, we must force a 1 to not fall below k
                u = trie[u].nxt[bx ^ 1];
                v = trie[v].nxt[bx ^ 1];
            }
        }
        return ans;
    }

    // Get maximum (x ^ A[j]) for j in [l, r]
    int get_max_xor(int x, int l, int r) {
        if (l > r || r >= roots.size()) return -1;
        int u = roots[r];
        if (trie[u].max_time < l) return -1;

        int ans = 0;
        for (int i = K - 1; i >= 0; --i) {
            int bit = (x >> i) & 1;
            int target = bit ^ 1;

            if (trie[trie[u].nxt[target]].max_time >= l) {
                ans |= (1 << i);
                u = trie[u].nxt[target];
            } else {
                u = trie[u].nxt[1 - target];
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
            int target = bit;

            if (trie[trie[u].nxt[target]].max_time >= l) {
                u = trie[u].nxt[target];
            } else {
                ans |= (1 << i);
                u = trie[u].nxt[1 - target];
            }
        }
        return ans;
    }
};