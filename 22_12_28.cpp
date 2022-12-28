
// 278. 数字组合

//  01背包问题
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 10010;

// int f[N][M];        // f[i][j]表前i个数已经确定了，目前凑到了重量j的方案数
int f[M];
int n, m;
int a[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    //f[0][0] = 1;
    //for (int i = 1; i <= n; ++i)
    //    for (int j = 0; j <= m; ++j) {      // 注意j从0开始
    //        // 当前第i个物品选
    //        if (j >= a[i]) f[i][j] += f[i - 1][j - a[i]];
    //        // 不选
    //        f[i][j] += f[i - 1][j];
    //    }    

    //cout << f[n][m] << endl;

   // 滚动数组
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= a[i]; --j)
            f[j] += f[j - a[i]];
    cout << f[m] << endl;

    return 0;
}




// 279. 自然数拆分

// 完全背包

#include <iostream>
#include <cstring>
#include <algorithm>  
using namespace std;

const int N = 4010;
typedef long long LL;
const LL MOD = 2147483648;

int n;
 LL f[N];       
// unsigned int f[N][N];         // f[i][j] 表1~i凑成j的方案数,主要用unsigned,否则空间超限

int main()
{
    cin >> n;


    //f[0][0] = 1;      // 可以n=n,拆分为1个，因为用的完全背包的做法
    //for (int i = 1; i <= n; ++i)
    //    for (int j = 0; j <= n; ++j) {
    //        // 选k个,包括0个
    //        for (int k = 0; k * i <= j; ++k)
    //            f[i][j] = (f[i][j] + f[i - 1][j - k * i]) % 2147483648u;
    //    }
    //cout << f[n][n] - 1;      // 实际要求至少拆分成两个

    // 优化

    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)        // 正序，相当于可以无限次使用
            f[j] = (f[j] + f[j - i]) % MOD;
    cout << f[n]-1 << endl;

    return 0;
}