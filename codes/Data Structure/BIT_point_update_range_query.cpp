// Binary Indexed Tree (Fenwick Tree) for point updates and range queries
// 1-based indexing

template<typename T>
class BIT{
private:
    vector<T> arr;
    int n;
    inline int lowbit(int x) { return x & (-x); }
    T query(int x){
        T ret = 0;
        while(x > 0){
            ret += arr[x];
            x -= lowbit(x);
        }
        return ret;
    }
public:
    void init(int n_){
        n = n_ + 1; // +1 for 1-based indexing
        arr.assign(n, 0);
    }
    void modify(int pos, T v){
        while(pos < n){
          arr[pos] += v;
          pos += lowbit(pos);
        }
    }
    T query(int l, int r){
        // sum of (l, r]
        return query(r) - query(l);
    }
};

int main() {
    int n = 5;
    vector<int> a = {0, 1, 2, 3, 4, 5}; // 1-based array (a[1..5])

    BIT<long long> bit;
    bit.init(n);

    // build BIT
    for (int i = 1; i <= n; i++) {
        bit.modify(i, a[i]);
    }

    // Query sum [1..3]
    cout << "Sum [1..3] = " << bit.query(0, 3) << "\n"; // (0,3] → 1+2+3 = 6

    // Query sum [2..5]
    cout << "Sum [2..5] = " << bit.query(1, 5) << "\n"; // (1,5] → 2+3+4+5 = 14

    // Update: add 10 to position 3
    bit.modify(3, 10);

    // Query sum [1..3] after update
    cout << "Sum [1..3] = " << bit.query(0, 3) << "\n"; // now 1+2+(3+10) = 16
}