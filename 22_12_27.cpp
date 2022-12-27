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
