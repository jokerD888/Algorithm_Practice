
// 1124. 表现良好的最长时间段

// 贪心 前缀和 单调栈
// 记大于8的为1，否则为-1，那么原问题可以看做求解区间分数和大于 0 的最长区间长度。
// 使用前缀和来处理区间上的分数和
// 至此我们只需要求出最长的一段区间[l,r]使得s[r]-s[l]>0，我们固定r,目标是找到最小的一个l,使得s[l]<s[r]，倘若有l1<l2,且s[l1]<=s[l2]，那么l1要比l2更优
// 因此，使用一个栈来维护，自顶向下递减
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        vector<int> s(n + 1);
        stack<int> stk;
        stk.push(0);
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
            if (s[stk.top()] > s[i]) {      // 递减
                stk.push(i);
            }
        }

        int res = 0;
        for (int r = n; r >= 1; --r) {      // 从右往左找右端点
            while (stk.size() && s[stk.top()] < s[r]) {     // 不断弹出栈找最左端点
                res = max(res, r - stk.top());
                stk.pop();
            }
        }

        return res;
    }
};


// 前缀和 哈希表
// 与上面的一样使用前缀和，不同的是我们使用哈希表来记录每一个前缀和第一次出现的位置
// 从左往右遍历，若前缀和s>0,自然当前最大长度为i+1
//      若s<0,因为分数都是1或-1，具有连续性，那么就找到哈希表前面存的前缀和s-1即是当前最大长度
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        unordered_map<int, int> ump;
        int s = 0, res = 0;
        for (int i = 0; i < n; ++i) {
            s += hours[i] > 8 ? 1 : -1;
            if (s > 0) {        // 前缀和大于0，那么自然当年最大长度为i+1
                res = max(res, i + 1);
            } else {            // 否则，找前面是否有一个位置j上的s[j]=s-1，之所以可以这样判断是因为本题中的分数只有1或者-1
                if (ump.count(s - 1)) {
                    res = max(res, i - ump[s - 1]);
                }
            }
            if (!ump.count(s)) {
                ump[s]=i;
            }
        }
        return res;
    }
};
