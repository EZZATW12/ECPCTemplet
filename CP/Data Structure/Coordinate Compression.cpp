void compression(vector<int> &a, int &n) {
    vector<int> comp(a.begin() + 1, a.end()); // skip index 0 (1-based)

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin() + 1;
    }
    n = comp.size();
}



map<long long, int> id;
void compression(vector<int> a, int &n) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    for (int i = 0; i < (int) a.size(); i++) {
        id[a[i]] = i + 1;
    }
    n = a.size();
}