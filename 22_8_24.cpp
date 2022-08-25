// 72. 编辑距离
 //动态规划
 //dp[i][j]为str1的前i个字符编辑为str2的前j个字符需要的代价
 //对于第0行和第0列明显可以直接得出，一直删除和一直添加
 //对于一般的dp[i][j],共有4种情况可以得到
 //1）由str1前i-1个得到str2前j个，那么对于str[i]直接删除
 //2）由str1前i个得到str2前j-1个，那么还需添加一个
 //3）若str[i]!=str[j]，那么由str1前i-1个得到str2前j-1个，再进行替换
 //4）若相等，那么直接由str1前i-1个得到str2前j-1个
class Solution {
public:
    // 通用性解法，对于添加，删除，替换操作可以赋值不同的代价
    int work(string& word1, string& word2, int a, int d, int r) {
        int n = word1.size(), m = word2.size();
        if (n * m == 0) return n + m;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));

        for (int i = 0; i <= n; ++i) dp[i][0] = i * d;
        for (int i = 1; i <= m; ++i)dp[0][i] = i * a;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = min(dp[i - 1][j] + d, dp[i][j - 1] + a);

                if (word1[i - 1] != word2[j - 1])
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + r);
                else
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            }
        }

        return dp[n][m];
    }
    int minDistance(string word1, string word2) {
        return work(word1, word2, 1, 1, 1);
    }
};


// 76. 最小覆盖子串
// 滑动窗口+哈希表
// 先将t中所有字符入哈希表，哈希表对应字符个数++
// i为滑动窗口的右边界，left为左边界，当i不断向右滑动，知道窗口中字符能覆盖t,此时进行结算，
// 计算过程为，不断缩小左边界，知道窗口中字符不能覆盖t,缩小的同时，不断更新res
// 记cnt为还需覆盖的数量，当cnt为0时，即认为完全覆盖t,使用哈希表的第二关键字记录窗口中所需覆盖字符的数量，
// >0说明该字符还没覆盖够数（因为会有重复元素），<0说明，窗口实际有的该字符数大于t中该字符数
// 时间为O(N),N为s的长度，空间O(M)，M为t的长度
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> map;
        for (auto c : t) {
            ++map[c];
        }

        int n = s.size(), cnt = t.size();
        int left = 0, res_len = 0, res_index = 0;
        for (int i = 0; i < n; ++i) {

            if (map.find(s[i]) != map.end()) {  // 找到一个可以覆盖的字符
                if (map[s[i]] > 0) {   // 这个字符还没覆盖够数
                    --cnt;
                }
                --map[s[i]];
            }
            while (!cnt) {
                if (!res_len || i - left < res_len) {
                    res_len = i - left + 1;
                    res_index = left;
                }
                // 窗口左收缩
                if (map.find(s[left]) != map.end()) {
                    if (map[s[left]] == 0) {
                        ++cnt;
                    }
                    ++map[s[left]];
                }
                ++left;
            }
        }
        return s.substr(res_index, res_len);
    }
};

// 简化版，不再明显进行s中字符是否在t中出现的判断，根据第二关键字进行是否大于0判断，
// 且左窗口向右缩时不用每次都对res进行更新了，左缩完毕后再进行判断即可
// 但由于map的特性，若所查字段不存在就会新建，所以空间上会有增长，可能会达到O(N)
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> map;
        for (auto c : t)  ++map[c];

        int n = s.size(), cnt = t.size(), m = t.size();
        int left = 0, res_len = 0, res_index = 0;
        for (int i = 0; i < n; ++i) {
            if (--map[s[i]] >= 0) --cnt;
            while (0 == cnt && map[s[left]] < 0) ++map[s[left++]];
            if (0 == cnt) 
                if (!res_len || i - left + 1 < res_len)
                    res_len = i - left + 1, res_index = left;
            
        }
        return s.substr(res_index, res_len);
    }
};
