const int N = 10000000;
vector<int> lp(N + 1);
vector<int> pr;

void linearSieve() {
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

vector<bool> isPrime(N + 1, true);

void SieveEratosthenes() {
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (isPrime[i] && (long long) i * i <= N) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

bool prime(ll n) {
    if (n <= 1)
        return false;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// primefactorization
map<ll, int> primefactorization(ll n) {
    map<ll, int> v;
    while (n != 1) {
        v[spf[n]]++;
        n /= spf[n];
    }
    return v;
}

/// primeFactorication
vector <ll> primeFactorication(ll n) {
    vector <ll> v;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            v.push_back(i);
            n /= i;
        }
    }
    if (n > 1)
        v.push_back(n);
    return v;
}

// divisor
vector<int> divs[N];

void DIVS() {
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
}
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
        phi[i] = i - 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2 * i; j <= n; j += i)
            phi[j] -= phi[i];
}