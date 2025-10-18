// binary lifting
class LCA {
    const vector<vector<int>>& adj;
    int n;
    vector<int> d;
    vector<int> log2;
    vector<vector<int>> an{};
    void dfs(int u, int w = -1, int dep = 0) {
        d[u] = dep;
        an[u][0] = w;
        for (int i{1}; i <= log2[n - 1] && an[u][i - 1] != -1; ++i)
            an[u][i] = an[an[u][i - 1]][i - 1]; // 走 2^(i-1) 再走 2^(i-1) 步

        // 因為計算 an 會用到祖先的資訊，所以先計算再繼續往下
        for (auto& v : adj[u]) {
            if (v == w) continue; // parent
            dfs(v, u, dep + 1);
        }
    }
public:
    LCA(const vector<vector<int>>& _adj, int root)
    : adj{_adj}, n{adj.size()}, d(n), log2(n) {
        log2[1] = 0;
        for (int i{2}; i < log2.size(); ++i) log2[i] = log2[i / 2] + 1;
        an.assign(n, vector<int>(log2[n - 1] + 1, -1));
        dfs(root);
    }
    int operator()(int u, int v) {
        if (d[u] > d[v]) swap(u, v);

        for (int i{log2[d[v] - d[u]]}; i >= 0; --i)
            if (d[v] - d[u] >= (1 << i)) v = an[v][i];
        // v 先走到跟 u 同高度
        if (u == v) return u;

        for (int i{log2[d[u]]}; i >= 0; --i)
            if (an[u][i] != an[v][i]) u = an[u][i], v = an[v][i];
        // u, v 一起走到 lca(u, v) 的下方

        return an[u][0];
        // 回傳 lca(u, v)
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);

    for (int i = 1; i < n; ++i) {
        int u;
        cin >> u;
        u--;
        adj[u].pb(i);
        adj[i].pb(u);
    }

    // adj, root
    LCA lca(adj, 0);

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << lca(u, v) + 1 << "\\n";
    }
    return 0;
}