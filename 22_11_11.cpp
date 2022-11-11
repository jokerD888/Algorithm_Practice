
//
//// 172. 立体推箱子


// 地图整体形态不变，寻找最少步数，只有少数特征随着每一步操作发现变化
// 所以把这些变化的部分提取为状态，分别是坐标和状态，所以进行bfs
#include <iostream>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 510;
int n, m;
char s[N][N];

// lie定义箱子的状态，0是立着，1是横着躺，(x,y)表箱子左部分的坐标，2是竖着躺，（x,y)表上半部分
struct rec { int x, y, lie; };
rec st, ed;     // 初态和终态
queue<rec> q;
const int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };    // 上右下左
int d[N][N][3];     // 每个状态离初始状态的最少步数


bool vaild(int x, int y) {
    return x >= 0 && y >= 0 && x < n&& y < m;
}
bool vaild(rec next) {
    if (!vaild(next.x, next.y)) return false;
    if (s[next.x][next.y] == '#') return false;
    if (next.lie == 0 && s[next.x][next.y] != '.') return false;
    if (next.lie == 1 && (next.y + 1 >= m || s[next.x][next.y + 1] == '#')) return false;
    if (next.lie == 2 && (next.x + 1 >= n || s[next.x + 1][next.y] == '#')) return false;
    return true;
}
void parse_st_end() {       // 找出起点和终点
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == 'O') {
                ed.x = i, ed.y = j, ed.lie = 0, s[i][j] = '.';
            } else if (s[i][j] == 'X') {
                for (int k = 0; k < 4; ++k) {
                    int x = i + dx[k], y = j + dy[k];
                    if (vaild(x, y) && s[x][y] == 'X') {
                        st.x = min(i, x), st.y = min(j, y);
                        st.lie = (k == 1 || k == 3) ? 1 : 2;    // 上右下左顺序查找四周
                        s[i][j] = s[x][y] = '.';
                        break;
                    }
                }
                if (s[i][j] == 'X') st.x = i, st.y = j, st.lie = 0;
            }
        }
    }
}
// next_x[i][j] 表lie=i时向j方向滚动x的变化情况
const int next_x[3][4] = { {-2,0,1,0},{-1,0,1,0},{-1,0,2,0} };
const int next_y[3][4] = { {0,1,0,-2},{0,2,0,-1},{0,1,0,-1} };
const int next_lie[3][4] = { {2,1,2,1},{1,0,1,0},{0,2,0,2} };


int bfs() {
    // 初始距离全置为-1
    memset(d, -1, sizeof d);
    // 清空队列
    while (q.size()) q.pop();

    d[st.x][st.y][st.lie] = 0;
    q.push(st);

    while (q.size()) {
        rec t = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            rec next;
            next.x = t.x + next_x[t.lie][i];
            next.y = t.y + next_y[t.lie][i];
            next.lie = next_lie[t.lie][i];
            if (!vaild(next)) continue;
            if (d[next.x][next.y][next.lie] == -1) {
                d[next.x][next.y][next.lie] = d[t.x][t.y][t.lie] + 1;
                q.push(next);
                if (next.x == ed.x && next.y == ed.y && next.lie == ed.lie)
                    return d[next.x][next.y][next.lie];
            }

        }
    }
    return -1;

}

int main()
{
    while (cin >> n >> m, n) {
        for (int i = 0; i < n; ++i)
            cin >> s[i];
        parse_st_end();
        int res = bfs();
        if (res == -1) {
            puts("Impossible");
        } else {
            cout << res << endl;
        }
    }
    return 0;
}





// 173. 矩阵距离

// bfs（泛洪）
// 一开始遍历一变将所有为1的点入队列，让后这些点同时开始bfs,使用d数组记录距离

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;

const int N = 1010;
int n, m;
char a[N][N];
int d[N][N];
queue<pair<int, int>> q;

void bfs() {
    int dire[]{ -1,0,1,0,-1 };
    while (q.size()) {
        auto t = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = t.first + dire[i], y = t.second + dire[i + 1];
            if (x >= 0 && y >= 0 && x < n && y < m && d[x][y] == -1) {
                d[x][y] = d[t.first][t.second] + 1;
                q.push({ x,y });
            }
        }
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    memset(d, -1, sizeof d);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '1') {
                q.push({ i,j });
                d[i][j] = 0;
            }
        }
    }
    bfs();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << d[i][j] << ' ';
        cout << endl;
    }

    return 0;
}