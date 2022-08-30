// 287. 寻找重复数
// 快慢指针，类似寻找带环单链表的入环口
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int fast = nums[nums[0]], slow = nums[0];
        while (fast != slow) {
            fast = nums[nums[fast]];
            slow = nums[slow];
        }
        fast = 0;
        while (slow != fast) {
            fast = nums[fast];
            slow = nums[slow];
        }
        return fast;
    }
};


// 二分查找
// 设cnt[i]为数组中小于等于i的个数，假设重复出现的数时target,那么target前cnt[i]<=i,target后cnt[i]>i
// 所以cnt呈递增，可以使用二分枚举答案，找到target这个分界点
// 时间O(NlogN)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int l = 1, r = n - 1, ans = -1;
        while (l < r) {
            int mid = (l + r) >> 1;
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                cnt += nums[i] <= mid;
            }
            if (cnt <= mid) {
                l = mid + 1;
            } else {
                r = mid;
                ans = mid;
            }
        }
        return l;
    }
};


// 二进制
// 利用二进制为上的0和1的个数进行判断
// 我们枚举二进制位上的每一位，对于每一位，统计nums数组（n+1个）中的数组在该二进制位上有1的个数x和1~n这n数在该二进制位上有1的个数y
// 那么重复数上的二进制位上的x一定大于y，至此我们每遍历一个二进制位，就确定了答案数中的一个二进制位
class Solution {
public:
    int findDuplicate(vector<int> nums) {
        int n = nums.size(), ans = 0;
        // 确定二进制下最高位是多少
        int bit_max = 31;
        while (!((n - 1) >> bit_max)) {
            bit_max -= 1;
        }
        for (int bit = 0; bit <= bit_max; ++bit) {
            int x = 0, y = 0;
            for (int i = 0; i < n; ++i) {
                if (nums[i] & (1 << bit)) {     // n个数
                    x += 1;
                }
                if (i >= 1 & i & (1 << bit)) {  // 1~n-1 n-1个数
                    y += 1;
                }
            }
            if (x > y) {
                ans |= 1 << bit;
            }
        }
        return ans;
    }
};



// 300. 最长递增子序列

// 动态规划
// f[i]表以nums[i]结尾的最长递增子序列的长度，
// 我们一次从左往右枚举结尾，结尾定好有，再使用O(N)的时间找到最大的在nums[i]前结尾的
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> f(n, 0);
        f[0] = 1;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) f[i] = max(f[i], f[j]);
            }
            ++f[i];
        }
        int res = 0;
        for (int i = 0; i < n; ++i) res = max(res, f[i]);

        return res;
    }
};


// 贪心+二分
// 上面动态规划的时间复杂度为O(N^2),瓶颈主要在内层的遍历中
// 我们这里使用end[i] 表示递增子序列长度为i+1的结尾最小数字
// 具体流程为：从左往右遍历数组，从end[0~len]中二分大于等于nums[i]的位置，若找的到，更新为nums[i]
// 若找不到，说明nums[i]比end中的数都大，最大递增子序列长度++，nums[i]放在end后面
// 最后len的值即为答案

// 时间O(NlogN)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), len = 0;

        vector<int> f(n, 0), end(n, -1);
        for (int i = 0; i < n; ++i) {
            int l = 0, r = len; // 左闭右开区间
            while (l < r) {
                int mid = l + r >> 1;
                if (end[mid] < nums[i]) l = mid + 1;
                else r = mid;
            }
            if (r == len) {     // 没找到
                end[len++] = nums[i];
            } else {
                end[l] = nums[i];
            }
        }
        return len;
    }
};
