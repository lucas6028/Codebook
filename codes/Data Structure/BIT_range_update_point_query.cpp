// Fenwick Tree (Binary Indexed Tree) for Range Updates and Point Queries

template<typename T>
class BIT {
#define ALL(x) begin(x), end(x)
private:
    vector<T> arr;
    int n;
    inline int lowbit(int x) { return x & (-x); }
    void addInternal(int s, T v) {
        while (s > 0) {
            arr[s] += v;
            s -= lowbit(s);
        }
    }
public:
    void init(int n_) {
        n = n_;
        arr.resize(n + 1);
        fill(ALL(arr), 0);
    }
    void add(int l, int r, T v) {
        // add v to interval (l, r], 1-based
        addInternal(l, -v);
        addInternal(r, v);
    }
    T query(int x) {
        // value at index x
        T res = 0;
        while (x <= n) {
            res += arr[x];
            x += lowbit(x);
        }
        return res;
    }
#undef ALL
};

int main() {
    BIT<int> bit;
    bit.init(5);

    // add +3 to indices 1..3
    bit.add(0, 3, 3);

    // add +2 to indices 3..5
    bit.add(2, 5, 2);

    cout << "Value at 1 = " << bit.query(1) << "\n"; // expect 3
    cout << "Value at 3 = " << bit.query(3) << "\n"; // expect 3+2=5
    cout << "Value at 5 = " << bit.query(5) << "\n"; // expect 2
}

