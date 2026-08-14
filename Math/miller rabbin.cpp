#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

using namespace std;

struct NumberTheory {
    const int MX = 1e6 + 16;
    vector<bool> is_prime_small;
    vector<long long> small_primes;

    // Fast modular exponentiation avoiding overflow using __int128_t
    static long long power(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1) res = (long long)((__int128_t)res * base % mod);
            base = (long long)((__int128_t)base * base % mod);
            exp /= 2;
        }
        return res;
    }

    NumberTheory() {
        // Precompute primes up to MX using Sieve of Eratosthenes
        is_prime_small.assign(MX, true);
        is_prime_small[0] = is_prime_small[1] = false;
        for (long long i = 2; i < MX; ++i) {
            if (is_prime_small[i]) {
                small_primes.push_back(i);
                for (long long j = i * i; j < MX; j += i) {
                    is_prime_small[j] = false;
                }
            }
        }
    }

    // Miller-Rabin composite check
    bool check_composite(long long n, long long a, long long d, int s) {
        long long x = power(a, d, n);
        if (x == 1 || x == n - 1) return false;
        for (int r = 1; r < s; ++r) {
            x = (long long)((__uint128_t)x * x % n);
            if (x == n - 1) return false;
        }
        return true;
    }

    // Deterministic Miller-Rabin Primality Test
    bool isPrime(long long n) {
        if (n < 2) return false;
        if (n < MX) return is_prime_small[n];
        if (n % 2 == 0) return false;

        int s = 0;
        long long d = n - 1;
        while (d % 2 == 0) {
            s++;
            d /= 2;
        }

        // 12 bases are enough to deterministically check up to 2^64
        for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
            if (n <= a) break;
            if (check_composite(n, a, d, s)) return false;
        }
        return true;
    }

    // Pollard's Rho algorithm to find a non-trivial divisor
    long long pollard_rho(long long n) {
        if (n % 2 == 0) return 2;
        if (isPrime(n)) return n;

        long long x = 2, y = 2, d = 1, c = 1;
        auto f = [&](long long val, long long n, long long c) {
            return (long long)(((__uint128_t)val * val + c) % n);
        };

        mt19937_64 rng(1337); // random seed for fallback
        while (d == 1) {
            x = f(x, n, c);
            y = f(f(y, n, c), n, c);
            long long diff = (x > y) ? (x - y) : (y - x);
            d = std::gcd(diff, n);

            // If cycle is found, randomize the polynomial constant and try again
            if (d == n) {
                x = rng() % (n - 2) + 2;
                y = x;
                c = rng() % (n - 1) + 1;
                d = 1;
            }
        }
        return d;
    }

    // Helper for factorization
    void factorize_recursive(long long n, vector<long long>& factors) {
        if (n == 1) return;
        if (isPrime(n)) {
            factors.push_back(n);
            return;
        }
        long long divisor = pollard_rho(n);
        factorize_recursive(divisor, factors);
        factorize_recursive(n / divisor, factors);
    }

    // Main Factorize function
    // Returns a sorted vector of prime factors
    vector<long long> factorize(long long n) {
        vector<long long> factors;

        // 1. Trial division for small primes speeds up the process significantly
        for (long long p : small_primes) {
            if (p * p > n) break;
            while (n % p == 0) {
                factors.push_back(p);
                n /= p;
            }
        }

        // 2. Use Pollard's Rho for the remaining large factor
        if (n > 1) {
            factorize_recursive(n, factors);
        }

        sort(factors.begin(), factors.end());
        return factors;
    }
} nt;
