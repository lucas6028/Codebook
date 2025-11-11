int sz = 1;
const int maxn = 2e6;
int t[maxn << 1];

void build(const vector<int>& a) {
    for (int i = 0; i < n; ++i) {
        t[i + sz] = a[i];
    }
    for (int i = sz - 1; i >= 1; --i) {
        t[i] = max(t[i << 1], t[i << 1 | 1]);
    }
}

void update(int i, int val) {
    i += sz;
    t[i] = val;
    for (i >>= 1; i >= 1; i >>= 1) {
        t[i] = max(t[i << 1], t[i << 1 | 1]);
    }
}

int query(int r) {
    if (t[1] < r) return 0;

    int i = 1;
    while (i < sz) {
        if (t[i << 1] >= r) i = i << 1;
        else i = i << 1 | 1;
    }
    return i - sz + 1;
}
