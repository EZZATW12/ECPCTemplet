//
// Created by MODERN on 6/22/2025.
//
const int N = 5e5 + 5;

vector<pair<int,int>>quries[N];
int ans[N],basis[22],arr[N],last[22];

void add(int ind,int x){
    for (int i = 21; i >= 0; --i) {
        if((x >> i & 1) == 0)continue;
        if(ind > last[i]){
            swap(x,basis[i]);
            swap(ind,last[i]);
        }
        x ^= basis[i];
    }
}

int query(int ind){
    int ret = 0;
    for (int i = 21; i >= 0; --i) {
        if(last[i] >= ind){
            ret = max(ret,ret ^ basis[i]);
        }
    }
    return ret;
}

void solve() {
    int n;cin >> n;
    memset(last,-1,sizeof last);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    int q;cin >> q;
    for (int i = 0; i < q; ++i) {
        int l,r;cin >> l >> r;
        l--,r--;
        quries[r].emplace_back(l,i);
    }
    for (int i = 0; i < n; ++i) {
        add(i,arr[i]);
        for(auto &x:quries[i]){
            int l = x.fi;
            int ind = x.se;
            ans[ind] = query(l);
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
    }
}