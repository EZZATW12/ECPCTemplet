int arr[N],n;
void compress() {
    vector<int> vals;
    for (int i = 0; i < n; ++i) {
        vals.push_back(arr[i]);
    }
    sort(all(vals));
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < n; ++i) {
        arr[i] = lower_bound(all(vals), arr[i]) - vals.begin();
    }
}