int diam = 0;

int dfs(int u, int p = -1) {
    int mx = 0;
    for (int v : adj[u]) {
        if (v != p) {
            int len = 1 + dfs(v, u);
            diam = max(diam, mx + len);
            mx = max(mx, len);
        }
    }
    return mx;
}
