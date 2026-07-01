/**
 * Time Complexity: O(1)
 * Floating Point: No (integer-safe, only requires sign checking)
 * Requirements: None
 */
bool half(pt p) {
    return p.Y > 0.0 || (p.Y == 0.0 && p.X < 0.0);
}
