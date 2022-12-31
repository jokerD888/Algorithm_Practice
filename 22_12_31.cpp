// 281. 硬币

// 多重背包

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 210, M = 100010;

bool f[M];       // f[i,j]表 使用前i中硬币是否能凑到j元
int used[M];
int n, m;
int cnt[N], val[N];

int main()
{
    while (cin >> n >> m, n) {
        for (int i = 1; i <= n; ++i) cin >> val[i];
        for (int i = 1; i <= n; ++i) cin >> cnt[i];

        memset(f, 0, sizeof f);

        // TLE
        //f[0] = true;
        //for (int i = 1; i <= n; ++i) {
        //    for (int j = m; j >= 0; --j) {
        //        // 要k个第i种硬币
        //        if (f[j]) continue;
        //        for (int k = 0; k <= cnt[i] && j - val[i] * k >= 0; ++k) {
        //            f[j] |= f[j - val[i] * k];
        //        }
        //    }
        //}

        // 可以发现，本题的关注点是“能否”拼成j元
        // 本题仅关注“可行性”(面值能否拼成)而不是“最优性”,这是一个特殊之处。仔细分析动态规划的过程,我们可以发现，若前i种硬币能够拼成面值 j，只有两类可能情况:
        //   1.前 i - 1 种硬币就能拼成面值 j，即在第i阶段开始前，变量 F[j] 已经为true。
        //   2.使用了第 i种硬币，即在第 i阶段的递推中，发现 F[j-val[i] 为 true，从而变量 F[j] 变为 true。
        // 于是我们可以考虑一种贪心策略 : 设 used[j] 表示 F[j] 在阶段 i 时为 true 至少需要用多少枚第 i 种硬币，并且尽量选择第一类情况。也就是说，在 FV - alil] 为true 时，
        //   如果 F[j] 已经为 true，则不执行 DP 的转移，并令 used[j] = 0，否则才执行 F[j] = F[j]or F[j - val[i]] 的转移，并令 used[j] = used[j - val[i]] + 1。*/
        f[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) used[j] = 0;
            for (int j = val[i]; j <= m; j++)
                // 如果f[j]还不是true，且f[j-val[i]]是true(有机会从f[j-val[i]]转移）且f[j-val[i]]使用i的个数不超过cnt[i],才可以进行转移
                if (!f[j] && f[j - val[i]] && used[j - val[i]] < cnt[i]) {  
                    f[j] = 1;
                    used[j] = used[j - val[i]] + 1;
                }
        }
        int res = 0;
        for (int i = 1; i <= m; ++i)
            res += f[i];
        cout << res << endl;
    }
    return 0;
}