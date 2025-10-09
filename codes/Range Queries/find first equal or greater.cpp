// CSE: Hotel Queries

int n, m;
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
 
void solve() {
    cin >> n >> m;
    vector<int> a(n);
 
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
 
    while (sz < n) sz <<= 1;
    memset(t, 0, sizeof(t));
    build(a);
 
    int r;
    while (m--) {
        cin >> r;
        int idx = query(r);
        cout << idx << " ";
        if (idx) {
            a[idx - 1] -= r;
            update(idx - 1, a[idx - 1]);
        }
    }
    cout << "\n";
}
