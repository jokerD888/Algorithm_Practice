// 301. 删除无效的括号 
// 递归
// 利用cnt记录括号的状态，从左往右检测，需要左括号+1，右括号-1，当cnt<0,说明出现违规右括号，我们需要在这个违规右括号及其前面的位置删除一个右括号
// 以保证序列的合法性，其中这个过程跳过连续右括号的情况，因为连续的右括号不论删除哪一个结果都相同，所以删除一个即可，
// 每删除一个后，递归调用后缀的子过程，当整条字符串检查完后，我们还需要从右往左再来一遍，因为从左往右检查的右括号的违规情况，还需要检查一遍左括号的
// 每个分支跑完后即为合法序列，且每个序列都不同，最后加入到res集合

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        remove(s, res, 0, 0, "()");
        return res;
    }
    void remove(string s, vector<string>& res, int check_index, int del_index, const char* par) {
        for (int cnt = 0, i = check_index; i < s.size(); ++i) {
            if (s[i] == par[0]) ++cnt;
            if (s[i] == par[1]) --cnt;
            if (cnt < 0) {
                for (int j = del_index; j <= i; ++j) {
                    if (s[j] == par[1] && (j == del_index || s[j - 1] != s[j]))
                        remove(s.substr(0, j) + s.substr(j + 1, s.size() - j), res, i, j, par);
                }
                return;
            }
        }

        reverse(s.begin(), s.end());
        if (par[0] == '(')
            remove(s, res, 0, 0, ")(");
        else
            res.push_back(s);
    }
};


// 312. 戳气球

// 记忆化搜索
// 方便处理，我们先在头尾加上一个值为1的点。每次戳破一个太麻烦，看作添加气球的操作
// solve(i,j) 表示将开区间 (i,j) 内的位置全部填满气球能够得到的最多硬币数
// 每次我们枚举i,j内的全部位置mid,在递归左边右边，这样sokve(i,j)=max(val[i]×val[mid]×val[j]+solve(i,mid)+solve(mid,j))
// 时间O(N^3) 区间数N^2,区间迭代复杂度O(N)
class Solution {
public:
    vector<vector<int>> rec;
    vector<int> val;

public:
    int solve(int left, int right) {
        if (left >= right - 1) {
            return 0;
        }
        if (rec[left][right] != -1) {
            return rec[left][right];
        }
        for (int i = left + 1; i < right; i++) {
            int sum = val[left] * val[i] * val[right];
            sum += solve(left, i) + solve(i, right);
            rec[left][right] = max(rec[left][right], sum);
        }
        return rec[left][right];
    }

    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        val.resize(n + 2);
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i - 1];
        }
        val[0] = val[n + 1] = 1;
        rec.resize(n + 2, vector<int>(n + 2, -1));
        return solve(0, n + 1);
    }
};

// 动态规划
// 按照上法的思路，从自顶向下的记忆化搜索变为自低向上的动态规划
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> rec(n + 2, vector<int>(n + 2));
        vector<int> val(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++) {
            val[i] = nums[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {  // 区间左边界
            for (int j = i + 2; j <= n + 1; j++) {  // 区间右边界
                for (int k = i + 1; k < j; k++) {   // 区间内枚举mid
                    int sum = val[i] * val[k] * val[j];
                    sum += rec[i][k] + rec[k][j];
                    rec[i][j] = max(rec[i][j], sum);
                }
            }
        }
        return rec[0][n + 1];
    }
};

