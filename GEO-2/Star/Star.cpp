/**
 * Time Complexity: O(1)
 * Floating Point: Yes (uses PI, sin, tan, and floating-point arithmetic)
 * Requirements: None
 */
struct Star {
    int n;    // number of sides of the star
    T r;      // radius of the circumcircle
    Star(int _n, T _r) {
        n = _n;
        r = _r;
    }

    T area() {
        T theta = PI / n;
        T s = 2 * r * sin(theta);
        T R = 0.5 * s / tan(theta);
        T a = 0.5 * n * s * R;
        T a2 = 0.25 * s * s / tan(1.5 * theta);
        return a - n * a2;
    }
};
