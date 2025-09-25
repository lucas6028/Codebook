// calculate area using cross product and divide by base length
double point_line_distance(const point &p, const point &a, const point &b) {
    // area = 0.5 * |cross(b - a, p - a)|
    // base = |b - a|
    // height = 2 * area / base = |cross(b - a, p - a)| / |b - a|
    std::abs(cross(b - a, p - a)) / std::abs(b - a);
}

