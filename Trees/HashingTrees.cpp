unsigned long long pw(unsigned long long b, unsigned long long p) {
    if (!p) return 1ULL;
    unsigned long long ret = pw(b, p >> 1ULL);
    ret *= ret;
    if (p & 1ULL)
        ret = ret * b;
    return ret;
}

int n;
vector<int> adj[N];

unsigned long long dfs(int u, int par) {
    vector<unsigned long long> child;
    for (auto v: adj[u]) {
        if (v == par)continue;
        child.push_back(dfs(v, u));
    }
    sort(all(child));
    unsigned long long ret = 0;
    for (int i = 0; i < child.size(); ++i) {
        ret += child[i] * child[i] + child[i] * pw(31, i + 1) + (unsigned long long) 42;
    }
    return ret;
}