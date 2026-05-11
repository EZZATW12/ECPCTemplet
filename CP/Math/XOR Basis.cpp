#include <bits/stdc++.h>
using namespace std;

const int bits = 60;

template<typename T>
struct basis {
    T b[bits]{};
    int sz = 0;

    void insert(T x) {
        for (int bit = bits - 1; bit >= 0; bit--) {
            if (~x & (1LL << bit)) continue;
            if (!b[bit]) {
                sz++;
                b[bit] = x;
                break;
            }
            x ^= b[bit];
        }
    }

    bool exist(T x) {
        for (int bit = bits - 1; bit >= 0; bit--) {
            if (~x & (1LL << bit)) continue;
            if (!b[bit]) {
                return false;
            }
            x ^= b[bit];
        }
        return true;
    }

    T get_max(T x) {
        for (int bit = bits - 1; bit >= 0; bit--) {
            x = max(x, x ^ b[bit]);
        }
        return x;
    }

    T get_min(T x) {
        for (int bit = bits - 1; bit >= 0; bit--) {
            x = min(x, x ^ b[bit]);
        }
        return x;
    }

    // it ensures that for every basis, its highest set bit is unique, and no other basis has a '1' in this bit position.
    void reduce() {
        for (int bit = 0; bit < bits; bit++) {
            if (!b[bit]) continue;
            for (int j = bit + 1; j < bits; j++) {
                if (b[j] & (1LL << bit)) {
                    b[j] ^= b[bit];
                }
            }
        }
    }

    void merge(basis<int> &other) {
        for (int bit = bits - 1; bit >= 0; bit--) {
            insert(other.b[bit]);
        }
    }

    // TODO mod
    // sum of all distinct XOR values
    T sum() {
        T orz = 0;
        for (int bit = bits - 1; bit >= 0; bit--) {
            orz |= b[bit];
            orz %= mod;
        }
        return (orz * fp(2, sz - 1)) % mod;
    }
};
