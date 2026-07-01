// a and b are convex polygons
// returns a convex hull of their minkowski sum
// min(a.size(), b.size()) >= 2
// https://cp-algorithms.com/geometry/minkowski.html
vector<pt> minkowskiSum(vector<pt> a, vector<pt> b) {
    reorderPolygon(a); reorderPolygon(b);
    int n = a.size(), m = b.size();
    int i = 0, j = 0;
    a.push_back(a[0]); a.push_back(a[1]);
    b.push_back(b[0]); b.push_back(b[1]);
    vector<pt> c;
    while (i < n || j < m) {
        c.push_back(a[i] + b[j]);
        T p_val = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
        if (sgn(p_val) >= 0) ++i;
        if (sgn(p_val) <= 0) ++j;
    }
    return c;
}
