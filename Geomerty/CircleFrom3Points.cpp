typedef Point<double> P;
 
bool isColliner(const P &A, const P &B, const P &C)
{
    return dcmp(P(B - A).cross(P(C - A)), 0) == 0;
}
 
P ccCenter(const P &A, const P &B, const P &C)
{
    P b = C - A, c = B - A;
    return A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
}
 
double ccRadius(const P &A, const P &B, const P &C)
{
    return (B - A).dist() * (C - B).dist() * (A - C).dist() /
           abs((B - A).cross(C - A)) / 2;
}