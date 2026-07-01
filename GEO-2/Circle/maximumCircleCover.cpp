// find a circle of radius r that contains as many points as possible
// O(n^2 log n);
int maximumCircleCover(const vector<pt>& p, T r, pt &c_out) {
    int n = p.size();
    int ans = 0;
    int id = 0; T th = 0;
    for (int i = 0; i < n; ++i) {
        vector<pair<T, int>> events = {{-PI, +1}, {PI, -1}};
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            T d = abs(p[i] - p[j]);
            if (d > r * 2) continue;
            T dir = arg(p[j] - p[i]);
            T ang = acos(d / 2 / r);
            T st = dir - ang, ed = dir + ang;
            if (st > PI) st -= PI * 2;
            if (st <= -PI) st += PI * 2;
            if (ed > PI) ed -= PI * 2;
            if (ed <= -PI) ed += PI * 2;
            events.push_back({st - EPS, +1}); 
            events.push_back({ed, -1});
            if (st > ed) {
                events.push_back({-PI, +1});
                events.push_back({+PI, -1});
            }
        }
        sort(events.begin(), events.end());
        int cnt = 0;
        for (auto &&e: events) {
            cnt += e.second;
            if (cnt > ans) {
                ans = cnt;
                id = i; th = e.first;
            }
        }
    }
    c_out = pt(p[id].X + r * cos(th), p[id].Y + r * sin(th));
    return ans;
}
