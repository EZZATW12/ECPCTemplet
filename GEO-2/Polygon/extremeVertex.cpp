// id of the vertex having maximum dot product with z
// polygon must need to be convex
// top - upper right vertex
// for minimum dot product negate z and return -dot(z, p[id])
int extremeVertex(const vector<pt> &p, const pt &z, const int top) { // O(log n)
    int n = p.size();
    if (n == 1) return 0;
    T ans = dot(p[0], z); int id = 0;
    if (dot(p[top], z) > ans) { ans = dot(p[top], z); id = top; }
    int l = 1, r = top - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (dot(p[mid + 1], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    if (dot(p[l], z) > ans) { ans = dot(p[l], z); id = l; }
    l = top + 1, r = n - 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (dot(p[(mid + 1) % n], z) >= dot(p[mid], z)) l = mid + 1;
        else r = mid;
    }
    l %= n;
    if (dot(p[l], z) > ans) { ans = dot(p[l], z); id = l; }
    return id;
}
