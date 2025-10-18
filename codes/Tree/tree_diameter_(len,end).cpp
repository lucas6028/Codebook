array<int, 2> dfs(int u, int w = -1) {
    array<int, 2> mx{0, u};  // {length, farthest leaf}
    for (auto& v : adj[u]) {
        if (v == w) continue;
        auto [len, leaf]{dfs(v, u)};
        mx = max(mx, {len + 1, leaf});
    }
    return mx;
}

array<int, 3> tree_diameter(int a = 0) {
    auto b{dfs(a)[1]};      // farthest node from 'a'
    auto [l, c]{dfs(b)};    // farthest node from 'b'
    return {l, b, c};       // {diameter length, endpoint1, endpoint2}
}