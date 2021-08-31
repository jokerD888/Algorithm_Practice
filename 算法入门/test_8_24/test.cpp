//动态规划
#include<iostream>
using namespace std;
#include<vector>
//70. 爬楼梯

//法一，斐波那契数列
class Solution {
public:
    int climbStairs(int n) {
        int count = fib_n(n);
        return count;
    }
    int fib_n(int n)
    {
        int a = 0, b = 1;
        while (n--)
        {
            int tmp = b;
            b = a + b;
            a = tmp;
        }
        return b;
    }
};
//时间复杂度O(N)
//空间复杂度O(1)

//或官解斐波那契公式
class Solution {
public:
    int climbStairs(int n) {
        double sqrt_5 = sqrt(5);
        double fib_n = pow((1 + sqrt_5) / 2, n +1) - pow((1 - sqrt_5) / 2,n+1);
        return (int)(fib_n / sqrt_5);
    }
};
//时间复杂度O(1)
//空间复杂度O(1)


//动态规划
//优化版递归斐波那契
//假设现已在第n阶台阶上，那么它的上一步要么是跳了一阶要么是跳了两阶，依次往前类推，可以得出公式如下(还是斐波那契数列定义）
//f(x)=f(x-1)+f(x-2)，如果之间按此公式进行递归，会出现大量冗余的计算，导致超时，为此，要对其进行优化
class Solution {
public:
    int climbStairs(int n) {
        
        return (int)Fib(1,1,n);
    }
    long Fib(long a,long b,long n)
    {
        if (n >= 2)
            return Fib(a + b, a, n - 1);//将本次计算的结果和上次计算的结果作为参数传入下一次计算中，以减少重复计算
        return a;
    }
        
    
};

//官解动态规划
//还是非递归斐波那契
class Solution {
public:
    int climbStairs(int n) {
        int p = 0, q = 0, r = 1;
        for (int i = 1; i <= n; ++i) {
            p = q;
            q = r;
            r = p + q;
        }
        return r;
    }
};
//时间复杂度O(N)
//空间复杂度O(1)

//官解
//方法二：矩阵快速幂
class Solution {
public:
    vector<vector<long long>> multiply(vector<vector<long long>>& a, vector<vector<long long>>& b) {
        vector<vector<long long>> c(2, vector<long long>(2));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return c;
    }

    vector<vector<long long>> matrixPow(vector<vector<long long>> a, int n) {
        vector<vector<long long>> ret = { {1, 0}, {0, 1} };
        while (n > 0) {
            if ((n & 1) == 1) {
                ret = multiply(ret, a);
            }
            n >>= 1;
            a = multiply(a, a);
        }
        return ret;
    }

    int climbStairs(int n) {
        vector<vector<long long>> ret = { {1, 1}, {1, 0} };
        vector<vector<long long>> res = matrixPow(ret, n);
        return res[0][0];
    }
};

//时间复杂度O(logN)
//空间复杂度O(1)


//198. 打家劫舍
//动态规划
//S[i]=max(S[i-1],S[i-2]+nums[i])
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty())
            return 0;
        int size = nums.size();
        if (size == 1)
        {
            return nums[0];
        }
        int first = nums[0], second = max(nums[0],nums[1]);
        for (int i = 2; i < size; i++)
        {
            int tmp = second;
            second = max(second, first + nums[i]);
            first = tmp;
        }
        return second;
    }
};
//时间复杂度O(n)
//空间复杂度O(1)