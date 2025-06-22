const int M = 26, N = 1000005;

struct suffixAutomaton {
    struct state {
        int len;        // length of longest string in this class
        int link;        // pointer to suffix link
        int next[M];    // adjacency list
        ll cnt;    // number of times the strings in this state occur in the original string

        bool terminal;    // by default, empty string is a suffix
        // a state is terminal if it corresponds to a suffix

        state() {
            len = 0, link = -1, cnt = 0;
            terminal = false;
            for (int i = 0; i < M; i++)
                next[i] = -1;
        }
    };

    vector<state> st;
    int sz, last, l;
    char offset = 'a';    // Careful!

    suffixAutomaton(string &s) {

        l = s.length();
        st.resize(2 * l);
        for (int i = 0; i < 2 * l; i++)
            st[i] = state();

        sz = 1, last = 0;
        st[0].len = 0;
        st[0].link = -1;

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

        for (int i = 0; i < M; i++)
            st[clone].next[i] = st[q].next[i];
        st[clone].link = st[q].link;
        st[clone].len = st[p].len + 1;
        st[clone].cnt = 0;                // cloned states initially have cnt = 0

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

    // alternatively, compute the number of paths in a DAG
    // since each substring corresponds to one unique path in SA
    ll numberOfSubstrings() {
        ll res = 0;
        for (int i = 1; i < sz; i++)
            res += st[i].len - st[st[i].link].len;
        return res;
    }

    void numberOfOccPreprocess() {
        vector<pii> v;
        for (int i = 1; i < sz; i++)
            v.emplace_back(st[i].len, i);

        sort(v.begin(), v.end(), greater<>());

        for (int i = 0; i < sz - 1; i++) {
            int suf = st[v[i].second].link;
            st[suf].cnt += st[v[i].second].cnt;
        }
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
            ll cur = num_strings * (longest + shortest) / 2;
            tot += cur;
        }
        return tot;
    }   
};
