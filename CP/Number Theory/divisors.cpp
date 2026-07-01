const int N = 2e5;
vector<vector<int> > divisor(N + 1);

void divisors() {
    for (int i = 2; i <= N; ++i) {
        for (int j = i; j <= N; j += i) {
            divisor[j].push_back(i);
        }
    }
}