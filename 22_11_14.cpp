


// 176. 装满的油箱

// 使用二元组（city,fuel)来表示每个状态，city为城市编号，fuel为剩余油量
// 用数组dist[city][fuel]来记录每个状态的最小花费
// 那么所求就是（start,0) 到（end,0)的最短距离
// 使用优先队列dijkstra来对每次的询问做计算

// 注意：这里我们每个状态有两类分支，
//      1）原地加一升油
//      2）前往下一个地点
// 为什么每次只加一升油，因为顶点的边可能很多，若一次将所有能到达其他地方的油量一下计算出来加入到堆中，会增加很多状态，堆的调整规模就会变大
// 其次，每次原地只加一升油也不会漏掉某个状态，油的上限也不会超过100，且编码也简单。

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 1010, M = 20010, C = 110;;
int n, m;
int e[M], ne[M], w[M], price[N], head[N], idx;
bool vis[N][C];
int dist[N][C];

struct node
{
    int dist, u, rest;
    bool operator<(const node& b) const {
        return dist > b.dist;
    }
};
void add(int x, int y, int z) {
    e[idx] = y, w[idx] = z, ne[idx] = head[x], head[x] = idx++;
}
int dijkstra(int st, int ed, int cap) {
    memset(vis, 0, sizeof vis);
    memset(dist, 0x3f, sizeof dist);

    priority_queue<node> q;
    q.push({ 0, st, 0 });        // 0距离，st点，剩下0个油
    dist[st][0] = 0;

    while (q.size()) {
        auto t = q.top(); q.pop();

        if (t.u == ed) return t.dist;
        if (vis[t.u][t.rest]) continue;;
        vis[t.u][t.rest] = true;


        if (t.rest < cap) {
            // 如果加一升油的新状态的花费还未小于该状态已知的花费的话
            if (dist[t.u][t.rest + 1] > t.dist + price[t.u]) {
                dist[t.u][t.rest + 1] = t.dist + price[t.u];
                q.push({ dist[t.u][t.rest + 1], t.u, t.rest + 1 });
            }
        }
        for (int i = head[t.u]; ~i; i = ne[i]) {
            int j = e[i];
            if (t.rest >= w[i]) {
                if (dist[j][t.rest - w[i]] > t.dist) {      // 此做法将加油和去往下一个地点分离，去往下一个地点不用消耗
                    dist[j][t.rest - w[i]] = t.dist;
                    q.push({ dist[j][t.rest - w[i]], j, t.rest - w[i] });
                }
            }
        }

    }
    return -1;

}
int main()
{
    cin >> n >> m;
    memset(head, -1, sizeof head);
    for (int i = 0; i < n; ++i)
        cin >> price[i];

    int x, y, z;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
        add(x, y, z); add(y, x, z);
    }
    int query;
    cin >> query;
    while (query--) {
        cin >> x >> y >> z;
        int t = dijkstra(y, z, x);
        if (t == -1)puts("impossible");
        else cout << t << endl;
    }
    return 0;
}



// 177. 噩梦

// 模拟bfs
// 鬼先走，一秒可以扩展两步，所以bfs两层
// 人再走，男人一秒三步，所以bfs三层，女人一秒一步，bfs一层


// !!!注意：在鬼bfs过程中，如果某个人所以bfs的结果都出现在鬼的范围内，那么即在鬼扩展中，人还没来得及走时，就被抓到了，false
//          有多组数据，记得清空队列以及其他状态

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int N = 810;
int n, m;
char s[N][N];
int dist[N][N];
const int dx[]{ -1,0,1,0 }, dy[]{ 0,1,0,-1 };
queue<PII> qboy,qgirl;
int boy_cnt, girl_cnt;
PII encounter;
bool vaild(int x, int y) {
    return x >= 0 && y >= 0 && x < n&& y < m;
}

bool bfs_peop() {
    // 男孩
    int time = 3;
    while (time--) {
        int size = qboy.size();
        while (size--) {
            auto t = qboy.front(); qboy.pop();
            for (int i = 0; i < 4; ++i) {
                int x = t.first + dx[i];
                int y = t.second + dy[i];

                if(!vaild(x,y) || s[x][y]=='X' || s[x][y]=='Z' || s[x][y]=='M') continue;
                dist[x][y] = dist[t.first][t.second] + 1;

                if (s[x][y] == 'G') {
                    encounter = { x,y };
                    return true;
                }
                s[x][y] = 'M';
                ++boy_cnt;
                qboy.push({ x,y });
            }
        }
    }
    // 女孩
    int size = qgirl.size();
    while (size--) {
        auto t = qgirl.front(); qgirl.pop();
        for (int i = 0; i < 4; ++i) {
            int x = t.first + dx[i];
            int y = t.second + dy[i];

            if (!vaild(x, y) || s[x][y] == 'X' || s[x][y] == 'Z' || s[x][y] == 'G') continue;
            dist[x][y] = dist[t.first][t.second] + 3;
            if (s[x][y] == 'M') {
                encounter = { x,y };
                return true;
            }
            s[x][y] = 'G';
            ++girl_cnt;
            qgirl.push({ x,y });
        }
    }
    return false;
}

bool bfs_ghost() {
    memset(dist, 0x3f, sizeof dist);
    while (qboy.size()) qboy.pop();     // 注意清空
    while (qgirl.size()) qgirl.pop();

    queue<PII> q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (s[i][j] == 'Z') q.push({ i,j });
            else if (s[i][j] == 'M' || s[i][j]=='G') {
                dist[i][j] = 0;
                if (s[i][j] == 'M')
                    qboy.push({ i,j });
                else
                    qgirl.push({ i,j });
            }
    boy_cnt = girl_cnt = 1;

    while (q.size()) {
        int time = 2;
        while (time--) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto t = q.front(); q.pop();

                for (int j = 0; j < 4; ++j) {
                    int x = t.first + dx[j];
                    int y = t.second + dy[j];
                    if (!vaild(x, y) || s[x][y] == 'Z') continue;

                    if (s[x][y] == 'M')         // 若途中人的所有可能出现的地点，都在鬼的范围里，false
                       if (--boy_cnt == 0) return false; 
                    if (s[x][y] == 'G')
                        if (--girl_cnt == 0) return false;

                    s[x][y] = 'Z';
                    q.push({ x,y });

                }
            }
        }
        if (bfs_peop()) return true;
    }

    return false;
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> s[i];
        if (bfs_ghost()) cout << (dist[encounter.first][encounter.second]+2) / 3 << endl;
        else puts("-1");
    }
    return 0;
}


// 进一步省略鬼的bfs过程,根据题目的鬼的曼哈顿距离可以直接判断是否处于鬼的范围

#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 810;

int n, m;
char g[N][N];
int st[N][N];
PII ghost[2];

bool check(int x, int y, int step)
{
    if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] == 'X') return false;

    for (int i = 0; i < 2; i++)
        if (abs(x - ghost[i].first) + abs(y - ghost[i].second) <= step * 2)
            return false;

    return true;
}

int bfs()
{
    int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, 1, 0, -1 };

    memset(st, 0, sizeof st);

    int cnt = 0;
    PII boy, girl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == 'M') boy = { i, j };
            else if (g[i][j] == 'G') girl = { i, j };
            else if (g[i][j] == 'Z') ghost[cnt++] = { i, j };

    queue<PII> qb, qg;
    qb.push(boy);
    qg.push(girl);

    int step = 0;
    while (qb.size() || qg.size())
    {
        step++;
        for (int i = 0; i < 3; i++)
            for (int j = 0, len = qb.size(); j < len; j++)
            {
                auto t = qb.front();
                qb.pop();
                int x = t.first, y = t.second;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; k++)
                {
                    int a = x + dx[k], b = y + dy[k];
                    if (check(a, b, step))
                    {
                        if (st[a][b] == 2)
                        {
                            return step;
                        }
                        if (!st[a][b])
                        {
                            st[a][b] = 1;
                            qb.push({ a, b });
                        }
                    }
                }
            }

        for (int i = 0; i < 1; i++)
            for (int j = 0, len = qg.size(); j < len; j++)
            {
                auto t = qg.front();
                qg.pop();

                int x = t.first, y = t.second;
                if (!check(x, y, step)) continue;
                for (int k = 0; k < 4; k++)
                {
                    int a = x + dx[k], b = y + dy[k];
                    if (check(a, b, step))
                    {
                        if (st[a][b] == 1)
                        {
                            return step;
                        }
                        if (!st[a][b])
                        {
                            st[a][b] = 2;
                            qg.push({ a, b });
                        }
                    }
                }
            }
    }

    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%s", g[i]);

        printf("%d\n", bfs());
    }

    return 0;
}
