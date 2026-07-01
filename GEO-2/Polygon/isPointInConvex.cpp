// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int isPointInConvex(const vector<pt> &p, const pt& x) { // O(log n)
    int n = p.size(); assert(n >= 3);
    int a = sgn(orient(p[0], p[1], x)), b = sgn(orient(p[0], p[n - 1], x));
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (sgn(orient(p[0], p[mid], x)) >= 0) l = mid;
        else r = mid;
    }
    int k = sgn(orient(p[l], p[r], x));
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}
