// Kruskal’s algorithm
vector<tuple<int, int, long long>> Kruskal(int n, vector<tuple<long long, int, int>>& edges) {
    vector<tuple<int, int, long long>> mst{};
    DSU dsu{n};

    sort(edges.begin(), edges.end());
    for (auto& [w, u, v] : edges)
        if (dsu.find(u) != dsu.find(v))
            dsu.unionn(u, v), mst.emplace_back(u, v, w);
    return mst;
}