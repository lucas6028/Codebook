// Calculate the smallest divisor of integers in [2, maxn) in O(maxn)
vector<int> min_div{[] {
    constexpr int maxn = 400000 + 10;

    vector<int> v(maxn), p;

    for (int i = 2; i < maxn; ++i) {
        if (!v[i]) {
            v[i] = i;
            p.push_back(i);
        }
        for (int j = 0; p[j] * i < maxn; ++j) {
            v[p[j] * i] = p[j];
            if (p[j] == v[i]) break;
        }
    }

    return v;
}()};
