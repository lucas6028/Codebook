// Euler Tour Technique
class LCA {
    const vector<vector<int>>& adj;
    int n;
    vector<int> d, first, euler{}, log2{};
    vector<vector<int>> st{};
    void dfs(int u, int w = -1, int dep = 0) {
        d[u] = dep;
        first[u] = euler.size();
        euler.push_back(u);
        for (auto& v : adj[u]) {
            if (v == w) continue;
            dfs(v, u, dep + 1);
            euler.push_back(u);
        }
    }
public:
    LCA(const vector<vector<int>>& _adj, int root) : adj{_adj}, n{adj.size()}, d(n), first(n) {
        dfs(root);

        int tn{euler.size()};
        log2.resize(tn + 1);
        log2[1] = 0;
        for (int i{2}; i <= tn; ++i) log2[i] = log2[i / 2] + 1;

        st.assign(tn, vector<int>(log2[tn] + 1));
        for (int i{tn - 1}; i >= 0; --i) {
            st[i][0] = euler[i];
            for (int j{1}; i + (1 << j) <= tn; ++j) {
                auto& x{st[i][j - 1]};
                auto& y{st[i + (1 << (j - 1))][j - 1]};
                st[i][j] = d[x] <= d[y] ? x : y;
            }
        }
    }
    int operator()(int u, int v) {
        int l{first[u]}, r{first[v]};
        if (l > r) swap(l, r);
        ++r; // make the interval left closed right open

        int j{log2[r - l]};
        auto& x{st[l][j]};
        auto& y{st[r - (1 << j)][j]};
        return d[x] <= d[y] ? x : y;
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

    LCA lca(adj, 0);

    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << lca(u, v) + 1 << "\\n";
    }
    return 0;
}