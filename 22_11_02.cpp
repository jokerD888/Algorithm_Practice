//  剑指 Offer 09. 用两个栈实现队列

// 弹出时两个栈相互倒
class CQueue {
public:
    stack<int> st1, st2;
    int pop_num;
    CQueue() {
        pop_num = 0;
    }

    void appendTail(int value) {
        st1.push(value);
    }

    int deleteHead() {
        if (st1.empty()) return -1;

        while (st1.size()) {
            st2.push(st1.top());
            st1.pop();
        }
        int res = st2.top();
        st2.pop();
        while (st2.size()) {
            st1.push(st2.top());
            st2.pop();
        }
        return res;
    }
};


// 进一步，我们发现
// 若每次弹出都将栈中全部数据倒一遍的话，有很多重复不必要的过程
// 不妨将一个栈当作输入栈，用于压入appendTail传入的数据;另一个栈当作输出栈，用于deleteHead操作。
// 每次deleteead时，若输出栈为空则将输入栈的全部数据依次弹出并压入输出栈，这样输出栈从栈顶往栈底的顺序就是队列从队首往队尾的顺序。


class CQueue {
private:
    stack<int> inStack, outStack;

    void in2out() {
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }

public:
    CQueue() {}

    void appendTail(int value) {
        inStack.push(value);
    }

    int deleteHead() {
        if (outStack.empty()) {
            if (inStack.empty()) {
                return -1;
            }
            in2out();
        }
        int value = outStack.top();
        outStack.pop();
        return value;
    }
};


// 剑指 Offer 10- I. 斐波那契数列

// 迭代
class Solution {
public:
    int fib(int n) {
        if (n < 2) return n;

        int a = 0, b = 1, c;
        const int mod = 1e9 + 7;
        for (int i = 2; i <= n; ++i) {
            c = (a + b) % mod;
            a = b;
            b = c;
        }
        return c;
    }
};


// 矩阵快速幂
// | 1 1| | f(n)  |   -->>    | f(n)+f(n-1) |      -->>  | f(n+1) |  
// | 1 0| | f(n-1)|           |     f(n)    |            |  f(n)  |

// 利用如上递归关系，只要可以快速计算矩阵的n次幂，就可以快速得出答案

class Solution {
public:
    const int MOD = 1000000007;
    int fib(int n) {
        if (n < 2) return n;
        vector<vector<long>> q{ {1,1},{1,0} };
        vector<vector<long>> res = pow(q, n - 1);

        return res[0][0];
    }

    vector<vector<long>> pow(vector<vector<long>>& a, int n) {
        vector<vector<long>> res{ {1,0},{0,1} };    // 单位矩阵
        while (n) {
            if (n & 1)
                res = multiply(res, a);
            n >>= 1;
            a = multiply(a, a);
        }
        return res;
    }

    vector<vector<long>> multiply(vector<vector<long>>& a, vector<vector<long>>& b) {
        vector<vector<long>> res{ {0,0,},{0,0} };
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                res[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j]) % MOD;
            }
        }
        return res;
    }
};




// 剑指 Offer 10- II. 青蛙跳台阶问题

// dp dp[i]=dp[i-1]+dp[i-2] 与斐波那契等同
class Solution {
public:
    int numWays(int n) {
        if (n <= 2) return n;

        int a = 1, b = 2, c;
        const int MOD = 1e9 + 7;
        for (int i = 3; i <= n; ++i) {
            c = a + b;
            a = b;
            b = c;
        }
        return c;
    }
};


// 剑指 Offer 11. 旋转数组的最小数字

// 寻找旋转点
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int n = numbers.size();
        int min_v = numbers[0];
        for (int i = 1; i < n; ++i) {
            if (numbers[i] < numbers[i - 1])
                return numbers[i];
        }
        return min_v;
    }
};

//二分
// 由于给定的数组是升序数组在经过旋转后的数组
// 所以在最小值x右侧的值都大于等于x,左侧的值都小于等于x,所以可以据此进行二分
// 具体的：左右指针l,r指向两端,mid指向中间位置
//  1）nums[mid]<nums[r], 即说明mid在最小值的右边，即r=mid,可以舍去右半边
// 2）num[mid]>nums[r],说明mid在最小值的左边，即l=mid+1,可以舍去左半边
// 3）但nums[mid]==nums[r],由于有重复元素，所以不能确定mid在左侧还是右侧，
//      但我们可以知道，无论nums[r]是不是最小值，都有一个替代品nums[mid]，所以--r;

class Solution {
public:
    int minArray(vector<int>& numbers) {
        int l = 0;
        int r = numbers.size() - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (numbers[mid] < numbers[r]) {
                r = mid;
            } else if (numbers[mid] > numbers[r]) {
                l = mid + 1;
            } else {
                r -= 1;
            }
        }
        return numbers[l];
    }
};
