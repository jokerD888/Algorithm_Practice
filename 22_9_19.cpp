// 416. 分割等和子集
// 背包问题
// 先累计总和，若和为奇数，false
// 随后问题就变为了01背包问题，对于每个数都有选和不选两中选择
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int N = nums.size();
        int sum = 0;
        for (int i = 0; i < N; ++i) sum += nums[i];
        if (sum % 2) return false;      // 奇数，无法分配，false
        sum >>= 1;

        // f[i][j] 考虑了前i个，能否凑到j数量
        vector<vector<bool>> f(N + 1, vector<bool>(sum  + 1));
        for (int i = 0; i <= N; ++i) f[i][0] = true;

        for (int index = 1; index <= N; ++index) {
            for (int w = 1; w <= sum; ++w) {
                f[index][w] = f[index - 1][w];// 不选
                if (w - nums[index-1] >= 0)   // 选
                    f[index][w] = f[index][w]| f[index - 1][w - nums[index-1]];

            }
        }
        return f[N][sum];

    }
};

// 优化
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return false;
        }
        int sum = 0, maxNum = 0;
        for (auto& num : nums) {
            sum += num;
            maxNum = max(maxNum, num);
        }
        if (sum & 1) {
            return false;
        }
        int target = sum / 2;
        if (maxNum > target) {
            return false;
        }
        vector<int> dp(target + 1, 0);
        dp[0] = true;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            for (int j = target; j >= num; --j) {
                dp[j] |= dp[j - num];
            }
        }
        return dp[target];
    }
};




// 461. 汉明距离
class Solution {
public:
    int hammingDistance(int x, int y) {
        int res = 0;
        while (x && y) {
            if ((x & 1) != (y & 1)) ++res;
            x >>= 1;
            y >>= 1;
        }
        while (x) {
            if (x & 1)
                ++res;
            x >>= 1;
        }
        while (y) {
            if (y & 1)
                ++res;
            y >>= 1;
        }
        return res;
    }
};
class Solution {
public:
    int hammingDistance(int x, int y) {
        x ^= y;
        int res = 0;
        while (x) {
            if (x & 1) ++res;
            x >>= 1;
        }
        return res;
    }
};

