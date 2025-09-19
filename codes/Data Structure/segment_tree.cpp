// Segment tree
template<typename value_t, class merge_t>
class SGT {
    int n;
    vector<value_t> t;
    value_t defa;
    merge_t merge;
public:
    explicit SGT(int _n, value_t _defa, const merge_t& _merge = merge_t{})
        : n{_n}, t(2 * n), defa{_defa}, merge{_merge} {}

    void modify(int p, const value_t& x) {
        for (t[p += n] = x; p > 1; p >>= 1)
            t[p >> 1] = merge(t[p], t[p ^ 1]);
    }

    value_t query(int l, int r) { return query(l, r, defa); }

    value_t query(int l, int r, value_t init) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) init = merge(init, t[l++]);
            if (r & 1) init = merge(init, t[--r]);
        }
        return init;
    }
};

// Custom merge for range minimum + index
struct MergeMin {
    pair<int, int> operator()(const pair<int, int>& a,
                              const pair<int, int>& b) const {
        if (a.first != b.first) return (a.first < b.first) ? a : b;
        return (a.second < b.second) ? a : b; // tie-break on index
    }
};

int main() {
    int n = 6;
    SGT<pair<int, int>, MergeMin> tree(n, {INT_MAX, -1});

    vector<int> a = {5, 3, 6, 1, 4, 2};
    for (int i = 0; i < n; ++i)
        tree.modify(i, {a[i], i});

    auto [min_val, min_idx] = tree.query(1, 5); // range [1, 5)
    cout << "Min value in [1, 5): " << min_val << ", at index " << min_idx << '\\n';

    return 0;
}