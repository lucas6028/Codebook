// Stable Marriage Problem (stable matching)
// Gale–Shapley algorithm
class bipartiteGraph {
public:
    int n;
    vector<vector<int>> px, py;
    vector<int> mx, my;

    bipartiteGraph(int _n) : n(_n), px(n, vector<int>(n)), py(n, vector<int>(n)), mx(n, -1), my(n, -1) {}
    void Gale_Shapley() {
        queue<int> qu{};
        vector<priority_queue<pair<int, int>>> pq(n);
        for (int x{0}; x < n; ++x) {
            qu.push(x);
            for (int y{0}; y < n; ++y) pq[x].emplace(px[x][y], y);
        }

        while (!qu.empty()) {
            auto x{qu.front()}; qu.pop();
            
            int y;
            do {
                y = pq[x].top().second; pq[x].pop();
            } while (my[y] != -1 && py[y][x] <= py[y][my[y]]);

            if (my[y] != -1) mx[my[y]] = -1, qu.push(my[y]); // y prefers x to my[y]
            mx[x] = y, my[y] = x;
        }
    }
};

int main() {
    int n = 3;
    bipartiteGraph g(n);

    // Men preferences (from most to least preferred)
    vector<vector<int>> men = {
        {0, 1, 2},
        {1, 2, 0},
        {1, 0, 2}
    };

    // Women preferences (from most to least preferred)
    vector<vector<int>> women = {
        {1, 0, 2},
        {2, 1, 0},
        {0, 1, 2}
    };

    // Convert orders to scores (higher is better)
    for (int x = 0; x < n; ++x)
        for (int pos = 0; pos < n; ++pos)
            g.px[x][men[x][pos]] = n - pos;

    for (int y = 0; y < n; ++y)
        for (int pos = 0; pos < n; ++pos)
            g.py[y][women[y][pos]] = n - pos;

    g.Gale_Shapley();

    // Output matches: man x is matched to woman g.mx[x]
    for (int x = 0; x < n; ++x)
        cout << x << " " << g.mx[x] << '\n';

    return 0;
}