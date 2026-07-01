#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;

long long fp(long long b, long long p) {
    long long res = 1;
    while (p) {
        if (p & 1) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    return 0;
}
