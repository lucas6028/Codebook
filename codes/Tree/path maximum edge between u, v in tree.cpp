int depth[maxn];
int up[LOG][maxn];
int maxEdge[LOG][maxn];

void dfs(int u, int p = -1, int w = 0) {
    up[0][u] = (p == -1 ? u : p);
    maxEdge[0][u] = (p == -1 ? 0 : w);
    for (auto &[v, rw] : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, rw);
        }
    }
}

int lca_weight(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    int ans = 0;

    for (int k = 0; diff; ++k) {
        if (diff & 1) { 
            ans = max(ans, maxEdge[k][a]);
            a = up[k][a];
        }
        diff >>= 1;
    }
    if (a == b) { 
        return ans;
    }
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[k][a] != up[k][b]) {
            ans = max(ans, maxEdge[k][a]);
            ans = max(ans, maxEdge[k][b]);
            a = up[k][a];
            b = up[k][b];
        }
    }

    ans = max(ans, maxEdge[0][a]);
    ans = max(ans, maxEdge[0][b]);
    return ans;
}

void solve() {
    dfs(0, -1, 0);
    for (int k = 1; k < LOG; ++k) {
        for (int v = 0; v < n; ++v) {
            up[k][v] = up[k - 1][up[k - 1][v]];
            maxEdge[k][v] = max(maxEdge[k - 1][v], maxEdge[k - 1][up[k - 1][v]]);
        }
    }
    int path_max = lca_weight(0, 1);
}
