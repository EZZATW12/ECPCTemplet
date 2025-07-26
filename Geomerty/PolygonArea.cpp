template<class T>
ld polygonArea(vector<T>&v){
    ld ret = 0;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        ret += v[i].cross(v[(i+1)%n]);
    }
    return 0.5 * abs(ret);
}
