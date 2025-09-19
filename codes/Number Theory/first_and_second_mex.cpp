// Calculate first and second MEX
pair<int, int> calculate_mexes(vector<int>& nums) {
    int n = nums.size();
    vector<bool> seen(n + 2, false);

    for (int num : nums) {
        if (num >= 0 && num < seen.size()) {
            seen[num] = true;
        }
    }

    int first_mex = -1;
    int second_mex = -1;

    for (int i = 0; i < seen.size(); ++i) {
        if (!seen[i]) {
            if (first_mex == -1) {
                first_mex = i;
            } else {
                second_mex = i;
                break;
            }
        }
    }

    return {first_mex, second_mex};
}