T rat(pt a, pt b, pt p) {
    return !sgn(a.X - b.X) ? (p.Y - a.Y) / (b.Y - a.Y) : (p.X - a.X) / (b.X - a.X);
}

// calculates the area of the union of n polygons (not necessarily convex). 
// the points within each polygon must be given in CCW order.
// complexity: O(N^2), where N is the total number of points
T polygonUnion(vector<vector<pt>> &p) {
    int n = p.size();
    T ans = 0;
    for(int i = 0; i < n; ++i) {
        for (int v = 0; v < (int)p[i].size(); ++v) {
            pt a = p[i][v], b = p[i][(v + 1) % p[i].size()];
            vector<pair<T, int>> segs;
            segs.emplace_back(0, 0); segs.emplace_back(1, 0);
            for(int j = 0; j < n; ++j) {
                if(i != j) {
                    for(size_t u = 0; u < p[j].size(); ++u) {
                        pt c = p[j][u], d = p[j][(u + 1) % p[j].size()];
                        int sc = sgn(cross(b - a, c - a)), sd = sgn(cross(b - a, d - a));
                        if(!sc && !sd) {
                            if(sgn(dot(b - a, d - c)) > 0 && i > j) {
                                segs.emplace_back(rat(a, b, c), 1); segs.emplace_back(rat(a, b, d), -1);
                            }
                        } 
                        else {
                            T sa = cross(d - c, a - c), sb = cross(d - c, b - c);
                            if(sc >= 0 && sd < 0) segs.emplace_back(sa / (sa - sb), 1);
                            else if(sc < 0 && sd >= 0) segs.emplace_back(sa / (sa - sb), -1);
                        }
                    }
                }
            }
            sort(segs.begin(), segs.end());
            T pre = min(max(segs[0].first, (T)0.0), (T)1.0), now, sum = 0;
            int cnt = segs[0].second;
            for(int j = 1; j < segs.size(); ++j) {
                now = min(max(segs[j].first, (T)0.0), (T)1.0);
                if (!cnt) sum += now - pre;
                cnt += segs[j].second;
                pre = now;
            }
            ans += cross(a, b) * sum;
        }
    }
    return ans * 0.5;
}
