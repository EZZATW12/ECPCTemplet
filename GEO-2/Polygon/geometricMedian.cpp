// it returns a point such that the sum of distances
// from that point to all points in p is minimum
// O(n log^2 MX)
pt geometricMedian(const vector<pt>& p) {
    auto tot_dist = [&](pt z) {
        T res = 0;
        for (int i = 0; i < p.size(); i++) res += abs(p[i] - z);
        return res;
    };
    auto findY = [&](T x) {
        T yl = -1e5, yr = 1e5;
        for (int i = 0; i < 60; i++) {
            T ym1 = yl + (yr - yl) / 3;
            T ym2 = yr - (yr - yl) / 3;
            T d1 = tot_dist(pt(x, ym1));
            T d2 = tot_dist(pt(x, ym2));
            if (d1 < d2) yr = ym2;
            else yl = ym1;
        }
        return pair<T, T>(yl, tot_dist(pt(x, yl)));
    };
    T xl = -1e5, xr = 1e5;
    for (int i = 0; i < 60; i++) {
        T xm1 = xl + (xr - xl) / 3;
        T xm2 = xr - (xr - xl) / 3;
        T y1, d1, y2, d2;
        auto z = findY(xm1); y1 = z.first; d1 = z.second;
        z = findY(xm2); y2 = z.first; d2 = z.second;
        if (d1 < d2) xr = xm2;
        else xl = xm1;
    }
    return {xl, findY(xl).first};
}
