//  309. 最佳买卖股票时机含冷冻期
// dp[i] 表在0~i-1做无限次买卖，在i位置做买入的最大收益
// sell[i] 表0~i做无限次买卖的最大收益,且最后一次卖出是在i位置
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> buy(n, INT_MIN), sell(n, INT_MIN);
        buy[0] = -prices[0];
        sell[0] = 0;
        for (int i = 1; i < n; ++i) {
            // 找出i位置处卖出的最大收益，枚举最后一次的买入
            for (int j = i - 1; j >= 0; --j)
                sell[i] = max(sell[i], buy[j] + prices[i]);
            // 找出i位置买入的最大收益，枚举最后一次的卖出
            for (int j = i - 2; j >= 0; --j)
                buy[i] = max(buy[i], sell[j] - prices[i]);
            buy[i] = max(buy[i], -prices[i]);
        }
        return *max_element(sell.begin(), sell.end());
    }
};

// 优化
// buy[i] 定义为0~i位置做了无限次交易且最后一次是买入的最大收益
// sell[i] 定义为0~i位置做了无限次交易且最后一次是卖出的最大收益
// 这里就不限制最后一次买卖的位置，为了简化内层的for
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int n = prices.size();
        vector<int> buy(n, 0), sell(n, 0);

        // 很明显我们可以得出前两个位置的信息
        buy[1] = max(-prices[0], -prices[1]);
        sell[1] = max(0, prices[1] - prices[0]);
        for (int i = 2; i < n; ++i) {
            buy[i] = max(buy[i - 1], sell[i - 2] - prices[i]);  // 要么此位置不做处理，要么次位置买入
            sell[i] = max(sell[i - 1], buy[i - 1] + prices[i]); // 要么不做处理，要么卖出
        }
        return sell[n - 1];
    }
};

// 滚动数组，空间优化
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int n = prices.size();
        int buy1 = max(-prices[0], -prices[1]);
        int sell1 = max(0, prices[1] - prices[0]);
        int sell2 = 0;
        for (int i = 2; i < n; ++i) {
            int tmp = sell1;
            sell1 = max(sell1, buy1 + prices[i]);
            buy1 = max(buy1, sell2 - prices[i]);
            sell2 = tmp;
        }
        return sell1;
    }
};



// 338. 比特位计数

// 直接法
class Solution {
public:
    int getbits(int n) {
        int res = 0;
        while (n) {
            if (n & 1) ++res;
            n >>= 1;
        }
        return res;
    }
    vector<int> countBits(int n) {
        vector<int> res(n + 1);
        for (int i = 1; i <= n; ++i) {
            res[i] = getbits(i);
        }
        return res;
    }
};


// 动态规划 ，最高有效位
// 如果bits[i]已知，且j的二进制位数比i多一个的话，就可以通过bits[i]得到，bits[j]=bits[i]+1
// 那么对于一个普遍的j，i该如何寻找呢，我们只要将j减去其最高的二机制位上的1，得到的就是i
// 对于最高位上的1，high_bit可以用(j & j- 1) == 0来检查，且high_bit可以通过迭代了获得,不必对每一个j,算其最高位
class Solution {
public:
   
    vector<int> countBits(int n) {
        vector<int> res(n + 1);
        int high_bit = 0;
        for (int i = 1; i <= n; ++i) {
            if ((i & i - 1) == 0)   
                high_bit = i;
            res[i] = res[i - high_bit] + 1;
        }
        return res;
    }
};

// 动态规划 ， 最低有效位

// 同理我们也可以通过最低有效位来进行递推
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits(n + 1);
        for (int i = 1; i <= n; i++) {
            bits[i] = bits[i >> 1] + (i & 1);
        }
        return bits;
    }
};

// 动态规划，最低设置位
// 通过 y = x & (x -1)将x的最低位上的1变为0，显然也可以进行递推
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits(n + 1);
        for (int i = 1; i <= n; i++) {
            bits[i] = bits[i & (i - 1)] + 1;
        }
        return bits;
    }
};
