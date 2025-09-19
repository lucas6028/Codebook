// Eulerian cycle in an undirected graph

vector<int> euler_cycle(vector<vector<pair<int, int>>>& adj, int w = 0) {
    int n{adj.size()}, m{};
    for (int v{0}; v < n; ++v) m += adj[v].size();
    m /= 2;

    vector<int> res{};
    stack<pair<int, int>> stk{};
    stk.emplace(w, -1);
    vector<int> nxt(n);
    vector<bool> usd(m);
    while (!stk.empty()) {
        auto [u, i]{stk.top()};
        while (nxt[u] < adj[u].size() && usd[adj[u][nxt[u]].second]) ++nxt[u];
        if (nxt[u] < adj[u].size()) {
            auto [v, j]{adj[u][nxt[u]]};
            ++nxt[u], usd[j] = true, stk.emplace(v, j);
        } else {
            if (i != -1) res.push_back(i);
            stk.pop();
        }
    }
    return res;
}

int main() {
    int n = 4; // number of vertices
    vector<vector<pair<int, int>>> adj(n);

    // Add edges with edge IDs
    int eid = 0;
    auto add_edge = [&](int u, int v) {
        adj[u].push_back({v, eid});
        adj[v].push_back({u, eid});
        ++eid;
    };

    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 3);
    add_edge(3, 0);

    vector<int> cycle = euler_cycle(adj, 0);

    cout << "Euler cycle (edge IDs in order): ";
    for (int id : cycle) cout << id << " ";
    cout << "\n";

    return 0;
}
