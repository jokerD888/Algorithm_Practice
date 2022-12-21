

// 250. 磁力块

// 分块
// 先整体按重量排序，再分块，块内再按距离排序,用一重量数组记maxm录每个块最后面的那个重量
// 随后使用队列bfs,从maxm里面遍历，找到第一次maxm[i]<now.p的，随后即可从0~k块进行判断找出可被吸引的，再从k+1块内查看是否有可能被吸引的
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;
typedef long long LL;

const int N = 250010;
int n, t,cnt;
int l[N], r[N], maxm[N];
struct node {
    int x, y, m, p, r;
    bool operator<(const node& t)const {
        return m < t.m;
    }
}a[N],st;
queue<node> q;
bool flag[N];

LL dist(const node& a, const node& b) {
    return (LL)(a.x - b.x) * (a.x - b.x) + (LL)(a.y - b.y) * (a.y - b.y);
}
bool cmp(const node& a, const node& b) {
    return dist(a, st) < dist(b, st);
}


void bfs() {
    q.push(st);
    while (q.size()) {
        auto now = q.front();
        q.pop();

        int k = 0;
        // 找出最大的重量满足小于等于对头的磁力
        for (int i = 0; i < t; ++i) {
            if (maxm[i] <= now.p) k = i;
            else break;
        }

        // 0~k段内一找出所有满足距离now.r的
        for (int i = 0; i <= k; ++i) {
            while (l[i] <= r[i] && dist(a[l[i]], st) <= (LL)now.r * now.r) {
                if (!flag[l[i]]) {
                    flag[l[i]] = true;
                    ++cnt;
                    q.push(a[l[i]]);
                }
                ++l[i];
            }
        }
        // 查看k+1段是否有可能被吸引
        if (k < t-1) {
            ++k;
            for (int i = l[k]; i <= r[k]; ++i) {
                if (!flag[i] && a[i].m <= now.p && dist(a[i], st) <= (LL)now.r * now.r) {
                    flag[i] = true;
                    q.push(a[i]);
                    cnt++;
                }
            }
        }
    }
}
int main()
{
    cin >> st.x >> st.y >> st.p >> st.r >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y >> a[i].m >> a[i].p >> a[i].r;

    // 分块，先按重量排序，再在每一个段内半径排序
    t = sqrt(n);
    sort(a, a + n);

    l[0] = 0, r[0] = t - 1;     // 下标不如从0开始
    sort(a + l[0], a + r[0] + 1, cmp);
    for (int i = 1; i < t; ++i) {
        l[i] = r[i - 1] + 1, r[i] = (i+1) * t-1 ;
        maxm[i] = a[r[i]].m;
        sort(a + l[i], a + r[i] + 1, cmp);
    }

    if (r[t-1] < n-1) {
        l[t] = r[t - 1] + 1, r[t] = n-1;
        maxm[t] = a[r[t]].m;
        sort(a + l[t], a + r[t] + 1, cmp);
        ++t;
    }

    bfs();
    cout << cnt << endl;

    return 0;
}



// 251. 小Z的袜子
// 莫队算法，离线对询问进行查询分块，先把所有询问读入，把询问按左端点排序，然后分块，每块内部再安装右端点排序

#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 50010;

int n, m, t;
int a[N], cnt[N];
LL tres, x[N], y[N];
struct Query {
    int l, r, id;
    bool operator<(const Query& q) const {
        return l / t == q.l / t ? r < q.r : l < q.l;        // 同一块内按右端点排序，否则按左端点排序
    }
}q[N];

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}
void add(int x) {
    // x=a[x]
    // tres-=cnt[x]*(cnt[x]-1)>>1
    // cnt[x]++
    // tres+=cnt[x]*(cnt[x]-1)>>1
    // 合并简化如下
    tres += cnt[x = a[x]]++;
}
void sub(int x) {
    // x=a[x]
    // tres-=cnt[x]*(cnt[x]-1)>>1
    // cnt[x]--
    // tres+=cnt[x]*(cnt[x]-1)>>1
    // 合并简化如下
    tres -= --cnt[x = a[x]];
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        q[i] = { l,r,i };
        y[i] = (r - l + 1ll) * (r - l) >> 1;    // 分母，C(区间长度，2）
    }
    t = sqrt(n);            // 块大小
    sort(q, q + m);         // 同一块内按右端点排序，否则按左端点排序
    for (int i = 0, l = 1, r = 0; i < m; ++i) {
        while (r < q[i].r) add(++r);
        while (r > q[i].r) sub(r--);
        while (l < q[i].l) sub(l++);
        while (l > q[i].l) add(--l);
        x[q[i].id] = tres;
    }
    for (int i = 0; i < m; ++i) {
        LL d = gcd(x[i], y[i]);
        x[i] /= d, y[i] /= d;
        cout << x[i] << '/' << y[i] << endl;
    }

    return 0;
}