#include <bits/stdc++.h>
using namespace std;

//TODO
const int MAX = 1e6 + 5;

struct Query {
    //TODO
    int l, r, idx;
};

struct Mo {
    vector<Query> queries;
    vector<int> v, frq, ans;
    int n, block_size, cur = 0, mo_left = 0, mo_right = -1; // 0-Based

    Mo(int n_, vector<int> &v_) : n(n_), v(v_) {
        block_size = ceil(sqrt(n));
        frq.assign(MAX, 0);
    }

    void add_query(int l, int r, int idx) {
        queries.push_back({l, r, idx});
    }

    void add(int idx) {
        //TODO
        frq[v[idx]]++;
        if (frq[v[idx]] == 1) {
            cur++;
        }
    }

    void remove(int idx) {
        //TODO
        frq[v[idx]]--;
        if (frq[v[idx]] == 0) {
            cur--;
        }
    }

    void process() {
        sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b) {
            return make_pair(a.l / block_size, ((a.l / block_size) & 1) ? -a.r : +a.r) < make_pair(b.l / block_size, ((b.l / block_size) & 1) ? -b.r : +b.r);
        });

        ans.resize(queries.size());

        for (const auto &[l, r, idx]: queries) {
            while (mo_left > l) add(--mo_left);
            while (mo_right < r) add(++mo_right);
            while (mo_left < l) remove(mo_left++);
            while (mo_right > r) remove(mo_right--);
            ans[idx] = cur;
        }
    }

    void print_answers() {
        for (auto &x: ans) {
            cout << x << '\n';
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    Mo mo(n, v);

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        mo.add_query(--l, --r, i);
    }

    mo.process();
    mo.print_answers();

    return 0;
}
