// returns outer tangents line of two circles
// if inner == 1 it returns inner tangent lines
int tangentsLinesFromCircle(pt c1, T r1, pt c2, T r2, bool inner, line &u, line &v) {
    if (inner) r2 = -r2;
    pt d = c2 - c1;
    T dr = r1 - r2, d2 = sq(d), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {
        assert(h2 != 0);
        return 0;
    }
    vector<pair<pt, pt>> out;
    for (int tmp: {- 1, 1}) {
        pt v_vec = (d * dr + perp(d) * sqrt(h2) * (T)tmp) / d2;
        out.push_back({c1 + v_vec * r1, c2 + v_vec * r2});
    }
    u = line(out[0].first, out[0].second);
    if (out.size() == 2) v = line(out[1].first, out[1].second);
    return 1 + (h2 > 0);
}
