/* solve x, y for ax + by = gcd(a, b) = g */
template<typename T>
void extEcu(T a, T b, T &g, T &x, T &y) {
    if (b) extEcu(b, a % b, g, y, x), y -= x * (a / b);
    else g = a, x = 1, y = 0;
}