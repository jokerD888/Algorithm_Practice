//1139. 最大的以 1 为边界的正方形
// 枚举+一点动态规划  O（N×M×min(N,M)）
// 矩阵最大100*100，我们可以枚举正方形的右下角（x,y)，然后计算4个方向上的最小连续1的个数，
//  left[i][j]即从点[i][j]开始向左连续1的个数
//  right[i][j]即从点[i][j]开始向右连续1的个数
//  down[i][j]即从点[i][j]开始向下连续1的个数
//  up[i][j]即从点[i][j]开始向上连续1的个数
// 但实际上我们只需要left和up方向上的即可，因为left[i - border + 1][j]即可替代上边，up[i][j - border + 1]即可替代左边
// 我们从上到下，从左到右处理即可，这个过程可以使用动态规划来完成即：
//      left[i][j] = left[i][j - 1] + 1;    up[i][j] = up[i - 1][j] + 1;   （if (grid[i-1][j-1] == 1)）
class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> left(n + 1, vector<int>(m + 1));
        vector<vector<int>> up(n + 1, vector<int>(m + 1));
        int res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (grid[i - 1][j - 1] == 1) {
                    left[i][j] = left[i][j - 1] + 1;
                    up[i][j] = up[i - 1][j] + 1;
                    int border = min(left[i][j], up[i][j]);
                    while (left[i - border + 1][j] < border || up[i][j - border + 1] < border) {
                        --border;
                    }
                    res = max(res, border);
                }
            }
        }
        return res * res;

    }
};


//O（N*M)
// 与上法思想类似，不同的是从4个方向上的判断变换为了对角线的判断
// 整体复杂度为O(N*M），因为左上角和右下角两个点都是呈45度角进行滑动的
class Solution {
public:
    int u[100][100], d[100][100], l[100][100], r[100][100];
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), res = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (grid[i][j]) {
                    l[i][j] = j ? l[i][j - 1] + 1 : 1;
                    u[i][j] = i ? u[i - 1][j] + 1 : 1;
                } else {
                    l[i][j] = 0;
                    u[i][j] = 0;
                }
            }
        for (int i = n - 1; i >= 0; i--)
            for (int j = m - 1; j >= 0; j--) {
                if (grid[i][j]) {
                    r[i][j] = j < m - 1 ? r[i][j + 1] + 1 : 1;
                    d[i][j] = i < n - 1 ? d[i + 1][j] + 1 : 1;
                } else {
                    r[i][j] = 0;
                    d[i][j] = 0;
                }
            }
        // 遍历左下三角
        for (int i = 0; i < n; i++) {// 一行一行来
            int li = i, lj = 0, ri = i, rj = 0; // 左上角和右下角最开始都从(i,0)开始
            while (li < n && lj < m) {

                // 只要左上角的点的下面和右边连续的1最小值>左上角和右下角的横坐标差
                while (ri < n && rj<m && min(d[li][lj], r[li][lj])>ri - li) {
                    if (min(u[ri][rj], l[ri][rj]) > ri - li)    // 右下角的上面和坐标也符号
                        res = max(res, (ri - li + 1) * (ri - li + 1));  // 结算
                    ri++;       // 右下角从右下方移动
                    rj++;
                }
                li++;   // 左上角向右下方移动
                lj++;
            }

        }
        // 遍历右上三角
        for (int i = 1; i < m; i++) {     // 一列一列
            int li = 0, lj = i, ri = 0, rj = i;
            while (li < n && lj < m) {
                while (ri < n && rj<m && min(d[li][lj], r[li][lj])>ri - li) {
                    if (min(u[ri][rj], l[ri][rj]) > ri - li)
                        res = max(res, (ri - li + 1) * (ri - li + 1));
                    ri++;
                    rj++;
                }
                li++;
                lj++;
            }
        }
        return res;

    }

};



// 1223. 掷骰子模拟

// 可以很容易写出暴力做法
// 1223. 掷骰子模拟
class Solution {
public:
    int dfs(int n, int last, int cnt, vector<int>& rollMax) {
        if (n == 0) return 1;
        int res = 0;
        for (int i = 0; i < 6; ++i) {
            if (i == last && cnt == rollMax[i]) continue;
            if (i == last)
                res += dfs(n - 1, i, cnt + 1, rollMax);
            else
                res += dfs(n - 1, i, 1, rollMax);
        }
        return res;

    }
    int dieSimulator(int n, vector<int>& rollMax) {
        return dfs(n, -1, 0, rollMax);
    }
};

// 可以发现dfs有三个“变量”是n,last和cnt
// 所以可以根据暴力递归来实现动态规划
class Solution {
public:
    int f[5010][6][16];
    //f[i][j][k]表示已经摇了i次，最后一次是j,且连续k次都是j
    int dieSimulator(int n, vector<int>& rollMax) {
        const int MOD = 1e9 + 7;
        for (int i = 0; i < 6; ++i)
            f[1][i][1] = 1;

        for (int i = 2; i <= n; ++i) {
            for (int last = 0; last < 6; ++last) {
                for (int cnt = 1; cnt <= rollMax[last]; ++cnt) {
                    // 已将摇了i-1次，最后一次是last,且连续cnt次都是last
                    // 开始摇第i次
                    for (int j = 0; j < 6; ++j) {   // 第i次摇的点数
                        if (j == last && cnt == rollMax[last]) continue;
                        if (j == last)
                            f[i][j][cnt + 1] = (f[i][j][cnt + 1] + f[i - 1][last][cnt]) % MOD;
                        else
                            f[i][j][1] = (f[i][j][1] + f[i - 1][last][cnt]) % MOD;
                    }
                }
            }
        }
        int res = 0;
        for (int j = 0; j < 6; ++j)
            for (int k = 1; k <= rollMax[j]; ++k)
                res=(res + f[n][j][k])%MOD;
        return res;
    }
};

// 空间优化,滚动数组
// O(knm^2)
class Solution {
public:
    int f[2][6][16];
    //f[i][j][k]表示已经摇了i次，最后一次是j,且连续k次都是j
    int dieSimulator(int n, vector<int>& rollMax) {
        const int MOD = 1e9 + 7;
        for (int i = 0; i < 6; ++i)
            f[1][i][1] = 1;

        for (int i = 2; i <= n; ++i) {
            int t = i & 1;
            for (int j = 0; j < 6; ++j)
                for (int k = 1; k <= 15; ++k)
                    f[t][j][k] = 0;
            for (int last = 0; last < 6; ++last) {
                for (int cnt = 1; cnt <= rollMax[last]; ++cnt) {
                    // 已将摇了i-1次，最后一次是last,且连续cnt次都是last
                    // 开始摇第i次
                    for (int j = 0; j < 6; ++j) {   // 第i次摇的点数
                        if (j == last && cnt == rollMax[last]) continue;
                        if (j == last)
                            f[t][j][cnt + 1] = (f[t][j][cnt + 1] + f[t^1][last][cnt]) % MOD;
                        else
                            f[t][j][1] = (f[t][j][1] + f[t^1][last][cnt]) % MOD;
                    }
                }
            }
        }
        int res = 0;
        for (int j = 0; j < 6; ++j)
            for (int k = 1; k <= rollMax[j]; ++k)
                res = (res + f[n&1][j][k]) % MOD;
        return res;
    }
};


// 状态表示优化
// 我们改变状态的表示，f[i][j]表示摇了i次，第i次摇的是j点
// 对于f[i][j]：第i次摇到的自然是j,我们考虑第i-1次的结果，可以是f[i-1][0],f[i-1][1]....f[i-1][5]
//      但是如果第i-1次摇到的还是j,那么对结果有影响吗？
//      若连续j的次数没超过rollMax[j]，就是合法的
//      若超过了，就不合法，还需要去除不合法的序列，
//  那么不合法的序列有多少呢，不合法的序列就是第i次j还没掷出去之前，连续j的已经出现了rollMax[j]次,设t=i-1-rollMax[j]
//      所以还需要减去这部分不合法的，即减去f[t][k],(k从0到5，但k!=j)
class Solution {
public:
    typedef long long LL;
    int dieSimulator(int n, vector<int>& rollMax) {
        const int MOD = 1e9 + 7;
        vector<vector<LL> > dp(n + 1, vector<LL>(6));
        // 初始化
        for (int j = 0; j < 6; j++) {
            dp[1][j] = 1;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < 6; j++) {
                // 加入第 i-1 次得所有可能序列总数
                LL ans = accumulate(dp[i - 1].begin(), dp[i - 1].end(), 0LL);
                int idx = i - 1 - rollMax[j];
                if (idx >= 1) {
                    // 减去不合法序列
                    ans = accumulate(dp[idx].begin(), dp[idx].end(), ans, [&](LL init, LL e) {
                        return init + MOD - e;
                        });
                    ans += dp[idx][j];      // 上面多减了，要加上
                } else if (idx == 0) {
                    // 特殊情况处理，因为当idx==0时，即违规情况只有前i-1次都是j
                    ans -= 1;
                }
                dp[i][j] = ans % MOD;
            }
        }
        return accumulate(dp[n].begin(), dp[n].end(), 0LL) % MOD;
    }
};


// 上法优化，我们发现求和会有重复，所以单独用一个sum数组记录
// O(N)
class Solution {
public:
    static constexpr int mod = 1E9 + 7;
    int dieSimulator(int n, vector<int>& rollMax) {
        vector f(n + 1, vector<int>(6, 0));
        vector<int> sum(n + 1, 0);      // sum[i]表第i次的结果总数
        sum[0] = 1;     // 特殊考虑
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 6; j++) {
                int pos = max(i - rollMax[j] - 1, 0);
                // sub为不合法的情况
                int sub = ((sum[pos] - f[pos][j]) % mod + mod) % mod;       // 多次取模防止模数为负数造成不正确的结果
                f[i][j] = ((sum[i - 1] - sub) % mod + mod) % mod;

                // i<=rollMax[j] 即表示即使之前全部都是j也都合法，所以上面多减去一次，要加回来
                if (i <= rollMax[j]) {
                    f[i][j] = (f[i][j] + 1) % mod;
                }
                sum[i] = (sum[i] + f[i][j]) % mod;
            }
        }
        return sum[n];
    }
};