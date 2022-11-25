
// 191. 天气预报

// 超时
#include <iostream>
#include <cstring>
#include <bitset>
#include <algorithm>

using namespace std;
int g[4][4][366];
int dist[4][4], bdist[366][4][4];     // 距离7天不下雨还有多久

int n;

const int dx[4]{ -1,0,1,0 }, dy[4]{ 0,1,0,-1 };

bool vaild(int x, int y, int i, int j) {
    return i >= x && j >= y && i < x + 2 && j < y + 2;
}
// 第u天时，当雨来到了(x,y)位置时，是否可以满足当天的需求
bool isCover(int u, int x, int y) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            if (vaild(x, y, i, j)) {     // 下雨
                dist[i][j] = 0;
                if (g[i][j][u] == 1) return false;      // 此区域当天不需要下雨，却下了，false
            } else {        // 不下雨
                if (++dist[i][j] >= 7) return false;
            }

        }
    return true;

}
bool dfs(int u, int x, int y) {
    if (x < 0 || y < 0 || x >= 3 || y >= 3) return false;
    if (u == n) return true;

    memcpy(bdist[u], dist, sizeof dist);
    bool success = isCover(u, x, y);

    if (!success) {
        memcpy(dist, bdist[u], sizeof dist);
        return false;
    }


    // 四个方向移动
    for (int i = 0; i < 4; ++i) {
        // 移动一步
        if (dfs(u + 1, x + dx[i], y + dy[i])) return true;

        // 移动两步
        if (dfs(u + 1, x + 2 * dx[i], y + 2 * dy[i])) return true;
    }
    // 云当天不移动

    success = dfs(u + 1, x, y);
    if (success) return true;
    memcpy(dist, bdist[u], sizeof dist);
    return false;
}
int main()
{
    while (cin >> n, n) {
        memset(dist, 0, sizeof dist);
        int t;
        for (int i = 0; i < n; ++i)
            for (int x = 0; x < 4; ++x)
                for (int y = 0; y < 4; ++y)
                    cin >> g[x][y][i];
        cout << dfs(0, 1, 1) << endl;
    }
    return 0;
}



// 上法超时的主要原因时没有做优化以及剪枝
// 我们可以发现，对于每一天整个图的可行性取决于4个角的可行性+当天的事件
// 对于云，用其左上角坐标来标识（x,y),4个角的连续没下雨天数,si
// 所以每个状态可以用（第几天，x,y,s1,s2,s3,s4)来表示，在搜索过程中一旦发现搜过，就返回false


#include <iostream>
#include <cstring>
#include <bitset>
#include <algorithm>

using namespace std;
int g[4][4][366];
int st[366][3][3][7][7][7][7];  // 记录某个状态来过没

int n;

const int dx[]{ -1,0,1,0,0 }, dy[]{ 0,1,0,-1,0 };

bool dfs(int u, int x, int y, int s1, int s2, int s3, int s4) {
    if (x < 0 || y < 0 || x >= 3 || y >= 3) return false;
    if (u == n) return true;
    if (st[u][x][y][s1][s2][s3][s4]) return false;
    st[u][x][y][s1][s2][s3][s4] = true;     // 标记来过

    if (x == 0 && y == 0) s1 = 0;
    else ++s1;
    if (x == 0 && y == 2) s2 = 0;
    else ++s2;
    if (x == 2 && y == 0) s3 = 0;
    else ++s3;
    if (x == 2 && y == 2) s4 = 0;
    else ++s4;
    if (s1 >= 7 || s2 >= 7 || s3 >= 7 || s4 >= 7) return false;
    if (g[x][y][u] || g[x + 1][y][u] || g[x][y + 1][u] || g[x + 1][y + 1][u]) return false;

    for (int i = 0; i < 5; ++i) {
        // 移动一步
        if (dfs(u + 1, x + dx[i], y + dy[i], s1, s2, s3, s4))
            return true;

        // 移动两步
        if (dfs(u + 1, x + 2 * dx[i], y + 2 * dy[i], s1, s2, s3, s4))
            return true;

    }
    return false;
}
int main()
{
    while (cin >> n, n) {
        memset(st, 0, sizeof st);
        int t;
        for (int i = 0; i < n; ++i)
            for (int x = 0; x < 4; ++x)
                for (int y = 0; y < 4; ++y)
                    cin >> g[x][y][i];
        cout << dfs(0, 1, 1, 0, 0, 0, 0) << endl;
    }
    return 0;
}

// 或也可以用宽搜过，不过与上面的深搜，记录的状态略有不同，上面中的4个角的状态为上一次的状态，下面的则为当天更新后的状态
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 366;

int n;
bool st[N][3][3][7][7][7][7];
struct Node
{
    int day, x, y, s0, s1, s2, s3;
};
int state[N][4][4];

int bfs()
{
    if (state[1][1][1] || state[1][1][2] || state[1][2][1] || state[1][2][2]) return 0;

    queue<Node> q;
    memset(st, 0, sizeof st);
    q.push({ 1, 1, 1, 1, 1, 1, 1 });
    st[1][1][1][1][1][1][1] = true;

    int dx[] = { -1, 0, 1, 0, 0 }, dy[] = { 0, 1, 0, -1, 0 };

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        if (t.day == n) return 1;

        for (int i = 0; i < 5; i++)
            for (int j = 1; j <= 2; j++)
            {
                int x = t.x + dx[i] * j, y = t.y + dy[i] * j;
                if (x < 0 || x >= 3 || y < 0 || y >= 3) continue;

                auto& s = state[t.day + 1];
                if (s[x][y] || s[x][y + 1] || s[x + 1][y] || s[x + 1][y + 1]) continue;

                int s0 = t.s0, s1 = t.s1, s2 = t.s2, s3 = t.s3;
                if (!x && !y) s0 = 0;
                else if (++s0 == 7) continue;
                if (!x && y == 2) s1 = 0;
                else if (++s1 == 7) continue;
                if (x == 2 && !y) s2 = 0;
                else if (++s2 == 7) continue;
                if (x == 2 && y == 2) s3 = 0;
                else if (++s3 == 7) continue;

                if (st[t.day + 1][x][y][s0][s1][s2][s3]) continue;

                st[t.day + 1][x][y][s0][s1][s2][s3] = true;
                q.push({ t.day + 1, x, y, s0, s1, s2, s3 });
            }
    }

    return 0;
}

int main()
{
    while (cin >> n, n)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++)
                    cin >> state[i][j][k];

        cout << bfs() << endl;
    }

    return 0;
}



// 192. 立体推箱子2

/*
本题是立体推箱子的升级版，数据更大了，但是其实代码难度上并没有加强。

首先横纵坐标的数据范围都有10^9，因此不可能直接bfs求最短路。

但是相比于立体推箱子那题，本题没有那么多的障碍，所有位置都是硬地，因此对于方案就少了很多可变性，我们可以来寻找一些规律。

求的是最小步数，那么什么时候能走的步数更少但是走的距离更长，可以发现只有横着横向滚动和竖着竖向滚动时，两步就能走三格，
这是最快的。

我们就可以从这个方向来入手，从横向来看(横竖都一样)，从立着开始滚，滚两步就能走过三格，且两步之后还是立着的。
因此我们可以发现，图中某些坐标(x, y)，如果x % 3 == 0, y % 3 == 0，那么从(x, y)到终点(0, 0)的最小步数是可以计算的。
就是x / 3 * 2 + y / 3 * 2。

可以发现，所有横纵坐标模3为0，且是立着的状态到终点的最小步数我们能直接计算得出，对于这些状态假设叫做合适点，
那么我们只要让起点状态用最小步数走到合适点上，那么从起点到终点的距离就可以相加得出。

然后由于合适点是横纵坐标每过3就会有一个(可自行画图)，因此在起点的周围一定都很多合适点，我们只需要用bfs求出起点
到其中一个最近的合适点的最小步数即可。但是起点的横纵坐标可能是10^9，我们没法开这个大的二维数组，一种方法是用map来求。
另一种方法就是缩小范围，由于起点一定被划分在一个4 * 4的方块中，且这个方块的四个角都一定是合适点，因此我们可以将
起点映射到一个4 * 4的矩阵中，这样可以求出起点到最近的一个合适点的最小步数，然后再通过相对关系将合适点的坐标还原到
原坐标系中，再计算一下合适点和终点的最小步数即可。

注意：由于立方体在移动到合适点上的过程中可能超出4 * 4的矩阵，因此这里可以开到7 * 7。刚好包含更外面一层的合适点。

具体细节可看代码
*/



#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int, int> PII;
const int N = 7;

struct Node //结构体表示每个状态，用于放入队列
{
    int x, y, dir;
};

char op[2]; //表示长方体的初始化状态
int tx, ty; //表示起点坐标
//d[x][y][0] 表示长方体从起点走到立在(x, y)的最短距离
//d[x][y][1] 表示长方体从起点走到横着躺在(x, y)的最短距离(左半边在(x, y))
//d[x][y][2] 表示长方体从起点走到竖着躺在(x, y)的最短距离(上半边在(x, y))
int d[N][N][3];

//下标 0, 1, 2, 3 分别对应方向 上、下、左、右。
int next_x[3][4] = { {-2, 1, 0, 0}, {-1, 1, 0, 0}, {-1, 2, 0, 0} }; //next_x[i][j] 表示长方体从i状态向j方向滚动后x的变化
int next_y[3][4] = { {0, 0, -2, 1}, {0, 0, -1, 2}, {0, 0, -1, 1} }; //next_y[i][j] 表示长方体从i状态向j方向滚动后y的变化
int next_dir[3][4] = { {2, 2, 1, 1}, {1, 1, 0, 0}, {0, 0, 2, 2} }; //next_st[i][j] 表示长方体从i状态向j方向滚动后dir的新值

int bfs(int sx, int sy, int dir) {
    memset(d, -1, sizeof d);
    d[sx][sy][dir] = 0;

    queue<Node> q;
    q.push({ sx,sy,dir });

    int res = 3e9;
    while (q.size()) {      // 只会搜索有限的几个，时间复杂度可以认为O(1)
        auto t = q.front(); q.pop();

        int x = t.x, y = t.y, dir = t.dir;
        if (x % 3 == 0 && y % 3 == 0 && dir == 0) { // 横纵坐标能模3，且是立着的，即找到了合适点
            int nx = tx / 3 * 3 + x - 3, ny = ty / 3 * 3 + y - 3;    // 将7 * 7的矩阵中的坐标变回原坐标系中的坐标
            int xd = nx / 3 * 2, yd = ny / 3 * 2;   // 计算求出合适点到终点的横方向和竖方向上需要移动的步数
            if (xd < 0 || yd < 0) continue;     //如果步数是负的，说明不合法，跳过
            
            res = min(res, d[x][y][dir] + xd + yd);     // 选出合适点的最小值
        }
        for (int i = 0; i < 4; ++i) {
            int a = x + next_x[dir][i];
            int b = y + next_y[dir][i];
            int new_dir = next_dir[dir][i];
            if(a<0 || a>=N || b<0 || b>=N) continue;

            if (d[a][b][new_dir] == -1) {
                d[a][b][new_dir] = d[x][y][dir] + 1;
                q.push({ a,b,new_dir });
            }
        }
    }
    return res;
}

int main()
{
    while (cin >> op >> tx >> ty) {
        int dir;
        if (op[0] == 'U') dir = 0;
        else if (op[0] == 'H') dir = 1;
        else dir = 2;

        int sx = tx % 3 + 3, sy = ty % 3 + 3;   // 将起始位置映射到一个7*7矩阵中
        cout << bfs(sx, sy, dir) << endl;
    }
    return 0;

}
