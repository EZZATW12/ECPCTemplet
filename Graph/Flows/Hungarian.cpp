#include <bits/stdc++.h>

using namespace std;

// Hungarian Algorithm for Min-Cost Assignment
// Time Complexity: O(N^2 * M)
// 1-based indexing is used internally for clean dummy node (0) logic.
template<typename T>
struct Hungarian {
    int n, m;
    vector<vector<T>> a;
    vector<T> u, v;
    vector<int> p, way;
    const T INF;

    // _n: number of workers (left partition)
    // _m: number of jobs (right partition)
    // Requires: _n <= _m
    Hungarian(int _n, int _m) : n(_n), m(_m), a(_n + 1, vector<T>(_m + 1, 0)),
                                u(_n + 1, 0), v(_m + 1, 0), p(_m + 1, 0),
                                way(_m + 1, 0), INF(numeric_limits<T>::max() / 2) {}

    // Add cost for worker i to do job j
    // i in [1, n], j in [1, m]
    void add_edge(int i, int j, T cost) {
        a[i][j] = cost;
    }

    // Returns the minimum cost to assign all N workers
    T solve() {
        for (int i = 1; i <= n; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<T> minv(m + 1, INF);
            vector<bool> used(m + 1, false);

            do {
                used[j0] = true;
                int i0 = p[j0], j1 = 0;
                T delta = INF;

                for (int j = 1; j <= m; ++j) {
                    if (!used[j]) {
                        T cur = a[i0][j] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }

                for (int j = 0; j <= m; ++j) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);

            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0 != 0);
        }
        return -v[0];
    }

    // Returns a 1-based array `ans` of size n + 1
    // ans[i] = j means worker i is assigned to job j
    vector<int> get_assignment() {
        vector<int> ans(n + 1);
        for (int j = 1; j <= m; ++j) {
            if (p[j] != 0) {
                ans[p[j]] = j;
            }
        }
        return ans;
    }
};