template<class T>
ld circleInter(T a,T b,ll r1,ll r2){
    if(r1 > r2){
        swap(r1,r2);
        swap(a,b);
    }
    ld d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    if(d >= r1 + r2){
        return 0;
    }
    if(d + r1 <= r2){
        return PI * r1 * r1;
    }
    ld theta = acos((d * d + r2*r2 - r1*r1)/(2 * d * r2));
    ld alpha = acos((d * d + r1*r1 - r2*r2)/(2 * d * r1));
    ld s1 = theta * r2 * r2;
    ld t1 = 0.5 * r2 * r2 * sin(2 * theta);
    ld s2 = alpha * r1 * r1;
    ld t2 = 0.5 * r1 * r1 * sin(2 * alpha);
    return (s1 - t1) + (s2 - t2);
}