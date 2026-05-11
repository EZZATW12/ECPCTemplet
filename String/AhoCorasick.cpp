struct Aho {
    int N, P;
    const int Alpha = 26;
    vector<vector<int>> nxt;
    vector<int> link, out_link, out;

    int Node() {
        nxt.emplace_back(Alpha, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(-1);
        return N++;
    }

    Aho() : N(0), P(0) { Node(); }

    void insert(const string T, int idx) {
        int u = 0;
        for (auto &c: T) {
            if (nxt[u][c - 'a'] == 0) nxt[u][c - 'a'] = Node();
            u = nxt[u][c - 'a'];
        }
        out[u] = idx, P++;
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < Alpha; ++c) {
                int v = nxt[u][c];
                if (!v)nxt[u][c] = nxt[link[u]][c];
                else {
                    link[v] = u ? nxt[link[u]][c] : 0;
                    out_link[v] = !~out[link[v]] ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    int advance(int u, char c) {
        return nxt[u][c - 'a'];
    }
};