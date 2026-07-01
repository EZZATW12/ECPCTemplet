#include <bits/stdc++.h>
using namespace std;

struct node {
    int nxt[2]{}, sz = 0;

    int &operator[](int x) {
        return nxt[x];
    }
};

struct trie {
    const int bits = 31;
    vector<node> t;

    int new_node() {
        t.push_back(node());
        return t.size() - 1;
    }

    trie() {
        t.clear();
        new_node();
    }

    int sz(int u) {
        return t[u].sz;
    }

    void update(int x, int op) {
        int u = 0;
        for (int bit = bits - 1; bit >= 0; bit--) {
            int b = x >> bit & 1;
            if (!t[u][b]) {
                int id = new_node();
                t[u][b] = id;
            }
            u = t[u][b];
            t[u].sz += op;
        }
    }

    // find the number in the trie that gives the maximum XOR when XOR-ed with x.
    int query_max_xor(int x) {
        int u = 0, ret = 0;
        for (int bit = bits - 1; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            // Prefer the opposite bit for maximum XOR
            if (t[u][b ^ 1] && sz(t[u][b ^ 1])) {
                ret |= (1 << bit); // this bit contributes a 1 to XOR
                u = t[u][b ^ 1];
            } else {
                u = t[u][b];
            }
        }
        return ret;
    }

    // find the number in the trie that gives the minimum XOR when XOR-ed with a given number x
    int query_min_xor(int x) {
        int u = 0, ret = 0;
        for (int bit = bits - 1; bit >= 0; bit--) {
            int b = (x >> bit) & 1;
            // go the same bit to minimize XOR
            if (t[u][b] && sz(t[u][b])) {
                u = t[u][b];
            } else {
                ret |= (1 << bit); // XOR bit is 1 here
                u = t[u][b ^ 1];
            }
        }
        return ret;
    }

    // count of numbers in the trie such that: (x ^ num) < k
    int query(int x, int k) {
        int u = 0, ret = 0;
        for (int bit = bits - 1; bit >= 0; bit--) {
            int b_x = x >> bit & 1, b_k = k >> bit & 1;
            if (b_k) {
                ret += sz(t[u][b_x]);
            }
            u = t[u][b_x ^ b_k];
            if (!t[u].sz) {
                break;
            }
        }
        return ret + t[u].sz;
    }
};
