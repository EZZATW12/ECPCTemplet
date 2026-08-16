#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Function to find prime factors in O(sqrt(N))
void add_factors(long long num, map<long long, int>& factors) {
    for (long long i = 2; i * i <= num; ++i) {
        while (num % i == 0) {
            factors[i]++;
            num /= i;
        }
    }
    if (num > 1) {
        factors[num]++;
    }
}

// DFS to generate all divisors from prime factors
void generate_divisors(map<long long, int>::iterator it, map<long long, int>& factors, long long current_divisor, vector<long long>& divisors) {
    if (it == factors.end()) {
        divisors.push_back(current_divisor);
        return;
    }

    long long p = it->first;
    int count = it->second;
    long long multiplier = 1;
    auto next_it = it;
    next_it++;

    for (int i = 0; i <= count; ++i) {
        generate_divisors(next_it, factors, current_divisor * multiplier, divisors);
        multiplier *= p;
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (!(cin >> n)) return 0;

    // 1. Prime Factorization of 4 * n * (n + 1)
    map<long long, int> factors;
    add_factors(n, factors);
    add_factors(n + 1, factors);
    factors[2] += 2; // Account for the constant 4

    // 2. Generate all divisors
    vector<long long> divisors;
    generate_divisors(factors.begin(), factors, 1, divisors);

    long long P = 4LL * n * (n + 1);
    vector<pair<long long, long long>> results;

    // 3. Find valid (w, h) pairs based on divisors <= sqrt(P)
    for (long long d : divisors) {
        if (d * d <= P) {
            long long w = 2LL * n + d + 2;
            long long h = 2LL * n + (P / d) + 2;
            results.push_back({w, h});
        }
    }

    // 4. Sort and print results formatted precisely to problem specifications
    sort(results.begin(), results.end());

    cout << results.size() << "\n";
    for (auto p : results) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}