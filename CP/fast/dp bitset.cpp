// https://cses.fi/problemset/task/1745

#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")

#include <string>
#include <bits/functexcept.h>
#include <iosfwd>
#include <bits/cxxabi_forced.h>
#include <bits/functional_hash.h>

#pragma push_macro("__SIZEOF_LONG__")
#pragma push_macro("__cplusplus")
#define __SIZEOF_LONG__ __SIZEOF_LONG_LONG__
#define unsigned unsigned long
#define __cplusplus 201102L

#define __builtin_popcountl __builtin_popcountll
#define __builtin_ctzl __builtin_ctzll

#include <bitset>

#pragma pop_macro("__cplusplus")
#pragma pop_macro("__SIZEOF_LONG__")
#undef unsigned
#undef __builtin_popcountl
#undef __builtin_ctzl

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    bitset<100005> dp;
    dp[0] = 1;
    for (auto &it: v) {
        dp |= (dp << it);
    }

    vector<int> ans;
    for (int i = 1; i <= 100005; i++) {
        if (dp[i]) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << '\n';
    for (auto &it: ans) {
        cout << it << ' ';
    }

    return 0;
}