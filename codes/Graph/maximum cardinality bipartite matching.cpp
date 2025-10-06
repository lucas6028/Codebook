class BipartiteMatching {
    vector<bool> vis;
    vector<int> mx{}, my{};
    bool dfs(const vector<vector<int>>& adj, int x) {
        for (int y : adj[x]) {
            if (vis[y]) continue;
            vis[y] = true;
            if (my[y] == -1 || dfs(adj, my[y])) {
                mx[x] = y; my[y] = x;
                return true;
            }
        }
        return false;
    }
public:
    pair<vector<int>, vector<int>> operator()(const vector<vector<int>>& adj, int ny) {
        vis.assign(ny, false);
        mx.assign((int)adj.size(), -1);
        my.assign(ny, -1);
        for (int x = 0; x < (int)adj.size(); ++x) {
            fill(vis.begin(), vis.end(), false);
            dfs(adj, x);
        }
        return {mx, my};
    }
};

// Usage example:
int main() {
    // Left partition has 4 nodes (0..3), right partition has 4 nodes (0..3).
    vector<vector<int>> adj(4);
    adj[0] = {0, 1};
    adj[1] = {1, 2};
    adj[2] = {2};
    adj[3] = {2, 3};

    BipartiteMatching bm;
    auto res = bm(adj, 4);
    const auto& mx = res.first;

    cout << "Matched pairs (left -> right):\n";
    for (int i = 0; i < (int)mx.size(); ++i)
        if (mx[i] != -1)
            cout << i << " -> " << mx[i] << "\n";
}