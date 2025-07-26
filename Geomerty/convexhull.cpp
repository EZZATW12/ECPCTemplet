template<class T>
vector<T> convexHull(vector<T> pts, bool inc_collinear = false) {

    T p0 = *min_element(pts.begin(), pts.end(), [](T &a, T &b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });

    sort(pts.begin(), pts.end(), [&p0](T &a, T &b) {
        ll o = p0.cross(a, b);
        if (o != 0)return o > 0;
        return (a - p0).dist2() < (b - p0).dist2();
    });

    if (inc_collinear) {
        int ind = pts.size() - 1;
        while (ind >= 0 && p0.cross(pts[ind], pts.back()) == 0) --ind;
        reverse(pts.begin() + ind + 1, pts.end());
    }

    vector<T> ch;
    for (int i = 0; i < (int) pts.size(); i++) {
        int sz = ch.size();
        while (ch.size() > 1 &&
               (ch[sz - 2].cross(ch[sz - 1], pts[i]) < 0 ||
                (!inc_collinear && ch[sz - 2].cross(ch[sz - 1], pts[i]) == 0))) {
            ch.pop_back();
            sz = ch.size();
        }
        ch.push_back(pts[i]);
    }

    return ch;
}
