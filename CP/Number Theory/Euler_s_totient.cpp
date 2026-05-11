#include <bits/stdc++.h>
using namespace std;

//TODO
const int N = 1e5;

vector<int> phi(N);

void phi_1_to_n() {
    phi[0] = 0, phi[1] = 1;
    for (int i = 2; i < N; i++) {
        phi[i] = i - 1;
    }

    for (int i = 2; i < N; i++) {
        for (int j = 2 * i; j < N; j += i) {
            phi[j] -= phi[i];
        }
    }
}
