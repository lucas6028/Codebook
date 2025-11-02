void dfs(int u, int p = -1) {
    up[0][u] = (p == -1 ? u : p);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

int get_kth_ancestor(int x, int k) {
    for (int i = 0; i <= LOG; ++i) {
        if (k & (1LL<<i)) {
            x = up[i][x];
        }
    }
    return (x == 0 ? -1 : x);
}

void solve() {
    int n, q;
    cin >> n >> q;

    adj[0].push_back(1);
    for (int i = 2; i <= n; ++i) {
        int u;
        cin >> u;
        adj[u].push_back(i);
    }

    dfs(0, -1);

    for (int k = 1; k <= LOG; ++k) {
        for (int v = 1; v <= n; ++v) {
            up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        cout << get_kth_ancestor(x, k) << "\n";
    }
}