#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}

// 8 neighbors

int Dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int Dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Knight Movement

int Kx[] = {2, 1, -1, -2, -2, -1, 1, 2};
int Ky[] = {1, 2, 2, 1, -1, -2, -2, -1};

// 4 neighbors

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char dir[] = {'U', 'D', 'L', 'R'};

/*
freopen("hps.in", "r", stdin);
freopen("hps.out", "w", stdout);
*/