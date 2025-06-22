struct AhoCorasick {
    int states = 0;
    vector<int> pi;
    vector <vector<int>> trie, patterns;

    AhoCorasick(int n, int m = 26) {
        pi = vector<int>(n + 10, -1);
        patterns = vector < vector < int >> (n + 10);
        trie = vector < vector < int >> (n + 10, vector<int>(m, -1));
    }

    AhoCorasick(vector <string> &p, int n, int m = 26) {
        /*
         * MAKE SURE THAT THE STRINGS IN P ARE UNIQUE
         * N is the summation of sizes of p
         * M is the number of used alphabet
        */

        pi = vector<int>(n + 10, -1);
        patterns = vector < vector < int >> (n + 10);
        trie = vector < vector < int >> (n + 10, vector<int>(m, -1));

        for (int i = 0; i < p.size(); i++)
            insert(p[i], i);
        build();
    }

    void insert(string &s, int idx) {
        int cur = 0;
        for (auto &it: s) {
            if (trie[cur][it - 'a'] == -1)
                trie[cur][it - 'a'] = ++states;
            cur = trie[cur][it - 'a'];
        }
        patterns[cur].push_back(idx);
    }

    int nextState(int trieNode, int nxt) {
        int cur = trieNode;
        while (trie[cur][nxt] == -1)
            cur = pi[cur];
        return trie[cur][nxt];
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (trie[0][i] != -1)
                pi[trie[0][i]] = 0, q.push(trie[0][i]);
            else
                trie[0][i] = 0;
        }

        while (q.size()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (trie[cur][i] == -1)
                    continue;
                int f = nextState(pi[cur], i);
                pi[trie[cur][i]] = f;
                patterns[trie[cur][i]].insert(patterns[trie[cur][i]].end(), patterns[f].begin(), patterns[f].end());
                q.push(trie[cur][i]);
            }
        }
    }


    vector <vector<int>> search(string &s, vector <string> &p, int n) {
        int cur = 0;
        vector <vector<int>> ret(n);
        for (int i = 0; i < s.length(); i++) {
            cur = nextState(cur, s[i] - 'a');
            if (cur == 0 || patterns[cur].empty())
                continue;

            // patterns vector have every pattern that is matched in this node
            // matched: the last index in the pattern is index i
            for (auto &it: patterns[cur])
                ret[it].push_back(i - p[it].length() + 1);
        }
        return ret;
    }
};