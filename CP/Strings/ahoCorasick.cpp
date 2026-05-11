#include <bits/stdc++.h>
using namespace std;

vector<int> ans;

struct ahoCorasick {
    struct node {
        int cnt = 0;
        int nxt[26]{};

        int &operator[](int c) {
            return nxt[c];
        }
    };

    vector<node> t;
    vector<int> pi, out_link;
    vector<vector<int> > leafs, al;

    int new_node() {
        pi.push_back(0);
        t.push_back(node());
        leafs.emplace_back();
        out_link.push_back(0);
        return (int) t.size() - 1;
    }

    ahoCorasick() {
        t.clear();
        new_node();
    }

    void insert(string &s, int idx) {
        int u = 0;
        for (auto &c: s) {
            if (!t[u][c - 'a']) {
                int id = new_node();
                t[u][c - 'a'] = id;
            }
            u = t[u][c - 'a'];
        }
        leafs[u].push_back(idx);
    }

    void build() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                int v = t[u][c];
                if (v) {
                    pi[v] = (u ? t[pi[u]][c] : 0);
                    out_link[v] = leafs[pi[v]].empty() ? out_link[pi[v]] : pi[v];
                    q.push(v);
                } else {
                    t[u][c] = t[pi[u]][c];
                }
            }
        }

        al.assign(t.size(), vector<int>());
        for (int u = 1; u < t.size(); u++) {
            if (!leafs[u].empty()) {
                al[out_link[u]].push_back(u);
            }
        }
    }

    void search(string &s) {
        int u = 0;
        for (auto &c: s) {
            u = t[u][c - 'a'];
            if (leafs[u].empty()) {
                t[out_link[u]].cnt++;
            } else {
                t[u].cnt++;
            }
        }
    }

    int dfs(int u) {
        int ret = t[u].cnt;
        for (auto &v: al[u]) {
            ret += dfs(v);
        }

        for (auto &it: leafs[u]) {
            ans[it] = ret;
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ahoCorasick aho;

    int n;
    string s;
    cin >> s >> n;
    ans.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
        string t;
        cin >> t;
        aho.insert(t, i);
    }

    aho.build();
    aho.search(s);
    aho.dfs(0);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
