// 41. 缺失的第一个正数

// 数组改哈希表
// 若没有空间O(1)的限制，我们可以想到使用哈希表将所有数加入其中，然后从1枚举结果
// 那么我们可以把原数组改为哈希表
// 实际上，对于一个长度为 N 的数组，其中没有出现的最小正整数只能在 [1,N+1] 中。
// 我们先把所有负数变为N+1,便于处理。此时所有数皆为正数，
// 若数i出现过，那么我们把nums[i]置为负数，用该位置上的数的正负号来标记该位置数是否出现过
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int& num : nums) {     // 把负数搞为N+1
            if (num <= 0) {
                num = n + 1;
            }
        }
        for (int i = 0; i < n; ++i) {   
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        return n + 1;
    }
};


// 置换
// 另一种直观的方法是，我们让数num放到nums[num-1]上，这样处理之后，只要nums[i]!=i+1,即为结果
// 由于每次的交换操作都会使得某一个数交换到正确的位置，因此交换的次数最多为 N，整个方法的时间复杂度为 O(N)。
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};



// 44. 通配符匹配 
// dp[i][j] 为s字符串以i位置及其往后能够与字符串p以j位置及其往后的字符串进行匹配
// base case: dp[N][M] = true;
// 1) 明显，若s串为空串，只有‘*’可以匹配
// 2）若s[i] == p[j] || p[j]=='?' ，则dp[i][j] = dp[i + 1][j + 1];
// 3）若p[j]='*', dp[i][j] = dp[i][j+1] | dp[i+1][j];
// 
// 对于第三点，'*'可以匹配0到多个，即dp[i][j]=dp[i][j+1] || dp[i+1][j+1] || dp[i+2][j+1] || dp[i+3][j+1]...
// 观察 dp[i-1][j]= dp[i-1][j+1] || dp[i][j+1] || dp[i+1][j+1] ...
// 可以发现 dp[i][j] = dp[i][j+1] | dp[i+1][j];
class Solution {
public:
    bool isMatch(string s, string p) {
        int N = s.size(), M = p.size();
        vector<vector<int>> dp(N+1, vector<int>(M+1,false));
        dp[N][M] = true;    // base case 
        for (int j = M - 1; j >= 0; --j)
            if (p[j] == '*') dp[N][j] = dp[N][j + 1];   // 只有‘*’可以匹配空字符串

        for (int i = N - 1; i >= 0; --i) {
            for (int j = M - 1; j >= 0; --j) {
                if (s[i] == p[j] || p[j]=='?') 
                    dp[i][j] = dp[i + 1][j + 1];
                else if(p[j]=='*')
                    dp[i][j] = dp[i][j+1] | dp[i+1][j];
                
            }
        }
        return dp[0][0];

    }
};
