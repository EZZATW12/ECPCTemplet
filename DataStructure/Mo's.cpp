//
// Created by Ezzat on 6/2/2025.
//
struct query {
    ll l , r , idx ;
    bool operator<( query& q) {
        if (l / sq != q.l / sq )return l / sq < q.l / sq;
        return (l / sq) & 1 ? r > q.r : r < q.r;
    }
};

void code() {
    vector<query> Q(q);
    for (int i = 0; i < q; ++i) {
        auto &[l, r, idx] = Q[i];
        cin >> l >> r, l--, r--, idx = i;
    }

    ll l = 1, r = 0, sum = 0;
    auto add = [&](ll idx) {

    };
    auto del = [&](ll idx) {

    };
    std::sort(Q.begin(), Q.end());
    vector<int> ans(q);
    for (auto [Ql, Qr, idx]: Q) {
        while (l > Ql)add(--l);
        while (r < Qr)add(++r);
        while (l < Ql)del(l++);
        while (r > Qr)del(r--);
        ans[idx] = sum;
    }
    for (auto i: ans)
        cout << i << ' ';
    cout << '\n';
}