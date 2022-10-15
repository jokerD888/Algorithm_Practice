// 940. 不同的子序列 II

// 法一：
// dp
// 定义dp[i] 为s[0,i]上不同子序列的个数
// 明显dp[0]=1
// 若字符串中每个字符串均不等我们发现，dp[i]=dp[i-1]*2+1
//      一般情况，若最右往左的一个的字符s[j]与s[i]相等，那么dp[i]=dp[i-1]*2-dp[j-1]-1;
//      减去dp[j-1]是由于若s（j,i)之间的字符都不出现，s[0,j)任意，那么若s[i]和s[j]只出现其一，便会冲突，两个字符串相等
//      所以减去其中的影响，即[0,j)前的所有情况，再-1是考虑每个字符单独出现会重复
class Solution {
public:
    int distinctSubseqII(string s) {
        const int M = 1e9 + 7;
        int N = s.size();
        vector<int> dp(N);
        dp[0] = 1;
        for (int i = 1; i < N; ++i) {
            dp[i] = 2 * dp[i - 1] % M + 1;
            int j = i - 1;
            while (j >= 0 && s[j] != s[i]) --j;
            if (j == 0)
                --dp[i];
            else if (j > 0)
                dp[i] -= dp[j - 1] + 1;
            // 这里需要+M,防止出现负数，因为上面dp[i]模完后，可能较小，而dp[j]可能摸完后比较打，相减为负数
            dp[i] = (dp[i] + M) % M;
        }
        return dp[N - 1];
    }
};


// 法二：
// 或另一种做法
// 定义f[i] 以s[i]为最后一个字符的子序列的个数，f[0]=1
// 如果子序列中至少有两个字符，那么我们可以枚举倒数第二个字符来进行状态转移。
// 容易想到的是:倒数第二个字符可以选择s[0], s[1], …, s[i - 1]中的某一个，这样就可以得到如下的状态转移方程 :
//   f[i] = f[0]＋f[1]＋……f[i - 1]
// 那么如果s[j1]和s[j2]不同，明显f[j1]和f[j2] 有重复项，所以我们需要统计各个字符最后一次出现的位置上的答案
// 每次只需要遍历那26个字符集即可
class Solution {
public:
    int distinctSubseqII(string s) {
        vector<int> last(26, -1);       // 每个字符最后出现的位置

        int n = s.size();
        vector<int> f(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                if (last[j] != -1) {
                    f[i] = (f[i] + f[last[j]]) % mod;
                }
            }
            last[s[i] - 'a'] = i;
        }

        // 最后再统计一遍
        int ans = 0;
        for (int i = 0; i < 26; ++i) {
            if (last[i] != -1) {
                ans = (ans + f[last[i]]) % mod;
            }
        }
        return ans;
    }

private:
    static constexpr int mod = 1000000007;
};


// 对上述的优化版
// 不再记录26个字符出现的位置，而是直接记录字符作为最后出现的答案
class Solution {
public:
    int distinctSubseqII(string s) {
        vector<int> g(26, 0);
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            int total = 1;
            for (int j = 0; j < 26; ++j) {
                total = (total + g[j]) % mod;
            }
            g[s[i] - 'a'] = total;
        }

        int ans = 0;
        for (int i = 0; i < 26; ++i) {
            ans = (ans + g[i]) % mod;
        }
        return ans;
    }

private:
    static constexpr int mod = 1000000007;
};
// 最终优化
// 上述两个版本时间规模都是O(26*N)
// 最终可优化为O(N)版本的
// 上版中由于我们的答案是数组g的和，记s[i]-'a'=o而遍历s[i]后只有g[o]的值发生了变化。
// 因此我们可以使用一个变量total直接维护数组g的和，每次将g[o]的值更新为1＋ total，再将total的值增加g[o]的变化量即可。

class Solution {
public:
    int distinctSubseqII(string s) {
        vector<int> g(26, 0);
        int n = s.size(), total = 0;
        for (int i = 0; i < n; ++i) {
            int oi = s[i] - 'a';
            int prev = g[oi];
            g[oi] = (total + 1) % mod;
            total = ((total + g[oi] - prev) % mod + mod) % mod;
        }
        return total;
    }

private:
    static constexpr int mod = 1000000007;
};


// 242. 有效的字母异位词
// 哈希表，对于字符集大的 unicode同样使用，这里只使用小写
class Solution {
public:
    bool isAnagram(string s, string t) {
        int cnt_s[26]{ 0 }, cnt_t[26]{ 0 };
        int N = t.size(), M = s.size();
        for (int i = 0; i < N; ++i)
            ++cnt_t[t[i] - 'a'];
        for (int j = 0; j < M; ++j)
            ++cnt_s[s[j] - 'a'];

        for (int i = 0; i < 26; ++i) {
            if (cnt_t[i] != cnt_s[i])
                return false;
        }
        return true;
    }
};
