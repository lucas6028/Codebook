// minimum cut maximum flow
// relabel-to-front algorithm
// (an implemention of generic push-relabel algorithm)

// handle the capacity, c, of a vertex, v.
// Add a new vertex, v', and an edge v-v' with capacity c.
template<typename T> //requires signed_integral<T>
void handle_vertex_capacity(int u, T c, int& n, vector<tuple<int, int, T>>& e) {
    int w{n++};
    for (auto& [_u, _v, _c] : e) if (_u == u) _u = w;
    e.emplace_back(u, w, c);
}

template<typename T> //requires signed_integral<T>
class flowNetwork {
    int n, s, t;
    vector<int> h; // height label
    vector<T> e; // excess
    vector<vector<int>> adj; // adjacent list
    vector<vector<T>> c, r{};
    vector<size_t> p; // record the position processed
    list<int> lst{}; // topological sort of admissible network
    void push(int u, int v) {
        T f{min(e[u], r[u][v])};
        r[u][v] -= f, r[v][u] += f;
        e[u] -= f, e[v] += f;
    }
    void relabel(int u) {
        int mn{numeric_limits<int>::max()};
        for (auto& v : adj[u])
            if (r[u][v]) mn = min(mn, h[v]);
        h[u] = mn + 1;
    }
    void init() {
        fill(h.begin(), h.end(), 0);
        fill(e.begin(), e.end(), 0);
        lst.clear();
        for (int u{0}; u < n; ++u) if (u != s && u != t) lst.push_back(u);
        fill(p.begin(), p.end(), 0);
        r = c;
    }
    void preflow() {
        h[s] = n;
        for (auto& v : adj[s]) {
            e[v] += r[s][v], e[s] -= r[s][v];
            r[v][s] += r[s][v], r[s][v] = 0;
        }
    }
    bool discharge(int u) {
        bool flag{false};
        while (e[u]) {
            for (; p[u] < adj[u].size(); ++p[u]) {
                int v{adj[u][p[u]]};
                if (r[u][v] && h[u] == h[v] + 1) push(u, v);
                if (!e[u]) break;
            }
            if (e[u]) relabel(u), p[u] = 0, flag = true;
        }
        return flag; // return if relabel or not
    }
public:
    flowNetwork(int _n) : n{_n}, s{0}, t{n - 1}, h(n), e(n), adj(n), c(n, vector<T>(n)), p(n) {}
    void set_st(int _s, int _t) {
        s = _s, t = _t;
    }
    void add_edge(int u, int v, T _c) {
        if (!c[u][v] && !c[v][u]) adj[u].push_back(v), adj[v].push_back(u);
        c[u][v] += _c;
    }
    T max_flow() {
        assert(s != t);

        init();
        preflow();

        auto it{lst.begin()};
        while (it != lst.end()) {
            if (discharge(*it)) { // relabel-to-front
                lst.push_front(*it), lst.erase(it);
                it = lst.begin();
            }
            it = next(it);
        }

        return e[t];
    };
};


int main() {
    using T = int;

    // Build an example graph with a vertex capacity on node 2.
    int n = 4; // nodes: 0 (source), 1, 2, 3 (sink)
    vector<tuple<int, int, T>> edges = {
        {0, 1, 3},
        {0, 2, 2},
        {1, 2, 5},
        {1, 3, 2},
        {2, 3, 3}
    };

    // Enforce vertex capacity of 2 on node 2.
    handle_vertex_capacity<T>(2, 2, n, edges);

    // Build the network and compute max flow.
    flowNetwork<T> net(n);
    net.set_st(0, 3);
    for (auto [u, v, cap] : edges) net.add_edge(u, v, cap);

    cout << "Max flow = " << net.max_flow() << '\n';
}