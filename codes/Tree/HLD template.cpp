struct HLD {
    int n, cur = 0;
    vector<int> sz, top, dep, par, tin, tout, seq;
    vector<vector<int>> adj;
    HLD(int n = 0) {
        init(n);
    }
    void init(int n_) {
        n = n_;
        sz.assign(n, 1);
        top.assign(n, -1);
        dep.assign(n, 0);
        par.assign(n, -1);
        tin.assign(n, 0);
        tout.assign(n, 0);
        seq.assign(n, 0);
        adj.resize(n, {});
    }
    void add_edge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
    void build(int root = 0) {
        top[root] = root, dep[root] = 0, par[root] = -1;
        dfs1(root), dfs2(root);
    }
    void dfs1(int u) {
        if (auto it = find(adj[u].begin(), adj[u].end(), par[u]); it != adj[u].end()) {
            adj[u].erase(it);
        }
        for (auto &v : adj[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) { swap(v, adj[u][0]); }
        }
    }
    void dfs2(int u) {
        tin[u] = cur++;
        seq[tin[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        tout[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = par[top[u]];
            } else {
                v = par[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
    int jump(int u, int k) {
        if (dep[u] < k) { return -1; }
        int d = dep[u] - k;
        while (dep[top[u]] > d) { u = par[top[u]]; }
        return seq[tin[u] - dep[u] + d];
    }
    // u is v's ancestor
    bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tin[v] < tout[u]; }
    // root's parent is itself
    int rooted_parent(int r, int u) {
        if (r == u) { return u; }
        if (is_ancestor(r, u)) { return par[u]; }
        auto it = upper_bound(adj[u].begin(), adj[u].end(), r, [&](int x, int y) {
            return tin[x] < tin[y];
        }) - 1;
        return *it;
    }
    // rooted at u, v's subtree size
    int rooted_size(int r, int u) {
        if (r == u) { return n; }
        if (is_ancestor(u, r)) { return sz[u]; }
        return n - sz[rooted_parent(r, u)];
    }
    int rooted_lca(int r, int a, int b) { return lca(a, b) ^ lca(a, r) ^ lca(b, r); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 7;
    HLD hld(n);

    // build this tree:
    //     0
    //    / \
    //   1   2
    //  / \   \
    // 3   4   5
    //         |
    //         6
    hld.add_edge(0, 1);
    hld.add_edge(0, 2);
    hld.add_edge(1, 3);
    hld.add_edge(1, 4);
    hld.add_edge(2, 5);
    hld.add_edge(5, 6);

    hld.build(0); // root at node 0

    cout << "LCA(3,4) = " << hld.lca(3,4) << "\n"; // expected 1
    cout << "LCA(3,6) = " << hld.lca(3,6) << "\n"; // expected 0
    cout << "Distance(3,4) = " << hld.dist(3,4) << "\n"; // expected 2
    cout << "Distance(3,6) = " << hld.dist(3,6) << "\n"; // expected 4
    cout << "Is 0 ancestor of 6? " << (hld.is_ancestor(0,6) ? "yes" : "no") << "\n"; // yes

    return 0;
}