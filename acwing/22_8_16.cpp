

// 172. 立体推箱子

// BFS
// BFS搜寻模型。难点在每一步有多种状态，且有多种限制
// 我们State结构体表示箱子的状态，x,y表坐标，lie表箱子的状态，0立，1横躺，2竖躺
// 其次是箱子的3种状态，向外走也有不同的结果，用一状态变化数字预先计算d[3][4][3]，3种状态，4个方向，3个变量

//#include <iostream>
//#include <algorithm>
//#include <cstring>
//#include <queue>
//using namespace std;
//
//const int N = 510;
//
//struct State {
//    int x, y, lie;      // lie:0为立着；1为横着，x,y坐标就是左边区域；2为竖着躺，x,y坐标就是上边区域
//};
//
//int n, m;
//char g[N][N];
//int dist[N][N][3];
//
//bool check(int x, int y) {
//    // 不能越界，且不能触到禁地
//    if (x < 0 || y < 0 || x >= n || y >= m) return false;
//    return g[x][y]!='#';
//}
//
//int bfs(State start, State end) {
//    memset(dist, -1, sizeof dist);
//    dist[start.x][start.y][start.lie] = 0;
//    queue<State> qu;
//    qu.push(start);
//
//    // 3中状态，4个方向，3个变量
//    int d[3][4][3] = {
//      // 上  右  下 左
//        {{-2,0,2},{0,1,1},{1,0,2},{0,-2,1}},      // 0 立着
//        {{-1,0,1},{0,2,0},{1,0,1},{0,-1,0}},      // 1 横着躺
//        {{-1,0,0},{0,1,2},{2,0,0},{0,-1,2}}       // 2 竖着躺
//    };
//
//    while (qu.size()) {
//        auto t = qu.front();
//        qu.pop();
//
//        // 扩展t
//        for (int i = 0; i < 4; ++i) {
//            State next;
//            next = { t.x + d[t.lie][i][0],t.y + d[t.lie][i][1],d[t.lie][i][2] };
//
//            int x = next.x, y = next.y;
//            
//            if(!check(x,y)) continue;
//            if (next.lie == 0 && g[x][y] == 'E') continue;
//            if (next.lie == 1 && !check(x, y + 1)) continue;
//            if (next.lie == 2 && !check(x + 1, y)) continue;
//
//            if (dist[x][y][next.lie] == -1) {       // 没搜过
//                dist[x][y][next.lie] = dist[t.x][t.y][t.lie] + 1;
//                qu.push(next);
//            }
//        }
//
//    }
//
//    return dist[end.x][end.y][end.lie];
//}
//int main()
//{
//    while (cin >> n >> m, n || m) {
//        for (int i = 0; i < n; ++i) cin >> g[i];
//
//        State start = { -1 }, end;
//        for (int i = 0; i < n; ++i)
//            for (int j = 0; j < m; ++j) {
//                if (g[i][j] == 'X' && start.x == -1) {
//                    if (g[i][j + 1] == 'X') start = { i,j,1 };
//                    else if (g[i + 1][j] == 'X')start = { i,j,2 };
//                    else start = { i,j,0 };
//                } else if (g[i][j] == 'O') {
//                    end = { i,j,0 };
//                }
//            }
//        int res = bfs(start, end);
//        if (res == -1) puts("Impossible");
//        else cout << res << endl;
//    }
//    return 0;
//}



// 173. 矩阵距离
// 本质是多源最短路问题
// bfs，
// 暴力版本无非就是枚举N*M个bfs的起点，根据曼哈顿距离定义，其实就是最短距离，所有只要先搜到1就可返回了
// N=1000 时间O(N^4)必定是要超时，代码如下

//#include <iostream>
//#include <queue>
//#include <cstring>
//using namespace std;
//
//const int N = 1010;
//char g[N][N];
//int res[N][N];
//bool vis[N][N];
//int n, m;
//
//int dire[]{ -1,0,1,0,-1 };
//
//bool check(int x, int y) {
//    if (x < 0 || y < 0 || x >= n || y >= m) return false;
//    return true;
//}
//int bfs(int x, int y) {
//    if (g[x][y] == '1') return 0;
//    memset(vis, false, sizeof vis);
//    queue<pair<int, int>> qu;
//    qu.push({ x,y });
//    vis[x][y] = true;
//
//    while (qu.size()) {
//        auto t = qu.front();
//        qu.pop();
//       
//
//        for (int i = 0; i < 4; ++i) {
//            int xx = t.first + dire[i], yy =t.second + dire[i + 1];
//            if (check(xx, yy) && !vis[xx][yy]) {
//                if (g[xx][yy] == '1') {
//                    return abs(x - xx) + abs(y - yy);
//                } else {
//                    qu.push({ xx,yy });
//                    vis[xx][yy] = true;
//                }
//            }
//        }
//    }
//    return -1;
//
//}
//
//int main()
//{
//    cin >> n >> m;
//    for (int i = 0; i < n; ++i) cin >> g[i];
//    
//
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j) cout << bfs(i, j) << ' ';
//        cout << endl;
//    }
//    return 0;
//}

// 但若返过来向呢，我们从终点进行扩散，即从值是1的点，往外扩散，遇到0的点就记上此时走过的距离即可
// 时间为O(N*N)，因为每个点最多只会被搜过一次

//#include <iostream>
//#include <queue>
//#include <cstring>
//using namespace std;
//
//const int N = 1010;
//char g[N][N];
//int dist[N][N];
//bool vis[N][N];
//int n, m;
//
//int dire[]{ -1,0,1,0,-1 };
//queue<pair<int, int>> qu;
//bool check(int x, int y) {
//    if (x < 0 || y < 0 || x >= n || y >= m) return false;
//    return true;
//}
//void bfs() {
//    int cnt = 0, len = 0;
//    while (qu.size()) {
//        cnt = qu.size();
//        ++len;
//        while (cnt--) {         // 每次遍历上一次循环入队的个数
//            auto t = qu.front();
//            qu.pop();
//
//            for (int i = 0; i < 4; ++i) {
//                int xx = t.first + dire[i], yy = t.second + dire[i + 1];
//                if (check(xx, yy) && !vis[xx][yy] && g[xx][yy] != '1') {
//                    dist[xx][yy] = len;
//                    qu.push({ xx,yy });
//                    vis[xx][yy] = true;
//                }
//            }
//        }
//
//    }
//
//
//}
//
//int main()
//{
//    cin >> n >> m;
//    for (int i = 0; i < n; ++i) cin >> g[i];
//
//    memset(vis, false, sizeof vis);
//    for (int i = 0; i < n; ++i)
//        for (int j = 0; j < m; ++j)     // 先将终点全部入队
//            if (g[i][j] == '1') qu.push({ i,j });
//
//    bfs();
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j)
//            cout << dist[i][j] << ' ';
//        cout << endl;
//    }
//    return 0;
//}
//
//
//// 又或者，上法我们是用扩展的层数来标记每一个被扩展的位置的，但也可以通过使他扩展的位置上的值加1来标记
//// 且，我们发现，res数组可以完全替换到vis数组，这样又可以省掉N*N的空间
//
//#include <iostream>
//#include <queue>
//#include <cstring>
//using namespace std;
//
//const int N = 1010;
//char g[N][N];
//int dist[N][N];
//int n, m;
//
//int dire[]{ -1,0,1,0,-1 };
//queue<pair<int, int>> qu;
//bool check(int x, int y) {
//    if (x < 0 || y < 0 || x >= n || y >= m) return false;
//    return true;
//}
//void bfs() {
//
//    while (qu.size()) {
//        auto t = qu.front();
//        qu.pop();
//        int x = t.first, y = t.second;
//
//        for (int i = 0; i < 4; ++i) {
//            int xx = t.first + dire[i], yy = t.second + dire[i + 1];
//            if (check(xx, yy) && dist[xx][yy]==-1 && g[xx][yy] != '1') {
//                dist[xx][yy] = dist[x][y] + 1;
//                qu.push({ xx,yy });
//            }
//        }
//    }
//}
//
//int main()
//{
//    cin >> n >> m;
//    for (int i = 0; i < n; ++i) cin >> g[i];
//    memset(dist, -1, sizeof dist);
//    for (int i = 0; i < n; ++i)
//        for (int j = 0; j < m; ++j)     // 先将终点全部入队
//            if (g[i][j] == '1') {
//                qu.push({ i,j });
//                dist[i][j] = 0;
//            }
//
//
//    bfs();
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j)
//            cout << dist[i][j] << ' ';
//        cout << endl;
//    }
//    return 0;
//}
//
//
//// 上面的两个类似的解法可以认为是dijkstra算法的特列
//// dijkstra算法是每次从堆中选出离原点最近的点进行扩展，我们本题的队列，每次也是选出离原点最近的点进行扩展，因权边为1，没有负边。





// 174. 推箱子

// 本题思路并不赋值，属于宽搜问题。麻烦的是状态变量比较多；
// 要求人推箱子到指定地点。人和箱子两个变量若一起看，比较困难，我们先不管人，那就转为了箱子到终点的最短路问题；
// 而箱子需要人推动，所以我们把“箱子与旁边的人”这个合体进行bfs;而人到箱子旁边又是一个bfs
// 这是一个双重BFS 算法。从整体上看，算法在对每次箱子移动后的“箱子与旁边的人”这个合体进行 BFS。
// 而在这个 BFS 的每一次状态扩展时，我们再用“对人进行的另一个 BFS”求出人在两个位置之间移动的最少步数。
// 整体思路就是bfs套bfs。对于每一个位置（x,y)都有4种状态dir,含义：那个方向到的这个位置。我们设0，1，2，3分别表示下，上，右，左
// 本题还要求输出具体的路径方案，我们可以用一些额外的数组记录每个状态的箱子每个状态的人是从上一步的哪个状态来的。求出最优解后，我们可以从向前逆推得出运动轨迹
// 其中本题共有4种限制：
// 1）箱子移动次数最少。这个bfs本身就可一保证
// 2） 在保证 1 的前提下，人的移动次数最少。这个我们会用pair<箱子的移动次数，人的移动次数>本身的小于运算符来进行比较更新
// 3）在保证 1, 2 的前提下，箱子按照 N、S、W、E 的顺序优先选择移动方向 。3和4的话，只要我们枚举箱子和人方向按照上，下，左，右即可保证
// 4) 在保证 1, 2, 3 的前提下，人按照 n、s、w、e 的顺序优先选择移动方向
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

const int N = 25;

struct Node
{
    int x, y, dir;
};

int n, m;
char g[N][N];   // 存储游戏地图
Node pre[N][N][4];  // 表示箱子在(x, y)，上一个格子在i方向上的状态，即上一个状态是(x + dx[i], y + dy[i])
vector<int> path[N][N][4];  // path[j][k][i] 表示人从推(j,k,i)的上一个状态的位置，走到推(j,k,i)这个状态的位置的行走路径
bool st[N][N][4], used[N][N];   // BFS的判重数组，为了防止BFS遍历相同状态
PII dist[N][N][4];  // dist[j][k][i]是表示从初始状态到达j,k,i状态所需要的箱子最短路程和人行走最短路程
int dx[4] = { 1, -1, 0, 0 }, dy[4] = { 0, 0, 1, -1 };  // 依次表示下、上、右、左四个方向,这里与限制方向相反主要是为了编码的简洁，因为后续有很多地方要表示上一位置所处的方向
int pre_man[N][N];  // pre_man[x][y]表示人从哪个方向走到(x, y)，如果pre_man[x][y] = i, 那么上一个状态是(x - dx[i], y - dy[i])

bool check(int x, int y)    // 判断(x, y)是否在地图内，且是空地
{
    return x >= 0 && x < n && y >= 0 && y < m && g[x][y] != '#';
}


// 求人从start走到end，中间不经过box的最短路径，行走序列保存在seq中，主要行走序列不包括终点
int bfs_man(PII start, PII end, PII box, vector<int>& seq)
{
    memset(used, false, sizeof used);
    memset(pre_man, -1, sizeof pre_man);

    queue<PII> q;
    q.push(start);
    used[start.first][start.second] = true;
    used[box.first][box.second] = true;     // 不能经过box，所以直接认为走过了

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        if (t == end)       // 如果走到了终点，那么就是最短路了，处理完路径后，直接返回
        {
            seq.clear();        // 清空。虽然是个局部变量，进来就是空的，但还是操作一下，习惯
            int x = t.first, y = t.second;
            while (pre_man[x][y] != -1)     // 往回找路径
            {
                // 记得这里的方向要反一下，比如：(x,y)时上一步在右边推了过来的，但是实际人是往左边推的
                // 如0和1互变，2和3互变
                int dir = pre_man[x][y] ^ 1;    
                seq.push_back(dir);
                x += dx[dir], y += dy[dir];     // 变为上一步的位置
            }

            return seq.size();
        }

        for (int ii = 0; ii < 4; ii++)  // 4个方向扩展
        {
            int i = ii ^ 1;     // 因为我们定义的dx和dy是和规定的上下左右相反，所以需要再反一下        
            int x = t.first, y = t.second;
            int a = x + dx[i], b = y + dy[i];
            if (check(a, b) && !used[a][b])
            {
                used[a][b] = true;
                pre_man[a][b] = i;
                q.push({ a, b });
            }
        }
    }

    return -1;
}

bool bfs_box(PII man, PII box, Node& end)
{
    memset(st, false, sizeof st);

    queue<Node> q;
    // 枚举箱子初始状态可以走哪些方向
    for (int i = 0; i < 4; i++)
    {
        int x = box.first, y = box.second;
        int a = x + dx[i], b = y + dy[i];       // 人要推箱子时所处的位置
        int j = x - dx[i], k = y - dy[i];       // 箱子要推到的位置
        vector<int> seq;                        // 人从当前位置走到要推箱子所处的位置所经过的路径
        // 如果位置合法，且人确实能够走到推箱子时所处的位置的话
        if (check(a, b) && check(j, k) && bfs_man(man, { a, b }, box, seq) != -1)
        {
            st[j][k][i] = true;     // 标记状态
            q.push({ j, k, i });    
            dist[j][k][i] = { 1, seq.size() };  // 箱子的初始状态到此处的距离即为1，因为第一次扩展，人的距离记时路径的长度
            path[j][k][i] = seq;                // 路径存下
            pre[j][k][i] = { x, y, -1 };        // 记录当前箱子状态的由来，因为首次扩展，所以方向记为-1
        }
    }

    bool success = false;
    PII man_d = { 1e9, 1e9 };   // 记录bfs时到达终点的最小距离

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        if (g[t.x][t.y] == 'T') // 如果bfs到了终点
        {
            success = true;

            if (dist[t.x][t.y][t.dir] < man_d)  // 如果距离小于当前答案距离，更新，类型时Pair<int,int>,比较时遵循了限制1限制2
            {
                man_d = dist[t.x][t.y][t.dir];  // 更新
                end = t;                        // 更新终点的状态，因为到达终点可能有多条路径
            }
        }

        for (int i = 0; i < 4; i++) // 扩展4个方向
        {
            int a = t.x + dx[i], b = t.y + dy[i];   // 人要推箱子时所处的位
            int j = t.x - dx[i], k = t.y - dy[i];   // 箱子要推到的位置
            if (check(a, b) && check(j, k))         // 位置合法的话
            {
                vector<int> seq;
                auto& p = dist[j][k][i];            // (j,k)位置i状态的距离
                // 人从当前位置（t.x + dx[t.dir]，, t.y + dy[t.dir]）到箱子要推到（a, b）
                int distance = bfs_man({ t.x + dx[t.dir], t.y + dy[t.dir] }, { a, b }, { t.x, t.y }, seq);
                if (distance != -1) // 人走的过去的话
                {
                    
                    PII td = { dist[t.x][t.y][t.dir].first + 1, dist[t.x][t.y][t.dir].second + distance };
                    if (!st[j][k][i])   // 若这个状态还没走过
                    {
                        st[j][k][i] = true;     // 标记走过
                        q.push({ j, k, i });    
                        path[j][k][i] = seq;
                        pre[j][k][i] = t;   // 记录上一步从哪里走到这里的
                        p = td;             // 更新dist[j][k][i]
                    } else if (p > td)  // 虽然走过了，但距离更小了，更新
                    {
                        p = td;
                        path[j][k][i] = seq;
                        pre[j][k][i] = t;
                    }
                }
            }
        }
    }

    return success;
}

int main()
{
    int T = 1;
    while (cin >> n >> m, n || m)
    {
        for (int i = 0; i < n; i++) cin >> g[i];

        printf("Maze #%d\n", T++);

        PII man, box;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (g[i][j] == 'S') man = { i, j };         // 找人
                else if (g[i][j] == 'B') box = { i, j };    // 找箱子

        Node end;                                           // 终点

        if (!bfs_box(man, box, end)) puts("Impossible.");
        else
        {
            char ops[] = "nswe";        // 规定顺序
            string res;
            while (end.dir != -1)       // 从终点回溯到箱子的起点
            {
                res += ops[end.dir] - 32;   // 箱子
                for (auto dir : path[end.x][end.y][end.dir]) res += ops[dir];   // 人
                end = pre[end.x][end.y][end.dir];   // 变到箱子的上一个位置
            }
            reverse(res.begin(), res.end());
            cout << res << endl;
        }

        puts("");
    }

    return 0;
}

