/*
We can cast a ray from the point P going in any fixed direction (people usually go to the right).
If the point is located on the outside of the polygon the ray will intersect its edges an even number of times.
If the point is on the inside of the polygon then it will intersect the edge an odd number of times.
*/

struct Point {
    int x, y;
};

int cross(const Point& a, const Point& b, const Point& c) {
    // return (c - a) x (c - b)
    int ans = (c.x - a.x) * (c.y - b.y) - (c.x - b.x) * (c.y - a.y);
    if (ans == 0) return 0;
    return ans > 0 ? 1 : -1;
}

bool intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    int c1 = cross(a, b, c);
    int c2 = cross(a, b, d);
    int c3 = cross(c, d, a);
    int c4 = cross(c, d, b);

    return (c1 * c2 < 0 && c3 * c4 < 0);
}

bool onSegment(const Point& a, const Point& b, const Point& c) {
    return (cross(a, b, c) == 0 && 
            min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) &&
            min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y));
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<Point> poly(n);

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        poly[i] = {a, b};
    }

    // set a point at outside point to form the ray
    Point outside = {(int)2e9 + 7, (int)2e9 + 13};
    for (int i = 0; i < m; ++i) {
        int a, b;
        bool found = false;
        cin >> a >> b;
        Point p = {a, b};

        int cnt = 0;
        if (intersect(poly.back(), poly[0], p, outside)) {
            cnt++;
        }
        if (onSegment(poly.back(), poly[0], p)) {
            cout << "BOUNDARY\n";
            found = true;
        }
        for (int j = 0; j < n - 1 && !found; ++j) {
            if (intersect(poly[j], poly[j + 1], p, outside)) {
                cnt++;
            }
            if (onSegment(poly[j], poly[j + 1], p)) {
                cout << "BOUNDARY\n";
                found = true;
            }
        }
        if (found) continue;
        if (cnt & 1) {
            cout << "INSIDE\n";
        }
        else {
            cout << "OUTSIDE\n";
        }
    }
}
