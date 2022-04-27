//�����ݣ���nΪ������ʱ����ȡ����
long long fastPow(int base, int n) {
    int ans = 1;
    while (n) {
        if (n & 1)  //����һλΪ1
            ans *= base;
        base *= base;
        n >>= 1;
    }
    return ans;
}
typedef long long LL;
//���ȡģ
LL fastPow(LL a, LL n, LL mod) {
    LL res = 1;
    while (n) {
        if (n & 1)
            res = res * a % mod;
        a = ((a % mod) * (a % mod)) % mod;
        n >>= 1;
    }
    return res % mod;
}

//��һ����ֹ���
//���ٳ�

//a*11=a*2^0 + a*2^1 + a*2^2
LL fastMul(LL a, LL b) {//ԭ����ٳˣ�����mod
    LL res = 0;
    while (b) {
        if (b & 1)
            res += a;
        a += a;
        b >>= 1;
    }
    return res;
}
//ȡģ������
LL fastMul(LL a, LL b, LL mod) {
    LL res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}

LL fastPowMul(LL base, LL n, LL mod) {
    LL res = 1;
    while (n) {
        if (n & 1)
            res = fastMul(res, base, mod);
        base = fastMul(base, base, mod);
        n >>= 1;
    }
    return res % mod;
}


//���������
//�Ƚ������Ŀ����ݣ������ǰ��������˾�������Ӧ������
const int N = 10;
int tmp[N][N];
void multi(int a[][N], int b[][N], int n)
{
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                tmp[i][j] += a[i][k] * b[k][j];

    //���¸�ֵ��a
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = tmp[i][j];
}
int res[N][N];
void Pow(int a[][N], int n)
{
    memset(res, 0, sizeof res);//n���ݣ�N�Ǿ����С
    for (int i = 0; i < N; i++)     //��λ����
        res[i][i] = 1;
    while (n)
    {
        if (n & 1)
            multi(res, a, N);//res=res*a;����ֱ����multi����ʵ���ˣ�
        multi(a, a, N);//a=a*a
        n >>= 1;
    }
}


//21_1_17ÿ��һ��
//1220. ͳ��Ԫ����ĸ���е���Ŀ

//dp
class Solution {
public:
    int countVowelPermutation(int n) {
        long long mod = 1e9 + 7;
        vector<long long> dp(5, 1);
        vector<long long> ndp(5);
        for (int i = 2; i <= n; ++i) {
            /* aǰ�����Ϊe,u,i */
            ndp[0] = (dp[1] + dp[2] + dp[4]) % mod;
            /* eǰ�����Ϊa,i */
            ndp[1] = (dp[0] + dp[2]) % mod;
            /* iǰ�����Ϊe,o */
            ndp[2] = (dp[1] + dp[3]) % mod;
            /* oǰ�����Ϊi */
            ndp[3] = dp[2];
            /* uǰ�����Ϊi,o */
            ndp[4] = (dp[2] + dp[3]) % mod;
            dp = ndp;
        }
        return accumulate(dp.begin(), dp.end(), 0LL) % mod;
    }
};


//���������--------------------------------------
using LL = long long;
using Mat = vector<vector<LL>>;
class Solution {
public:
    Mat multiply(const Mat& matrixA, const Mat& matrixB, LL mod) {
        int m = matrixA.size();
        int n = matrixB[0].size();
        Mat res(m, vector<LL>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < matrixA[i].size(); ++k) {
                    res[i][j] = (res[i][j] + matrixA[i][k] * matrixB[k][j]) % mod;
                }
            }
        }
        return res;
    }

    Mat fastPow(const Mat& matrix, LL n, LL mod) {
        int m = matrix.size();
        Mat res(m, vector<LL>(m, 0));
        Mat curr = matrix;

        //��λ����
        for (int i = 0; i < m; ++i) {
            res[i][i] = 1;
        }

        while (n) {
            if (n & 1)
                res = multiply(curr, res, mod);
            curr = multiply(curr, curr, mod);
            n >>= 1;
        }
        //��
        /*for (int i = n; i != 0; i >>= 1) {
            if (i & 1) {
                res = multiply(curr, res, mod);
            }
            curr = multiply(curr, curr, mod);
        }*/
        return res;
    }

    int countVowelPermutation(int n) {
        LL mod = 1e9 + 7;
        Mat factor =
        {
            {0, 1, 0, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 1},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0}
        };
        Mat res = fastPow(factor, n - 1, mod);
        long long ans = 0;
        for (int i = 0; i < 5; ++i) {
            ans = (ans + accumulate(res[i].begin(), res[i].end(), 0LL)) % mod;
        }
        return  ans;
    }
};
