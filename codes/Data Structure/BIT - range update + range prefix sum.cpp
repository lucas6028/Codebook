int n, q;

void solve() {
    cin >> n >> q;
    Fenwick bit_values(n), bit_count(n);

    while (q--) {
        int mode, l, r, val;
        cin >> mode;
        if (mode == 0) {
            cin >> l >> r >> val;
            bit_values.update(l, val);
            bit_count.update(l, val * (l - 1));
            bit_values.update(r + 1, -val);
            bit_count.update(r + 1, -val * r);
        }
        else {
            cin >> l >> r;
            int pref_l = bit_values.query(l - 1) * (l - 1) - bit_count.query(l - 1);
            int pref_r = bit_values.query(r) * r - bit_count.query(r);
            cout << pref_r - pref_l << "\n";
        }
    }
}
