//
// Created by EZZAT on 6/22/2025.
//
typedef pair<int, int> pii;
typedef vector <vector<int>> vvi;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector <pii> vpi;

struct SCC {
    vvi adj, adjRev, comps;
    vpi edges;
    vi revOut, compOf;
    vb vis;
    int N;

    void init(int n) {
        N = n;
        adj.resize(n);
        adjRev.resize(n);
        vis.resize(n);
        compOf.resize(n);
    }

    void addEdge(int u, int v) {
        edges.emplace_back(u, v);
        adj[u].push_back(v);
        adjRev[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = true;
        for (auto v: adj[u])
            if (!vis[v])
                dfs1(v);
        revOut.push_back(u);
    }

    void dfs2(int u) {
        vis[u] = true;
        comps.back().push_back(u);
        compOf[u] = comps.size() - 1;
        for (auto v: adjRev[u])
            if (!vis[v])dfs2(v);
    }

    void gen() {
        fill(all(vis), false);
        for (int i = 0; i < N; ++i) {
            if (!vis[i])
                dfs1(i);
        }
        reverse(all(revOut));
        fill(all(vis), false);
        for (auto node: revOut) {
            if (vis[node])continue;
            comps.push_back(vi());
            dfs2(node);
        }
    }

    vvi generateCondensedGraph() {
        vvi adjCon(comps.size());
        for (auto edge: edges)
            if (compOf[edge.first] != compOf[edge.second])
                adjCon[compOf[edge.first]].push_back(compOf[edge.second]);
        return adjCon;
    }
};


struct TwoSat {
    int N;
    vpi edges;

    void init(int _N) {
        N = _N;
    }

    int addVar() { return N++; }

    // x or y, edges will be refined in the end
    void either(int x, int y) {
        x = max(2 * x, -1 - 2 * x);
        y = max(2 * y, -1 - 2 * y);
        edges.emplace_back(x, y);
    }

    void implies(int x, int y) {
        either(~x, y);
    }

    void must(int x) {
        either(x, x);
    }

    void XOR(int x, int y) {
        either(x, y);
        either(~x, ~y);
    }

    void atMostOne(const vi &li) { // ( optional )
        if (li.size() <= 1) return;
        int last = ~li[1];
        for (int i = 2; i < li.size(); i++) {
            int next = addVar();
            implies(li[i], last);
            either(last, next);
            implies(li[i], next);
            last = ~next;
        }
        implies(li[0], last);
    }

    vb solve(int _N = -1) {
        if (_N != -1) N = _N;
        SCC scc;
        scc.init(2 * N);
        for (auto e: edges) {
            scc.addEdge(e.first ^ 1, e.second);
            scc.addEdge(e.second ^ 1, e.first);
        }
        scc.gen();
        for (int i = 0; i < 2 * N; ++i) {
            if (scc.compOf[i] == scc.compOf[i ^ 1])return {};
        }
        vvi comps = scc.comps;
        reverse(all(comps));
        vi compOf(2 * N);
        for (int i = 0; i < comps.size(); ++i) {
            for (auto e: comps[i])
                compOf[e] = i;
        }
        vi tmp(comps.size());
        for (int i = 0; i < comps.size(); ++i) {
            if (!tmp[i]) {
                tmp[i] = 1;
                for (auto e: comps[i])
                    tmp[compOf[e ^ 1]] = -1;
            }
        }
        vb ans(N);
        for (int i = 0; i < N; ++i)
            ans[i] = tmp[compOf[2 * i]] == 1;
        return ans;
    }
};