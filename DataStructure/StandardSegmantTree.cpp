
struct Node {
    ll sum;

    Node() {
        sum = 0; // set the defult vallue
    }

    Node(ll n) {
        sum = n; //  set the node to n;
    }

    void change(ll x) {
        sum = x;  // add x to the node
    }
};

struct SegTree {
    int tree_sz;
    vector <Node> Seg_Data;

    SegTree(int n) {
        tree_sz = 1;
        while (tree_sz < n)tree_sz <<= 1; // the nearst pow 2 greater than or eql n
        Seg_Data.assign(2 * tree_sz, Node());
    }

    // can change to  (min,max,gcd,lcm......)
    Node merge(Node &li, Node &ri) {
        Node parent = Node();
        return parent.sum = li.sum + ri.sum;
    }

    void update(int idx, ll val, int ni, int li, int ri) {
        if (ri - li == 1) {
            Seg_Data[ni].change(val);
            return;
        }
        int mid = (li + ri) >> 1;
        if (idx < mid)
            update(idx, val, 2 * ni + 1, li, mid);
        else
            update(idx, val, 2 * ni + 2, mid, ri);
        Seg_Data[ni] = merge(Seg_Data[2 * ni + 1], Seg_Data[2 * ni + 2]);
    }

    void update(int idx, ll val) {
        set(idx, val, 0, 0, tree_sz);
    }

    Node get(int l, int r, int ni, int li, int ri) {
        if (l <= li && r >= ri)
            return Seg_Data[ni];
        if (l >= ri || r <= li)
            return Node();
        int mid = (ri + li) >> 1;
        Node lnode = get(l, r, ni * 2 + 1, li, mid);
        Node rnode = get(l, r, ni * 2 + 2, mid, ri);
        return merge(lnode, rnode);
    }

    ll get(int l, int r) {  // note r not included
        return get(l, r, 0, 0, tree_sz).sum;
    }
};