struct Node {
    int open, close;

    Node() : open(0), close(0) {}
};

struct SegTree {
    vector<Node> seg_data;
    int seg_sz;

    SegTree(int n) {
        seg_sz = 1;
        while (seg_sz < n)seg_sz <<= 1LL;
        seg_data.assign(2 * seg_sz, Node());
    }

    Node merge(Node &li, Node &ri) {
        Node parent = Node();
        int mn = (li.open, ri.close);
        parent.open = li.open + ri.open - mn;
        parent.close = ri.close + li.close - mn;
        return parent;
    }

    void update(int l, int r, int idx, int ni, int li, int ri) {
        if (ri - li == 1) {
            seg_data[ni].open = l;
            seg_data[ni].close = r;
            return;
        }
        int mid = (li + ri) >> 1;
        if (idx < mid)
            update(l, r, idx, 2 * ni + 1, li, mid);
        else
            update(l, r, idx, 2 * ni + 2, mid, ri);
        seg_data[ni] = merge(seg_data[ni * 2 + 1], seg_data[ni * 2 + 2]);
    }

    void update(int l, int r, int idx) {
        update(l, r, idx, 0, 0, seg_sz);
    }

    Node query(int l, int r, int ni, int li, int ri) {
        if (l >= li && r <= ri)
            return seg_data[ni];
        if (l >= ri || r <= li)
            return Node();
        int mid = (li + ri) >> 1;
        Node lef = query(l, r, 2 * ni + 1, li, mid);
        Node rig = query(l, r, 2 * ni + 2, mid, ri);
        return merge(lef, rig);
    }

    int query(int l, int r) {
        return query(l, r, 0, 0, seg_sz).close;
    }
};
