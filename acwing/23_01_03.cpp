

// 282. 石子合并

// 区间dp

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 310;

int a[N], sum[N];
int f[N][N];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; ++i) f[i][i] = 0;

    for (int len = 2; len <= n; ++len) {    // 阶段
        for (int l = 1; l <= n - len + 1; ++l) {    // 状态：左端点
            int r = l + len - 1;                    //  状态：右端点
            for (int k = l; k < r; ++k)        // 决策
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
            f[l][r] += sum[r] - sum[l - 1];
        }
    }

    cout << f[1][n] << endl;


    return 0;
}


// 283. 多边形

// 区间dp
// 任意选择一个位置断开，复制形成 2 倍长度的链，随后的操作跟上题类似
// 需要主要的时，我们不仅仅需要存储区间的最大值，也要最小值，因为有乘法的存在

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, INF = 32768;

int n;
int val[N];
char oper[N];
int f[N][N], g[N][N];   // f数组和g数组都为dp数组，f[l][r]表把第 l 到 r 个顶点合成一个顶点后，顶点上的数值最大是多少，g[l][r]则是最小是多少

int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> oper[i] >> val[i];
        // 环断开，复制链形成2倍长度的链
        oper[i + n] = oper[i];
        val[i + n] = val[i];
    }

    for (int len = 1; len <= n; ++len) {                // 阶段
        for (int l = 1; l + len - 1 <= n * 2; ++l) {    // 状态左端点
            int r = len + l - 1;                        // 状态右端点
            if (len == 1) {
                f[l][r] = g[l][r] = val[l];
                continue;
            }
            f[l][r] = -INF, g[l][r] = INF;
            for (int k = l; k < r; ++k) {       // 决策
                char op = oper[k + 1];
                int minl = g[l][k], minr = g[k + 1][r];
                int maxl = f[l][k], maxr = f[k + 1][r];
                if (op == 't') {
                    f[l][r] = max(f[l][r], maxl + maxr);
                    g[l][r] = min(g[l][r], minl + minr);
                } else {
                    int x1 = maxl * maxr, x2 = maxl * minr, x3 = minl * maxr, x4 = minl * minr;
                    f[l][r] = max({ f[l][r], x1, x2, x3, x4 });
                    g[l][r] = min({ g[l][r], x1, x2, x3, x4 });
                }
            }
        }
    }

    int res = -INF;
    for (int i = 1; i <= n; ++i) res = max(res, f[i][i + n - 1]);
    cout << res << endl;

    for (int i = 1; i <= n; ++i)
        if (res == f[i][i + n - 1])
            cout << i << ' ';
    return 0;
}




// 284. 金字塔

// 一棵树的每棵子树都对应着这棵树 DFS 序中的一个区间
// 本题中记录的序列虽然不是 DFS 序，但仍然满足这条性质。因此，这道题目在“树形结构”与“字符串”之间通过“子树”和“区间”建立了联系。
// 不难想到用 F[L,r] 表示子串 S[l~r] 对应着多少种可能的金字塔结构(树形结构)。
//     我们的决策就是区间上最后一个树开始的位置

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 310,MOD=1e9;

string str;
int f[N][N];

int main()
{   
    cin >> str;
    int n = str.size();
    if (n % 2 == 0) puts("0");     // 因为n个节点，n-1个边，每个边一进一出各打印一个点，再加上最开始的根节点，所以长度为2*n-1,一定为奇数
    else {
        for (int len = 1; len <= n; len += 2)      // 长度一定是奇数
            for (int l = 0; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                if (len == 1) f[l][r] = 1;          
                else if(str[l]==str[r]) {               
                    for (int k = l; k < r; k += 2) {     
                        if (str[k] == str[l]) {
                            f[l][r] = (f[l][r] +(LL)f[l][k] * f[k + 1][r - 1]) % MOD;
                        }
                    }
                }
            }
        cout << f[0][n - 1] << endl;
    }
    return 0;
}

