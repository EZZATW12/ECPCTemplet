template<class T>
pair<int ,int> closest(vector<T> a) {
    vector<pair<T,int>>v;
    for (int i = 0; i < a.size(); ++i)v.push_back({a[i],i});
    int n = v.size();
    assert(n > 1);
    set<pair<T,int>> S;
    sort(all(v), [](pair<T,int> a, pair<T,int> b) { return a.first.y < b.first.y; });
    pair<ll, pair<int ,int>> ret{LLONG_MAX, {0, 0}};
    int j = 0;
    for(int i = 0;i < n;++i){
        T p = v[i].first;
        T d{1 + (ll)sqrt(ret.first), 0};
        while (v[j].first.y <= p.y - d.x) {
            S.erase(v[j]);
            j++;
        }
        auto lo = S.lower_bound(make_pair(p - d,-1)), hi = S.upper_bound(make_pair(p + d,INF));
        for (; lo != hi; ++lo)
            ret = min(ret, {(lo->first - p).dist2(), {lo->second, v[i].second}});
        S.insert(v[i]);
    }
    return ret.second;
}