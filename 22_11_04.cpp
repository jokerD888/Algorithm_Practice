// 剑指 Offer 14- I. 剪绳子

// dp

// dp[i]的含义为长度为n的绳子所得到的最大乘积
// 明显dp[1]=0,dp[2]=1
// 对于普遍的dp[i],我们可以尝试和之前所有可能的已计算过的绳子进行组合
//   1）和之前的dp[j]组合， dp[i]=max(dp[i,dp[j]*(i-j)]
//   2) 不和之前的dp组合，枚举第一段的长度，dp[i]=max(dp[i],j*(i-j));

class Solution {
public:
    int cuttingRope(int n) {

        vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            int acc = 0;
            for (int j = 1; j < i; ++j) {
                acc = max({ acc, dp[j] * (i - j) ,j * (i - j) });
            }
            dp[i] = acc;
        }
        return dp[n];
    }
};



// 优化

// 有这样一个事实
// 如果一个最优乘积包含一个因子f>=4，那么你可以用因子2和f-2代替它，而不会失去最优性，因为2*（f-2）=2f-4>=f。
// 所以你永远不需要一个大于或等于4的因子，这意味着你只需要因子1、2和3（当然1是浪费的，你只需要在需要的时候使用它n=2和n=3）。
// 同时3*3比2*2*2好，所以你永远不会使用2超过两次。
// 所以我们拆分得数要么是2要么是3
// 所以可以优化上法为如下形式
// 我们只需要枚举长度2和长度3得组合即可

class Solution {
public:
    int cuttingRope(int n) {
        vector <int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            dp[i] = max({ 2 * (i - 2), 2 * dp[i - 2],3 * (i - 3) ,3 * dp[i - 3] });
        }
        return dp[n];
    }
};


// 法三：最终可以利用数学方法做到 时间O(n),空间O(1)
// 通过上面分析，可知，拆分出来得要么是3要么是2，那么我们可以不断分出3来，最后不足3的乘上即可
// 为什么不分2呢，因为当n等于6，3*3比2*2*2好，所以你永远不会使用2超过两次。

class Solution {
public:
    int cuttingRope(int n) {
        if (n <= 3) return n - 1;
        int res = 1;
        while (n > 4) {
            res *= 3;
            n -= 3;
        }
        return res * n;
    }
};



// 剑指 Offer 14- II. 剪绳子 II

class Solution {
public:
    int cuttingRope(int n) {
        const int MOD = 1e9 + 7;
        if (n <= 3) return n - 1;
        long long res = 1;
        while (n > 4) {
            res = res * 3 % MOD;
            n -= 3;
        }
        return (res * n) % MOD;
    }
};


//剑指 Offer 15. 二进制中1的个数

// 遍历
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        for (; n; n >>= 1) {
            if (n & 1) ++res;
        }
        return res;
    }
};

// 或
// 快速找到最低为的1，再不断消去

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        for (; n; ++res) {
            // n -= n & (-n);      // n&(-n) 是最低为的1表示的数
            // 或
            n &= n - 1;
            // 或
            //n ^= n & (-n);      // 与第一个道理一样
        }
        return res;
    }
};



// 剑指 Offer 16. 数值的整数次方

// 快速幂
// 只需要对指数正负做一些判断即可,不同关系底数的正负，其能正确处理
class Solution {
public:
    double myPow(double x, int n) {
        bool neg_n = false;
        long long m = n;        // 整数的最小值转为正数会溢出，用long long来接收
        if (m < 0) {        // 指数是负数
            neg_n = true;
            m = -m;
        }

        double res = 1;
        for (; m; m >>= 1, x *= x) {
            if (m & 1)
                res *= x;
        }
        return neg_n ? 1 / res : res;
    }
};

// 简化指数的特殊处理


class Solution {
public:
    double quickPow(double x, long long m) {
        double res = 1;
        for (; m; m >>= 1, x *= x) {
            if (m & 1)
                res *= x;
        }
        return res;
    }
    double myPow(double x, int n) {
        long long m = n;
        return m > 0 ? quickPow(x, m) : 1.0 / quickPow(x, -m);
    }
};


// 剑指 Offer 17. 打印从1到最大的n位数

class Solution {
public:
    vector<int> printNumbers(int n) {
        int N = pow(10, n) - 1;
        vector<int> res(N);
        for (int i = 1; i <= N; ++i)
            res[i - 1] = i;
        return res;
    }
};


// 剑指 Offer 18. 删除链表的节点

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* cur = dummy;
        while (cur && cur->next) {
            if (cur->next->val == val) {
                cur->next = cur->next->next;
                break;
            }
            cur = cur->next;
        }
        return dummy->next;
    }
};
// 简洁
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if (head->val == val) return head->next;
        ListNode* cur = head;
        
        // 可以这样判断，因为要删除的一定在表中
        while (cur->next && cur->next->val != val) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        return head;
    }
};

