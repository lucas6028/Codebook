class Solution {
public:
    int countSubstrings(string s) {
        int l1 = s.size(), l2 = l1 * 2 + 1;
        string ch = "#";
        for(char c: s) {
            ch = ch + c + "#";
        } 

        int c = 0, r = 0, cnt = 0;
        vector<int> p(l2);
        for(int i = 0; i < l2; i++) {
            p[i] = (i < r)? min(p[2 * c - i], r - i): 1;
            while(i + p[i] < l2 && i - p[i] >= 0 && ch[i + p[i]] == ch[i - p[i]]) p[i]++;
            if(i + p[i] > r) {
                r = i + p[i];
                c = i;
            }
            int l = p[i] - 1;
            if(l % 2 == 0) cnt += l / 2;
            else cnt += l / 2 + 1;
        }
        return cnt;
    }
};