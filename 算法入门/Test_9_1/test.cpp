//位运算
#include<iostream>
using namespace std;
#include<algorithm>
//231. 2 的幂
//n& n - 1可以把n最低位的1变0,而当n & n-1 == 0时，则说明n只有一个1。
//66
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;//注意运算优先级
    }
};
//n & (-n) 可以直接获取 nn 二进制表示的最低位的 1。
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (-n)) == n;
    }
};

//判断是否为最大 2 的幂的约数
class Solution {
private:
    static constexpr int BIG = 1 << 30;//规定范围内的最大2次幂

public:
    bool isPowerOfTwo(int n) {
        return n > 0 && BIG % n == 0;
    }
};


//位1的个数
//...
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int num=0;
        while (n)
        {
            if (n & 1)
                num++;
            n=n >> 1;
        }
        return num;

    }
};
//类似
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ret = 0;
        for (int i = 0; i < 32; i++) {
            if (n & (1 << i)) {
                ret++;
            }
        }
        return ret;
    }
};

//利用n& n - 1可以把n最低位的1变0，变了几次，就有几个0；
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ret = 0;
        while (n) {
            n &= n - 1;
            ret++;
        }
        return ret;
    }
};


//190. 颠倒二进制位

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;
        for (int i = 0; i < 32; i++)
        {
            result <<= 1;

            if (n & 1 << i)
            {
                result += 1;
            }

        }
        return result;
    }
};
//或while
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;
        int i = 32;
        while (i--)
        {
            result <<= 1;
            result += n & 1;
            n >>= 1;
        }
        return result;
    }
};
//官解类似
//逐位颠倒
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t rev = 0;
        for (int i = 0; i < 32 && n > 0; ++i) {
            rev |= (n & 1) << (31 - i);//用了按位或运算，也是较为巧妙
            n >>= 1;
        }
        return rev;
    }
};

//位运算分治
class Solution {
private:
    const uint32_t M1 = 0x55555555; // 01010101010101010101010101010101
    const uint32_t M2 = 0x33333333; // 00110011001100110011001100110011
    const uint32_t M4 = 0x0f0f0f0f; // 00001111000011110000111100001111
    const uint32_t M8 = 0x00ff00ff; // 00000000111111110000000011111111

public:
    uint32_t reverseBits(uint32_t n) {
        //注意运算符优先级
        n = n >> 1 & M1 | (n & M1) << 1;//每2位中低1位和高1位交换
        n = n >> 2 & M2 | (n & M2) << 2;//每4位中低2位和高2位交换
        n = n >> 4 & M4 | (n & M4) << 4;//每8位中低4位和高4位交换
        n = n >> 8 & M8 | (n & M8) << 8;//每16位中低8位和高8位交换
        //或这样更符合分治的理解
        //n = n >> 8 & M8 | (n & M8) << 8;//每16位中低8位和高8位交换
        //n = n >> 4 & M4 | (n & M4) << 4;//每8位中低4位和高4位交换
        //n = n >> 2 & M2 | (n & M2) << 2;//每4位中低2位和高2位交换
        //n = n >> 1 & M1 | (n & M1) << 1;//每2位中低1位和高1位交换


        return n >> 16 | n << 16;
    }
};


int main()
{
    Solution s;
    cout<<s.reverseBits(00000000000000000000000000001011);
    return 0;
}
