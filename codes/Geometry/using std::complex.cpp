#include <iostream>
#include <complex>
#include <cmath>

typedef std::complex<double> point;
#define x real()
#define y imag()

constexpr double PI = std::acos(-1.0);
// conj(a) = a 的共軛， reflection of a across x-axis

// Basic operations
double dot(const point &a, const point &b) { return (std::conj(a) * b).real(); }
double cross(const point &a, const point &b) { return (std::conj(a) * b).imag(); }

// Projections / reflections / geometry helpers
point project_onto_vector(const point &p, const point &v) {
    return v * (dot(p, v) / std::norm(v));
}

point project_onto_line(const point &p, const point &a, const point &b) {
    return a + (b - a) * (dot(p - a, b - a) / std::norm(b - a));
}

point reflect_across_line(const point &p, const point &a, const point &b) {
    return a + std::conj((p - a) / (b - a)) * (b - a);
}

point intersection(const point &a, const point &b, const point &p, const point &q) {
    double c1 = cross(p - a, b - a), c2 = cross(q - a, b - a);
    return (c1 * q - c2 * p) / (c1 - c2); // undefined if parallel (divide by zero)
}

double angle_between(const point &a, const point &b) {
    // angle of vector b - a
    return std::arg(b - a);
}

double angle_ABC(const point &a, const point &b, const point &c) {
    double r = std::remainder(std::arg(a - b) - std::arg(c - b), 2.0 * PI);
    return std::abs(r);
}

int main() {
    // sample
    point a = 2.0;            // (2,0)
    point b(3.0, 7.0);        // (3,7)
    std::cout << a << ' ' << b << '\n'; // (2,0) (3,7)
    std::cout << a + b << '\n';         // (5,7)

    // usage examples
    point p1(3, 2), p2(2, -7);
    std::cout << "p1 + p2 = " << p1 + p2 << '\n';   // (5,-5)
    std::cout << "p1 - p2 = " << p1 - p2 << '\n';   // (1,9)
    std::cout << "3.0 * p1 = " << 3.0 * p1 << '\n'; // (9,6)
    std::cout << "p1 / 5.0 = " << p1 / 5.0 << '\n'; // (0.6,0.4)

    // dot / cross via complex
    std::cout << "dot(p1,p2) = " << dot(p1, p2) << '\n';
    std::cout << "cross(p1,p2) = " << cross(p1, p2) << '\n';

    // distances, angle, rotation, polar/cartesian
    std::cout << "squared dist = " << std::norm(p1 - p2) << '\n';
    std::cout << "euclid dist = " << std::abs(p1 - p2) << '\n';
    std::cout << "angle p1->p2 = " << angle_between(p1, p2) << '\n';
    std::cout << "angle ABC = " << angle_ABC(point(1,0), point(0,0), point(0,1)) << '\n';

    // project / reflect / intersect examples
    point v(1, 1);
    point proj = project_onto_vector(p1, v);
    std::cout << "project p1 onto v = " << proj << '\n';

    point lineA(0,0), lineB(2,0);
    std::cout << "project p1 onto line = " << project_onto_line(p1, lineA, lineB) << '\n';
    std::cout << "reflect p1 across line = " << reflect_across_line(p1, lineA, lineB) << '\n';

    // intersection example
    point r1a(0,0), r1b(1,1);
    point r2a(0,1), r2b(1,0);
    std::cout << "intersection = " << intersection(r1a, r1b, r2a, r2b) << '\n';

    // polar/cartesian and rotation
    point polar_pt = std::polar(5.0, PI/4);
    std::cout << "polar(5,PI/4) = " << polar_pt << '\n';
    point rotated = p1 * std::polar(1.0, PI/2); // rotate p1 by 90 degrees about origin
    std::cout << "rotate p1 by 90deg = " << rotated << '\n';

    return 0;
}
