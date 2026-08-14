#include <vector>
#include <algorithm>

using namespace std;

namespace FWHT {
    // Core FWHT function
    // type: 0 = XOR, 1 = AND, 2 = OR
    template <typename T = long long>
    void fwht(vector<T> &a, int type, bool inv) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1) {
            for (int i = 0; i < n; i += 2 * len) {
                for (int j = 0; j < len; j++) {
                    T u = a[i + j];
                    T v = a[i + len + j];

                    if (type == 0) { // XOR
                        a[i + j] = u + v;
                        a[i + len + j] = u - v;
                    } else if (type == 1) { // AND
                        if (!inv) {
                            a[i + j] = u + v;
                        } else {
                            a[i + j] = u - v;
                        }
                    } else if (type == 2) { // OR
                        if (!inv) {
                            a[i + len + j] = u + v;
                        } else {
                            a[i + len + j] = v - u;
                        }
                    }
                }
            }
        }

        // Scale down for Inverse XOR Transform
        if (type == 0 && inv) {
            for (int i = 0; i < n; i++) {
                a[i] /= n;
            }
        }
    }

    // Wrapper for Convolutions
    // Automatically pads arrays to the next power of 2
    template <typename T = long long>
    vector<T> convolute(vector<T> a, vector<T> b, int type) {
        int sz = max(a.size(), b.size());
        int n = 1;
        while (n < sz) n <<= 1;

        a.resize(n, 0);
        b.resize(n, 0);

        fwht(a, type, false);
        fwht(b, type, false);

        for (int i = 0; i < n; i++) {
            a[i] *= b[i];
        }

        fwht(a, type, true);
        return a;
    }
}