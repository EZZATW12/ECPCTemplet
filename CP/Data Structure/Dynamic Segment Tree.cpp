#include <bits/stdc++.h>
using namespace std;

class SparseSegtree {
private:
    struct Node {
        long long freqmn = 0, freqmx = 0, lazy = 0;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    Node *root = new Node;
    const long long n;

    long long combine_min(long long a, long long b) {
        return min(a, b);
    }

    long long combine_max(long long a, long long b) {
        return max(a, b);
    }

    void apply(Node *cur, long long val) {
        (cur->lazy) += val;
        (cur->freqmn) += val;
        (cur->freqmx) += val;
    }

    void push_down(Node *cur, long long l, long long r) {
        if ((cur->left) == nullptr) {
            (cur->left) = new Node;
        }

        if ((cur->right) == nullptr) {
            (cur->right) = new Node;
        }

        apply(cur->left, cur->lazy);
        apply(cur->right, cur->lazy);
        cur->lazy = 0;
    }

    void range_set(Node *cur, long long l, long long r, long long ql, long long qr, long long val) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(cur, val);
        } else {
            push_down(cur, l, r);
            long long m = (l + r) / 2;
            range_set(cur->left, l, m, ql, qr, val);
            range_set(cur->right, m + 1, r, ql, qr, val);
            (cur->freqmn) = combine_min((cur->left)->freqmn, (cur->right)->freqmn);
            (cur->freqmx) = combine_max((cur->left)->freqmx, (cur->right)->freqmx);
        }
    }

    pair<long long, long long> range_sum(Node *cur, long long l, long long r, long long ql, long long qr) {
        if (qr < l || ql > r) {
            return make_pair(2e18, -2e18);
        }
        if (ql <= l && r <= qr) {
            return make_pair(cur->freqmn, cur->freqmx);
        }
        push_down(cur, l, r);
        long long m = (l + r) / 2;
        auto n1 = range_sum(cur->left, l, m, ql, qr);
        auto n2 = range_sum(cur->right, m + 1, r, ql, qr);
        return {combine_min(n1.first, n2.first), combine_max(n1.second, n2.second)};
    }

public:
    SparseSegtree(long long n) : n(n) {
    }

    void range_set(long long ql, long long qr, long long val) {
        range_set(root, 0, n - 1, ql, qr, val);
    }

    pair<long long, long long> range_sum(long long ql, long long qr) {
        return range_sum(root, 0, n - 1, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long RANGE_SIZE = 2e18;
    SparseSegtree seg(RANGE_SIZE + 1);

    int q;
    cin >> q;
    while (q--) {
        char c;
        long long l, p;
        cin >> c >> l >> p;
        if (c == '|') {
            seg.range_set(p, p, l);
            cout << 'S';
        } else {
            auto [mn, mx] = seg.range_sum(p, p + l - 1);
            if (mn == mx) {
                seg.range_set(p, p + l - 1, 1);
                cout << 'S';
            } else {
                cout << 'U';
            }
        }
    }

    return 0;
}