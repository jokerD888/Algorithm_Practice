// 122. 买卖股票的最佳时机 II
// 看作波形图，每次低谷买入，锋顶卖出
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        for (int i = 1; i < prices.size(); ++i) {
            res += max(prices[i] - prices[i - 1], 0);
        }
        return res;
    }
};



// 123. 买卖股票的最佳时机 III

// 在任意一天结束之后，我们会处于以下五个状态中的一种
// 未进行过任何操作；                                                               
// 只进行过一次买操作；                                buy1     
// 进行了一次买操作和一次卖操作，即完成了一笔交易；       sell1
// 在完成了一笔交易的前提下，进行了第二次买操作；        buy2   
// 完成了全部两笔交易                                  sell2

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int buy1 = prices[0], sell1 = 0;
        int buy2 = prices[0], sell2 = 0;
        for (int i = 1; i < n; ++i) {
            buy1 = min(buy1, prices[i]);            // 不做任何操作，或在未进行过任何操作上进行买入
            sell1 = max(sell1, prices[i] - buy1);   // 不做任何操作，或在此处卖出
            buy2 = min(buy2, prices[i] - sell1);    // 不做任何操作，或第二次未买入情况下买入（-sell1是累计第一次买卖的利润）
            sell2 = max(sell2, prices[i] - buy2);   // 不做任何操作，或在此处卖出
        }
        return sell2;
    }
};



// 188. 买卖股票的最佳时机 IV

// 与上一题类似，不过问题变为了多组买卖，上题是本问题的一个子问题
// 我们用bug[i][j]表示对于数组prices[0..i]中的价格而言，进行恰好j笔交易，并且当前手上持有一支股票，这种情况下的最大利润;
// 用sell[i][j]表示恰好进行i笔交易，并且当前手上不持有股票，这种情况下的最大利润。

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int n = prices.size();
        k = min(k, n / 2);
        vector<vector<int>> buy(n, vector<int>(k + 1));
        vector<vector<int>> sell(n, vector<int>(k + 1));

        buy[0][0] = -prices[0];
        sell[0][0] = 0;
        for (int i = 1; i <= k; ++i) {
            buy[0][i] = sell[0][i] = INT_MIN / 2;   // 不合法状态
        }

        for (int i = 1; i < n; ++i) {
            buy[i][0] = max(buy[i - 1][0], sell[i - 1][0] - prices[i]);     // 啥也不干依赖之前的操作，或在此位置进行买入
            for (int j = 1; j <= k; ++j) {
                buy[i][j] = max(buy[i - 1][j], sell[i - 1][j] - prices[i]);     // 啥也不干依赖之前的操作，或此位置进行买入
                sell[i][j] = max(sell[i - 1][j], buy[i - 1][j - 1] + prices[i]);    // 啥也不干依赖之前的操作，或此位置进行卖出
            }
        }

        return *max_element(sell[n - 1].begin(), sell[n - 1].end());        // 返回总共n个时段不同买卖数卖出的最大值
    }
};

// 其中我们可以发现，数组中一维遍历总是i-1，所以可以做状态压缩
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int n = prices.size();
        k = min(k, n / 2);
        vector<int> buy(k + 1);
        vector<int> sell(k + 1);

        buy[0] = -prices[0];
        sell[0] = 0;
        for (int i = 1; i <= k; ++i) {
            buy[i] = sell[i] = INT_MIN / 2; // 不合法状态
        }

        for (int i = 1; i < n; ++i) {
            buy[0] = max(buy[0], sell[0] - prices[i]);
            for (int j = 1; j <= k; ++j) {
                buy[j] = max(buy[j], sell[j] - prices[i]);
                sell[j] = max(sell[j], buy[j - 1] + prices[i]);
            }
        }

        return *max_element(sell.begin(), sell.end());
    }
};

// 或另一种动态规划

// 这里dp的含义不同于上面
// dp[i][j] 表前[0，i）范围上，不超过j组买卖的最大收益，其中状态只有买卖完成这一种
// 明显dp[...][0]=0，dp[0][...]=0，
// 对于一般的dp[i][j],有
//      不做任何操作，依赖前面的i-1个不超过j组买卖的状态，dp[i-1][j]
//      在i位置完成一组买卖，即确定在i位置进行卖出，那么买入的位置就可能是前面的每一个我位置
//          收益就是dp[i-1][j-1]+prices[i]-prices[i-1]，dp[i-2][j-1]+prieces[i]-prices[i-2]，dp[i-3][j-1]+prices[i]-prices[i-3]....
//          把prices[i]提出来，就是max([i-k][j-1]-prices[i-k]) 
//      然后我们看看dp[i+1][j],可以发现，dp[i][j-1]+prices[i+1]-prices[i],  dp[i-1][j-1]+prices[i]-prices[i-1]，dp[i-2][j-1]+prieces[i]-prices[i-2]，dp[i-3][j-1]+prices[i]-prices[i-3]....
//      发现dp[i+1][j]，除开第一项，后面的都可以用dp[i][j]表示，可以使用斜率优化
// 这里是一列一列来的，每个位置依赖上面的。
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size();
        k = min(k, n / 2);
        vector<vector<int>> dp(n, vector<int>(k + 1));
        
        // dp[...][0]=0
        // dp[0][...]=0

        for (int j = 1; j <= k; ++j) {
            int p1 = dp[0][j];
            int best = max(dp[1][j - 1] - prices[1], dp[0][j - 1] - prices[0]);
            dp[1][j] = max(dp[0][j], best + prices[1]);

            for (int i = 2; i < n; ++i) {
                p1 = dp[i - 1][j];  // 不做任何操作依赖前面的操作
                int newP = dp[i][j - 1] - prices[i];    // 本次买入
                best = max(newP, best);
                dp[i][j] = max(p1, best + prices[i]);
            }

        }
        return dp[n - 1][k];
    }
};
