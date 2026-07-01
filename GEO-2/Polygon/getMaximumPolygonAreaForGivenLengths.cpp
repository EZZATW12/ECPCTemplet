// given a list of lengths of the sides of a polygon in counterclockwise order
// returns the maximum area of a non-degenerate polygon that can be formed using those lengths
T getMaximumPolygonAreaForGivenLengths(vector<T> v) {
    if (v.size() < 3) return 0;
    int m = 0;
    T sum = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] > v[m]) m = i;
        sum += v[i];
    }
    if (sgn(v[m] - (sum - v[m])) >= 0) return 0; 
    T l = v[m] / 2, r = 1e6;
    int it = 60;
    auto ang = [](T x, T r) { return 2 * asin((x / 2) / r); };
    auto calc = [=](T r) {
        T sum = 0;
        for (auto x: v) sum += ang(x, r);
        return sum;
    };
    while (it--) {
        T mid = (l + r) / 2;
        if (calc(mid) <= 2 * PI) r = mid;
        else l = mid;
    }

    if (calc(r) <= 2 * PI - EPS) { 
        auto calc2 = [&](T r) {
            T sum = 0;
            for (int i = 0; i < v.size(); i++) {
                T x = v[i];
                T th = ang(x, r);
                if (i != m) sum += th;
                else sum += 2 * PI - th;
            }
            return sum;
        };
        l = v[m] / 2; r = 1e6;
        it = 60;
        while (it--) {
            T mid = (l + r) / 2;
            if (calc2(mid) > 2 * PI) r = mid;
            else l = mid;
        }
        auto get_area = [=](T r) {
            T ans = 0;
            for (int i = 0; i < v.size(); i++) {
                T x = v[i];
                T area = r * r * sin(ang(x, r)) / 2;
                if (i != m) ans += area;
                else ans -= area;
            }
            return ans;
        };
        return get_area(r);
    }
    else { 
        auto get_area = [=](T r) {
            T ans = 0;
            for (auto x: v) ans += r * r * sin(ang(x, r)) / 2;
            return ans;
        };
        return get_area(r);
    }
}
