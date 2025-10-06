// maximum cardinality bipartite matching
// Hopcroft–Karp algorithm - O(E√V)
class bipartiteGraph {
    int nx, ny;
    vector<int> dx, dy;
    bool dfs(int y) {
        for (auto& x : adjy[y]) {
            if (dx[x] + 1 != dy[y]) continue;
            if (mx[x] == -1 || dfs(mx[x])) {
                my[y] = x, mx[x] = y;
                dy[y] = -1; // augmented - remove from BFS forest
                return true;
            }
        }
        dy[y] = -1; // no augmenting path - remove from BFS forest
        return false;
    }
    bool bfs() {
        fill(dx.begin(), dx.end(), -1);
        fill(dy.begin(), dy.end(), -1);
        queue<int> qu{}, qu2{};
        for (int x{0}; x < nx; ++x) // use all unmatched x's as roots
            if (mx[x] == -1) qu.push(x), dx[x] = 0;
 
        bool found{false};
        while (!qu.empty() && !found) { // stop at the level found
            while (!qu.empty()) {
                auto x{qu.front()}; qu.pop();
                for (auto& y : adjx[x])
                    if (dy[y] == -1 && my[y] != x) {
                        dy[y] = dx[x] + 1;
                        if (my[y] == -1) found = true;
                        else qu2.push(my[y]), dx[my[y]] = dy[y] + 1;
                    }
            }
            qu.swap(qu2);
        }
        return found;
    }
    vector<vector<int>> adjx, adjy;
public:
    vector<int> mx, my;
    bipartiteGraph(int _nx, int _ny) : nx{_nx}, ny{_ny}, dx(nx), dy(ny)
        , adjx(nx), adjy(ny), mx(nx, -1), my(ny, -1) {}
    void addEdge(int x, int y) {
        adjx[x].push_back(y), adjy[y].push_back(x);
    }
    int Hopcroft_Karp() {
        int c{0};
        while (bfs()) {
            for (int y{0}; y < ny; ++y)
                if (my[y] == -1 && dy[y] != -1) c += dfs(y);
        }
        return c;
    }
};

// Usage example:
int main() {
    // Left partition has 4 nodes (0..3), right partition has 4 nodes (0..3).
    bipartiteGraph bg(4, 4);
    bg.addEdge(0, 0);
    bg.addEdge(0, 1);
    bg.addEdge(1, 1);
    bg.addEdge(1, 2);
    bg.addEdge(2, 2);
    bg.addEdge(3, 2);
    bg.addEdge(3, 3);

    int max_matching = bg.Hopcroft_Karp();
    cout << "Maximum matching size: " << max_matching << "\n";
    cout << "Matched pairs (left -> right):\n";
    for (int i = 0; i < (int)bg.mx.size(); ++i)
        if (bg.mx[i] != -1)
            cout << i << " -> " << bg.mx[i] << "\n";
}