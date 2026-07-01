#include <bits/stdc++.h>

using namespace std;

// 1. Define Block Size globally so the Query struct can access it
int B;

struct MoQuery {
    int l, r, lca, id;

    // LGM Optimization: Odd/Even Block Sorting
    // This reverses the right-pointer direction in alternate blocks,
    // reducing the total movement of the 'r' pointer by ~50%.
    bool operator<(const MoQuery &other) const {
        if (l / B != other.l / B) return l / B < other.l / B;
        return ((l / B) & 1) ? r < other.r : r > other.r;
    }
};

// 2. The Black Box: Flattens the tree and generates 1D Mo Queries
struct TreeMoFlattener {
    int n, timer, LOG;
    vector<vector<int>> adj;
    vector<int> tin, tout, euler_tour, depth;
    vector<vector<int>> up;

    TreeMoFlattener(int _n) : n(_n), timer(1), adj(_n + 1), tin(_n + 1),
                              tout(_n + 1), depth(_n + 1) {
        LOG = __lg(n) + 2;
        up.assign(n + 1, vector<int>(LOG, 0));
        euler_tour.reserve(2 * n + 1);
        euler_tour.push_back(0); // 1-based indexing for the flat array
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Call this after adding all edges
    void build(int root = 1) {
        dfs(root, 0, 0);
    }

    // O(log N) LCA via Binary Lifting
    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; i++) {
            if ((diff >> i) & 1) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    // Safely converts a Tree Query into a 1D Array Query
    MoQuery get_query(int u, int v, int id) {
        if (tin[u] > tin[v]) swap(u, v);
        int lca = get_lca(u, v);

        // Case 1: 'u' is an ancestor of 'v'. LCA is already inside [tin[u], tin[v]]
        if (lca == u) {
            return {tin[u], tin[v], 0, id};
        }
            // Case 2: 'u' and 'v' are on different branches.
            // We query [tout[u], tin[v]] and must manually process the LCA later.
        else {
            return {tout[u], tin[v], lca, id};
        }
    }

private:
    void dfs(int u, int p, int d) {
        tin[u] = timer++;
        euler_tour.push_back(u);
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < LOG; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int v: adj[u]) {
            if (v != p) dfs(v, u, d + 1);
        }
        tout[u] = timer++;
        euler_tour.push_back(u);
    }
};

void code() {
    int n, q;
    cin >> n >> q;
    // 1. Read values and coordinate compress (if needed)
    vector<int> val(n + 1);
    vector<int> elm;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        elm.push_back(val[i]);
    }
    sort(elm.begin(), elm.end());
    elm.erase(unique(elm.begin(), elm.end()), elm.end());
    for (int i = 1; i <= n; ++i) {
        val[i] = lower_bound(elm.begin(), elm.end(), val[i]) - elm.begin();
    }

    // 2. Build the Tree Flattener
    TreeMoFlattener tree(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.build(1);

    // 3. Setup Mo's Queries
    // B = max(1, N / sqrt(Q)) is mathematically optimal for Mo's
    B = max(1, (int) (2 * n / sqrt(max(1, q))));
    vector<MoQuery> queries(q);

    for (int i = 0; i < q; i++) {
        int u, v; // Not reading 'k' assuming it was specific to your original problem
        cin >> u >> v;
        queries[i] = tree.get_query(u, v, i);
    }
    sort(queries.begin(), queries.end());

    // 4. Mo's Algorithm State
    vector<int> ans(q);
    vector<bool> in_path(n + 1, false); // Tracks if a node is currently active
    // vector<int> frq(elm.size() + 1, 0); // Example frequency array
    // int current_ans = 0;

    auto add = [&](int node) {
        // int v = val[node];
        // e.g., if (++frq[v] == 1) current_ans++;
    };
    auto remove = [&](int node) {
        // int v = val[node];
        // e.g., if (--frq[v] == 0) current_ans--;
    };

    // Core logic: If we see a node twice (enter and exit), it's not on the path!
    auto toggle = [&](int node) {
        if (in_path[node]) remove(node);
        else add(node);
        in_path[node] = !in_path[node];
    };

    // 5. Run Mo's
    int L = 1, R = 0;
    for (const auto &Q: queries) {
        while (L > Q.l) toggle(tree.euler_tour[--L]);
        while (R < Q.r) toggle(tree.euler_tour[++R]);
        while (L < Q.l) toggle(tree.euler_tour[L++]);
        while (R > Q.r) toggle(tree.euler_tour[R--]);

        // Manually toggle LCA if 'u' and 'v' are on different branches
        if (Q.lca != 0) toggle(Q.lca);

        // Record Answer
        // ans[Q.id] = current_ans;

        // Untoggle LCA immediately to restore state for the next query
        if (Q.lca != 0) toggle(Q.lca);
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n'; // Replace with elm[ans[i]] if you need the original value
    }

}

int main() {
    int t = 1;
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    // cin >> t;
    for (int i = 0; i < t; ++i) {
        code();
    }
}

