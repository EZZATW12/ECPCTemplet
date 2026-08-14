#include <bits/stdc++.h>

using namespace std;

struct AhoCorasick {
    int N, P; // tot number of node ( sum len of pattern ) , num of pattern
    const int Alpha = 26;
    vector<vector<int>> nxt; // trie
    vector<int> link, out_link;
    vector<vector<int>> out;

    AhoCorasick() : N(0), P(0) { Node(); }

    int Node() {
        nxt.emplace_back(Alpha, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }

    inline int get(char c) { return c - 'a'; }

    void Add_Pattern(const string T, int idx) {
        int u = 0;
        for (auto c: T) {
            if (nxt[u][get(c)] == 0) { nxt[u][get(c)] = Node(); }
            u = nxt[u][get(c)];
        }
        out[u].push_back(idx);
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < Alpha; ++c) {
                int v = nxt[u][c];
                if (!v) {
                    nxt[u][c] = nxt[link[u]][c];
                } else {
                    link[v] = u ? nxt[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    int advance(int u, char c) {
        return nxt[u][get(c)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n, id = 0;
    cin >> n;
    map<string, int> mp;
    vector<int> elm(n);
    for (int i = 0; i < n; ++i) {
        string t;
        cin >> t;
        if (!mp.count(t))
            mp[t] = id++;
        elm[i] = mp[t];
    }
    AhoCorasick Aho;
    for (auto &i: mp)
        Aho.Add_Pattern(i.first, i.second);
    Aho.build();
    vector<int> ok(n + 5);
    int u = 0;
    for (auto &i: s) {
        u = Aho.advance(u, i);
        for (int v = u; v != 0; v = Aho.out_link[v]) {
            for (auto idx: Aho.out[v]) {
                ok[idx]++;
            }
        }
    }
    for (int i = 0; i < n; ++i)
        cout << (ok[elm[i]] ? "YES\n" : "NO\n");

    return 0;
}