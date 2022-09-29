// 69. x 的平方根 
// 二分
class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x;
        while (l < r) {
            long long mid = l + r + 1ll >> 1;
            if (mid * mid <= x) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        return l;
    }
};

// 91. 解码方法


class Solution {
public:
    int numDecodings(string s) {
        int N = s.size();
        vector<int> dp(N+1);  // 字符串s前i个字符的解码方案数
        dp[0]=1;     // base case   没有任何字符
        if (s[0] != '0') dp[1] = 1;       // 首字母不能为0
        for (int i = 2; i <= N; ++i) {
            char prev = s[i - 2], cur = s[i - 1];
            if (cur == '0') {       // 0只能和前面的一起构造
                if (prev == '1' || prev == '2') dp[i] += dp[i - 2];
                else return 0;      // 非法
            } else {
                dp[i] = dp[i - 1];      // 单独构造
                // 和前面的一同构造
                if (prev == '1' || prev == '2' && cur <= '6') {
                    dp[i] += dp[i - 2];
                }
            }
        }
        return dp[N];
    }
};
// 或
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> f(n + 1);
        f[0] = 1;
        for (int i = 1; i <= n; ++i) {
            if (s[i - 1] != '0') {
                f[i] += f[i - 1];
            }
            if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
                f[i] += f[i - 2];
            }
        }
        return f[n];
    }
};
//注意到在状态转移方程中，f[i]仅与f[i-1]和f[i-2]有关，因此我们可以使用三个变量进行状态转移，省去数组的空间。
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        // a = f[i-2], b = f[i-1], c = f[i]
        int a = 0, b = 1, c;
        for (int i = 1; i <= n; ++i) {
            c = 0;
            if (s[i - 1] != '0') {
                c += b;
            }
            if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
                c += a;
            }
            tie(a, b) = { b, c };
        }
        return c;
    }
};
