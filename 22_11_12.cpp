
// 174. 推箱子

// 由于箱子和人一共4个状态，且会出现一些问题：单调性无法满足，且每个状态只访问一次会出现错误答案
// 可以发现每次箱子的移动后，人一定处于箱子移动前的位置。所以可以把箱子刚刚移动后，箱子与人的位置打包成一个状态
// 基本框架是，先单独对箱子做bfs找箱子到目标位置的最短路，每次箱子移动时，做bfs找人到箱子推的位置的最短路

#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int N = 25;
char s[N][N];
int n, m;
struct node { int x, y, dire; };        // bfs_box中记录每个位置（x,y)上从那个方向来的
vector<int> path[N][N][4];  // path[j][k][i] 表示人从推(j,k,i)的上一个状态的位置，走到推(j,k,i)这个状态的位置的行走路径
bool vis[N][N][4], used[N][N]; // vis用于bfs_box中标记箱子的每个位置的每个方向是否走过，use用于标记bfs_man中人的某个位置是否走过
PII dist[N][N][4];  // dist[j][k][i]是表示从初始状态到达j,k,i状态所需要的箱子最短路程和人行走最短路程
node pre[N][N][4];  // 表示箱子在(x, y)，上一个格子在i方向上的状态，即上一个状态是(x + dx[i], y + dy[i])
int pre_man[N][N];  // pre_man[x][y]表示人从哪个方向走到(x, y)，如果pre_man[x][y] = i, 那么上一个状态是(x - dx[i], y - dy[i])

const int dx[4] = { 1, -1, 0, 0 }, dy[4] = { 0, 0, 1, -1 };  // 依次表示下、上、右、左四个方向,这里与限制方向相反主要是为了编码的简洁，因为后续有很多地方要表示上一位置所处的方向
bool vaild(int x, int y) {
    return x >= 0 && y >= 0 && x < n&& y < m&& s[x][y] != '#';
}
// 求人从start走到end，中间不经过box的最短路径，行走序列保存在seq中（行走序列不包括终点）
int bfs_man(PII start, PII end, PII box, vector<int>& seq) {        // 注意这里的返回值是int
    memset(used, false, sizeof used);
    memset(pre_man, -1, sizeof pre_man);

    queue<PII> q;
    q.push(start);
    used[start.first][start.second] = true;
    used[box.first][box.second] = true;     // 不能经过box，所以直接认为走过了

    while (q.size()) {
        auto t = q.front(); q.pop();

        if (t == end)       // 如果走到了终点，那么就是最短路了，处理完路径后，直接返回
        {
            seq.clear();        // 清空。虽然是个局部变量，进来就是空的，但还是操作一下，习惯
            int x = t.first, y = t.second;
            while (pre_man[x][y] != -1)     // 往回找路径
            {
                // 记得这里的方向要反一下，因为我们定义的顺序时下上左右为0123，翻转一下变为实际的nswe上下左右
                // 如0和1互变，2和3互变
                int dir = pre_man[x][y] ^ 1;
                seq.push_back(dir);
                x += dx[dir], y += dy[dir];     // 变为上一步的位置
            }

            return seq.size();
        }

        for (int i = 0; i < 4; ++i) {
            int ii = i ^ 1;     // 因为我们定义的dx和dy是和规定的上下左右相反，所以需要再反一下        
            int x = t.first + dx[ii];
            int y = t.second + dy[ii];
            if (vaild(x, y) && !used[x][y]) {       // 合法且没访问过
                used[x][y] = true;
                pre_man[x][y] = ii;
                q.push({ x,y });
            }
        }
    }
    return -1;
}
bool bfs_box(PII man, PII box, node& end) {
    memset(vis, false, sizeof vis);

    queue<node> q;
    // 枚举箱子初始状态可以走哪些点
    for (int i = 0; i < 4; ++i) {
        int x = box.first, y = box.second;
        int a = x + dx[i], b = y + dy[i];       // 人要推箱子时所处的位置
        int j = x - dx[i], k = y - dy[i];       // 箱子要推到的位置
        vector<int> seq;                    // 存储bfs_man最短路的行走序列，即每一步行走的方向
         // 如果位置合法，且人确实能够走到推箱子时所处的位置的话
        if (vaild(a, b) && vaild(j, k) && bfs_man(man, { a,b }, box, seq) != -1) {
            vis[j][k][i] = true;        // 标记该状态走过
            q.push({ j,k,i });
            dist[j][k][i] = { 1,seq.size() };
            path[j][k][i] = seq;        // 路径存下
            pre[j][k][i] = { x,y,-1 };      // 记录当前箱子状态的由来，因为首次扩展，方向记为-1
        }
    }

    bool success = false;
    PII man_d = { 1e9,1e9 };    //  记录bfs到达终点的最小距离

    while (q.size()) {
        auto t = q.front(); q.pop();
        if (s[t.x][t.y] == 'T') {   // bfs到了终点
            success = true;
            if (dist[t.x][t.y][t.dire] < man_d) {   //如果距离小于当前答案距离，更新，类型时Pair<int,int>,比较时遵循了限制1限制2
                man_d = dist[t.x][t.y][t.dire];
                end = t;                // 更新终点的状态，因为到达终点可能有多条路径
            }
        }

        for (int i = 0; i < 4; ++i) {       // 扩展方向
            int a = t.x + dx[i], b = t.y + dy[i];   // 人要推箱子时所处的位
            int j = t.x - dx[i], k = t.y - dy[i];   // 箱子要推到的位置
            if (vaild(a, b) && vaild(j, k)) {       // 位置合法的话
                vector<int> seq;
                auto& p = dist[j][k][i];        // (j,k)位置i状态的距离
                 // 人从当前位置（t.x + dx[t.dir] , t.y + dy[t.dir]）到要推箱子的位置（a, b）
                // 人的位置一定是箱子上一步所处的位置
                int d = bfs_man({ t.x + dx[t.dire],t.y + dy[t.dire] }, { a,b }, { t.x,t.y }, seq);
                if (d != -1) {
                    // 人能过的去的话
                    auto& dd = dist[t.x][t.y][t.dire];
                    PII td = { dd.first + 1,dd.second + d };
                    if (!vis[j][k][i]) {        // 扩展的这个状态还没走过
                        vis[j][k][i] = true;
                        q.push({ j,k,i });
                        path[j][k][i] = seq;
                        pre[j][k][i] = t;   // 记录上一步从哪里走到这里的
                        p = td;             // 更新dist[j][k][i](引用）
                    } else if (p > td) {        // 虽然走过了，但距离更小了，更新
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
    int T = 0;
    while (cin >> n >> m, n) {
        for (int i = 0; i < n; ++i)
            cin >> s[i];
        cout << "Maze #" << ++T << endl;

        PII man, box;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (s[i][j] == 'S') man = { i,j };
                else if (s[i][j] == 'B') box = { i,j };

        node ed;
        if (!bfs_box(man, box, ed)) puts("Impossible.");
        else {
            char ops[] = "nswe";
            string res;
            while (ed.dire != -1) { // 从终点回溯到箱子的起点
                res += ops[ed.dire] - 32;   // 箱子
                for (auto dir : path[ed.x][ed.y][ed.dire]) res += ops[dir];     // 人
                ed = pre[ed.x][ed.y][ed.dire];      // 上一步所处状态
            }
            reverse(res.begin(), res.end());
            cout << res << endl;
        }
        puts("");
    }
    return 0;
}