const int LOG = 32;
const int maxn = 2e5 + 2;

int depth[maxn];
int up[LOG][maxn];
vector<int> adj[maxn];

void dfs(int u, int p = -1) {
    up[0][u] = (p == -1 ? u : p);
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    int diff = depth[a] - depth[b];
    for (int k = 0; diff; ++k) {
        if (diff & 1) a = up[k][a];
        diff >>= 1;
    }
    if (a == b) return a;
    for (int k = LOG - 1; k >= 0; --k) {
        if (up[k][a] != up[k][b]) {
            a = up[k][a];
            b = up[k][b];
        }
    }
    return up[0][a];
}

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; ++i) {
        int u;
        cin >> u;
        adj[u].push_back(i);
    }

    dfs(1, -1);  // root = 1

    for (int k = 1; k < LOG; ++k) {
        for (int v = 1; v <= n; ++v) {
            up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
}
