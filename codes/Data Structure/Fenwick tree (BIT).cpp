// 1-based
struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int _n=0): n(_n), bit(n+1, 0) {}
    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
    int query(int l, int r) {
        return query(r) - query(l-1);
    }
};

int main() {
    Fenwick fw(n);
    for (int i = 1; i < n; ++i) {
        fw.update(i, a[i]);
    }
    cout << fw.query(3, 7) << "\\n";  // range sum [3..7]
    int current = ...; // old value at idx
    int newVal  = ...; // new value you want
    fw.update(idx, newVal - current);
}