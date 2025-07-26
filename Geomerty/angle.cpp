template<class T>
// angle between [0, 2*pi]
ld angleBetween(T a,T b){
    ld ret = atan2(a.cross(b),a.dot(b));
    if(dcmp(ret,0) == -1){
        ret += 2 * PI;
    }
//    return min(ret,2 * PI - ret);    to return the smaller angle
    return ret;
}

template<class T>
ld angleO(T a, T O, T b){ /// angle(aOb)
    assert(a.dist(O) > eps && b.dist(O) > eps); // nan
    T v1 = (a - O), v2 = (b - O);
    return angleBetween(v1,v2);
}