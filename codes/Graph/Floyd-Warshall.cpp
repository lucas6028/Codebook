// Floyd-Warshall algorithm
template<typename T>
vector<vector<optional<T>>> Floyd_Warshall(const vector<vector<optional<T>>>& adj) {
    const auto& n{adj.size()};
    auto d{adj};

    for (int i{0}; i < n; ++i) d[i][i] = 0;
    for (int k{0}; k < n; ++k)
        for (int i{0}; i < n; ++i)
            for (int j{0}; j < n; ++j) {
                if (!d[i][k] || !d[k][j]) continue; // no value
                if (!d[i][j] || d[i][j] > d[i][k].value() + d[k][j].value())
                    d[i][j] = d[i][k].value() + d[k][j].value();
            }

    return d;
}