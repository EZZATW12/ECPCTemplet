
struct Node {
    int left = 0, right = 0, val = 0;
    Node(){}
    Node (int v) : val(v){}
};
struct PST {

    vector<Node> nodes;
    int L, R;

    PST(int l, int r) {
        L = l;
        R = r;
        nodes.reserve(5e5);
        nodes.push_back({});
    }

    void merge(Node &ans, const Node & lf, const Node & ri) {
        ans.val = lf.val + ri.val;
    }

    int create_node() {
        nodes.push_back({});
        return nodes.size() - 1;
    }

    int set(int idx, int val, int ni, int lx, int rx) {
        int id = create_node();
        if(rx - lx == 1) {
            nodes[id] = Node(nodes[ni].val + val);
            return id;
        }

        int mid = (lx + rx) >> 1;

        nodes[id].left = nodes[ni].left;
        nodes[id].right = nodes[ni].right;

        if(idx < mid)
            nodes[id].left = set(idx, val, nodes[ni].left, lx, mid);
        else
            nodes[id].right = set(idx, val, nodes[ni].right, mid, rx);

        merge(nodes[id], nodes[nodes[id].left], nodes[nodes[id].right]);
        return id;
    }

    int set(int idx, int val, int version) {
        return set(idx, val, version, L, R + 1);
    }

    Node get(int idx, int ni, int lx, int rx) {
        if(ni == 0) return nodes[ni];
        if(rx - lx == 1)
            return nodes[ni];

        int mid = (lx + rx) >> 1;
        if(idx < mid)
            return get(idx, nodes[ni].left, lx, mid);

        return get(idx, nodes[ni].right, mid, rx);
    }
    int get(int idx, int version) {
        return get(idx, version, L, R + 1).val;
    }
} pst(1, N);
//
// Created by josal on 8/11/2026.
//
