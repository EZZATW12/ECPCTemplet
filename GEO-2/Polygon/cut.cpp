/**
 * Time Complexity: O(N)
 * Floating Point: Yes (computes segment intersection using inter, which requires floats)
 * Requirements: None
 */
// returns a vector with the vertices of a polygon with everything
// to the left of the line going from a to b cut away.
vector<pt> cut(const vector<pt> &p, pt a, pt b) {
    vector<pt> ans;
    int n = (int)p.size();
    for (int i = 0; i < n; i++) {
        T c1 = cross(b - a, p[i] - a);
        T c2 = cross(b - a, p[(i + 1) % n] - a);
        if (sgn(c1) >= 0) ans.push_back(p[i]);
        if (sgn(c1 * c2) < 0) {
            if (!isParallel(p[i], p[(i + 1) % n], a, b)) {
                pt tmp; 
                inter(line(p[i], p[(i + 1) % n]), line(a, b), tmp);
                ans.push_back(tmp);
            }
        }
    }
    return ans;
}
