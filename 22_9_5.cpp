// 322. 零钱兑换
// 记忆化搜索
// dp(conins,res)含义：对于conins数组，需要凑齐rem所需要的最少硬币数 
class Solution {
    vector<int>count;
    int dp(vector<int>& coins, int rem) {
        if (rem == 0) return 0;
        if (count[rem - 1] != 0) return count[rem - 1];     // 记忆表查过
        int Min = INT_MAX;
        for (int coin : coins) {
            if (rem - coin >= 0) {
                int res = dp(coins, rem - coin);
                if(res!=-1)     // 能凑成的话，进行更新
                    Min = min(Min, res + 1);
            }
        }
        count[rem - 1] = Min == INT_MAX ? -1 : Min;     // 始终无法凑成，-1
        return count[rem - 1];
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 1) return 0;
        count.resize(amount);
        return dp(coins, amount);
    }
};
// 记忆化搜索化为dp
// dp[i]为组成金额i所需要最少硬币数量
// 我们从0~amount考虑每个dp
// 对于每个dp[i]我们考虑选择一个硬币
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {     // 枚举每个金额
            for (int j = 0; j < coins.size(); ++j) {   // 枚举每个硬币
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};



// 518. 零钱兑换 II

// dp[index][amount]含义：index及其往后的位置，凑出amount金额的的方案数
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        dp[n][0] = 1;   // base case, 啥也选不了，凑出0
        for (int index = n - 1; index >= 0; --index) {      // 从后往前推
            for (int rest = 0; rest <= amount; ++rest) {    // 枚举金额
                dp[index][rest] = dp[index + 1][rest];      // index位置不选
                if (rest - coins[index] >= 0) {             // 如果index位置可以选
                    dp[index][rest] += dp[index][rest - coins[index]];
                }
            }
        }
        return dp[0][amount];
    }
};

// 或
// dp[i]为凑i金额的方案数
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1);
        dp[0] = 1;
        for (int& coin : coins) {   // 枚举每个币值
            for (int i = coin; i <= amount; i++) {  // 枚举每个金额
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};