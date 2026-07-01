struct TwoSat {
    int n;
    vector <vector<int>> adj, radj;
    vector<int> order, comp, assignment;
    vector<bool> vis;

    // n is the number of boolean variables (0-indexed)
    TwoSat(int _n) : n(_n), adj(2 * n), radj(2 * n), comp(2 * n, -1), assignment(n), vis(2 * n, false) {}

    // Internal helper to get the node index.
    int get_node(int u, bool is_true) {
        return 2 * u + (!is_true);
    }

    // Adds a clause: (u is val_u) OR (v is val_v)
    void add_clause(int u, bool val_u, int v, bool val_v) {
        int not_u = get_node(u, !val_u);
        int node_u = get_node(u, val_u);
        int not_v = get_node(v, !val_v);
        int node_v = get_node(v, val_v);

        // ~u -> v
        adj[not_u].push_back(node_v);
        radj[node_v].push_back(not_u);

        // ~v -> u
        adj[not_v].push_back(node_u);
        radj[node_u].push_back(not_v);
    }

    // Force a variable to be a specific value
    void force_variable(int u, bool val) {
        add_clause(u, val, u, val);
    }

    // 1. OR: At least one must be True
    void add_or(int u, int v) {
        add_clause(u, true, v, true);
    }

    // 2. AND: Both must be True
    void add_and(int u, int v) {
        force_variable(u, true);
        force_variable(v, true);
    }

    // 3. XOR: Must be different (one True, the other False)
    void add_xor(int u, int v) {
        add_clause(u, true, v, true);   // Cannot be both False
        add_clause(u, false, v, false); // Cannot be both True
    }

    // 4. EQUAL / XNOR: Must be exactly the same (both True or both False)
    void add_equal(int u, int v) {
        add_clause(u, false, v, true);  // u -> v
        add_clause(u, true, v, false);  // v -> u
    }

    // 5. NAND: Cannot be True at the same time (at least one is False)
    void add_nand(int u, int v) {
        add_clause(u, false, v, false);
    }

    // 6. IMPLICATION: If the first is True, the second must be True (u -> v)
    void add_implication(int u, int v) {
        add_clause(u, false, v, true);
    }
    // ==========================================
    // DYNAMIC VARIABLES & PREFIX OPTIMIZATION
    // ==========================================

    // Creates a new dummy boolean variable and returns its index
    int add_var() {
        adj.push_back({});
        adj.push_back({});
        radj.push_back({});
        radj.push_back({});
        comp.push_back(-1);
        comp.push_back(-1);
        vis.push_back(false);
        vis.push_back(false);
        assignment.push_back(0);
        return n++;
    }

    // Enforces that AT MOST ONE of the given literals can be true in O(k) edges
    // Each literal is passed as {variable_index, required_boolean_value}
    void add_at_most_one(const vector <pair<int, bool>> &literals) {
        int k = literals.size();
        if (k <= 1) return;

        // Step 1: Create k prefix variables dynamically
        vector<int> p(k);
        for (int i = 0; i < k; ++i) {
            p[i] = add_var();
        }

        // Step 2: Apply the 3 Prefix Rules
        for (int i = 0; i < k; ++i) {
            int L = literals[i].first;
            bool val = literals[i].second;

            // Rule 1: L_i implies P_i
            // (If L is 'val', then P_i MUST be true)
            add_clause(L, !val, p[i], true);

            if (i > 0) {
                // Rule 2: P_{i-1} implies P_i
                add_implication(p[i - 1], p[i]);

                // Rule 3: L_i implies NOT P_{i-1}
                // (If L is 'val', then P_{i-1} MUST be false)
                add_clause(L, !val, p[i - 1], false);
            }
        }
    }
    // ==========================================

    void dfs1(int u) {
        vis[u] = true;
        for (int v: adj[u]) {
            if (!vis[v]) dfs1(v);
        }
        order.push_back(u);
    }

    void dfs2(int u, int id) {
        comp[u] = id;
        for (int v: radj[u]) {
            if (comp[v] == -1) dfs2(v, id);
        }
    }

    // Returns true if satisfiable, false otherwise.
    // If true, the `assignment` vector contains a valid boolean assignment.
    bool solvable() {
        for (int i = 0; i < 2 * n; ++i) {
            if (!vis[i]) dfs1(i);
        }

        int id = 0;
        for (int i = 2 * n - 1; i >= 0; --i) {
            int u = order[i];
            if (comp[u] == -1) dfs2(u, ++id);
        }

        for (int i = 0; i < n; ++i) {
            if (comp[2 * i] == comp[2 * i + 1]) {
                return false; // Contradiction: x and ~x in the same SCC
            }
            // Kosaraju assigns SCC IDs in reverse topological order.
            assignment[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }
};