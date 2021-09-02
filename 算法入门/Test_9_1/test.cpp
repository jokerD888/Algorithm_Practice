//λ����
#include<iostream>
using namespace std;
#include<algorithm>
//231. 2 ����
//n& n - 1���԰�n���λ��1��0,����n & n-1 == 0ʱ����˵��nֻ��һ��1��
//66
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;//ע���������ȼ�
    }
};
//n & (-n) ����ֱ�ӻ�ȡ nn �����Ʊ�ʾ�����λ�� 1��
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (-n)) == n;
    }
};

//�ж��Ƿ�Ϊ��� 2 ���ݵ�Լ��
class Solution {
private:
    static constexpr int BIG = 1 << 30;//�涨��Χ�ڵ����2����

public:
    bool isPowerOfTwo(int n) {
        return n > 0 && BIG % n == 0;
    }
};


//λ1�ĸ���
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
//����
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

//����n& n - 1���԰�n���λ��1��0�����˼��Σ����м���0��
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


//190. �ߵ�������λ

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
//��while
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
//�ٽ�����
//��λ�ߵ�
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t rev = 0;
        for (int i = 0; i < 32 && n > 0; ++i) {
            rev |= (n & 1) << (31 - i);//���˰�λ�����㣬Ҳ�ǽ�Ϊ����
            n >>= 1;
        }
        return rev;
    }
};

//λ�������
class Solution {
private:
    const uint32_t M1 = 0x55555555; // 01010101010101010101010101010101
    const uint32_t M2 = 0x33333333; // 00110011001100110011001100110011
    const uint32_t M4 = 0x0f0f0f0f; // 00001111000011110000111100001111
    const uint32_t M8 = 0x00ff00ff; // 00000000111111110000000011111111

public:
    uint32_t reverseBits(uint32_t n) {
        //ע����������ȼ�
        n = n >> 1 & M1 | (n & M1) << 1;//ÿ2λ�е�1λ�͸�1λ����
        n = n >> 2 & M2 | (n & M2) << 2;//ÿ4λ�е�2λ�͸�2λ����
        n = n >> 4 & M4 | (n & M4) << 4;//ÿ8λ�е�4λ�͸�4λ����
        n = n >> 8 & M8 | (n & M8) << 8;//ÿ16λ�е�8λ�͸�8λ����
        //�����������Ϸ��ε����
        //n = n >> 8 & M8 | (n & M8) << 8;//ÿ16λ�е�8λ�͸�8λ����
        //n = n >> 4 & M4 | (n & M4) << 4;//ÿ8λ�е�4λ�͸�4λ����
        //n = n >> 2 & M2 | (n & M2) << 2;//ÿ4λ�е�2λ�͸�2λ����
        //n = n >> 1 & M1 | (n & M1) << 1;//ÿ2λ�е�1λ�͸�1λ����


        return n >> 16 | n << 16;
    }
};


int main()
{
    Solution s;
    cout<<s.reverseBits(00000000000000000000000000001011);
    return 0;
}
