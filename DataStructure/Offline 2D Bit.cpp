//
// Created by ezzat on 3/15/2026.
//
template<class T>
struct OffBIT2D {
    bool mode = 0;
    int SZ; // Maximum X-coordinate boundary
    std::vector<std::pair<int, int>> todo;

    // Replaced fixed arrays with dynamic vectors
    std::vector<int> cnt, st, val;
    std::vector<T> bit;

    // Constructor to set the size at runtime
    OffBIT2D(int sz) : SZ(sz) {
        cnt.assign(SZ, 0);
        st.assign(SZ, 0);
    }

    void init() {
        assert(!mode);
        mode = 1;

        // Replaced int lst[SZ] with a dynamic vector initialized to 0
        std::vector<int> lst(SZ, 0);

        std::sort(todo.begin(), todo.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
            return a.second < b.second;
        });

        for (auto t: todo) {
            for (int x = t.first; x < SZ; x += x & -x) {
                if (lst[x] != t.second) {
                    lst[x] = t.second;
                    cnt[x]++;
                }
            }
        }

        int sum = 0;
        for (int i = 0; i < SZ; ++i) {
            lst[i] = 0;
            st[i] = (sum += cnt[i]);
        }

        val.resize(sum);
        bit.assign(sum, 0); // Safely initialize the BIT with zeros
        std::reverse(todo.begin(), todo.end());

        for (auto t: todo) {
            for (int x = t.first; x < SZ; x += x & -x) {
                if (lst[x] != t.second) {
                    lst[x] = t.second;
                    val[--st[x]] = t.second;
                }
            }
        }
    }

    int rank(int y, int l, int r) {
        return std::upper_bound(val.begin() + l, val.begin() + r, y) - val.begin() - l;
    }

    void UPD(int x, int y, T t) {
        for (y = rank(y, st[x], st[x] + cnt[x]); y <= cnt[x]; y += y & -y) {
            bit[st[x] + y - 1] += t;
        }
    }

    void upd(int x, int y, T t) {
        x++, y++;
        x = std::min(x, SZ - 1);
        if (!mode) {
            todo.push_back({x, y});
        } else {
            for (; x < SZ; x += x & -x) {
                UPD(x, y, t);
            }
        }
    }

    T QUERY(int x, int y) {
        T res = 0;
        for (y = rank(y, st[x], st[x] + cnt[x]); y; y -= y & -y) {
            res += bit[st[x] + y - 1];
        }
        return res;
    }

    T query(int x, int y) {
        x++, y++;
        x = std::min(x, SZ - 1); // <--- Add the clamp here!
        assert(mode);
        T res = 0;
        for (; x; x -= x & -x) {
            res += QUERY(x, y);
        }
        return res;
    }

    T query(int xl, int xr, int yl, int yr) {
        return query(xr, yr) - query(xl - 1, yr) - query(xr, yl - 1) + query(xl - 1, yl - 1);
    }
};