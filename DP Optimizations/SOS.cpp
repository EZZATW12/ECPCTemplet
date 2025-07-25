const int B = 22;
const int M = 1 << B;

// subset contribute to its superset
void forward(vector<int> &dp) {
    for (int i = 0; i < B; ++i)
        for (int m = 0; m < M; ++m)
            if ((m & (1 << i)) && ~dp[m ^ (1 << i)])
                dp[m] += dp[m ^ (1 << i)];
}

// superset contribute to its subset
void forwardRev(vector<int> &dp) {
    for (int i = 0; i < B; ++i)
        for (int m = M - 1; ~m; --m)
            if (m & (1 << i))
                dp[m ^ (1 << i)] += dp[m];
}

// remove subset contribution from superset
void backward(vector<int> &dp) {
    for (int i = 0; i < B; ++i)
        for (int m = M - 1; ~m; --m)
            if (m & (1 << i))
                dp[m] -= dp[m ^ (1 << i)];
}

// remove superset contribution from subset
void backwardRev(vector<int> &dp) {
    for (int i = 0; i < B; ++i)
        for (int m = 0; m < M; ++m)
            if (m & (1 << i))
                dp[m ^ (1 << i)] -= dp[m];
}

