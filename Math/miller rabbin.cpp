#include<bits/stdc++.h>
using namespace std;
struct primaryTesting {
    vector<bool> prime;
    const int MX = 1e6 + 16;
    static long long power(long long b, long long p, long long mod) {
        long long res;
        for (res = 1; p; p >>= 1, b = ((__int128_t(b % mod) * (b % mod)) % mod + mod) % mod) if (p & 1) res = __int128_t(res) * b % mod;
        return res;
    }
    primaryTesting() {
        prime.assign(MX, true);
        prime[0] = prime[1] = false;
        for (long long i = 2; i < MX; ++i)
            if (prime[i])
                for (long long j = i * i; j < MX; j += i)
                    prime[j] = false;
    }
    bool check(long long n, long long a, long long d, long long s) {
        long long x = power(a, d, n);
        if (x == 1 || x == n - 1) return false;
        for (int r = 0; r < s; ++r) {
            x = __uint128_t(x) * x % n;
            if (x == n - 1) return false;
        }
        return true;
    }
    bool isPrime(long long n) {
        if (n & 1 ^ 1) return (n == 2);
        if (n < MX) return prime[n];
        long long s = 0, d = n - 1;
        while (d & 1 ^ 1) s++, d >>= 1;
        for (int a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) if (check(n, a, d, s)) return false;
        return true;
    }
} pt;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int tt = 1;
    cin >> tt;
    for (int tc = 1; tc <= tt; tc++) {
        long long n;
        cin >> n;
        cout << (pt.isPrime(n) ? "Yes\n" : "No\n");
    }
    return 0;
}