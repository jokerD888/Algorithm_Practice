
// 167. 木棒

#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

const int N = 70;
int a[N], vis[N];
int n, sum, len,num;

bool dfs(int curlen, int cnt, int index) {
    if (curlen == 0 && cnt == num) return true;
    // 从大到小枚举木棍来拼当然原始棒
    for (int i = index; i < n; ++i) {
        if (vis[i] || curlen + a[i] > len) continue;
        // 优化3：当前原始木棒刚好拼好，但接下来的第cnt+1个拼不好，直接return
        // 因为我们从大到小尝试的木棍，所以就连灵活性更高的小木棍都拼不好，所以用多个小的来替换当前a[i]这个大的，也拼不好之后的木棒
        // 用贪心来解释，“再用一根木棍恰好拼完当前原始木棒”，必然比“再用若干根木棍拼完当前原始木棒”更好
        if (curlen + a[i] == len) {
            vis[i] = true;
            if (dfs(0, cnt + 1, 0)) {
                return true;
            } else {
                vis[i] = false;
                return false;
            }
        }
        // 优化4：在尝试拼入的第一根木棍的递归分支就失败，那么直接判定当前分支失败，立即回溯
        // 因为当前木棍是“空状态”与其他还未拼的木棒等效，所以其他木棒在拼的时候也会失败
        if (curlen == 0) {  // 当前是拼原始木棒的第一个
            vis[i] = true;
            if (dfs(a[i], cnt, i + 1)) {
                return true;
            } else {
                vis[i] = false;
                return false;
            }
        }
        vis[i] = true;
        if (dfs(curlen + a[i], cnt, i + 1)) return true;
        vis[i] = false;
        // 优化5：当当时木棍拼接失败时，后面长度和当前长度相同的木棍都可以跳过了
        while (a[i + 1] == a[i])++i;
    }
    return false;
}

int main()
{
    while (cin >> n, n) {
        sum = 0;
        len = 0;
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            sum += a[i];
            len = max(len, a[i]);
        }
        sort(a, a + n, greater<int>()); // 优化1：木棍长度从大到小排，减少分支
        //  从小到大枚举原始木棍的长度
        for (;; ++len) {
            if (sum % len) continue;      // 优化2：如果枚举的长度不是总长度的约数，跳过
            num = sum / len;
            if (dfs(0, 0, 0)) break;
        }
        cout << len << endl;
    }
    return 0;
}

// 简化


#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

const int N = 70;
int a[N], vis[N];
int n, sum, len, num;

bool dfs(int curlen, int cnt, int index) {
    if (curlen == 0 && cnt == num) return true;
    if (curlen == len) return dfs(0, cnt + 1, 0);
    int fail = 0;       // 优化5
    // 从大到小枚举木棍来拼当然原始棒
    for (int i = index; i < n; ++i) {
        if (!vis[i] && curlen + a[i] <= len && fail != a[i]) {
            vis[i] = true;
            if (dfs(curlen + a[i], cnt, i + 1)) return true;
            fail = a[i];
            vis[i] = false;
            if (curlen == 0 || curlen + a[i] == len) return false;      // 优化3，优化4
        }
    }
    return false;
}


int main()
{
    while (cin >> n, n) {
        sum = 0;
        len = 0;
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            sum += a[i];
            len = max(len, a[i]);
        }
        sort(a, a + n, greater<int>()); // 优化1：木棍长度从大到小排，减少分支
        //  从小到大枚举原始木棍的长度
        for (;; ++len) {
            if (sum % len) continue;      // 优化2：如果枚举的长度不是总长度的约数，跳过
            num = sum / len;
            if (dfs(0, 0, 0)) break;
        }
        cout << len << endl;
    }
    return 0;
}



// 168. 生日蛋糕


#include <iostream>
#include <algorithm>
#include <string.h>
#include <cmath>
using namespace std;

const int N = 25, INF = 1e9;
int n, m;
int minv[N], mins[N];
int R[N], H[N];     // 记录每层的半径和高，因为上一层需要用到下一层半径和高
int res = INF;

void dfs(int level, int v, int s) {
    // 可行性剪枝：若当前体积v加上上面的最小体积和 大于 n
    if (v + minv[level] > n) return;
    // 最优性剪枝：若当前体积s加上上面的最小面积和 大于 res
    if (s + mins[level] >= res) return;
    // 最优性剪枝，若通过剩余体积能推断出剩余最小面积，若s加上剩余最小面积大于等于res的话
    if (s + 2 * (n - v) / R[level + 1] >= res) return;

    if (!level) {       // 每一层都枚举完了
        if (v == n) res = s;    // 看最后体积是否等于n
        return;
    }

    int q = sqrt((n - v - minv[level - 1]) / level);
    // 优化搜索顺序，因为体积是r*r，所以先枚举半径，后枚举高，同时，从大值枚举到小值
    // 上下界剪枝：预处理获得枚举范围内的半径和高度
    for (int r = min(R[level + 1] - 1, q); r >= level; --r) {
        q = (n - v - minv[level - 1]) / r / r;
        for (int h = min(H[level + 1] - 1, q); h >= level; --h) {
            H[level] = h, R[level] = r;
            // 最底层时需要加上r*r,因为整个上面积为最低层的表面积
            int t = level == m ? r * r : 0;
            dfs(level - 1, v + r * r * h, s + 2 * r * h + t);
        }
    }

}
int main()
{
    cin >> n >> m;
    // 预处理每上方最小的体积和面积,当从上往下，需严格递增，高和半径分别取1，2，3...可有最小体积和最小表面积
    for (int i = 1; i <= m; ++i) {
        minv[i] = minv[i - 1] + i * i * i;  // R^2 * H
        mins[i] = mins[i - 1] + 2 * i * i;      // 2*R * H
    }

    R[m + 1] = H[m + 1] = INF;  // 哨兵节点
    dfs(m, 0, 0);

    if (res == INF) res = 0;
    cout << res << endl;
    return 0;
}