// maximum weight matching in a weighted bipartite graph
// Hungarian Algorithm - O(V^3)
class bipartiteGraph {
    int n;
    vector<long long> lx, ly;
    vector<bool> vx, vy;
    queue<int> qu{}; // only X's vertices
    vector<int> py;
    vector<long long> dy; // smallest (lx[x] + ly[y] - w[x][y])
    vector<int> pdy; // & which x
    void relax(int x) {
        for (int y{0}; y < n; ++y)
            if (lx[x] + ly[y] - w[x][y] < dy[y])
                dy[y] = lx[x] + ly[y] - w[x][y], pdy[y] = x;
    }
    void augment(int y) {
        while (y != -1) {
            int x{py[y]}, yy{mx[x]};
            mx[x] = y, my[y] = x;
            y = yy;
        }
    }
    bool bfs() {
        while (!qu.empty()) {
            int x{qu.front()}; qu.pop();
            for (int y{0}; y < n; ++y) {
                if (!vy[y] && lx[x] + ly[y] == w[x][y]) {
                    vy[y] = true, py[y] = x;
                    if (my[y] == -1) return augment(y), true;
                    int xx{my[y]};
                    qu.push(x), vx[xx] = true, relax(xx);
                }
            }
        }
        return false;
    }
    void relabel() {
        long long d{numeric_limits<long long>::max()};
        for (int y{0}; y < n; ++y) if (!vy[y]) d = min(d, dy[y]);
        for (int x{0}; x < n; ++x) if (vx[x]) lx[x] -= d;
        for (int y{0}; y < n; ++y) if (vy[y]) ly[y] += d;
        for (int y{0}; y < n; ++y) if (!vy[y]) dy[y] -= d;
    }
    bool expand() { // expand one layer with new equality edges
        for (int y{0}; y < n; ++y) {
            if (!vy[y] && dy[y] == 0) {
                vy[y] = true, py[y] = pdy[y];
                if (my[y] == -1) return augment(y), true;
                int xx{my[y]};
                qu.push(xx), vx[xx] = true, relax(xx);
            }
        }
        return false;
    }
public:
    vector<vector<long long>> w;
    vector<int> mx, my;
    bipartiteGraph(int _n) : n{_n}, lx(n), ly(n), vx(n), vy(n), py(n), dy(n), pdy(n),
        w(n, vector<long long>(n, 0)), mx(n, -1), my(n, -1) {}
    long long Hungarian() {
        for (int i{0}; i < n; ++i) {
            lx[i] = ly[i] = 0;
            for (int j{0}; j < n; ++j)
                lx[i] = max(lx[i], w[i][j]);
            mx[i] = my[i] = -1;
        }
    
        for (int x{0}; x < n; ++x) {
            fill(vx.begin(), vx.end(), false);
            fill(vy.begin(), vy.end(), false);
            fill(dy.begin(), dy.end(), numeric_limits<long long>::max());

            qu = {}, qu.push(x), vx[x] = true, relax(x);
            while (!bfs()) {
                relabel();
                if (expand()) break;
            }
        }
     
        long long weight{0};
        for (int x{0}; x < n; ++x) weight += w[x][mx[x]];
        return weight;
    }
};

// usage example:
int main() {
    int n = 4;
    bipartiteGraph g(n);
    long long mat[4][4] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            g.w[i][j] = mat[i][j];

    long long maxWeight = g.Hungarian();
    std::cout << "Maximum weight: " << maxWeight << "\n";
    for (int i = 0; i < n; ++i)
        std::cout << "X " << i << " matched with Y " << g.mx[i] << "\n";
}