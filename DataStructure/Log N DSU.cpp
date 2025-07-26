class CMP {
public:
    bool operator()(ii a, ii b) //For min priority_queue .
    {
        return !(a.X<b.X || (a.X == b.X && a.Y <= b.Y));
    }
};

void add(map<lli, lli> &m, lli x, lli cnt = 1) {
    auto jt = m.find(x);
    if (jt == m.end()) m.insert({x, cnt});
    else jt->Y += cnt;
}

void del(map<lli, lli> &m, lli x, lli cnt = 1) {
    auto jt = m.find(x);
    if (jt->Y <= cnt) m.erase(jt);
    else jt->Y -= cnt;
}

bool cmp(const ii &a, const ii &b) {
    return a.X<b.X || (a.X == b.X && a.Y < b.Y);
}


int main(void) {
    lli T = 1;
    while (T--) {
        lli n;
        cin >> n;
        vi a(n);
        for (auto &x: a)
            cin >> x;

        const lli logN = 22, N = 2 * n;
        vector<atcoder::dsu> dsus(logN, atcoder::dsu(N));

        // [0,n) -> s
        // [n,2*n) -> sRev
        for (lli i = 0; i < n; i++)
            dsus[0].merge(i, N - i - 1);

        auto mergeSeg2 = y_combinator([&](const auto &self, const lli p, const lli l, const lli r)-> void {
            if (p == -1)
                return;
            if (dsus[p].same(l, r))
                return;
            dsus[p].merge(l, r);
            const lli len2 = (1LL << p) / 2;
            self(p - 1, l, r);
            self(p - 1, l + len2, r + len2);
        });

        auto mergeSeg = [&](const lli L, const lli R)-> void {
            const lli len = R - L + 1;
            lli u = L, v = N - R - 1;
            for (lli j = 0; j < logN; j++) {
                if (len & (1LL << j)) {
                    mergeSeg2(j, u, v);
                    u += 1LL << j;
                    v += 1LL << j;
                }
            }
        };

        for (lli i = 1; i <= n; i++) {
            const lli ai = a[i - 1];
            const lli L = i - ai - 1, R = i + ai - 1;
            mergeSeg(L, R);
        }

        auto &d = dsus[0];
        vector<vi> e(n);
        for (lli i = 1; i <= n; i++) {
            const lli ai = a[i - 1];
            const lli L = i - ai - 1, R = i + ai - 1;
            if (L == 0 || R == n - 1)
                continue;
            const lli u = d.leader(L - 1), v = d.leader(R + 1);
            if (u == v) {
                cout << "No" << endl;
                return 0;
            }
            e[u].eb(v);
            e[v].eb(u);
        }

        cout << "Yes" << endl;

        vi asn(n, -1);
        for (lli i = 0; i < n; i++) {
            const lli ld = d.leader(i);
            if (asn[ld] == -1) {
                set < lli > st;
                for (const auto &v: e[ld])
                    st.insert(asn[v]);
                lli col = 1;
                while (st.count(col))
                    col++;
                asn[ld] = col;
            }
            cout << asn[ld] << " \n"[i + 1 == n];
        }
    }
    aryanc403();
    return 0;
}
