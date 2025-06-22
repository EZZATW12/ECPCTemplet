//
// Created by Ezzat on 6/2/2025.
//
struct query {
    int l, r, idx;

    bool operator<(const query &other) {
        return make_pair(l / SQ, r) < make_pair(other.l / SQ, other.r);
    }
};

void code() {
   uto del = [&](ll idx) {
        // to do
    };
    auto query = [&]() {
        // to do
    };
    std::sort(Q.begin(), Q.end());
    for (auto [Ql, Qr, idx]: Q) {
        while (l > Ql)add(--l);
        while (l < Ql)del(l++);
        while (r < Qr)add(++r);
        while (r > Qr)del(r--);
        ans[idx] = query();
    } ll l = 1, r = 0, sum = 0;
    auto add = [&](ll idx) {
        // to do
    };
    a
}