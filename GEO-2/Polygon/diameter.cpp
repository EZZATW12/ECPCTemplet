// maximum distance from any point on the perimeter to another point on the perimeter
T diameter(const vector<pt> &p) {
    int n = (int)p.size();
    if (n == 1) return 0;
    if (n == 2) return abs(p[0] - p[1]);
    T ans = 0;
    int i = 0, j = 1;
    while (i < n) {
        while (cross(p[(i + 1) % n] - p[i], p[(j + 1) % n] - p[j]) >= 0) {
            ans = max(ans, sq(p[i] - p[j]));
            j = (j + 1) % n;
        }
        ans = max(ans, sq(p[i] - p[j]));
        i++;
    }
    return sqrt(ans);
}
