//��̬�滮
#include<iostream>
using namespace std;
#include<vector>
//70. ��¥��

//��һ��쳲���������
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
//ʱ�临�Ӷ�O(N)
//�ռ临�Ӷ�O(1)

//��ٽ�쳲�������ʽ
class Solution {
public:
    int climbStairs(int n) {
        double sqrt_5 = sqrt(5);
        double fib_n = pow((1 + sqrt_5) / 2, n +1) - pow((1 - sqrt_5) / 2,n+1);
        return (int)(fib_n / sqrt_5);
    }
};
//ʱ�临�Ӷ�O(1)
//�ռ临�Ӷ�O(1)


//��̬�滮
//�Ż���ݹ�쳲�����
//���������ڵ�n��̨���ϣ���ô������һ��Ҫô������һ��Ҫô���������ף�������ǰ���ƣ����Եó���ʽ����(����쳲��������ж��壩
//f(x)=f(x-1)+f(x-2)�����֮�䰴�˹�ʽ���еݹ飬����ִ�������ļ��㣬���³�ʱ��Ϊ�ˣ�Ҫ��������Ż�
class Solution {
public:
    int climbStairs(int n) {
        
        return (int)Fib(1,1,n);
    }
    long Fib(long a,long b,long n)
    {
        if (n >= 2)
            return Fib(a + b, a, n - 1);//�����μ���Ľ�����ϴμ���Ľ����Ϊ����������һ�μ����У��Լ����ظ�����
        return a;
    }
        
    
};

//�ٽ⶯̬�滮
//���Ƿǵݹ�쳲�����
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
//ʱ�临�Ӷ�O(N)
//�ռ临�Ӷ�O(1)

//�ٽ�
//�����������������
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

//ʱ�临�Ӷ�O(logN)
//�ռ临�Ӷ�O(1)


//198. ��ҽ���
//��̬�滮
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
//ʱ�临�Ӷ�O(n)
//�ռ临�Ӷ�O(1)