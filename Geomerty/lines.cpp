template<class T>
double lineDist(T p, T s, T e) {
    if (s == e) {
        return s.dist(p);
    }
    return fabs((p - s).cross(e - s) / (e - s).dist());
}

template<class T>
pair<int, T> lineInter(T s1, T e1, T s2, T e2) {
    // first = 0 no intersection
    // first = 1 intersection
    // first = -1 infinite intersection
    auto d = (e1 - s1).cross(e2 - s2);
    if (dcmp(d,0) == 0) // if parallel   same line first = -1 else first = 0
        return {-(s1.cross(e1, s2) == 0), {0,0}};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}



template<class T>
bool onSegment(T p,T s, T e) {
    return dcmp(p.cross(s, e) ,0) == 0 && dcmp((s - p).dot(e - p) , 0) <= 0;
}


template<class T>
double segDist(T p, T s, T e) {
    if (dcmp((p - s).dot(e - s),0) <= 0)return s.dist(p);
    if (dcmp((p - e).dot(e - s),0) >= 0)return e.dist(p);
    return lineDist(p, s, e);
}

template<class T>
pair<int, T> segInter(T s1, T e1, T s2, T e2) {
    // first = 0 no intersection
    // first = 1 intersection`
    // first = -1 infinite intersection
    pair<int, T> ret = lineInter(s1, e1, s2, e2);
    if (ret.first == 0)return ret;
    else if (ret.first == 1) {
        if (onSegment(ret.second, s1, e1) && onSegment(ret.second, s2, e2))
            return ret;
        else
            return {0, {0, 0}};
    } else {
        if (onSegment(s1, s2, e2) || onSegment(e1, s2, e2))
            return {-1, (onSegment(s1, s2, e2) ? s1 : e1)};
        else if (onSegment(s2, s1, e1) || onSegment(e2, s1, e1))
            return {-1, (onSegment(s2, s1, e1) ? s2 : e2)};
        else
            return {0, {0, 0}};
    }
}


template<class T>
T closestOnSegment(T p, T s, T e) {
    if ((p - s).dot(e - s) <= 0) return s;
    else if ((p - e).dot(e - s) >= 0) return e;
    else return p.projectOnLine(s, e);
}

template<class T>
double segSegDist(T s1, T e1, T s2, T e2) {
    if(segInter(s1,e1,s2,e2).first != 0)
        return 0;
    double ret = min({segDist(s1,s2,e2), segDist(e1,s2,e2), segDist(s2,s1,e1), segDist(e2,s1,e1)});
    return ret;
}



template<class T>
bool onRay(T p, T s, T e) {
    return dcmp(p.cross(s, e) , 0) == 0 && dcmp((p - s).dot(e - s) , 0) >= 0;
}

template<class T>
double rayDist(T p, T s, T e) {
    if ((p - s).dot(e - s) <= 0) {
        return s.dist(p);
    }
    return lineDist(p, s, e);
}


template<class T>
pair<int, T> rayInter(T s1, T e1, T s2, T e2) {
    // first = 0 no intersection
    // first = 1 intersection
    // first = -1 infinite intersection
    pair<int, T> ret = lineInter(s1, e1, s2, e2);
    if (ret.first == 0)return ret;
    else if (ret.first == 1) {
        if (onRay(ret.second, s1, e1) && onRay(ret.second, s2, e2))
            return ret;
        else
            return {0, {0,0}};
    } else {
        if(onRay(s1, s2, e2) || onRay(s2, s1, e1))
            return {-1,onRay(s1, s2, e2) ? s1:s2};
        else
            return {0, {0,0}};
    }
}

template<class T>
double rayRayDist(T s1, T e1, T s2, T e2) {
    if(rayInter(s1,e1,s2,e2).first != 0)
        return 0;
    double ret = min(rayDist(s1,s2,e2), rayDist(s2,s1,e1));
    return ret;
}
