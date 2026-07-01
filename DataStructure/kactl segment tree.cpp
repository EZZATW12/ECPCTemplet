struct Tree {
    struct Node {
        long long sum;
        Node() : sum(0) {}
    };

    typedef Node T;
    T f(T a, T b) {
        Node ret;
        ret.sum = a.sum + b.sum;
        return ret;
    }

    vector <T> s;
    int n;
    Tree(int n = 0) : s(2 * n, Node()), n(n) {}

    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }

    T query(int l, int r) {
        r++;
        T ra = Node(), rb = Node();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) ra = f(ra, s[l++]);
            if (r % 2) rb = f(s[--r], rb);
        }
        return f(ra, rb);
    }
};