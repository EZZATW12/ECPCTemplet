/*
 * NAME: Berlekamp-Massey
 * USE WHEN: given the first ~2k terms of a sequence that follows an
 *           unknown linear recurrence, find the shortest recurrence —
 *           then combine with matrix power / Kitamasa to get term n.
 * COMPLEXITY: O(n^2) for n given terms
 * GOTCHAS:
 *   - Needs MOD to be prime (uses modular inverse).
 *   - Give it enough terms: at least 2 * (expected recurrence order),
 *     ideally a few extra to be safe.
 *   - Returned vector c means: a[i] = c[0]*a[i-1] + c[1]*a[i-2] + ...
 * TESTED ON: standard "find nth term of unknown linear recurrence" problems
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;

ll power(ll a, ll b, ll mod){
    ll res = 1; a %= mod;
    while (b > 0){
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll inv(ll a){ return power(a, MOD-2, MOD); }

// returns recurrence coefficients c such that a[i] = sum(c[j]*a[i-1-j])
vector<ll> berlekampMassey(vector<ll> s){
    vector<ll> ls, cur;
    ll lf = 0, ld = 0;
    for (int i = 0; i < (int)s.size(); i++){
        ll t = 0;
        for (int j = 0; j < (int)cur.size(); j++)
            t = (t + cur[j] * s[i-1-j]) % MOD;
        if (((s[i] - t) % MOD + MOD) % MOD == 0) continue;
        if (cur.empty()){
            cur.resize(i+1);
            lf = i; ld = (s[i] - t) % MOD;
            continue;
        }
        ll k = (s[i] - t) % MOD * inv(ld) % MOD;
        vector<ll> c(i - lf - 1, 0);
        c.push_back(k);
        for (ll x : ls) c.push_back(-x * k % MOD);
        if (c.size() < cur.size()) c.resize(cur.size());
        for (int j = 0; j < (int)cur.size(); j++)
            c[j] = (c[j] + cur[j]) % MOD;
        if (i - (int)cur.size() >= lf - (int)ls.size()){
            ls = cur; lf = i; ld = (s[i] - t) % MOD;
        }
        cur = c;
    }
    for (ll& x : cur) x = ((x % MOD) + MOD) % MOD;
    return cur;
}

/*
 * USAGE EXAMPLE:
 * vector<ll> s = {1,1,2,3,5,8,13,21,34,55}; // fibonacci-like
 * vector<ll> rec = berlekampMassey(s);
 * // a[i] = sum(rec[j] * a[i-1-j]) for j in [0, rec.size())
 * // then use matrix power (Kitamasa) with `rec` to jump to a[n] in O(k^2 log n)
 */
