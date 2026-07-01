#include <bits/stdc++.h>
using namespace std;
void random() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    auto rang = [&](int l, int r) {
        return uniform_int_distribution<int>(l, r)(rng);
    };
}