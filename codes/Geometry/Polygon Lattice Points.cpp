/*
Pick's Theorem:
For a simple polygon with integer coordinates, the area A, the number of interior lattice points a
nd the number of boundary lattice points b satisfy:
A = a + b/2 - 1
*/

/*
The number of intersections of a line with lattice points is the greatest common divisor of 
P1.x - P2.x and P1.y - P2.y
*/
int countOnSegment(const Point& a, const Point& b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    return __gcd(dx, dy);
}
 
void solve() {
    int n;
    cin >> n;
    vector<Point> poly(n);
 
    for (int i = 0; i < n; ++i) {
        cin >> poly[i].x >> poly[i].y;
    }
 
    // b: boundary points
    int b = countOnSegment(poly.back(), poly[0]);
    for (int i = 0; i < n - 1; ++i) {
        b += countOnSegment(poly[i], poly[i + 1]); 
    }
    int area2 = abs(polygonArea2(poly));
    // a: interior points
    int a = (area2 + 2 - b) / 2;
    cout << a << " " << b << "\n";
}
