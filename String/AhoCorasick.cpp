struct Aho_corasick {
    struct Node {
        int link{}, sean{};
        vector<int> to, aut, ids, g;

        Node() {
            aut.assign(26, 0);
            to.assign(26, -1);
        }
    };
    vector<Node> trie;
    vector<long long> ans;
    Aho_corasick() { trie.emplace_back(); }
    void insert(const string &ele, const int &id) {
        int u = 0;
        for (auto &ch: ele) {
            if (trie[u].to[ch - 'a'] == -1) {
                trie[u].to[ch - 'a'] = (int) trie.size();
                trie.emplace_back();
            }
            u = trie[u].to[ch - 'a'];
        }
        trie[u].ids.push_back(id);
    }
    void compute_automaton() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            Node &cur = trie[u];
            for (int i = 0; i < 26; ++i) {
                if (!~cur.to[i]) {
                    cur.aut[i] = trie[cur.link].aut[i];
                    continue;
                }
                Node &next = trie[cur.to[i]];
                next.link = (u == 0 ? 0 : trie[cur.link].aut[i]);
                cur.aut[i] = cur.to[i];
                trie[next.link].g.push_back(cur.to[i]);
                q.push(cur.to[i]);
            }
        }
    }
    void match(const string &text, const int &sz) {
        compute_automaton();
        ans.assign(sz, 0);
        int u = 0;
        for (auto &ch: text) {
            u = trie[u].aut[ch - 'a'];
            trie[u].sean++;
        }
        dfs(0);
    }
    long long dfs(int u) {
        long long res = trie[u].sean;
        for (auto &v: trie[u].g)
            res += dfs(v);
        for (auto &id: trie[u].ids)
            ans[id] = res;
        return res;
    }
};