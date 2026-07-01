#include <bits/stdc++.h>
using namespace std;

int n, m, q;
long long pref[45][45][45][45];
int pref2D[45][45], zeros[45][45][45][45];

void build4D() {
    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= m; b++) {
            for (int c = 1; c <= n; c++) {
                for (int d = 1; d <= m; d++) {
                    long long ret = zeros[a][b][c][d];
                    for (int mask = 1; mask < (1 << 4); mask++) {
                        int na = (mask & (1 << 0)) ? a - 1 : a;
                        int nb = (mask & (1 << 1)) ? b - 1 : b;
                        int nc = (mask & (1 << 2)) ? c - 1 : c;
                        int nd = (mask & (1 << 3)) ? d - 1 : d;
                        if (na >= 1 && nb >= 1 && nc >= 1 && nd >= 1) {
                            int sign = (__builtin_popcount(mask) & 1 ? 1 : -1);
                            ret += sign * pref[na][nb][nc][nd];
                        }
                    }
                    pref[a][b][c][d] = ret;
                }
            }
        }
    }
}

// TODO 1-based
long long query(int a, int b, int c, int d) {
    long long res = 0;
    for (int mask = 0; mask < (1 << 4); mask++) {
        int na = (mask & (1 << 0)) ? a - 1 : c;
        int nb = (mask & (1 << 1)) ? b - 1 : d;
        int nc = (mask & (1 << 2)) ? a - 1 : c;
        int nd = (mask & (1 << 3)) ? b - 1 : d;
        if (na >= 1 && nb >= 1 && nc >= 1 && nd >= 1) {
            int sign = (__builtin_popcount(mask) & 1 ? -1 : 1);
            res += sign * pref[na][nb][nc][nd];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    vector<vector<int> > grid(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++) {
            grid[i][j] = s[j - 1] - '0';
            pref2D[i][j] = grid[i][j] + pref2D[i - 1][j] + pref2D[i][j - 1] - pref2D[i - 1][j - 1];
        }
    }

    for (int a = 1; a <= n; a++) {
        for (int b = 1; b <= m; b++) {
            for (int c = a; c <= n; c++) {
                for (int d = b; d <= m; d++) {
                    zeros[a][b][c][d] = (pref2D[c][d] - pref2D[a - 1][d] - pref2D[c][b - 1] + pref2D[a - 1][b - 1] == 0);
                }
            }
        }
    }

    build4D();

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << query(a, b, c, d) << '\n';
    }

    return 0;
}
