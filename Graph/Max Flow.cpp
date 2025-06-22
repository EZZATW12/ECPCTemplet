template<typename T>
struct Dinic {
    struct edge {
        int to;
        T cap;
        edge(int _to, T _cap) : to(_to), cap(_cap) {}
    };
    int n;
    vector<edge> e;
    vector<vector<int>> adj;
    vector<int> height, id;
    explicit Dinic(int _n = 0) : n(_n), adj(_n), e(), id(n), height(n, -1) {}
    void addEdge(int u, int v, T c) {
        adj[u].push_back((int) e.size());
        e.emplace_back(v, c);
        adj[v].push_back((int) e.size());
        e.emplace_back(u, 0);
    }
    bool bfs(int s, int t) {
        height.assign(n, -1);
        queue<int> q;
        q.push(s);
        height[s] = 0;
        while (!q.empty()) {
            const int u = q.front();
            q.pop();
            for (int i: adj[u]) {
                auto [v, c] = e[i];
                if (height[v] != -1 || c <= 0) continue;
                height[v] = height[u] + 1;
                q.push(v);
                if (v == t) return true;
            }
        }
        return false;
    }
    T dfs(int u, int t, T curFlow) {
        if (u == t) return curFlow;
        T remFlow = curFlow;
        for (int &i = id[u]; i < int(adj[u].size()); ++i) {
            int j = adj[u][i];
            auto [v, c] = e[j];
            if (c <= 0 || remFlow == 0 || height[v] != height[u] + 1) continue;
            T f = dfs(v, t, min(remFlow, c));
            e[j].cap -= f;
            e[j ^ 1].cap += f;
            remFlow -= f;
        }
        return curFlow - remFlow;
    }
    T maxFlow(int s, int t) {
        T res = 0;
        while (bfs(s, t)) {
            id.assign(n, 0);
            res += dfs(s, t, numeric_limits<T>::max());
        }
        return res;
    }
    bool sameGroup(int u, int v) {
        return ((height[u] == -1) == (height[v] == -1));
    };
    struct Edge {
        int from, to;
        T cap, flow;
    };
    vector<Edge> edges() {
        vector<Edge> res;
        for (int i = 0; i < e.size(); i += 2)
            res.emplace_back(Edge{e[i + 1].to, e[i].to, e[i].cap + e[i + 1].cap, e[i + 1].cap});
        return res;
    }
};