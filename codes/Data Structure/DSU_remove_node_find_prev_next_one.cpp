// previous/next one
class PvNx {
    vector<int> pa, sz, mn, mx;
    int find(int x) { // collapsing find
        return pa[x] == -1 ? x : pa[x] = find(pa[x]);
    }
    void unionn(int x, int y) { // weighted union
        auto rx{find(x)}, ry{find(y)};
        if (rx == ry) return ;
        if (sz[rx] < sz[ry]) swap(rx, ry);
        pa[ry] = rx, sz[rx] += sz[ry], mn[rx] = min(mn[rx], mn[ry]), mx[rx] = max(mx[rx], mx[ry]);
    }
public:
    explicit PvNx(int n) : pa(n + 1, -1), sz(n + 1, 1), mn(n + 1) { iota(mn.begin(), mn.end(), 0), mx = mn; }
    void remove(int i) { unionn(i, i + 1); }
    int prev(int i) { return mn[find(i)] - 1; }
    int next(int i) {
        int j{mx[find(i)]};
        if (i == j) j = mx[find(j + 1)];
        return j;
    }
    bool exist(int i) { return i == mx[find(i)]; }
};