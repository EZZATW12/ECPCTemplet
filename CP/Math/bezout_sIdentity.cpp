// Extended Euclidean Algorithm
// Returns gcd(a, b), and finds x and y such that ax + by = gcd(a, b)
int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int g = extended_gcd(b, a % b, x1, y1);
    x = y1, y = x1 - (a / b) * y1;
    return g;
}

pair<int, int> clc(int a, int b) {
    int x, y, g;
    g = extended_gcd(a, b, x, y);
    return make_pair(x, y);
}