// longest increasing subsequence
int LIS(const vector<int>& s) {
// use binary search to update the smallest element
// that ends in a subsequence of length d
    vector<int> v{};
    v.push_back(s[0]);
    for (int i{1}; i < s.size(); ++i)
        if (s[i] > v.back()) v.push_back(s[i]);
        else *lower_bound(v.begin(), v.end(), s[i]) = s[i];
    return v.size();
}