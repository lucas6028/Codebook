// Bellman-Ford algorithm
template<typename T>
optional<vector<optional<T>>> Bellman_Ford(const vector<vector<pair<int, T>>>& adj, int s) {
    const auto& n{adj.size()};
    vector<optional<T>> d(n, nullopt);
    d[s] = 0;

    queue<int> qu{}, qu2{};
    vector<bool> in(n, false), in2(n, false);
    qu.push(s), in[s] = true;
    for (int i{0}; i < n; ++i) { // at most n-1 edges
        while (!qu.empty()) {
            int u{qu.front()};
            qu.pop(), in[u] = false;
            for  (auto& [v, w] : adj[u])
                if (!d[v] || d[v] > d[u].value() + w) { // relax
                    d[v] = d[u].value() + w;
                    if (!in2[v]) qu2.push(v), in2[v] = true;
                }
        }
        qu.swap(qu2), in.swap(in2);
    }

    if (qu.empty()) return d;
    return nullopt; // if negative cycle
}