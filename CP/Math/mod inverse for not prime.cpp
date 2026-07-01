#include <bits/stdc++.h>
using namespace std;

// mod is NOT prime

long long egcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

long long mod_inv(long long a, long long mod) {
    long long x, y;
    long long g = egcd(a, mod, x, y);
    if (g != 1) return -1;
    x = (x % mod + mod) % mod;
    return x;
}