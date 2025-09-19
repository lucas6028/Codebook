int fir[maxn]; // length of the longest downward path from u into its subtree.
int sec[maxn]; // length of the second longest downward path from u
int res[maxn];

void dfs1(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs1(v, u);
            if (fir[v] + 1 > fir[u]) {
                sec[u] = fir[u];
                fir[u] = fir[v] + 1;
            }
            else if (fir[v] + 1 > sec[u]) {
                sec[u] = fir[v] + 1;
            }
        }
    }
}

// to_p: the best path length that comes from the parent’s side
void dfs2(int u, int p, int to_p) {
    res[u] = max(to_p, fir[u]);

    for (int v : adj[u]) {
        if (v != p) {
            if (fir[v] + 1 == fir[u]) {
                dfs2(v, u, max(to_p, sec[u]) + 1);
            }
            else {
                dfs2(v, u, res[u] + 1);
            }
        }
    }
}

// usage
dfs1(1, 0);
dfs2(1, 0, 0);
// Now res[i] is the maximum distance from node i to any other node
for (int i = 1; i <= n; i++) {
    cout << res[i] << " ";
}