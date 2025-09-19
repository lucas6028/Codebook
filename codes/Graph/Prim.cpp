// Prim's algorithm
vector<tuple<int, int, long long>> Prim(const vector<vector<pair<int, long long>>>& adj) {
    const auto& n = adj.size();
    vector<tuple<int, int, long long>> mst{};

    vector<bool> found(n, false);
    using ti = tuple<long long, int, int>;
    priority_queue<ti, vector<ti>, greater<ti>> pq{};
    found[0] = true;
    for (auto& [v, w] : adj[0]) pq.emplace(w, 0, v);

    for (int i = 0; i < n - 1; ++i) {
        int mn, u, v;
        do {
            tie(mn, u, v) = pq.top(), pq.pop();
        } while (found[v]);
        found[v] = true, mst.emplace_back(u, v, mn);
        for (auto& [x, w] : adj[v]) pq.emplace(w, v, x);
    }
    return mst;
}