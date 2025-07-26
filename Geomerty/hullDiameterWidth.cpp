template<class T>
ll hullDiameter(vector<T> S) {
    int n = S.size(), j = n < 2 ? 0 : 1;
    ll ret = 0;
    for (int i = 0; i < j; ++i) {
        for (;; j = (j + 1) % n) {
            ret = max(ret, (ll)(S[i] - S[j]).dist2());
            if ((S[(j + 1) % n] - S[j]).cross(S[i + 1] - S[i]) >= 0)
                break;
        }
    }
    // returns the squared diameter
    return ret;
}

template<class T>
ld hullWidth(vector<T> S) {
    int n = S.size();
    if(n <= 2)return 0;
    int i = 0,j = 1;
    ld ret = 1e18;
    while (i < n){
        while((S[(i + 1) % n] - S[i]).cross(S[(j + 1)%n] - S[j]) >= 0)j = (j + 1) % n;
        ret = min(ret,lineDist(S[j], S[i],S[(i+1)%n]));
        i++;
    }
    return ret;
}
