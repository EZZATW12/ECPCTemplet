// minimum distance from a convex polygon to another convex polygon
// the polygon doesnot overlap or touch
T distFromPolygonToPolygon(const vector<pt> &p1, const vector<pt> &p2) { // O(n log n)
    T ans = 1e100;
    for (int i = 0; i < p1.size(); i++) {
        ans = min(ans, distFromPointToPolygon(p2, p1[i]));
    }
    for (int i = 0; i < p2.size(); i++) {
        ans = min(ans, distFromPointToPolygon(p1, p2[i]));
    }
    return ans;
}
