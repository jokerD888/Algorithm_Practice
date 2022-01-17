//快速幂，当n为负数的时候再取倒数
long long fastPow(int base, int n) {
    int ans = 1;
    while (n) {
        if (n & 1)  //若第一位为1
            ans *= base;
        base *= base;
        n >>= 1;
    }
    return ans;
}
typedef long long LL;
//结果取模
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

//进一步防止溢出
//快速乘

//a*11=a*2^0 + a*2^1 + a*2^2
LL fastMul(LL a, LL b) {//原版快速乘，不加mod
    LL res = 0;
    while (b) {
        if (b & 1)
            res += a;
        a += a;
        b >>= 1;
    }
    return res;
}
//取模快速幂
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


//矩阵快速幂
//比较与数的快速幂，不过是把数换成了矩阵做相应的运算
const int N = 10;
int tmp[N][N];
void multi(int a[][N], int b[][N], int n)
{
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                tmp[i][j] += a[i][k] * b[k][j];

    //重新赋值给a
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = tmp[i][j];
}
int res[N][N];
void Pow(int a[][N], int n)
{
    memset(res, 0, sizeof res);//n是幂，N是矩阵大小
    for (int i = 0; i < N; i++)     //单位矩阵
        res[i][i] = 1;
    while (n)
    {
        if (n & 1)
            multi(res, a, N);//res=res*a;复制直接在multi里面实现了；
        multi(a, a, N);//a=a*a
        n >>= 1;
    }
}


//21_1_17每日一题
//1220. 统计元音字母序列的数目

//dp
class Solution {
public:
    int countVowelPermutation(int n) {
        long long mod = 1e9 + 7;
        vector<long long> dp(5, 1);
        vector<long long> ndp(5);
        for (int i = 2; i <= n; ++i) {
            /* a前面可以为e,u,i */
            ndp[0] = (dp[1] + dp[2] + dp[4]) % mod;
            /* e前面可以为a,i */
            ndp[1] = (dp[0] + dp[2]) % mod;
            /* i前面可以为e,o */
            ndp[2] = (dp[1] + dp[3]) % mod;
            /* o前面可以为i */
            ndp[3] = dp[2];
            /* u前面可以为i,o */
            ndp[4] = (dp[2] + dp[3]) % mod;
            dp = ndp;
        }
        return accumulate(dp.begin(), dp.end(), 0LL) % mod;
    }
};


//矩阵快速幂--------------------------------------
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

        //单位矩阵
        for (int i = 0; i < m; ++i) {
            res[i][i] = 1;
        }

        while (n) {
            if (n & 1)
                res = multiply(curr, res, mod);
            curr = multiply(curr, curr, mod);
            n >>= 1;
        }
        //或
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
