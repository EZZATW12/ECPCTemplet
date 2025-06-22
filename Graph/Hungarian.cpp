class Hungarian
{
public:
    Hungarian(int n, int m) : n(n), m(m), u(n + 1), v(m + 1), p(m + 1), way(m + 1), minv(m + 1), used(m + 1), minv2(m + 1), way2(m + 1)
    {
        a = vector<vector<ll>>(n + 1, vector<ll>(m + 1));
    }

    ll solve()
    {
        for (int i = 1; i <= n; ++i)
        {
            p[0] = i;
            int j0 = 0;
            vector<ll> minv(m + 1, OO);
            vector<bool> used(m + 1, false);
            do
            {
                used[j0] = true;
                int i0 = p[j0], j1;
                ll delta = OO;
                for (int j = 1; j <= m; ++j)
                {
                    if (!used[j])
                    {
                        ll cur = a[i0][j] - u[i0] - v[j];
                        if (cur < minv[j])
                        {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta)
                        {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }
                for (int j = 0; j <= m; ++j)
                {
                    if (used[j])
                    {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    }
                    else
                    {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do
            {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        return -v[0];
    }

    void set(int i, int j, ll val)
    {
        a[i][j] = val;
    }

    vector<vector<ll>> a;
    int n, m;
    vector<ll> u, v, p, way, minv, used, minv2, way2;
};