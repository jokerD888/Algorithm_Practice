

// 249. 蒲公英

// 分块+前缀和
// 取值范围大，先离散化，先预处理两个二维数组，第一个是 s[i][x]，其含义是前 i个块里 x 的出现次数，这是为了快速算出连续若干个整块里 x的出现次数，
//  例如第 l 到第 r 个块里 x 的出现次数就是 s[r][x]−s[l−1][x]；第二个是 f[i][j]，代表第 i 个块到第 j 个块这一段区间的众数是多少。
//  具体查询的时候，例如查区间 [l,r] 的众数是多少，如果 [l:r] 内不含整块，则直接暴力求解众数；否则先假设众数是中间的整块里的众数，可以查 f 得到，接着遍历散块里的每个数，验证这些数是否能成为众数。

// 时间复杂度O(M*sqrt(N)) 大概极限是 1e7
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

typedef pair<int, int> PII;
const int N = 40010, T = 210;
// 第i个块的左右端点下标
PII idx[T];
// sz为每个整块的数字个数，cnt为块个数
int n, m, sz, cnt;
// block[i]是序列下标i所属的块的下标,t数组是计算块中的众数的
int a[N], block[N], t[N];
vector<int> ls;  // 离散化后的值
// s[i][j] 为前i个块里j的出现次数,f[i][j]为块[i~j]这段区间的众数
int s[T][N], f[T][T];

int find(int x) {
    return lower_bound(ls.begin(), ls.end(), x) - ls.begin();
}
// 查询区间在一个分块内，直接暴力求众数
int oneBlock(int l, int r) {
    for (int i = l; i <= r; ++i) t[a[i]]++;
    int mode = a[l];
    for (int i = l + 1; i <= r; ++i) {
        if (t[a[i]] > t[mode]) mode = a[i];
        else if (t[a[i]] == t[mode]) mode = min(mode, a[i]);
    }
    for (int i = l; i <= r; ++i) t[a[i]] = 0;
    return ls[mode];
}
// 查询范围为[L,R],试图用不完整块区间[l,r]内的数更新新的众数
void check(int l, int r, int L, int R, int& mode) {
    for (int i = l; i <= r; ++i) {
        int v1 = t[a[i]] + s[block[R] - 1][a[i]] - s[block[L]][a[i]];
        int v2 = t[mode] + s[block[R] - 1][mode] - s[block[L]][mode];
        if (v1 > v2) mode = a[i];
        else if (v1 == v2) mode = min(mode, a[i]);
    }
}
int solve(int l, int r) {
    // 查询区间在两个块上，直接朴素求
    if (block[r] - block[l] <= 1) return oneBlock(l, r);                // sqrt(N)
    // 求出左右不完整块各个数出现次数
    int ledge = idx[block[l]].second, redge = idx[block[r]].first;
    for (int i = l; i <= ledge; ++i) t[a[i]]++;
    for (int i = redge; i <= r; ++i) t[a[i]]++;
    // 整块查询
    int mode = f[block[l] + 1][block[r] - 1];
    // 和左右不完整的块比较，看其中能否有新的众数
    check(l, ledge, l, r, mode);                                    // sqrt(N)
    check(redge, r, l, r, mode);

    // 清零
    for (int i = l; i <= ledge; ++i) t[a[i]] = 0;
    for (int i = redge; i <= r; ++i) t[a[i]] = 0;
    return ls[mode];
}
void init() {
    cnt = (n + sz - 1) / sz;

    // 预处理没块的左右端点
    for (int i = 1; i <= cnt; ++i) idx[i] = { (i - 1) * sz + 1,i * sz };
    idx[cnt].second = n;

    // 预处理s数组，计算s[i][j] 前i个块内数字j的个数
    for (int i = 1; i <= cnt; ++i) {                                            // sqrt(N)
        int l = idx[i].first, r = idx[i].second;
        for (int j = l; j <= r; ++j) ++s[i][a[j]], block[j] = i;                // sqrt(N)
        for (int j = 0; j < ls.size(); ++j) s[i][j] += s[i - 1][j];             // N
    }

    // 预处理f[i][j],块[i~j]这段区间的众数
    for (int i = 1; i <= cnt; ++i) {                                                                                // sqrt(N)
        for (int j = i; j <= cnt; ++j) {                                                                            // sqrt(N)
            // 每次先取到i到j-1这几个分块里的众数，然后看一下第j个分块里的数字是否能称为新的众数
            int mode = f[i][j - 1];     //众数
            for (int k = idx[j].first; k <= idx[j].second; ++k) {       // 枚举j块的所有数，检查是否能成为新众数          // sqrt(N)
                // v1为块[i,j]内数字a[k]出现的个数，v2为块[i,j]内数字a[k]出现的个数
                int v1 = s[j][a[k]] - s[i - 1][a[k]], v2 = s[j][mode] - s[i - 1][mode];
                if (v1 > v2) mode = a[k];
                else if (v1 == v2) mode = min(mode, a[k]);
            }
            f[i][j] = mode;
        }
    }

}
int main()
{
    cin >> n >> m;
    sz = sqrt(n);
    int x;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        a[i] = x;
        ls.push_back(x);
    }

    sort(ls.begin(), ls.end());
    ls.erase(unique(ls.begin(), ls.end()), ls.end());

    // 将a变为离散化后的值
    for (int i = 1; i <= n; ++i) a[i] = find(a[i]);
    init();     // N*sqrt(N)

    int res = 0;
    for (int i = 1; i <= m; ++i) {                                      // m
        int l, r;
        cin >> l >> r;
        int ll = (l + res - 1) % n + 1, rr = (r + res - 1) % n + 1;
        if (ll > rr) swap(ll, rr);  
        cout << (res = solve(ll, rr)) << endl;                          // sqrt(N)
    }
    return 0;
}




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