#include <bits/stdc++.h>

using namespace std;

const int N = 45;

int n, m, q;
int grid[N][N], pref2D[N][N];
int base4[N][N][N][N];
long long pref4[N][N][N][N];


inline int sum2D(int a, int b, int c, int d) {
    return pref2D[c][d] - pref2D[a - 1][d] - pref2D[c][b - 1] + pref2D[a - 1][b - 1];
}


void build4D() {
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= m; b++)
            for (int c = 1; c <= n; c++)
                for (int d = 1; d <= m; d++) {
                    long long s = base4[a][b][c][d];
                    for (int mask = 1; mask < 16; mask++) {
                        int aa = (mask & 1) ? a - 1 : a;
                        int bb = (mask & 2) ? b - 1 : b;
                        int cc = (mask & 4) ? c - 1 : c;
                        int dd = (mask & 8) ? d - 1 : d;
                        if (aa >= 1 && bb >= 1 && cc >= 1 && dd >= 1) {
                            int sign = (__builtin_popcount(mask) % 2 ? +1 : -1);
                            s += sign * pref4[aa][bb][cc][dd];
                        }
                    }
                    pref4[a][b][c][d] = s;
                }
}

long long query(int a, int b, int c, int d) {
    long long res = 0;
    for (int mask = 0; mask < 16; mask++) {
        int aa = (mask & 1) ? a - 1 : c;
        int bb = (mask & 2) ? b - 1 : d;
        int cc = (mask & 4) ? a - 1 : c;
        int dd = (mask & 8) ? b - 1 : d;
        if (aa >= 1 && bb >= 1 && cc >= 1 && dd >= 1) {
            int sign = (__builtin_popcount(mask) % 2 ? -1 : +1);
            res += sign * pref4[aa][bb][cc][dd];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        for (int j = 1; j <= m; j++) {
            grid[i][j] = s[j - 1] - '0';
            pref2D[i][j] = grid[i][j] + pref2D[i - 1][j] + pref2D[i][j - 1] - pref2D[i - 1][j - 1];
        }
    }
    for (int a = 1; a <= n; a++)
        for (int b = 1; b <= m; b++)
            for (int c = a; c <= n; c++)
                for (int d = b; d <= m; d++)
                    base4[a][b][c][d] = (sum2D(a, b, c, d) == 0);
    build4D();
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << query(a, b, c, d) << '\n';
    }
    return 0;
}
