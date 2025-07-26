template<class T>
bool inPolygon(vector<T> &p, T a, bool strict = true) {
    int cnt = 0, n = p.size();
    for (int i = 0; i < n; ++i) {
        T q = p[(i + 1) % n];
        if (onSegment(a,p[i], q)) return !strict;
        //or: if (segDist(a,p[i], q) <= eps) return !strict;
        cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}