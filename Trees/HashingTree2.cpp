vector<int>adj[N];
map<vector<int>,int>mp;

int dfs(int u,int par){
    vector<int>cur;
    for(auto v:adj[u]){
        if(v == par)continue;
        cur.push_back(dfs(v,u));
    }
    sort(all(cur));
    if(!mp.count(cur))mp[cur] = mp.size();
    return mp[cur];
}