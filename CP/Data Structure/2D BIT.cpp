// https://codeforces.com/gym/100247/problem/K
#include <bits/stdc++.h>
using namespace std;

struct BIT2D {
    int n;
    vector<vector<int> > vals, bit;

    BIT2D(int n, vector<array<int, 2> > &todo) : n(n), vals(n + 1), bit(n + 1) {
        sort(todo.begin(), todo.end(), [](auto a, auto b) {
            return a[1] < b[1];
        });

        // TODO 1-Based
        for (int i = 1; i <= n; i++) {
            vals[i].push_back(0);
        }

        for (auto [r, c]: todo) {
            while (r <= n) {
                if (vals[r].back() != c) {
                    vals[r].push_back(c);
                }
                r += r & -r;
            }
        }

        for (int i = 1; i <= n; i++) {
            bit[i].resize(vals[i].size());
        }
    }

    int get(vector<int> &v, int c) {
        return upper_bound(v.begin(), v.end(), c) - v.begin() - 1;
    }

    // add val to point(r, c)
    void add(int r, int c, int val) {
        while (r <= n) {
            int idx = get(vals[r], c);
            while (idx < bit[r].size()) {
                bit[r][idx] += val;
                idx += idx & -idx;
            }
            r += r & -r;
        }
    }

    // sum of points with row in [1, r] and column in [1, c]
    int query(int r, int c) {
        int sum = 0;
        while (r > 0) {
            int idx = get(vals[r], c);
            while (idx > 0) {
                sum += bit[r][idx];
                idx -= idx & -idx;
            }
            r -= r & -r;
        }
        return sum;
    }

    // sum of points with row in [r1, r2] and column in [c1, c2]
    int query(int r1, int c1, int r2, int c2) {
        return query(r2, c2) - query(r2, c1 - 1) - query(r1 - 1, c2) + query(r1 - 1, c1 - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<array<int, 3> > teams(n);
    for (int i = 0; i < n; i++) {
        cin >> teams[i][0] >> teams[i][1] >> teams[i][2];
    }
    sort(teams.begin(), teams.end());

    vector<array<int, 2> > todo;
    for (int i = 0; i < n; i++) {
        todo.push_back({teams[i][1], teams[i][2]});
    }

    BIT2D bit(n, todo);

    // bad is a1 < a2 and b1 < b2 and c1 < c2
    long long tot = 1LL * n * (n - 1) / 2, bad = 0;
    for (int i = 0; i < n; i++) {
        bad += bit.query(teams[i][1] - 1, teams[i][2] - 1);
        bit.add(teams[i][1], teams[i][2], 1);
    }
    cout << tot - bad;

    return 0;
}
