const int maxn = 2e5;
int n, q;
int val[maxn];
int id[maxn];
int sz[maxn];
int parent[maxn];
int depth[maxn];
int tp[maxn];
vector<int> adj[maxn];
int timer = 0;

int dfs_sz(int u, int p) {
    sz[u] = 1;
    parent[u] = p;

    // calculate size of each subtree
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            sz[u] += dfs_sz(v, u);
        }
    }
    return sz[u];
}

void dfs_hld(int u, int p, int top, SGT<int, MergeMax>& tree) {
    id[u] = timer++;
    tp[u] = top;
    tree.update(id[u], val[u]);
    
    // find the heavy child
    int h_v = -1, h_sz = -1;
    for (int v : adj[u]) {
        if (v != p) {
            if (h_sz < sz[v]) {
                h_sz = sz[v];
                h_v = v;
            }
        }
    }
    if (h_v == -1) {
        return;
    }

    // continue the chain
    dfs_hld(h_v, u, top, tree);
    // start a new chain for each light child
    for (int v : adj[u]) {
        if (v != p && v != h_v) {
            dfs_hld(v, u, v, tree);
        }
    }
}

int path(int x, int y, SGT<int, MergeMax>& tree) {
    int ans = 0;
    // move x and y to their top nodes until they are in the same chain
    while (tp[x] != tp[y]) {
        if (depth[tp[x]] < depth[tp[y]]) swap(x, y);
        ans = max(ans, tree.query(id[tp[x]], id[x] + 1));
        x = parent[tp[x]];
    }
    if (depth[x] > depth[y]) swap(x, y);
    ans = max(ans, tree.query(id[x], id[y] + 1));
    return ans;
}

void solve() {
    cin >> n >> q;
    SGT<int, MergeMax> tree(n, -1);

    for (int i = 0; i < n; ++i) {
        cin >> val[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    dfs_sz(0, 0);
    dfs_hld(0, 0, 0, tree);

    cerr << "tp: ";
    for (int i = 0; i < n; ++i) {
        cerr << tp[i] << " ";
    }
    cerr << "\n";

    while (q--) {
        int mode;
        cin >> mode;
        if (mode == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            val[s] = x;
            tree.update(id[s], val[s]);
        }
        else {
            int a, b;
            cin >> a >> b;
            cout << path(a - 1, b - 1, tree) << " ";
        }
    }
}