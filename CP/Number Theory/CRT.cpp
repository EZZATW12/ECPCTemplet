#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
 
array<ll, 3> extend_euclid(ll a, ll b) {
    array<ll, 3> x = {1, 0, a};
    array<ll, 3> y = {0, 1, b};
    while (y[2] > 0) {
        ll k = x[2] / y[2];
        for (int i = 0; i < 3; i++) { x[i] -= k * y[i]; }
        swap(x, y);
    }
    return x; 
}
 
ll inv(ll a, ll m) {
    auto res = extend_euclid(a, m);
    if (res[2] != 1) return -1; // Inverse doesn't exist
    return (res[0] % m + m) % m;
}
 
// Merges two congruences: x = a1 (mod m1) and x = a2 (mod m2)
pair<ll, ll> merge(ll a1, ll m1, ll a2, ll m2) {
    auto res = extend_euclid(m1, m2);
    ll g = res[2];
    
    // Consistency check: (a2 - a1) must be divisible by gcd(m1, m2)
    if ((a2 - a1) % g != 0) return {-1, -1};
 
    ll mod = (m1 / g) * m2; // This is LCM(m1, m2)
    
    // We solve m1*k = (a2 - a1) (mod m2)
    // k = (a2 - a1)/g * inv(m1/g, m2/g) (mod m2/g)
    ll factor = (a2 - a1) / g;
    ll m2_reduced = m2 / g;
    ll k = (factor % m2_reduced * inv(m1 / g, m2_reduced)) % m2_reduced;
    if (k < 0) k += m2_reduced;
 
    ll x = (a1 + m1 * k) % mod;
    return {x, mod};
}
 
pair<ll, ll> general_crt(const vector<ll> &remainders, const vector<ll> &moduli) {
    ll cur_a = remainders[0];
    ll cur_m = moduli[0];
 
    for (int i = 1; i < (int)moduli.size(); i++) {
        auto next = merge(cur_a, cur_m, remainders[i], moduli[i]);
        if (next.second == -1) return {-1, -1}; // Inconsistent system
        cur_a = next.first;
        cur_m = next.second;
    }
    return {cur_a, cur_m};
}