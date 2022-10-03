//132. 分割回文串 II
// 分割部分=分割次数+1
// dp[i] ： 字符串s从i位置开始及其往后的字符串符合要求的最少分割部分
// 具体的：
//  若i~j是个回文串，那么dp[i]=min(dp[i],dp[j+1]),我们需要从(i,N)枚举j
// 但加上判断i~j是否是回文串需要O(N)，总体是O(N^3)
// 可以预先处理一个二维数组checkMap[i][j]来判断[i,j]上的字符串是否是回文串
//      明显，对角线上的都为true,如果对角线上移一行的位置上的字符等于对角上的字符，为true,即s[i][i]==s[i][j+1]

class Solution {
public:
    int minCut(string s) {
        if (s.empty() || s.size() < 2) return 0;
        int N = s.size();
        auto checkMap = createCheckMap(s, N);
        vector<int> dp(N + 1);
        dp[N] = 0;
        for (int i = N - 1; i >= 0; --i) {      // 从右往左
            int next = INT_MAX;
            for (int j = i; j < N; ++j) {
                if (checkMap[i][j]) {   // [i，j]上是回文
                    next = min(next, dp[j + 1]);
                }
            }
            dp[i] = 1 + next;

        }
        return dp[0] - 1;
    }
    vector<vector<bool>> createCheckMap(string str, int N) {
        vector<vector<bool>> res(N, vector<bool>(N));
        // base case
        for (int i = 0; i < N - 1; ++i) {
            res[i][i] = true;
            res[i][i + 1] = str[i] == str[i + 1];
        }
        res[N - 1][N - 1] = true;
        // 两边字符串相同，且中间是回文串
        for (int i = N - 3; i >= 0; --i) {
            for (int j = i + 2; j < N; ++j) {
                res[i][j] = str[i] == str[j] && res[i + 1][j - 1];
            }
        }
        return res;
    }
};

// 或
// f[i] 定义为[0,i]上的结果
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<int>> g(n, vector<int>(n, true)); // 默认全true

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                g[i][j] = (s[i] == s[j]) && g[i + 1][j - 1];
            }
        }

        vector<int> f(n, INT_MAX);
        for (int i = 0; i < n; ++i) {
            if (g[0][i]) {
                f[i] = 0;
            } else {
                for (int j = 0; j < i; ++j) {
                    if (g[j + 1][i]) {
                        f[i] = min(f[i], f[j] + 1);
                    }
                }
            }
        }

        return f[n - 1];
    }
};


// 若要返回最小切割数切成的字符串：
class Solution {
public:
    string minCut(string s) {
        if (s.empty() || s.size() < 2) return 0;
        int N = s.size();
        auto checkMap = createCheckMap(s, N);
        vector<int> dp(N + 1);
        dp[N] = 0;
        for (int i = N - 1; i >= 0; --i) {      // 从右往左
            int next = INT_MAX;
            for (int j = i; j < N; ++j) {
                if (checkMap[i][j]) {   // [i，j]上是回文
                    next = min(next, dp[j + 1]);
                }
            }
            dp[i] = 1 + next;

        }
        string ans;
        for (int i = 0, j = 1; j <= N; ++j) {
            if (checkMap[i][j - 1] && dp[i] == dp[j] + 1) {
                ans += s.substr(i, j - i);
                i = j;
            }
        }
        return ans;
    }
    vector<vector<bool>> createCheckMap(string str, int N) {
        vector<vector<bool>> res(N, vector<bool>(N));
        // base case
        for (int i = 0; i < N - 1; ++i) {
            res[i][i] = true;
            res[i][i + 1] = str[i] == str[i + 1];
        }
        res[N - 1][N - 1] = true;
        // 两边字符串相同，且中间是回文串
        for (int i = N - 3; i >= 0; --i) {
            for (int j = i + 2; j < N; ++j) {
                res[i][j] = str[i] == str[j] && res[i + 1][j - 1];
            }
        }

        return res;
    }
};

// 若要返回所有可能的分割结果
// 131. 分割回文串
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        if (s.empty() || s.size() < 2) {
            res.push_back(vector<string>(1, s));
        } else {
            int N = s.size();
            vector<vector<bool>> checkMap = createCheckMap(s, N);
            vector<int> dp(N + 1);
            dp[N] = 0;
            for (int i = N - 1; i >= 0; --i) {      // 从右往左
                int next = INT_MAX;
                for (int j = i; j < N; ++j) {
                    if (checkMap[i][j]) {   // [i，j]上是回文
                        next = min(next, dp[j + 1]);
                    }
                }
                dp[i] = 1 + next;

            }
            vector<string> ss;
            process(s, 0, 1, checkMap, dp, ss, res);
        }
        return res;
    }
    void process(string& s, int i, int j, vector<vector<bool>>& checkMap, vector<int>& dp,
        vector<string>& path, vector<vector<string>>& res) 
    {
        if (j == s.size()) {
            if (checkMap[i][j - 1] && dp[i] == dp[j] + 1) {
                path.push_back(s.substr(i, j - i));
                res.push_back(path);
                path.pop_back();
            }
        } else {
            if (checkMap[i][j - 1]) {       // [i,j)上的是回文串
                path.push_back(s.substr(i, j - i));     // 添加
                process(s, j, j + 1, checkMap, dp, path, res);
                path.pop_back();
            }
            process(s, i, j + 1, checkMap, dp, path, res);
        }
    }
    vector<vector<bool>> createCheckMap(string str, int N) {
        vector<vector<bool>> res(N, vector<bool>(N));
        // base case
        for (int i = 0; i < N - 1; ++i) {
            res[i][i] = true;
            res[i][i + 1] = str[i] == str[i + 1];
        }
        res[N - 1][N - 1] = true;
        // 两边字符串相同，且中间是回文串
        for (int i = N - 3; i >= 0; --i) {
            for (int j = i + 2; j < N; ++j) {
                res[i][j] = str[i] == str[j] && res[i + 1][j - 1];
            }
        }

        return res;
    }
};

// 或较暴力做法
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        backtrack(s, res, {});
        return res;
    }
    void backtrack(string s, vector<vector<string>>& res, vector<string> path) {
        if (s.size() == 0) {
            res.push_back(path);
            return;
        }
        for (int i = 1; i <= s.size(); i++) {
            string pre = s.substr(0, i);
            if (isPalindrome(pre)) {
                path.push_back(pre);
                backtrack(s.substr(i), res, path);
                path.pop_back();
            }
        }
    }
    bool isPalindrome(string s) {
        if (s.size() == 0) return true;
        int start = 0, end = s.size() - 1;
        while (start <= end) {
            if (s[start] != s[end])
                return false;
            start++;
            end--;
        }
        return true;
    }
};
