// 1812. 判断国际象棋棋盘中一个格子的颜色
// 奇偶性相同为黑
class Solution {
public:
    bool squareIsWhite(string coordinates) {
        int x = coordinates[0] - 'a' + 1, y = coordinates[1] - '0';
        return (x & 1) & (y & 1);
    }
};


// 1775. 通过最少操作次数使数组的和相等
// 贪心，和大的数值尽量从6往1弄，和小的从1往6弄，同时每个数可以连续变化具有独立性
class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int cnt1[7]{ 0 }, cnt2[7]{ 0 };
        int sum1 = 0, sum2 = 0;
        int n = nums1.size(), m = nums2.size();
        for (int i = 0; i < n; ++i) {
            ++cnt1[nums1[i]];
            sum1 += nums1[i];
        }
        for (int i = 0; i < m; ++i) {
            ++cnt2[nums2[i]];
            sum2 += nums2[i];
        }
        if (sum1 < sum2) {
            swap(nums1, nums2);
            swap(cnt1, cnt2);
            swap(sum1, sum2);
        }
        int t = sum1 - sum2;
        int res = 0;
        
        for (int i = 5; i > 0 && t>0; --i) {
            int k = min((t+i-1)/ i, cnt2[6 - i] + cnt1[i + 1]);
            res += k;
            t -= k * i;           
        }
        if (t>0) return -1;
        return res;
    }
};
// 或
class Solution {
public:
    int help(vector<int>& h1, vector<int>& h2, int diff) {
        vector<int> h(7, 0);
        for (int i = 1; i < 7; ++i) {
            h[6 - i] += h1[i];
            h[i - 1] += h2[i];
        }
        int res = 0;
        for (int i = 5; i && diff > 0; --i) {
            int t = min((diff + i - 1) / i, h[i]);
            res += t;
            diff -= t * i;
        }
        return res;
    }

    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if (6 * n < m || 6 * m < n) {
            return -1;
        }
        vector<int> cnt1(7, 0), cnt2(7, 0);
        int diff = 0;
        for (auto& i : nums1) {
            ++cnt1[i];
            diff += i;
        }
        for (auto& i : nums2) {
            ++cnt2[i];
            diff -= i;
        }
        if (!diff) {
            return 0;
        }
        if (diff > 0) {
            return help(cnt2, cnt1, diff);
        }
        return help(cnt1, cnt2, -diff);
    }
};