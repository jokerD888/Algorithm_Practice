
// 1326. 灌溉花园的最少水龙头数目

// 贪心：
// O（NlogN) 算法瓶颈在快排上
// 将所有点的左右边界计算出来作为一个pair,随后进行排序
// 从左到右遍历排序后的数组，记border为花园未浇的左边界
//  1）若area[i].first > border，所有水龙头的左范围都覆盖不到，return -1
//  2）找出所有可以满足border的水龙头，记录其中最右边界，那么就选那个最右边界的水龙头，border变为max_right，答案数res++
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<pair<int,int>> area(n + 1);
        for (int i = 0; i <= n; ++i) {
            area[i] = { max(0,i - ranges[i]),min(n,i + ranges[i]) };
        }

        sort(area.begin(), area.end());
        int res = 0;
        int border = 0;     // 花园未浇的左边界
        
        for (int i = 0; i <= n;) {
            if (area[i].first > border) return -1;
            int max_right = 0;
            while (i<= n && area[i].first <= border) {
                max_right = max(max_right,area[i].second);
                ++i;
            }
            ++res;
            border = max_right;
            if(border>=n) break;
        }
        if (border < n)
            res = -1;
        return res;
        
    }
};
// 或者类似的动态规划
// O(N(logN+max(ranges)))
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<pair<int, int>> intervals;
        for (int i = 0; i <= n; i++) {
            int start = max(0, i - ranges[i]);
            int end = min(n, i + ranges[i]);
            intervals.emplace_back(start, end);
        }
        sort(intervals.begin(), intervals.end());
        // dp[i] 表示覆盖区间 [0,i] 所需要的最少的区间数目
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (auto [start, end] : intervals) {
            if (dp[start] == INT_MAX) {
                return -1;
            }
            for (int j = start; j <= end; j++) {
                dp[j] = min(dp[j], dp[start] + 1);
            }
        }
        return dp[n];
    }
};


// 贪心优化
// O(N)
// 对于法一，我们实际上不用进行排序，定义一下的数组
// 我们记录以其为左端点的子区间中最远的右端点，记为rightMost[i]。
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<int> rightMost(n + 1);
        iota(rightMost.begin(), rightMost.end(), 0);
        for (int i = 0; i <= n; i++) {
            int start = max(0, i - ranges[i]);
            int end = min(n, i + ranges[i]);
            rightMost[start] = max(rightMost[start], end);
        }
        // last:左端点不大于 i 的所有子区间的最远右端点
        // pre:上一个被使用的子区间的结束位置
        int last = 0, ret = 0, pre = 0;
        for (int i = 0; i < n; i++) {
            last = max(last, rightMost[i]);
            if (i == last) {        // 说明i~i+1这块地将无法被浇灌，-1
                return -1;
            }
            if (i == pre) {
                ret++;
                pre = last;
            }
        }
        return ret;
    }
};



// 2347. 最好的扑克手牌

class Solution {
public:
    string bestHand(vector<int>& ranks, vector<char>& suits) {
        int rank_num[14]{0}, suit_num[4]{0};
        for (auto i : ranks)
            ++rank_num[i];
        for (auto c : suits)
            ++suit_num[c - 'a'];

        int same_rank = 0;       // 相同的个数
        for (int i = 1; i <= 13; ++i)
            same_rank = max(same_rank, rank_num[i]);

        int same_suit = 0;
        for (int i = 0; i < 4; ++i)
            same_suit = max(same_suit, suit_num[i]);

        if (same_suit == 5)
            return "Flush";
        if (same_rank >= 3)
            return "Three of a Kind";
        if (same_rank >= 2)
            return "Pair";
        return "High Card";
       
    }
};