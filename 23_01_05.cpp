
// 342. 道路与航线

// 如果只把双向边(也就是题目中的“道路”)添加到图里，那么会形成若干个连通块。
// 若把每个连通块整体看作一个“点”，再把单向边(也就是题目中的“航线”)添加到图里，会得到一张有向无环图。
// 在有向无环图上，无论边权正负，都可以按照拓扑序进行扫描，在线性时间内求出单源最短路。
// 这启发我们用拓扑序的框架处理整个图, 但在双向边构成的每个连通块内部使用堆优化的 Diikstra 算法快速计算该块内的最短路信息。
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
const int N = 25010, M = 150010, INF = 0x3f3f3f3f;
int head[N], ver[M], Next[M], edge[M], tot;
int dist[N];
bool st[N];

int n, mr, mp, s;
int id[N], bcnt;
int deg[N];
vector<int> block[N];
queue<int> q;

void add(int x, int y, int z) {
    ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;
}
void dfs(int u) {
    block[bcnt].push_back(u);
    id[u] = bcnt;

    for (int i = head[u]; i; i = Next[i]) {
        int y = ver[i];
        if (!id[y]) dfs(y);
    }
}

void dijkstra(int bid) {
    priority_queue<PII> heap;
    // 取出该连通块所有点，入堆
    for (auto u : block[bid]) {
        heap.push({ -dist[u],u });
    }

    while (heap.size()) {
        auto t = heap.top(); heap.pop();
        int u = t.second;

        if (st[u]) continue;
        st[u] = true;

        for (int i = head[u]; i; i = Next[i]) {
            int y = ver[i];
            if (dist[y] > dist[u] + edge[i]) {
                dist[y] = dist[u] + edge[i];
                if (id[y] == bid) heap.push({ -dist[y],y });
            }

            if (id[y] != bid && --deg[id[y]] == 0) q.push(id[y]);
        }
    }
}
void topoSort() {
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;

    // 所有入度为0连通块入队
    for (int i = 1; i <= bcnt; ++i) {
        if (!deg[i]) q.push(i);
    }

    while (q.size()) {
        int t = q.front(); q.pop();
        dijkstra(t);
    }
}
int main() {
    cin >> n >> mr >> mp >> s;
    for (int i = 0; i < mr; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
        add(y, x, z);
    }

    // 建立所有连通块
    for (int i = 1; i <= n; ++i) {
        if (!id[i]) {
            ++bcnt;
            dfs(i);
        }
    }

    // 再连通块之间键边
    for (int i = 0; i < mp; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
        deg[id[y]]++;
    }

    topoSort();

    for (int i = 1; i <= n; ++i) {
        if (dist[i] > INF / 2) puts("NO PATH");
        else cout << dist[i] << endl;
    }
    return 0;
}