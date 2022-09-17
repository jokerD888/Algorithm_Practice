// 1143. 最长公共子序列

// 暴力
// process(s1,s2,i,j)含义为s1[0..i],s2[0..j]字符串的最长公共子序列
class Solution {
public:
    int process(string& s1, string& s2, int i, int j) {
        if (i == 0 && j == 0) {             // s1只有1个，s2只有一个
            if (s1[i] == s2[j]) return 1;
            return 0;
        } else if (i == 0) {            // s1只有1个
            if (s1[i] == s2[j]) return 1;
            else return process(s1, s2, i, j - 1);
        } else if (j == 0) {        // s2只有1个
            if (s1[i] == s2[j]) return 1;
            else return process(s1, s2, i - 1, j);
        } else {                    // 普遍的i和j
            int p1 = process(s1, s2, i - 1, j);     // 不以i结尾，可能以j结尾
            int p2 = process(s1, s2, i, j - 1);     // 不以j结尾，可能以i结尾
            int p3 = s1[i] == s2[j] ? 1 + process(s1, s2, i - 1, j - 1) : 0;    // 同时以i和j结尾
            return max({ p1,p2,p3 });
        }
    }
    int longestCommonSubsequence(string text1, string text2) {
        if (text2.size() == 0 || text1.size() == 0) return 0;
        return process(text1, text2, text1.size() - 1, text2.size() - 1);
    }

};

// 缓存
class Solution {
public:
    vector<vector<int>> dp;
    int process(string& s1, string& s2, int i, int j) {
        if (dp[i][j]) return dp[i][j];
        if (i == 0 && j == 0) {             // s1只有1个，s2只有一个
            if (s1[i] == s2[j]) dp[i][j] = 1;
        } else if (i == 0) {            // s1只有1个
            if (s1[i] == s2[j]) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = process(s1, s2, i, j - 1);
            }
        } else if (j == 0) {        // s2只有1个
            if (s1[i] == s2[j]) {
                dp[i][j] = 1;
            } else {
                dp[i][j]= process(s1, s2, i - 1, j);
            }
        } else {                    // 普遍的i和j
            int p1 = process(s1, s2, i - 1, j);     // 不以i结尾，可能以j结尾
            int p2 = process(s1, s2, i, j - 1);     // 不以j结尾，可能以i结尾
            int p3 = s1[i] == s2[j] ? 1 + process(s1, s2, i - 1, j - 1) : 0;    // 同时以i和j结尾
            dp[i][j] = max({ p1,p2,p3 });
        }
        return dp[i][j];
    }
    int longestCommonSubsequence(string text1, string text2) {
        if (text2.size() == 0 || text1.size() == 0) return 0;
        dp.resize(text1.size(), vector<int>(text2.size()));
        return process(text1, text2, text1.size() - 1, text2.size() - 1);
    }

};


// 动态规划

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(n, vector<int>(m));

        if (text1[0] == text2[0]) dp[0][0] = 1;
        for (int i = 1; i < m; ++i)
            dp[0][i] = text1[0] == text2[i] ? 1 : dp[0][i - 1];
        for (int i = 1; i < n; ++i)
            dp[i][0]= text1[i] == text2[0]?1: dp[i - 1][0];

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                int p1 = dp[i][j - 1];
                int p2 = dp[i - 1][j];
                int p3 = text1[i] == text2[j] ? 1 + dp[i - 1][j - 1] : 0;
                dp[i][j] = max({ p1,p2,p3 });
            }
        }
        return dp[n - 1][m - 1];
    }
};


// 448. 找到所有数组中消失的数字

// 暴力枚举
// 数组的规模1e5,可以枚举
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int N = nums.size();
        vector<bool> vis(N + 1);
        for (int i = 0; i < N; ++i) vis[nums[i]] = true;
        vector<int> res;
        for (int i = 1; i <= N; ++i) if (!vis[i]) res.push_back(i);
        return res;
    }
};
// O(1)空间
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int N = nums.size();
        for (auto num : nums) {
            int x = (num - 1)%N;
            nums[x] += N;
        }
        vector<int> res;
        for (int i = 0; i < N; ++i) if (nums[i] <= N) res.push_back(i + 1);
        return res;
    }
};
