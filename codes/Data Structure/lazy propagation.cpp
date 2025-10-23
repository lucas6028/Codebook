// Lazy Propagation Segment Tree supporting range add, range set, and range sum queries

int n;
int sz;
struct Node {
    int sum = 0;
    int lazy_add = 0;
    int lazy_set = 0;
    bool has_set = false;
};
vector<Node> tree;
 
void build(const vector<int>& a) {
    tree.resize(sz << 1);
    for (int i = 0; i < sz; ++i) {
        tree[i + sz].sum = i < n ? a[i] : 0;
    }
    for (int i = sz - 1; i >= 1; --i) {
        tree[i].sum = tree[i << 1].sum + tree[i << 1 | 1].sum;
    }
}
 
void apply_set(int idx, int l, int r, int val) {
    tree[idx].sum = (r - l + 1) * val;
    tree[idx].lazy_set = val;
    tree[idx].lazy_add = 0;
    tree[idx].has_set = true;
}
 
void apply_add(int idx, int l, int r, int val) {
    if (tree[idx].has_set) {
        tree[idx].lazy_set += val;
    }
    else {
        tree[idx].lazy_add += val;
    }
    tree[idx].sum += (r - l + 1) * val;
}
 
void push(int idx, int l, int r) {
    if (l == r) return;
 
    int mid = l + (r - l) / 2;
    int left = idx << 1, right = idx << 1 | 1;
 
    if (tree[idx].has_set) {
        // progagate the set operation
        apply_set(left, l, mid, tree[idx].lazy_set);
        apply_set(right, mid + 1, r, tree[idx].lazy_set);
        tree[idx].has_set = false;
        tree[idx].lazy_set = 0;
        tree[idx].lazy_add = 0;
    }
    else if (tree[idx].lazy_add != 0) {
        // propagate the add operation
        apply_add(left, l, mid, tree[idx].lazy_add);
        apply_add(right, mid + 1, r, tree[idx].lazy_add);
        tree[idx].lazy_add = 0;
    }
}
 
void range_set(int idx, int l, int r, int ql, int qr, int val) {
    if (qr < l || ql > r) return;
    if (ql <= l && r <= qr) {
        apply_set(idx, l, r, val);
        return;
    }
 
    push(idx, l, r);
    int mid = (l + r) / 2;
    range_set(idx << 1, l, mid, ql, qr, val);
    range_set(idx << 1 | 1, mid + 1, r, ql, qr, val);
    tree[idx].sum = tree[idx << 1].sum + tree[idx << 1 | 1].sum;
}
 
void range_add(int idx, int l, int r, int ql, int qr, int val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        apply_add(idx, l, r, val);
        return;
    }
 
    push(idx, l, r);
    int mid = (l + r) / 2;
    range_add(idx << 1, l, mid, ql, qr, val);
    range_add(idx << 1 | 1, mid + 1, r, ql, qr, val);
    tree[idx].sum = tree[idx << 1].sum + tree[idx << 1 | 1].sum;
}
 
int range_sum(int idx, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;
    if (ql <= l && r <= qr) return tree[idx].sum;
 
    push(idx, l, r);
    int mid = (l + r) / 2;
    return range_sum(idx << 1, l, mid, ql, qr) + 
            range_sum(idx << 1 | 1, mid + 1, r, ql, qr);
}
 
void solve() {
    int q;
    cin >> n >> q;
    vector<int> a(n);
 
    sz = 1;
    while (sz < n) sz <<= 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
 
    build(a);
 
    while (q--) {
        int mode, l, r, x;
        cin >> mode >> l >> r;
        l--, r--;
        if (mode == 1) {
            cin >> x;
            range_add(1, 0, sz - 1, l, r, x);
        }
        else if (mode == 2) {
            cin >> x;
            range_set(1, 0, sz - 1, l, r, x);
        }
        else {
            cout << range_sum(1, 0, sz - 1, l, r) << "\n";
        }
    }
}
