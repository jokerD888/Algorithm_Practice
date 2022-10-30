// 784. 字母大小写全排列

class Solution {
public:
    void dfs(string& s, vector<string>& res, int cur) {
        if (cur == s.size()) {
            res.push_back(s);
            return;
        }
        if (isalpha(s[cur])) {
            s[cur] = tolower(s[cur]);
            dfs(s, res, cur + 1);
            s[cur] = toupper(s[cur]);
            dfs(s, res, cur + 1);
        } else {
            dfs(s, res, cur + 1);
        }
    }
    vector<string> letterCasePermutation(string s) {
        vector<string> res;
        dfs(s, res, 0);
        return res;
    }
};
// 或提前跳过数字
class Solution {
public:
    void dfs(string& s, int pos, vector<string>& res) {
        while (pos < s.size() && isdigit(s[pos])) {
            pos++;
        }
        if (pos == s.size()) {
            res.emplace_back(s);
            return;
        }
        s[pos] ^= 32;
        dfs(s, pos + 1, res);
        s[pos] ^= 32;
        dfs(s, pos + 1, res);
    }

    vector<string> letterCasePermutation(string s) {
        vector<string> ans;
        dfs(s, 0, ans);
        return ans;
    }
};

// 1822. 数组元素积的符号

class Solution {
public:
    int arraySign(vector<int>& nums) {
        int res = 1;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] < 0) res = -res;
            if (nums[i] == 0) return 0;
        }
        return res;
    }
};

// 89. 格雷编码

// 法一
// 如果以得到n-1位的格雷码序列G[n-1]，那么我们将G[n-1]对称翻转，得到G[n-1]'
// 然后我们给每个G[n-1]'前面加上2^(n-1)，那么G[n-1]的首元素和G[n-1]'的尾元素只有一位不相同
// 所以G[n]=(G[n-1],G[n-1]')

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ret;
        ret.reserve(1 << n);
        ret.push_back(0);
        for (int i = 1; i <= n; i++) {
            int m = ret.size();
            for (int j = m - 1; j >= 0; j--) {
                ret.push_back(ret[j] | (1 << (i - 1)));
            }
        }
        return ret;
    }
};

// 法二：
// 如果我们有一个二进制数序列，我们也可以将它直接转换成格雷码序列。假设n位二进制数为b,
// 对应的格雷码为g，转换规则如下， ret[i] = (i >> 1) ^ i;

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ret(1 << n);
        for (int i = 0; i < ret.size(); i++) {
            ret[i] = (i >> 1) ^ i;
        }
        return ret;
    }
};
