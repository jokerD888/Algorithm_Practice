
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