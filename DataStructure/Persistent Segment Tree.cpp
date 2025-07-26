const int N = 1e5 + 9;

struct PST
{
#define lc t[cur].l
#define rc t[cur].r

    struct node
    {
        int l = 0, r = 0, val = 0;
    } t[20 * N];

    int T = 0;

    int build(int b, int e)
    {
        int cur = ++T;
        if (b == e) return cur;
        int mid = b + e >> 1;
        lc = build(b, mid);
        rc = build(mid + 1, e);
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }

    int upd(int pre, int b, int e, int i, int v)
    {
        int cur = ++T;
        t[cur] = t[pre];
        if (b == e)
        {
            t[cur].val += v;
            return cur;
        }
        int mid = b + e >> 1;
        if (i <= mid)
        {
            rc = t[pre].r;
            lc = upd(t[pre].l, b, mid, i, v);
        }
        else
        {
            lc = t[pre].l;
            rc = upd(t[pre].r, mid + 1, e, i, v);
        }
        t[cur].val = t[lc].val + t[rc].val;
        return cur;
    }

    int query(int u, int v, int lca, int par_lc, int b, int e, int k)
    {
        if (b == e) return b;
        int cnt = t[t[u].l].val + t[t[v].l].val - t[t[lca].l].val - t[t[par_lc].l].val;
        int mid = b + e >> 1;
        if (cnt >= k)
            return query(t[u].l, t[v].l, t[lca].l, t[par_lc].l, b, mid, k);
        else
            return query(t[u].r, t[v].r, t[lca].r, t[par_lc].r, mid + 1, e, k - cnt);
    }
} t;
