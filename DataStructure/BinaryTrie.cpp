//
// Created by Ezzat on 6/2/2025.
//
struct trie {
    vector<array<int, 3>> tree;
    int len;

    trie() {
        tree.push_back({-1, -1, 0});
        len = 0;
    }

    void insert(int val) {
        int idx = 0;
        for (int i = 30; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (tree[idx][bit] == -1) {
                tree.push_back({-1, -1, 0});
                tree[idx][bit] = ++len;
            }
            tree[tree[idx][bit]][2]++;
            idx = tree[idx][bit];
        }
    }

    void delet(int val) {
        int idx = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = val >> i & 1;
            idx = tree[idx][bit];
            tree[idx][2]--;
        }
    }

    ll query(int x, int k) { // number of val in trie such that val^x smaller than k
        ll ans = 0, idx = 0;
        for (int i = 30; i >= 0; --i) {
            int bitx = (x >> i) & 1;
            int bitk = (k >> i) & 1;
            if (bitk) {
                if (tree[idx][bitx] != -1)ans += tree[tree[idx][bitx]][2];
                if (tree[idx][bitx ^ 1] == -1)break;
                idx = tree[idx][bitx ^ 1];
            } else {
                if (tree[idx][bitx] == -1)break;
                idx = tree[idx][bitx];
            }
        }
        return ans;
    }
};