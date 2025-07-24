struct RollbackDSU {
    vector<int> par; vector<pair<int,int>> st;
    int comps;
    RollbackDSU(int n) : par(n, -1), comps(n) {}
    int size(int x) { return -par[find(x)]; }
    int find(int x) { return par[x] < 0 ? x : find(par[x]); }
    int time() { return st.size(); }
    void rollback(int t) {
        comps += (time() - t)/2;
        for (int i = time(); i-- > t;)
            par[st[i].first] = st[i].second;
        st.resize(t);
    }
    // a : leader par[a] = -sz(a)
    // a : not par[a] = leader(a)
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (-par[a] < -par[b]) swap(a, b);
        st.emplace_back(a, par[a]);
        st.emplace_back(b, par[b]);
        par[a] += par[b]; par[b] = a;
        return true;
    }
};