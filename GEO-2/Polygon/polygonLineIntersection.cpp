// not necessarily convex, boundary is included in the intersection
// returns total intersected length
// it returns the sum of the lengths of the portions of the line that are inside the polygon
T polygonLineIntersection(vector<pt> p, pt a, pt b) {
    int n = p.size();
    p.push_back(p[0]);
    line l(a, b);
    T ans = 0.0;
    vector< pair<T, int> > vec;
    for (int i = 0; i < n; i++) {
        int s1 = sgn(orient(a, b, p[i]));
        int s2 = sgn(orient(a, b, p[i + 1]));
        if (s1 == s2) continue;
        line t(p[i], p[i + 1]);
        pt inter_pt = (t.v * l.c - l.v * t.c) / cross(l.v, t.v);
        T tmp = dot(inter_pt, l.v);
        int f;
        if (s1 > s2) f = s1 && s2 ? 2 : 1;
        else f = s1 && s2 ? -2 : -1;
        vec.push_back(make_pair((f > 0 ? tmp - EPS : tmp + EPS), f)); // keep eps very small
    }
    sort(vec.begin(), vec.end());
    for (int i = 0, j = 0; i + 1 < (int)vec.size(); i++){
        j += vec[i].second;
        if (j) ans += vec[i + 1].first - vec[i].first; 
    }
    ans = ans / abs(l.v);
    p.pop_back();
    return ans;
}
