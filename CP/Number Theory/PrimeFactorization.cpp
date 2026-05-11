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

vector<int> primeFactors(int n) {
    vector<int> ret;
    while (n > 1) {
        int p = lp[n];
        ret.push_back(p);
        while (n % p == 0) n /= p;
    }
    return ret;
}
