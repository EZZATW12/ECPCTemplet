int vis[N], p[N], ptot, mob[N];

void build() {
    mob[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i])
            p[++ptot] = i, mob[i] = -1;
        for (int j = 1; j <= ptot && i * p[j] < N; j++) {
            mob[i * p[j]] = -mob[i];
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) {
                mob[i * p[j]] = 0;
                break;
            }
        }
    }
}