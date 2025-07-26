struct Tree {
    struct Node {
        ll sum;

        Node() {
            sum = 0;
        }
    };

    typedef Node T;

    T f(T a, T b) {
        Node ret;
        ret.sum = a.sum + b.sum;
        return ret;
    }

    vector<T> s;
    int n;

    Tree(int n = 0) : s(2 * n, Node()), n(n) {}

    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }

    T query(int b, int e) {
        e++;
        T ra = Node(), rb = Node();
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};