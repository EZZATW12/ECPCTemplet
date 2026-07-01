#include <bits/stdc++.h>
using namespace std;

// Sieve of Eratosthenes O(n log long n)

vector<bool> isPrime(N + 1, true);

void sieve() {
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            if (1LL * i * i <= N) {
                for (int j = i * i; j <= N; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }
}
