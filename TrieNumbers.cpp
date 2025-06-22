
struct Trie {
    vector <vector<int>> trie;
    vector<int> cnt;
//    vector<int>leaves;
    int mxBit, sz;

    int addNode() {
        trie.emplace_back(2, -1);
        cnt.emplace_back();
//        leaves.emplace_back();
        sz++;
        return sz - 1;
    }

    Trie(int mx = 60) : mxBit(mx), sz(0) {
        addNode();
    };

    // insert or remove
    void insert(ll x, int type = 1) {
        int cur = 0;
        cnt[cur] += type;
        for (int i = mxBit; i >= 0; --i) {
            int t = (x >> i) & 1;
            if (trie[cur][t] == -1)
                trie[cur][t] = addNode();
            cur = trie[cur][t];
            cnt[cur] += type;
        }
//        leaves[cur] += type;
    }

    ll maxXor(ll x) {
        // no elements in trie
        int cur = 0;
        if (!cnt[cur])return -1e9;
        for (int i = mxBit; i >= 0; --i) {
            int t = (x >> i) & 1 ^ 1;
            if (trie[cur][t] == -1 || !cnt[trie[cur][t]])t ^= 1;
            cur = trie[cur][t];
            if (t)x ^= 1ll << i;
        }
        return x;
    }
};