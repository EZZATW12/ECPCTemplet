#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX;

struct line {
    mutable ll m, b, p;

    ll eval(ll x) const {
        return m * x + b;
    }

    bool operator<(const line &other) const {
        return m < other.m;
    }

    bool operator<(const ll x) const {
        return p < x;
    }
};

struct DynamicCHT : multiset<line, less<> > {
    ll div(ll num, ll den) {
        return num / den - ((num ^ den) < 0 && num % den);
    }

    // return true if l2 is useless
    bool inter(iterator l1, iterator l2) {
        if (l2 == end()) {
            l1->p = INF;
            return false;
        }
        if (l1->m == l2->m) {
            l1->p = (l1->b >= l2->b ? INF : -INF);
        } else {
            l1->p = div(l2->b - l1->b, l1->m - l2->m);
        }
        return l1->p >= l2->p;
    }

    void add_max(ll m, ll b) {
        iterator cur = insert({m, b, 0}), nxt = next(cur);
        while (inter(cur, nxt)) {
            nxt = erase(nxt);
        }

        if (cur != begin()) {
            auto prv = prev(cur);
            if (inter(prv, cur)) {
                nxt = erase(cur);
                inter(prv, nxt);
                return;
            }
        }

        while (cur != begin()) {
            auto prv = prev(cur);
            if (prv == begin()) break;
            auto prv2 = prev(prv);
            if (prv2->p >= prv->p) {
                cur = erase(prv);
                inter(prv2, cur);
            } else {
                break;
            }
        }
    }

    ll query_max(ll x) {
        assert(!empty());
        return (*lower_bound(x)).eval(x);
    }

    void add_min(ll m, ll b) {
        add_max(-m, -b);
    }

    ll query_min(ll x) {
        return -query_max(x);
    }
};