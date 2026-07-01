#include <bits/stdc++.h>
using namespace std;

typedef long double T;
typedef complex<T> pt;
#define x real()
#define y imag()

T cross(pt v, pt w) {
    return v.x * w.y - v.y * w.x;
}

// knowing base and perpendicular height
// area = 0.5 * base * height
T areaTriangle(int b, int h) {
    return 0.5L * b * h;
}

// Heron's Formula
// area = sqrt(s * (s - a) * (s - b) * (s - c))
// where s is the semi-perimeter: (a + b + c) / 2
T areaTriangle(T a, T b, T c) {
    T s = (a + b + c) / 2.0;
    return sqrtl(s * (s - a) * (s - b) * (s - c));
}

// knowing two sides and the included angle
// area = 0.5 * a * b * sin(c)
T areaTriangle(T a, T b, T c) {
    return 0.5L * a * b * sin(c);
}

// knowing the 2D coordinates of all three vertices
T areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

// given one side (len) and two adjacent angles (alpha, beta)
// area = c^2 / (2 * (cot(alpha) + cot(beta)))
// cot(x) = 1 / tan(x)
// area = (c * c) / (2.0 * (1.0 / tan(alpha) + 1.0 / tan(beta)))
T areaTriangle(int c, T alpha, T beta) {
    return (1.0L * c * c) / (2.0 * (1.0 / tan(alpha) + 1.0 / tan(beta)));
}
