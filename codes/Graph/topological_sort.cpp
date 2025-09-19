// topological sort 1
optional<vector<int>> top_sort(vector<vector<int>>& adj) {
    vector<int> res{};
    int n{static_cast<int>(adj.size())};
    vector<int> cnt(n, 0); // predecessor count
    for (int u = 0; u < n; ++u)
        for (auto& v : adj[u]) ++cnt[v];

    queue<int> qu{};
    for (int u = 0; u < n; ++u) if (!cnt[u]) qu.push(u);
    while (!qu.empty()) {
        auto u = qu.front();
        qu.pop();
        res.push_back(u);

        for (auto& v : adj[u])
            if (!--cnt[v]) qu.push(v);
    }

    if (res.size() != adj.size()) return nullopt;
    return res;
}