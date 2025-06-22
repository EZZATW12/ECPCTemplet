struct Trie{
    vector<vector<int>>trie;
    vector<int>cnt;
    //    vector<int>leaves;
    int m,sz;

    int addNode(){
        trie.emplace_back(m,-1);
        cnt.emplace_back();
        // leaves.emplace_back();
        sz++;
        return sz - 1;
    }

    Trie(int m = 26):m(m),sz(0){
        addNode();
    };

    // insert or remove
    void insert(string &s,int type = 1){
        int cur = 0;
        for(auto c:s){
            if(trie[cur][c-'a'] == -1)
                trie[cur][c-'a'] = addNode();
            cur = trie[cur][c-'a'];
            cnt[cur] += type;
        }
        // leaves[cur] += type;
    }


    int query(string &s){
        int cur = 0;
        for(auto c:s){
            if(trie[cur][c-'a'] == -1)
                // return
            cur = trie[cur][c-'a'];
        }
        return cnt[cur];
    }
};
