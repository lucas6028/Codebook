// Floyd's Cycle-Finding Algorithm
// Given a function succ(x) that returns the successor of x,
a = succ(x);
b = succ(succ(x));
while (a != b) {
    a = succ(a);
    b = succ(succ(b));
}

// Find the first element in the cycle
a = x;
while (a != b) {
    a = succ(a);
    b = succ(b);
}
first = a;

// Find the length of the cycle
length = 1;
b = succ(a);
while (a != b) {
    b = succ(b);
    length = length + 1;
}

// Finding the starting point of the cycle from any node
int n;
vector<int> adj, res;
vector<vector<int>> radj;

void fill_radj(int u) {
    for (int v : radj[u]) {
        if (res[v] == -1) {
            res[v] = res[u];
            fill_radj(v);
        }
    }
}

void floyd(int x) {
    int y = x;
    do { // find a cycle using Floyd's algorithm
        x = adj[x];
        y = adj[adj[y]];
    } while (y != x);
    do { // set res[x] = x for all x along cycle
        res[x] = x;
        x = adj[x];
    } while (y != x);
    do { // set res'es for all x not along cycle
        fill_radj(x);
        x = adj[x];
    } while (y != x);
}

void solve() {
    cin >> n;
    adj.resize(n);
    radj.assign(n, {});
    res.assign(n, -1);

    for (auto& e : adj) {
        cin >> e;
        e--;
    }

    for (int i = 0; i < n; ++i) {
        radj[adj[i]].push_back(i);
    }

    for (int i = 0; i < n; ++i) {
        if (res[i] == -1) {
            floyd(i);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << res[i] + 1 << " ";
    }
    cout << "\n";
}