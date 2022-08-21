// 10. 正则表达式匹配

// 动态规划
// 设dp[i][j]为s字符串以i开始及其往后能否与p字符串以j开始及其往后的字符串进行匹配
// 1） 所s是空串，那么p只能依靠‘*’进行匹配，
//  若p[j+1]!='*'
// 2） (s[i]==p[j] || p[j]=='.') ，i和j能配上，dp[i][j]=dp[i+1][j+1]    
//  若p[j+1]=='*'
// 3)  若当前位置能配成，利用'*'配一个，且后序dp[i+1][j]也成功的话,dp[i][j]=true; 这里为什么只利用‘*’配一个，因为可以利用i+1进行配，因为若两者相同多次配，会有重复部分
//     否则配不成，只能利用‘*’将配不成的消掉，看后序能否配成，dp[i][j]=dp[i][j+2]

// 情况3的第一个分支进一步解释：
// 若利用‘*’可以配多个，那么dp[i][j]=dp[i+1][j+2]||dp[i+2]dp[j+2]||dp[i+3]dp[j+2]....
// 如果i-1和i字母相同的话，dp[i-1][j]=dp[i][j+2]  || dp[i+1]dp[j+2]||dp[i+2][j+2]....
// 可以发现，dp[i-1][j]除了dp[i][j+2]需要考虑，其他后序的就等同于dp[i][j],可以进行替换
// 若i-1和i字母不同，也成立，因为i和i-1只有一个能与j匹配，且只能是i-1和j匹配
//    若i和j匹配，dp[i][j]=dp[i+1][j+2]||dp[i+2]dp[j+2]||dp[i+3]dp[j+2]....
//               dp[i-1][j]=dp[i-1][j+2],只能走到第二分支
//    若i-1和j匹配，dp[i][j]=dp[i][j+2]
//              dp[i-1][j]=dp[i-1][j+2]||dp[i][j+2]=dp[i-1][j+1]||dp[i][j]
//class Solution {
//public:
//    bool isMatch(string s, string p) {
//        bool dp[30][30] = { false };
//        int n = s.size(), m = p.size();
//        dp[s.size()][p.size()] = true;
//        // 情况1）
//        for (int j = m - 1; j >= 0; --j) {
//            dp[n][j] = (j + 1 < m && p[j + 1] == '*') && dp[n][j + 2];
//        }
//
//        for (int i = n - 1; i >= 0; --i)
//            for (int j = m - 1; j >= 0; --j) {
//                // 情况2)
//                if (j == m - 1 || p[j + 1] != '*') {
//                    dp[i][j] = (s[i] == p[j] || p[j] == '.') && dp[i + 1][j + 1];
//                } else {    // 情况3）
//                    if ((s[i] == p[j] || p[j] == '.') && dp[i + 1][j])
//                        dp[i][j] = true;
//                    else
//                        dp[i][j] = dp[i][j + 2];
//                }
//            }
//        return dp[0][0];
//    }
//};



// 12. 整数转罗马数字

// 模拟
//class Solution {
//public:
//    string intToRoman(int num) {
//        int a[]{ 1000,900,500,400,100,90,50,40,10,9,5,4,1 };
//        const char* c[]{ "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" };
//        string res;
//        for (int i = 0; i < 12; ++i) {
//            while (num >= a[i])
//                res += c[i],num-=a[i];
//        }
//        return res;
//    }
//};


// 13. 罗马数字转整数
// 模拟
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> m{ { 'M',1000 }, { 'D',500 }, { 'C',100 }, { 'L',50 }, { 'X',10 }, { 'V',5 }, { 'I',1 } };
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i+1<s.size() && m[s[i]] < m[s[i + 1]]) res -= m[s[i]];
            else res += m[s[i]];
        }
        return res;
    }
};
