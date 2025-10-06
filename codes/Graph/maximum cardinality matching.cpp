// maximum matching
// Edmonds' Blossom algorithm
// O(VEα(E,V))
class graph {
    int n;
    vector<int> p, d, a, c1, c2;
    // (alternating tree), (unvisited: -1, even: 0, odd: 1), (auxiliary for lca), (cross edge)
    int label{0};
    /* DSU */
    vector<int> dsu_p, dsu_sz, dsu_b;
    void dsu_reset() {
        fill(dsu_p.begin(), dsu_p.end(), -1);
        fill(dsu_sz.begin(), dsu_sz.end(), 1);
        iota(dsu_b.begin(), dsu_b.end(), 0);
    }
    int find(int x) { // collapsing find
        return dsu_p[x] == -1 ? x : dsu_p[x] = find(dsu_p[x]);
    }
    int base(int x) { return dsu_b[find(x)]; }
    void contract(int x, int y) { // weighted union
        auto rx{find(x)}, ry{find(y)};
        if (rx == ry) return ;
        auto b{dsu_b[rx]}; // treat x's base as new base
        if (dsu_sz[rx] < dsu_sz[ry]) swap(rx, ry);
        dsu_p[ry] = rx, dsu_sz[rx] += dsu_sz[ry], dsu_b[rx] = b;
    }
    /*******/
    queue<int> qu{}; // only even vertices
    void handle_one_side(int x, int y, int b) {
        for (int v{base(x)}; v != b; v = base(p[v])) {
            c1[v] = x, c2[v] = y, contract(b, v);
            if (d[v] == 1) qu.push(v); // odd vertex -> even vertex
        }
    }
    int lca(int u, int v) {
        ++label; // use next number in order not to clear a
        while (true) {
            if (a[u] == label) return u;
            a[u] = label;
            if (p[u] != -1) u = base(p[u]);
            swap(u, v);
        }
    }
    void augment(int r, int y) {
        if (r == y) return ;
        if (d[y] == 0) { // even vertex -> odd vertex
            // check d[y] == 0 instead of d[p[y]] == 1, so (m[y], y) is in the blossom
            augment(m[y], m[c1[y]]);
            augment(r, m[c2[y]]);
            m[c1[y]] = c2[y], m[c2[y]] = c1[y];
        } else {
            int x{p[y]};
            augment(r, m[x]);
            m[x] = y, m[y] = x;
        }
    }
    bool bfs(int r) {
        dsu_reset();
        fill(d.begin(), d.end(), -1);

        qu = {}, qu.push(r), d[r] = 0;
        while (!qu.empty()) {
            int x{qu.front()}; qu.pop();
            for (auto& y : adj[x]) {
                if (base(x) == base(y)) continue;
                if (d[y] == -1) {
                    p[y] = x, d[y] = 1;
                    if (m[y] == -1) { // augmenting path
                        augment(-1, y);
                        return true;
                    } else {
                        p[m[y]] = y, d[m[y]] = 0;
                        qu.push(m[y]);
                    }
                } else if (d[base(y)] == 0) { // blossom
                    int b{lca(base(x), base(y))};
                    handle_one_side(x, y, b);
                    handle_one_side(y, x, b);
                }
            }
        }
        return false;
    }
public:
    vector<vector<int>> adj;
    vector<int> m;
    explicit graph(int _n) : n{_n}, p(n, -1), d(n), a(n), c1(n), c2(n), dsu_p(n), dsu_sz(n), dsu_b(n), adj(n), m(n, -1) {}
    int Edmonds() {
        int c{0};
        for (int v{0}; v < n; ++v)
            if (m[v] == -1 && bfs(v)) ++c;
        return c;
    }
};

// usage example:
int main() {
    int n = 5;
    graph g(n);
    auto add = [&](int u, int v) {
        g.adj[u].push_back(v);
        g.adj[v].push_back(u);
    };

    // sample graph
    add(0, 1);
    add(0, 2);
    add(1, 2); // triangle (0,1,2)
    add(2, 3);
    add(3, 4);

    int match_size = g.Edmonds();
    cout << "Maximum matching size: " << match_size << "\n";
    for (int i = 0; i < n; ++i)
        if (g.m[i] != -1 && i < g.m[i])
            cout << i << " - " << g.m[i] << "\n";
}