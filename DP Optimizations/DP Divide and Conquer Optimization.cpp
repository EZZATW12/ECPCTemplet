#include <bits/stdc++.h>
// you just try again
using namespace std;
#define ll long long
#define sz(s) int(s.size())
const int N = 35000 + 6, K = 50 + 5;

int n, k, s, e = -1, tot;
int dp[N][K], frq[N];
vector<int> v;

void add(int i) {
    int x = v[i];
    if (frq[x]++ == 0) tot++;
}

void erase(int i) {
    int x = v[i];
    if (frq[x]-- == 1) tot--;
}

void update_range(int l, int r) {
    while (l < s)add(--s);
    while (e < r)add(++e);
    while (s < l)erase(s++);
    while (r < e)erase(e--);
}

void dnc(int l, int r, int optl, int optr, int currk) {
    if (l > r)return;
    int mid = (l + r) >> 1, opt = -1;
    for (int i = optl; i <= min(mid, optr); ++i) {
        update_range(i, mid);
        int sum = dp[i - 1][currk - 1] + tot;
        if (sum > dp[mid][currk]) {
            dp[mid][currk] = sum;
            opt = i;
        }
    }
    dnc(l, mid - 1, optl, opt, currk);
    dnc(mid + 1, r, opt, optr, currk);
}

void code() {
    cin >> n >> k;
    v = vector<int>(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= k; ++i) {
        dnc(1, n, 1, n, i);
    }
    cout << dp[n][k] << '\n';
}