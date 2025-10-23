struct Fenwick {
    int n;
    vector<int> bit, prefix;
    Fenwick(int _n) : n(_n), bit(n + 1, 0), prefix(n + 1, 0) {}
    void update(int i, int delta) {
        for (; i <= n; i += i & -i) {
            bit[i] += delta;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= i & -i) {
            ans += bit[i];
        }
        return ans;
    }
    int range(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    int n = 5;
    vector<int> a = {0, 1, 2, 3, 4, 5};  // 1-indexed
    Fenwick ft(n);
    for (int i = 1; i <= n; ++i) ft.update(i, a[i]);

    cout << ft.query(3) << "\n";    // 6
    cout << ft.range(2, 4) << "\n"; // 9

    ft.update(3, 10);                    // a[3] += 10
    cout << ft.query(3) << "\n";    // 16
    cout << ft.range(1, 5) << "\n"; // 25
}