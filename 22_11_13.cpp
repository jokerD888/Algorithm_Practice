
// 175. 电路维修


// 直接bfs暴力搜索，将每个顶点看作点，但由于每个搜索分支互不干扰，所以需要O(N*N*M*M)导致4个测试点超时

#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> PII;
const int N = 510;
int n, m;
char s[N][N];
int dis[N][N];
const int dx[4]{ -1,-1,1,1 }, dy[]{ -1,1,1,-1 };
const int da[4]{ -1,-1,0,0 }, db[]{ -1,0,0,-1 };

bool vaild(int x, int y) {
    return x >= 0 && y >= 0 && x <= n && y <= m;
}
bool bfs() {
    queue<PII> q;
    q.push({ 0,0 });
    dis[0][0] = 0;
    while (q.size()) {
        auto t = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {       // 方向：左上 \，右上/，右下\，左下/
            int x = t.first + dx[i];        // 点，即格子的四个定点
            int y = t.second + dy[i];
            if (!vaild(x, y)) continue;       // 要去的位置非法或以走过，跳过
            int a = t.first + da[i];    // 要到达点（x,y)需要经过的格子（a,b)
            int b = t.second + db[i];

            if (i & 1) {      // i==1 || i==3  /
                if (s[a][b] == '/') {       // 不用旋转
                    if (dis[x][y] > dis[t.first][t.second]) {
                        dis[x][y] = dis[t.first][t.second];
                        q.push({ x,y });
                    }
                } else {        // 需要旋转
                    if (dis[x][y] > dis[t.first][t.second] + 1) {
                        dis[x][y] = dis[t.first][t.second] + 1;
                        q.push({ x,y });
                    }
                }
            } else {

                if (s[a][b] == '\\') {       // 不用旋转
                    if (dis[x][y] > dis[t.first][t.second]) {
                        dis[x][y] = dis[t.first][t.second];
                        q.push({ x,y });
                    }
                } else {        // 需要旋转
                    if (dis[x][y] > dis[t.first][t.second] + 1) {
                        dis[x][y] = dis[t.first][t.second] + 1;
                        q.push({ x,y });
                    }
                }
            }
        }
    }
    return dis[n][m] != 0x3f3f3f3f;


}
int main()
{
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> s[i];
        memset(dis, 0x3f, sizeof dis);
        if (bfs())cout << dis[n][m] << endl;
        else puts("NO SOLUTION");
    }
    return 0;
}

// 上法之所以超时，是因为bfs过程中不满足“单调性”，即每一次向外层搜索时不一定会使得步数+1，所以上法的规模达到了O(N^2 * M^2)
// 基本的bfs搜索中，每次沿着分支扩展都记为“一步”，但上法中可能记为“0步”，所以破坏了队列中的单调性”
// 根据基本的bfs满足的“两段性”和“单调性”，从而我们可以得出每个状态在第一次被访问时并入队时，计算出的步数即为所求的最短性，但上法明显不满足


// 法一：双段队列bfs

// 将顶点看为点，那么这就是一张边权要么是0，要么是1的无向图，这样的图，可以使用双端队列广搜来计算
// 算法的整体框架与一般的广搜类型，只是在每个节点上沿分支扩展时稍作计算。
// 不同点有：1）如果边权是0，则把沿该分支到达新节点从对头入队，如果这些分支边权为1，就像一般广搜一样，队尾入队
//          2）每个节点虽然可能被更新（入队）多次，但它第一次扩展（出队）时，就能得到“最短距离”，之后再被取出可以直接忽略
#include <iostream>
#include <algorithm>
#include <string.h>
#include <deque>
using namespace std;

typedef pair<int, int> PII;

const int N = 510;
int n, m;
char s[N][N];
int dist[N][N];
bool vis[N][N];

const int dx[4]{ -1,-1,1,1 }, dy[]{ -1,1,1,-1 };
const int da[4]{ -1,-1,0,0 }, db[]{ -1,0,0,-1 };

bool vaild(int x, int y) {
    return x >= 0 && y >= 0 && x <= n && y <= m;
}
bool bfs() {
    deque<PII> q;
    q.push_back({ 0,0 });
    dist[0][0] = 0;

    while (q.size()) {
        auto t = q.front(); q.pop_front();

        if (t.first == n && t.second == m)
            return true;
        if (vis[t.first][t.second]) continue;       // 2）
        vis[t.first][t.second] = true;


        for (int i = 0; i < 4; ++i) {
            int x = t.first + dx[i], y = t.second + dy[i];
            int a = t.first + da[i], b = t.second + db[i];

            if (!vaild(x, y)) continue;
            char ss[3] = "\\/";

            int j = i & 1;

            int w = s[a][b] == ss[j] ? 0 : 1;
            int d = dist[t.first][t.second] + w;
            if (d < dist[x][y]) {           // 1）
                dist[x][y] = d;
                if (w) q.push_back({ x,y });
                else q.push_front({ x,y });
            }
            // 错误，需要增加if的判断，若不加if,dist[x][y]的值只依靠于最后一次对其的更新
            //if (s[a][b] == ss[j]) {     // 不用旋转,权值为0
            //    q.push_front({ x,y });
            //    dist[x][y] = dist[t.first][t.second];
            //} else {        // 用旋转,权值为1
            //    q.push_back({ x,y });
            //    dist[x][y] = dist[t.first][t.second] + 1;
            //}

        }
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
        memset(dist, 0x3f, sizeof(dist));
        memset(vis, false, sizeof(vis));
        if (bfs()) cout << dist[n][m] << endl;
        else puts("NO SOLUTION");
    }
    return 0;
}



// 优先队列dijkstra BFS
#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
#include <deque>
using namespace std;

typedef pair<int, int> PII;

const int N = 510;
int n, m;
char s[N][N];
int dist[N][N];
bool vis[N][N];
const int dx[]{ -1,-1,1,1 }, dy[]{ -1,1,1,-1 };
const int da[]{ -1,-1,0,0 }, db[]{ -1,0,0,-1 };

char ss[5] = "\\/\\/";

bool vaild(int x, int y) {
    return x >= 0 && y >= 0 && x <= n && y <= m;
}
bool bfs() {
    auto f = [](const PII& a, const PII& b) {return dist[a.first][a.second] >= dist[b.first][b.second]; };
    priority_queue<PII, vector<PII>, decltype(f)> q(f);
    q.push({ 0,0 });
    dist[0][0] = 0;

    while (q.size()) {
        auto t = q.top(); q.pop();
      
        if (vis[t.first][t.second]) continue;       
        vis[t.first][t.second] = true;


        for (int i = 0; i < 4; ++i) {
            int x = t.first + dx[i], y = t.second + dy[i];
            int a = t.first + da[i], b = t.second + db[i];

            if (!vaild(x, y)) continue;

            int w = s[a][b] == ss[i] ? 0 : 1;
            int d = dist[t.first][t.second] + w;
            if (d < dist[x][y]) {          
                dist[x][y] = d;
                q.push({ x,y });
            }
        }
    }
    return dist[n][m]!=0x3f3f3f3f;
}
int main()
{
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> s[i];
        memset(dist, 0x3f, sizeof(dist));
        memset(vis, false, sizeof(vis));
        if (bfs()) cout << dist[n][m] << endl;
        else puts("NO SOLUTION");
    }
    return 0;
}
