// 2D Point structure
struct Point {
    double x, y;
};

// Cross product (scalar in 2D)
double cross(const Point& a, const Point& b, const Point& c) {
    // Computes (b - a) × (c - a)
    return (b.x - a.x) * (c.y - a.y) - 
           (b.y - a.y) * (c.x - a.x);
}

// If cross(a,b,c) > 0, c is to the left of line ab
// If cross(a,b,c) < 0, c is to the right of line ab
// If cross(a,b,c) = 0, a, b, c are collinear