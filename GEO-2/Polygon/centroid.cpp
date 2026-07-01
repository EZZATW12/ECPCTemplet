/**
 * Time Complexity: O(N)
 * Floating Point: Yes (uses division and scaling factor 3.0)
 * Requirements: None
 */
pt centroid(const vector<pt> &p) {
    int n = p.size(); pt c(0, 0);
    T sum = 0;
    for (int i = 0; i < n; i++) sum += cross(p[i], p[(i + 1) % n]);
    T scale = 3.0 * sum;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        c = c + (p[i] + p[j]) * cross(p[i], p[j]);
    }
    return c / scale;
}
