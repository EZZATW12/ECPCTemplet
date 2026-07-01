// rotate the polygon such that the (bottom, left)-most point is at the first position
void reorderPolygon(vector<pt> &p) {
    int pos = 0;
    for (int i = 1; i < p.size(); i++) {
        if (p[i].Y < p[pos].Y || (sgn(p[i].Y - p[pos].Y) == 0 && p[i].X < p[pos].X)) pos = i;
    }
    rotate(p.begin(), p.begin() + pos, p.end());
}
