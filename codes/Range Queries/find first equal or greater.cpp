// CSE: Hotel Queries

int n, m;
int sz = 1;
const int maxn = 2e6;
int t[maxn << 1];

// Segment Tree (range max)

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
}
