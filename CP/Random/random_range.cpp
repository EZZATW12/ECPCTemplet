mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rand(int l, int r) {
    return l + rng() % (r - l + 1);
}
