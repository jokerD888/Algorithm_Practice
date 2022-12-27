
// 271. 杨老师的照相排列

//从高到低依次安排每个同学的位置，那么在安排过程中，当前同学一定占据每排最靠左的连续若干个位置，
// 且从后往前每排人数单调递减。否则一定不满足“每排从左到右身高递减，从后到前身高也递减”这个要求。

// 定义f[a][b][c][d][e]为第一排站了a个人，第二排站了b个人，。。。。f[0][0][0][0][0]=1,根据最后一个人站的哪排进行划分
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 31;

LL f[N][N][N][N][N];
int main()
{
    int k;
    while (cin >> k, k) {
        memset(f, 0, sizeof f);
        int s[5] = { 0 };
        for (int i = 0; i < k; ++i) cin >> s[i];

        f[0][0][0][0][0] = 1;

        for (int a = 0; a <= s[0]; ++a)
            for (int b = 0; b <= min(a, s[1]); ++b)
                for (int c = 0; c <= min(b, s[2]); ++c)
                    for (int d = 0; d <= min(c, s[3]); ++d)
                        for (int e = 0; e <= min(d, s[4]); ++e) {
                            LL& v = f[a][b][c][d][e];
                            // 站第一排
                            if (a && a - 1 >= b) v += f[a - 1][b][c][d][e];
                            // 第二排
                            if (b && b - 1 >= c) v += f[a][b - 1][c][d][e];
                            //...
                            if (c && c - 1 >= d) v += f[a][b][c - 1][d][e];
                            if (d && d - 1 >= e) v += f[a][b][c][d - 1][e];
                            if (e) v += f[a][b][c][d][e - 1];
                        }

        cout << f[s[0]][s[1]][s[2]][s[3]][s[4]] << endl;

    }
    return 0;
}




// 272. 最长公共上升子序列

// 结合LIS最长上升子序列和LCS最长公共子序列的做法
//  设f[i][j]表A1~Ai,与B1~Bj可以构成的以Bj为结尾的LCIS长度

// 首先可以根据公共子序列是否包含Ai做划分
// 当Ai!=Bi时，有f[i,j]=f[i-1,j]
// 当Ai==Bi时，有f[i,j]=max(f[i-1,k)+1  (0<=k<j,Bk<Ai) ，即枚举子序列倒数第二个元素在b[]中哪个数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3010;
int a[N], b[N];
int f[N][N];
int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    //for (int i = 1; i <= n; ++i) {
    //    for (int j = 1; j <= n; ++j) {
    //        f[i][j] = f[i - 1][j];      // 不包含a[i]
    //        if (a[i] == b[j]) {         // 可以包含a[i]的话
    //            int maxv = 1;
    //            for (int k = 1; k < j; ++k)
    //                if (a[i] > b[k])
    //                    maxv = max(maxv, f[i - 1][k] + 1);
    //            f[i][j] = max(f[i][j], maxv);
    //        }
    //    }
    //}

    for (int i = 1; i <= n; i++) {
        int maxv = 1;
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
            if (a[i] > b[j]) maxv = max(maxv, f[i - 1][j] + 1);     // 为下一轮做准备
        }
    }

    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, f[n][i]);
    cout << res << endl;
    return 0;
}


// 273. 分级
// 可以得知一条这样的性质，一定存在一组最优解，使得每个 Bi 都是原序列中的某个值。
// f[i,j]表给A[1~i]都分配好了且最后一个值为A'[j],A'是A排序后的值
// f[i,j]的划分类似上一题，枚举倒数第二个数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2010;
int n;
int a[N], b[N];
int f[N][N];

int work() {
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    sort(b + 1, b + 1 + n);

    for (int i = 1; i <= n; ++i) {
        int minv = 1 << 30;
        for (int j = 1; j <= n; ++j) {
            minv = min(minv, f[i - 1][j]);
            f[i][j] = minv + abs(a[i] - b[j]);
        }
    }

    int res = 1 << 30;
    for (int i = 1; i <= n; ++i) res = min(res, f[n][i]);
    return res;

}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int res = work();
    reverse(a + 1, a + 1 + n);
    res = min(res, work());
    cout << res << endl;
    return 0;
}



//274. 移动服务

// 容易想到定义f[i][a][b][c]为完成了前i个请求，三个员工分别位于a,b,c时，公司当前的最小花费
//  状态转移显然有三种，就是派三个员工之一去i+1个请求处
//  f[i+1,p,b,c]=min(f[i+1,p,b,c],f[i,a,b,c]+c[x,p])
//  f[i+1,a,p,c]=min(f[i+1,a,p,c],f[i,a,b,c]+c[b,p])
//  f[i+1,a,b,p]=min(f[i+1,a,b,p],f[i,a,b,c]+c[c,p])

// 但是时间规模在1000*200^3，不能接受，但仔细观察可以发现，在在第 i个请求完成时，一定有某个员工位于位置 pi，只需要知道阶段 和另外两个员工的位置即可描述一个状态，处于 pi的员工位置对 DP 来说是余信息。
// 因此，可用 F[i, x, y] 表示完成了前i 个请求，其中一个员工位于 pi，另外两个员工位于 x 和 y 时，公司当前最小花费。三种转移则分别是让位于 pi，x 和 y 的员工前往 pi + 1 处理请求。
//F[i + 1, x, y] = min(F[i + 1, x, y], F[i, x, y] + c(pi, pi + i))
//F[i + 1, pi, y] = min(F[i + 1, pi, y], F[i, x, y] + c(x, pi + i))
//F[i + 1, x, pi] = min(F[i + 1, x, pil, F[i, x, y] + c(y, pi + i))


#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210, M = 1010;
int q[M];
int cost[N][N];
int n, m;
int f[M][N][N];
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> cost[i][j];

    for (int i = 1; i <= m; ++i) cin >> q[i];

    memset(f, 0x3f, sizeof f);
    q[0] = 3;
    f[0][1][2] = 0;

    for (int i = 1; i <= m; ++i) {
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                if (x == y || x == q[i - 1] || y == q[i - 1]) continue;
                // q[i-1]位置的去
                f[i][x][y] = min(f[i][x][y], f[i - 1][x][y] + cost[q[i - 1]][q[i]]);
                // x位置的去
                f[i][q[i - 1]][y] = min(f[i][q[i - 1]][y], f[i - 1][x][y] + cost[x][q[i]]);
                // y位置的去
                f[i][x][q[i - 1]] = min(f[i][x][q[i - 1]], f[i - 1][x][y] + cost[y][q[i]]);
            }
        }
    }

    int res = 1 << 30;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            res = min(res, f[m][i][j]);
    cout << res << endl;

    return 0;
}



// 275. 传纸条

// 由于需要找出两条路线，且两条路线不能相交（每个同学只能用一次），所以不妨同时对两条线路进行搜寻
// 同样我们可以确定f[i,x1,y1,x2,y2]即已经确定了线路i个长度，线路1的末尾为（x1,y1),线路2的末尾为（x2,y2)
//      可以发现x1+y1=x2+y2=i+2,所以可以从五个变量减少为三个变量f[i][x1][x2]

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 60;
int f[N * 2][N][N], a[N][N];
int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];

    for (int i = 1; i <= n + m - 2; ++i) {
        for (int x1 = 1; x1 <= min(n, i + 1); ++x1) {
            int y1 = i + 2 - x1;
            for (int x2 = 1; x2 <= min(n, i + 1); ++x2) {
                if (x1 == x2 && i != n + m - 2) continue;       // 注意一个同学只能用一次
                int y2 = i + 2 - x2;
                int& v = f[i][x1][x2];
                // f[i,x1,x2]可由4个状态转移而来
                // (x1,y1-1),(x2,y2-1)
                if (y1 > 1 && y2 > 1) v = max(v, f[i - 1][x1][x2]);
                // (x1-1,y1),(x2-1,y2)
                if (x1 > 1 && x2 > 1) v = max(v, f[i - 1][x1 - 1][x2 - 1]);
                // (x1,y1-1),(x2-1,y2)
                if (y1 > 1 && x2 > 1) v = max(v, f[i - 1][x1][x2 - 1]);
                // (x1-1,y1),(x2,y2-1)
                if (x1 > 1 && y2 > 1)v = max(v, f[i - 1][x1 - 1][x2]);
                v += a[x1][y1] + a[x2][y2];
            }
        }
    }
    cout << f[n + m - 2][n][n];

    return 0;
}




// 277. 饼干


// 我们可以发现贪婪度大的孩子获得的饼干数应该比贪婪度小的孩子多
// 所以我们先根据贪婪度从大到小进行排序，我们依次从前往后算，那么对于i位置的孩子，比他饼干数多的孩子数量为i-1
// f[i][j]表已经完成了前i个孩子的分配，消耗了j个饼干,所造成的最小贪婪和
//   随后即可根据第i个孩子的获得的饼干数进行讨论，
//      1）第i个孩子获得的饼干数比第i-1个孩子少，此时a[i]=i-1
//      2) 相同，则需要知道i前面有几个孩子与i-1获得的饼干数相同，才能计算a[i]
// 总而言之，无论那种情况，我们都需要知道第i个孩子获得的饼干数，以及i前面有多少个孩子与i获得的饼干数相同
// 为此我们可以使用等价转换，为方便描述，将上述表法的i变为i+1
//  若第i个孩子获得的饼干数大于1，则等价于分配j-i个饼干给前i个孩子,每人少拿一个饼干，获得的相对顺序不变，不影响怨气之和
//  若等于1，枚举i前面有多少个孩子也获得1块饼干
// 即 f[i,j]=min(f[i,j-i],min(f[k,j-(i-k)]+k*累加g[p](p从k+1到i)(k从0到i)
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 35, M = 5010;

struct node {
    int g, id;
    bool operator<(const node& t)const {
        return g > t.g;
    }
}g[N];
int n, m;
int f[N][M];    // f[i][j]表已经完成了前i个，消耗了j个饼干,所造成的最小贪婪和
int s[N];       // 贪婪度前缀和
int ans[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> g[i].g;
        g[i].id = i;
    }
    sort(g + 1, g + n + 1);
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;  // 初态

    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + g[i].g;

    for (int i = 1; i <= n; ++i) {
        int sumg = 0;
        for (int j = i; j <= m; ++j) {
            // 若获得饼干数大于1
            f[i][j] = min(f[i][j], f[i][j - i]);
            // 等于1,枚举有几个1
            for (int k = 1; k <= i && k <= j; ++k) {
                f[i][j] = min(f[i][j], f[i - k][j - k] + (s[i] - s[i - k]) * (i - k));
            }

        }
    }
    cout << f[n][m] << endl;

    // 倒退找方案
    int i = n, j = m, h = 0;    // h是整体的增量
    while (i && j) {
        if (j >= i && f[i][j] == f[i][j - i]) j -= i, ++h;
        else {
            for (int k = 1; k <= i && k <= j; ++k) {
                // 连续多个1，一起结算
                if (f[i][j] == f[i - k][j - k] + (s[i] - s[i - k]) * (i - k)) {
                    for (int u = i; u > i - k; --u) {
                        ans[g[u].id] = 1 + h;
                    }
                    i -= k, j -= k;
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << endl;
    return 0;
}
