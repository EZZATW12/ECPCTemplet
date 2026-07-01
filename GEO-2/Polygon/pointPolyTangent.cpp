pair<pt, int> pointPolyTangent(const vector<pt> &p, pt Q, int dir, int l, int r) {
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        bool pvs = sgn(orient(Q, p[mid], p[mid - 1])) != -dir;
        bool nxt = sgn(orient(Q, p[mid], p[mid + 1])) != -dir;
        if (pvs && nxt) return {p[mid], mid};
        if (!(pvs || nxt)) {
            auto p1 = pointPolyTangent(p, Q, dir, mid + 1, r);
            auto p2 = pointPolyTangent(p, Q, dir, l, mid - 1);
            return sgn(orient(Q, p1.first, p2.first)) == dir ? p1 : p2;
        }
        if (!pvs) {
            if (sgn(orient(Q, p[mid], p[l])) == dir)  r = mid - 1;
            else if (sgn(orient(Q, p[l], p[r])) == dir) r = mid - 1;
            else l = mid + 1;
        }
        if (!nxt) {
            if (sgn(orient(Q, p[mid], p[l])) == dir)  l = mid + 1;
            else if (sgn(orient(Q, p[l], p[r])) == dir) r = mid - 1;
            else l = mid + 1;
        }
    }
    pair<pt, int> ret = {p[l], l};
    for (int i = l + 1; i <= r; i++) ret = sgn(orient(Q, ret.first, p[i])) != dir ? make_pair(p[i], i) : ret;
    return ret;
}
