bool half(pt p) {
    return p.Y > 0.0 || (p.Y == 0.0 && p.X < 0.0);
}
