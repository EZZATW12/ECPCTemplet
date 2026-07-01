/**
 * Time Complexity: O(N)
 * Floating Point: Yes (uses abs to compute Euclidean distance, which relies on sqrt)
 * Requirements: None
 */
T perimeter(const vector<pt> &p) {
    T ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += abs(p[i] - p[(i + 1) % n]);
    return ans;
}
