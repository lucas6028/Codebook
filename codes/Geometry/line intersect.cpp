#include <iostream>
using namespace std;

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

// Check if value is between two others (with endpoints allowed)
bool between(double a, double b, double x) {
    return min(a, b) <= x && x <= max(a, b);
}

// Check if point c lies on segment ab
bool onSegment(const Point& a, const Point& b, const Point& c) {
    return cross(a, b, c) == 0 &&
           between(a.x, b.x, c.x) &&
           between(a.y, b.y, c.y);
}

// Main intersection check
bool segmentsIntersect(const Point& A, const Point& B,
                       const Point& C, const Point& D) {
    double c1 = cross(A, B, C);
    double c2 = cross(A, B, D);
    double c3 = cross(C, D, A);
    double c4 = cross(C, D, B);

    // General case
    if (c1 * c2 < 0 && c3 * c4 < 0) return true;

    // Special cases: collinear + overlapping
    if (c1 == 0 && onSegment(A, B, C)) return true;
    if (c2 == 0 && onSegment(A, B, D)) return true;
    if (c3 == 0 && onSegment(C, D, A)) return true;
    if (c4 == 0 && onSegment(C, D, B)) return true;

    return false;
}

int main() {
    Point A{0, 0}, B{4, 4};
    Point C{0, 4}, D{4, 0};

    if (segmentsIntersect(A, B, C, D))
        cout << "Segments intersect\n";
    else
        cout << "Segments do not intersect\n";

    return 0;
}
