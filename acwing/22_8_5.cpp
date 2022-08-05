// 164. 可达性统计

// 拓扑排序+压位
// 思路：设a->b,a->c,点a都两条出边，分别到b,c，设f[i]为从点i出发能够到达的点的数量，f[i]是个集合，存储着能到达的具体的某个点
// 那么f[a]=f[b]+f[c]+1,所以自身的结果为各自孩子的结果的和加上自身的1个点
// 点的个数最大30000，若直接开f[N][N],爆空间，为此需要压位，可以借助bitset,那么最多需要30000*30000/32大概需要3e7个int,1e6个int需要4MB,总的选哟120MB,可以解决

#include <iostream>
#include <cstring>
#include <bitset>
#include <queue>
using namespace std;

const int N = 30010;
int n, m;
int h[N], e[N], ne[N], idx; // 邻接表
int d[N], seq[N];           // 入度，拓扑序列
bitset<N> f[N];


void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {  //入度为0的点入对列
        if (!d[i]) q.push(i);
    }

    int k = 0;
    while (q.size()) {
        int t = q.front();
        q.pop();

        seq[k++] = t;   // 拓扑序列
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0)    // 删边，终点入度-1，若为0，入对
                q.push(j);
        }
    }
}
int main()
{
    cin >> n >> m;

    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b);      // 插入a到b的边
        d[b]++;         // b的入度++
    }

    topsort();  // 拓扑排序

    // 从后往前累加
    for (int i = n - 1; ~i; --i) {
        int j = seq[i];
        f[j][j] = 1;    // 自身到自身

        for (int p = h[j]; ~p; p = ne[p])   // 累加上孩子的结果
            f[j] |= f[e[p]];
    }

    for (int i = 1; i <= n; ++i) cout << f[i].count() << endl;
    return 0;
}


// 或，使用数组模拟队列，而队列中的顺序即为拓扑序
#include <iostream>
#include <cstring>
#include <bitset>
#include <queue>
using namespace std;

const int N = 30010;
int n, m;
int h[N], e[N], ne[N], idx; // 邻接表
int d[N];           // 入度
bitset<N> f[N];
int q[N];   // 队列


void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void topsort() {
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; ++i) {  //入度为0的点入对列
        if (!d[i]) q[++tt] = i;
    }

    int k = 0;
    while (hh<=tt) {
        int t = q[hh++];

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0)    // 删边，终点入度-1，若为0，入对
                q[++tt] = j;
        }
    }
}
int main()
{
    cin >> n >> m;

    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b);      // 插入a到b的边
        d[b]++;         // b的入度++
    }

    topsort();  // 拓扑排序

    // 从后往前累加
    for (int i = n - 1; ~i; --i) {
        int j = q[i];   // 我们使用数组模拟队列，而队列中元素排列即为拓扑序
        f[j][j] = 1;    // 自身到自身

        for (int p = h[j]; ~p; p = ne[p])   // 累加上孩子的结果
            f[j] |= f[e[p]];
    }

    for (int i = 1; i <= n; ++i) cout << f[i].count() << endl;
    return 0;
}