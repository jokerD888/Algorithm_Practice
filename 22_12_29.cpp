
// 280. 陪审团

// 这是一个多维度的01背包问题
// 若要暴力搜索的话，可以定义如下的dfs(u,rest,psum,dum),已经决定了u个人，还要选rest个人，目前各分得分为psum,dum
// 定义为dp的话。f[u][rest][psun][dsum],使用滚动数组的话，可以省去第一维度
//  进一步我们可以把每个候选人辩、控双方得分的差 a[i] - bli] 作为该物品的“体积”之一,把辩、控双方得分的和作为该物品的价值。
//  至此可简化为f[j][k],当外层循环到 i 时，设 F[j,k] 表示已经在前i个候选人中选出了j个，此时辩方总分与控方总分的差为 k 时，辩方总分与控方总分的和的最大值。
//      即f[j,k]=max(f[j,k],f[j-1,k-(a[i]-b[i])]+a[i]+b[i])
// 关于具体方案的输出，采用记录转移路径的方法，额外建立一个数组 D，其中 D[i,j,k] 表示外层循环执行到 时，状态 Fli,k] 的最大值是选了哪一名候选人而得到的。

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 210, M = 810;     // 因为分差有正有负，-400~400
const int offset = 400;
int n, m;
int a[N], b[N];
int f[25][M];       // 前i个人，选了j个，双方总分差为-400~400
int d[N][25][M];    // 记录路径要三维不能省略，不然后面的更新可能会覆盖前面的记录
vector<int> c;
int suma, sumb;

void get_path(int i, int j, int k) {
    if (j == 0) return;
    int last = d[i][j][k];
    get_path(last - 1, j - 1, k - (a[last] - b[last]));
    c.push_back(last);
    suma += a[last], sumb += b[last];
}
int main()
{
    int T = 0;
    while (cin >> n >> m, n) {

        for (int i = 1; i <= n; ++i) {
            cin >> a[i] >> b[i];
        }

        memset(f, 0xcf, sizeof f);      // 需要搞成INF
        f[0][offset] = 0;

        int limit = m * 20;
        for (int i = 1; i <= n; ++i) {
            // 不选i
            for (int j = 0; j <= m; ++j)
                for (int k = -limit; k <= limit; ++k) d[i][j][offset + k] = d[i - 1][j][offset + k];
            for (int j = m; j >= 1; --j)
                for (int k = -limit; k <= limit; ++k) {
                    // 不要,利用滚动数组已经默认操作了f[i][j][k]=max(f[i][j][k],f[i-1][j][k])
                    // 选i
                    if (k - (a[i] - b[i]) < -400 || k - (a[i] - b[i]) > 400) continue;
                    // f[j][k + offset] = max(f[j][k + offset], f[j - 1][offset + k - (a[i] - b[i])] + a[i] + b[i]);
                    if (f[j][offset + k] < f[j - 1][offset + k - (a[i] - b[i])] + a[i] + b[i]) {
                        f[j][offset + k] = f[j - 1][offset + k - (a[i] - b[i])] + a[i] + b[i];
                        d[i][j][offset + k] = i;
                    }
                }
        }
        int ans = 0;        // 总分差
        while (f[m][offset - ans] < 0 && f[m][offset + ans] < 0) ++ans;
        // if (f[m][offset + ans]<0) ans = -ans;    // 错误,因为两边不是对称的
        if (f[m][offset - ans] > f[m][offset + ans]) ans = offset - ans;
        else ans = offset + ans;


        c.clear();
        suma = sumb = 0;
        get_path(n, m, ans);
        printf("Jury #%d\n", ++T);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", suma, sumb);
        for (int i = 0; i < c.size(); i++) printf(" %d", c[i]);
        printf("\n\n");
    }

    return 0;
}

// 或

#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 210, M = 810, base = 400;

int n, m;
int p[N], d[N];
int f[N][21][M];
int ans[N];

int main()
{
    int T = 1;
    while (scanf("%d%d", &n, &m), n || m)
    {
        for (int i = 1; i <= n; i++) scanf("%d%d", &p[i], &d[i]);

        memset(f, -0x3f, sizeof f);
        f[0][0][base] = 0;

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++)
                for (int k = 0; k < M; k++)
                {
                    f[i][j][k] = f[i - 1][j][k];
                    int t = k - (p[i] - d[i]);
                    if (t < 0 || t >= M) continue;
                    if (j < 1) continue;
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][t] + p[i] + d[i]);
                }

        int v = 0;
        while (f[n][m][base - v] < 0 && f[n][m][base + v] < 0) v++;

        if (f[n][m][base - v] > f[n][m][base + v]) v = base - v;
        else v = base + v;

        int cnt = 0;
        int i = n, j = m, k = v;
        while (j)
        {
            if (f[i][j][k] == f[i - 1][j][k]) i--;
            else
            {
                ans[cnt++] = i;
                k -= (p[i] - d[i]);
                i--, j--;
            }
        }

        int sp = 0, sd = 0;
        for (int i = 0; i < cnt; i++)
        {
            sp += p[ans[i]];
            sd += d[ans[i]];
        }

        printf("Jury #%d\n", T++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", sp, sd);

        sort(ans, ans + cnt);
        for (int i = 0; i < cnt; i++) printf(" %d", ans[i]);
        puts("\n");
    }

    return 0;
}