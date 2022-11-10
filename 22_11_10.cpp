
// 170. 加成序列

// 因为答案序列长度较小，且递归分支多，使用迭代加深
// 具体：搜索枚举序列的每个位置，同时对于每个位置枚举其和的组成i和j位置

#include <iostream>
#include <string.h>
using namespace std;

const int N = 110;
int n;
int res[N];
bool dfs(int u, int depth) {
    if (u == depth) return res[u - 1] == n;
    int vis[N] = { 0 };

    // 优化搜索顺序，从大往小枚举
    int sum = 0;
    for (int i = u - 1; i >= 0; --i) {
        for (int j = i; j >= 0; --j) {
            sum = res[i] + res[j];
            // 排除冗余性，当不同的组合的和是相同时，枚举一个即可
            // 可行性剪枝，小于等于前一个或大于n的组合跳过
            if (vis[sum] || sum <= res[u - 1] || sum > n) continue;
            vis[sum] = 1;
            res[u] = sum;
            if (dfs(u + 1, depth)) return true;
        }
    }
    return false;

}
int main()
{
    while (cin >> n, n) {
        int depth = 1;
        res[0] = 1;
        while (!dfs(1, depth)) ++depth;

        for (int i = 0; i < depth; ++i)
            cout << res[i] << ' ';
        cout << endl;
    }
    return 0;
}



// 171. 送礼物

// 直接做法就是对每个礼物枚举选或不选
// 但最多有45个礼物，直接递归枚举2^45,规模太大
// 所以双向搜索，时间复杂度为2^23

#include<iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 50;
int n, w, res, k;
int a[N];
int weights[1 << 23], cnt;

void dfs_1(int u, int s) {
    if (u == k) {
        weights[cnt++] = s;    // 对枚举到的所有重量组合存起来
        return;
    }
    if ((LL)s + a[u] <= w) dfs_1(u + 1, s + a[u]);  // 当前位置要
    dfs_1(u + 1, s);                                // 不要
}

void dfs_2(int u, int s) {
    if (u == n) {
        // 二分，查找和小于w的最大和
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if ((LL)s + weights[mid] > w) r = mid - 1;
            else l = mid;
        }
        if ((LL)s + weights[l] <= w) res = max(res, weights[l] + s);
        return;
    }
    if ((LL)s + a[u] <= w) dfs_2(u + 1, s + a[u]);
    dfs_2(u + 1, s);
}
int main()
{
    cin >> w >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n, greater<int>());

    k = n / 2;
    dfs_1(0, 0);
    // 去重
    sort(weights, weights + cnt);
    cnt = unique(weights, weights + cnt) - weights;

    dfs_2(k, 0);
    cout << res << endl;
    return 0;
}