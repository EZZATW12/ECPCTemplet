#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// Define a type alias for complex numbers to keep the code clean
using cd = complex<double>;

// Constants for math and floating-point precision
const double PI = acos(-1);
const double EPS = 5e-4; // Tolerance for floating-point comparisons

/**
 * Fast Fourier Transform (FFT) algorithm.
 * Converts a polynomial from coefficient representation to point-value representation
 * (or vice versa if invert == true) in O(N log N) time.
 */
void fft(vector<cd> &a, bool invert) {
    int n = a.size();

    // 1. Bit-reversal permutation: Rearranges the array elements 
    // so we can perform the FFT iteratively bottom-up.
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    // 2. Butterfly operations: Combine the results of smaller subproblems
    for (int len = 2; len <= n; len <<= 1) {
        // Calculate the primitive root of unity
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));

        for (int i = 0; i < n; i += len) {
            cd w(1); // w starts at w^0 = 1
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;

                // Combine
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;

                // Move to the next power of the root of unity
                w *= wlen;
            }
        }
    }

    // 3. If this is the inverse FFT, divide all elements by N
    if (invert) {
        for (cd &x: a) {
            x /= n;
        }
    }
}

/**
 * Multiplies two polynomials in O(N log N) time using FFT.
 */
vector<cd> multiply(vector<cd> const &a, vector<cd> const &b) {
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());

    // Find the nearest power of 2 that is >= the sum of the sizes
    int n = 1;
    while (n < (int) a.size() + (int) b.size()) {
        n <<= 1;
    }

    // Pad the polynomials with zeros up to the power of 2
    fa.resize(n);
    fb.resize(n);

    // Convert both polynomials to point-value representation
    fft(fa, false);
    fft(fb, false);

    // Point-wise multiplication of the values
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // Convert the result back to coefficient representation
    fft(fa, true);

    return fa;
}

void solve() {
    string text, pattern;
    cin >> text >> pattern;

    int n = text.length();
    int m = pattern.length();

    // Arrays to hold the complex number representations of our strings
    vector<cd> text_poly(n);
    vector<cd> pattern_poly(m);

    // 1. Process the Text
    // Map each character to a point on the unit circle in the complex plane.
    for (int i = 0; i < n; ++i) {
        double angle = 2 * PI * (text[i] - 'a') / 26.0;
        text_poly[i] = cd(cos(angle), sin(angle));
    }

    // 2. Process the Pattern (Reversed)
    // We reverse the pattern index (m - i - 1) to turn string matching into polynomial convolution.
    for (int i = 0; i < m; ++i) {
        if (pattern[m - i - 1] == '*') {
            // Wildcards map to 0 so they don't affect the multiplication sum
            pattern_poly[i] = cd(0, 0);
        } else {
            // Standard characters map to the complex conjugate (negative angle)
            // so that matching characters multiply to exactly 1 + 0i.
            double angle = 2 * PI * (pattern[m - i - 1] - 'a') / 26.0;
            pattern_poly[i] = cd(cos(angle), -sin(angle));
        }
    }

    // 3. Multiply the polynomials
    vector<cd> ans = multiply(text_poly, pattern_poly);

    // 4. Count how many wildcards exist to know our target score
    int wild_cnt = count(pattern.begin(), pattern.end(), '*');
    int target_score = m - wild_cnt; // The number of exact character matches required

    // 5. Evaluate the results
    int match_count = 0;
    vector<int> match_positions;

    // Iterate through all possible starting positions in the text
    for (int i = 0; i < n - m + 1; ++i) {
        // The result of the alignment starting at index 'i' is located at 'm - 1 + i' in the output
        double real_part = ans[m - 1 + i].real();
        double imag_part = ans[m - 1 + i].imag();

        // Check if the real part is exactly the target score and the imaginary part is 0
        // (We use EPS because of tiny floating-point inaccuracies from sin/cos)
        if (fabs(real_part - target_score) < EPS && fabs(imag_part) < EPS) {
            match_count++;
            match_positions.push_back(i);
        }
    }

    // Print the number of matches followed by their starting indices
    cout << match_count << "\n";
    for (int pos: match_positions) {
        cout << pos << " ";
    }
    cout << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}