
// 340. 通信线路

// 二分+dijkstra

// 本题的答案显然具有单调性，因为支付的钱更多时，合法的升级方案一定包含了花费更少的升级方案。
// 所以我们可以二分答案，把问题转化为:是否存在一种合法的升级方法，使花费不超过mid。
// 转化后的判定问题非常容易。只需要把升级价格大于mid 的电缆看作长度为1的边，把升级价格不超过 mid 的电缆看作长度为0的边，然后求从1到N的最短路是否不超过K即可。
// 整个算法时间复杂度为O((N + P) log MAX_L)。

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1010, M = 20010;
int h[N], e[M], edge[M], ne[M], d[N];
bool v[N];
int n, m, k, tot;

void add(int x, int y, int z) {
    e[++tot] = y, edge[tot] = z, ne[tot] = h[x], h[x] = tot;
}
int check(int max_w) {
    memset(d, 0x3f, sizeof d);
    memset(v, 0, sizeof v);
    d[1] = 0;
    priority_queue<pair<int, int>> q;

    q.push({ 0,1 });
    while (q.size()) {
        int x = q.top().second; q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = h[x]; i; i = ne[i]) {
            int y = e[i], z = edge[i] > max_w;
            if (d[y] > d[x] + z) {
                d[y] = d[x] + z;
                q.push({ -d[y],y });        // 利用相反数变成小根堆   
            }
        }
    }
    return d[n];
}
int main() {
    cin >> n >> m >> k;
    int max_w = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
        max_w = max(max_w, z);
    }
    int l = 0, r = max_w + 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid) <= k) r = mid;
        else l = mid + 1;
    }

    if (l == max_w + 1) puts("-1");
    else printf("%d\n", l);

    return 0;
}



// 341. 最优贸易

// 建立返图，正向求最小价格，方向求最大价格，由于最大最小值没有累加性，后面出现的数不一定比前面的数都差，所以使用spfa求

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 100010, M = 2000010;
int n, m;
int price[N];
int head[N], rhead[N], ver[M], Next[M], tot;
int dmin[N], dmax[N];
bool st[N];

void add(int* h, int x, int y) {
    ver[++tot] = y, Next[tot] = h[x], h[x] = tot;
}
void spfa(int* d, int start, int* h, bool flag) {
    queue<int> q;
    memset(st, 0, sizeof st);

    if (flag) memset(d, 0x3f, sizeof dmin);

    q.push(start);
    st[start] = true;
    d[start] = price[start];

    while (q.size()) {
        int t = q.front(); q.pop();
        st[t] = false;

        for (int i = h[t]; i; i = Next[i]) {
            int y = ver[i];
            if (flag && d[y] > min(d[t], price[y]) || !flag && d[y] < max(d[t], price[y])) {
                if (flag) d[y] = min(d[t], price[y]);
                else d[y] = max(d[t], price[y]);

                if (!st[y]) {
                    st[y] = true;
                    q.push(y);
                }
            }
        }
    }
}


int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) cin >> price[i];
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        add(head, x, y); add(rhead, y, x);
        if (z == 2) add(head, y, x), add(rhead, x, y);
    }
    spfa(dmin, 1, head, true);
    spfa(dmax, n, rhead, false);

    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, dmax[i] - dmin[i]);

    cout << res << endl;

    return 0;
}