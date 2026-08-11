//
// Created by josal on 7/26/2026.
//
const int M = 26, N = 1000005;

struct suffixAutomaton {
    struct state {
        int len; // length of longest string in this class

        int link; // pointer to suffix link
        int next[M]; // adjacency list
        ll cnt; // number of times the strings in this state occur in the original string


        bool terminal; // by default, empty string is a suffix
        // a state is terminal if it corresponds to a suffix

        int firstposition; // this is first end position of that state
        vector<int> inv_link; // add this if you want to know all position of any substring
        bool is_clone; // add this if you want to know all position of any substring

        ll numberofpaths;

        state() {
            len = 0, link = -1, cnt = 0, firstposition = -1, numberofpaths = 0;
            terminal = false, is_clone = false;
            for (int i = 0; i < M; i++)
                next[i] = -1;
        }
    };

    vector<state> st;
    int sz, last;
    char offset = 'a'; // Careful!

    suffixAutomaton(string &s) {
        int l = s.length();
        st.resize(2 * l);
        for (int i = 0; i < 2 * l; i++)
            st[i] = state();

        sz = 1, last = 0;
        st[0].len = 0;
        st[0].link = -1;

        // add this if you interested in first position
        st[0].firstposition = -1;

        for (int i = 0; i < l; i++)
            addChar(s[i] - offset);

        for (int i = last; i != -1; i = st[i].link)
            st[i].terminal = true;
    }

    void addChar(int c) {
        int cur = sz++;
        assert(cur < N * 2);
        st[cur].len = st[last].len + 1;
        st[cur].cnt = 1;

        // add this if you interested in first position
        st[cur].firstposition = st[cur].len - 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        last = cur;

        if (p == -1) {
            st[cur].link = 0;
            return;
        }

        int q = st[p].next[c];

        if (st[q].len == st[p].len + 1) {
            st[cur].link = q;
            return;
        }

        int clone = sz++;

        // add this if you interested in first position
        st[clone].firstposition = st[q].firstposition;

        st[clone].is_clone = true;

        for (int i = 0; i < M; i++)
            st[clone].next[i] = st[q].next[i];
        st[clone].link = st[q].link;
        st[clone].len = st[p].len + 1;
        st[clone].cnt = 0; // cloned states initially have cnt = 0

        while (p != -1 and st[p].next[c] == q) {
            st[p].next[c] = clone;
            p = st[p].link;
        }

        st[q].link = st[cur].link = clone;
    }

    bool contains(string &t) {
        int cur = 0;
        for (int i = 0; i < t.length(); i++) {
            cur = st[cur].next[t[i] - offset];
            if (cur == -1)
                return false;
        }
        return true;
    }

    int stateOf(string &t) {
        int cur = 0;
        for (int i = 0; i < t.length(); i++) {
            cur = st[cur].next[t[i] - offset];
        }
        return cur;
    }

    // alternatively, compute the number of paths in a DAG
    // since each substring corresponds to one unique path in SA

    ll numberOfSubstrings() {
        ll res = 0;
        for (int i = 1; i < sz; i++)
            res += st[i].len - st[st[i].link].len;
        return res;
    }

    void numberOfOccPreprocess() {
        vector<pair<int, int> > v;
        for (int i = 1; i < sz; i++)
            v.emplace_back(st[i].len, i);

        sort(v.begin(), v.end(), greater<>());

        for (int i = 0; i < sz - 1; i++) {
            int suf = st[v[i].second].link;
            st[suf].cnt += st[v[i].second].cnt;
        }
    }

    void numberOfpathsPreprocess() {
        vector<pair<int, int> > v;
        for (int i = 1; i < sz; i++)
            v.emplace_back(st[i].len, i);

        sort(v.begin(), v.end(), greater<>());

        for (int i = 0; i < sz - 1; i++) {
            for (int j = 0; j < M; ++j) {
                if (st[v[i].second].next[j] == -1) continue;
                st[v[i].second].numberofpaths += st[st[v[i].second].next[j]].numberofpaths;
            }
            st[v[i].second].numberofpaths += 1;
        }
        // to erase empty string
        st[0].numberofpaths--;
    }

    ll numberOfOcc(string &t) {
        int cur = 0;
        for (int i = 0; i < t.length(); i++) {
            cur = st[cur].next[t[i] - offset];
            if (cur == -1)
                return 0;
        }
        return st[cur].cnt;
    }

    ll totLenSubstrings() {
        // different Substrings
        ll tot = 0;
        for (int i = 1; i < sz; i++) {
            ll shortest = st[st[i].link].len + 1;
            ll longest = st[i].len;
            ll num_strings = longest - shortest + 1;
            ll cur = num_strings * (longest + shortest) /
                     2;
            tot += cur;
        }
        return tot;
    }


    // must run this before numberOfpathsPreprocess
    // this is only considered distinct substring
    string kthLexSubstr(int k) {
        string ret = "";
        int current = 0;
        while (k) {
            for (int i = 0; i < M; ++i) {
                int nxt = st[current].next[i];
                if (nxt == -1) continue;
                if (st[nxt].numberofpaths >= k) {
                    ret.push_back(offset + i);
                    k--;
                    current = nxt;
                    break;
                } else {
                    k -= st[nxt].numberofpaths;
                }
            }
        }
        return ret;
    }


    string lcs(string &t) {
        int cur = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < t.size(); i++) {
            while (cur && st[cur].next[t[i] - offset] == -1) {
                cur = st[cur].link;
                l = st[cur].len;
            }
            if (st[cur].next[t[i] - offset] != -1) {
                cur = st[cur].next[t[i] - offset];
                l++;
            }
            if (l > best) {
                best = l;
                bestpos = i;
            }
        }
        return t.substr(bestpos - best + 1, best);
    }
    void getKthCalc() {
        vis = vector<int>(sz + 1);
        dp = vector<ll>(sz + 1);
        calc(0);
    }

    ll calc(int u) {
        if (vis[u])return dp[u];
        vis[u] = true;
        ll &ret = dp[u];
        ret = st[u].cnt;
        for (auto v: st[u].next) {
            if (v == -1)continue;
            ret += calc(v);
        }
        return ret;
    }

    string out(ll k) {
        int cur = 0;
        string ans;
        while (k) {
            for (int i = 0; i < M; ++i) {
                int v = st[cur].next[i];
                if (v == -1)continue;
                if (dp[v] < k)k -= dp[v];
                else {
                    ans.push_back(char(i + offset));
                    if (k <= st[v].cnt) {
                        return ans;
                    }
                    k -= st[v].cnt;
                    cur = v;
                    break;
                }
            }
        }
        return ans;
    }
    void inverseLinkPreprocess() {
        for (int v = 1; v < sz; v++) {
            st[st[v].link].inv_link.push_back(v);
        }
    }

    void findAllPosition(string &t, vector<int> &ret) {
        if (!contains(t)) return;
        int v = stateOf(t);
        findAllPosition(v, ret);
    }

    void findAllPosition(int v, vector<int> &ret) {
        if (!st[v].is_clone)
            ret.push_back(st[v].firstposition);
        for (int u: st[v].inv_link)
            findAllPosition(u, ret);
    }
    void printAutomaton() {
        for (int u = 0; u < sz; u++) {
            for (int c = 0; c < M; c++) {
                if (st[u].next[c] != -1) {
                    cout << u << " " << st[u].next[c] << " " << char(offset + c) << "\n";
                }
            }
        }
    }
    void printTreeEdges() {
        for (int i = 1; i < sz; i++) {
            cout << i << " " << st[i].link << "\n";
        }
    }
};