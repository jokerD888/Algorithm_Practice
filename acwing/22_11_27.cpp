

// 183. 靶形数独

// 本想从中间往外搜索，从9到1的方向枚举填的数字，一旦完完成整个搜素就返回，但这是不可性的
//   因为，每个填写的数字并不是独立的，内圈的局部最优解可能并不是全局最优解，如果选择了局部的最优解，会干扰到后面的选择
// 所以还是老规矩来，枚举每个位置可以选择的数字，同时做剪枝，每次选出“选择数最小的位置”进行DFS



#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 9;
int g[N][N];
int row[N], col[N], cell[3][3];
int ones[1 << N], bitPos[1 << N];
int ans = -1;

inline int lowbit(int x) {
    return x & (-x);
}
int getW(int x, int y) {
    //int tx = min(x, 8 - x);    // !!!这里粗心，是min
    //int ty = min(y, 8 - y);
    //return min(tx, ty) + 6;
    return min({ x,y,8 - x,8 - y }) + 6;
}
void filp(int x, int y, int t) {
    t = 1 << (t - 1);
    row[x] ^= t;
    col[y] ^= t;
    cell[x / 3][y / 3] ^= t;
}
int getbtis(int x, int y) {
    return row[x] & col[y] & cell[x / 3][y / 3];
}
void dfs(int cnt, int tot) {
    if (!cnt) {
        ans = max(ans, tot);
        return;
    }
    // 选出可选数最小的那个
    int minv = 10, x, y;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (!g[i][j]) {
                int t = ones[getbtis(i, j)];
                if (t < minv) {
                    minv = ones[getbtis(i, j)];
                    x = i, y = j;
                }
            }
        }
    //if (minv < 10)
    for (int i = getbtis(x, y); i; i -= lowbit(i)) {
        int bit = lowbit(i);
        int num = bitPos[bit] + 1;
        filp(x, y, num);
        g[x][y] = num;

        dfs(cnt - 1, tot + g[x][y] * getW(x, y));

        filp(x, y, num);
        g[x][y] = 0;
    }
}

int main()
{
    for (int i = 0; i < N; ++i)
        cell[i / 3][i % 3] = row[i] = col[i] = (1 << N) - 1;
    for (int i = 1; i < 1 << N; ++i) {
        int s = 0;
        for (int j = i; j; j -= lowbit(j))
            ++s;
        ones[i] = s;
    }
    for (int i = 0; i < N; ++i) {
        bitPos[1 << i] = i;
    }

    int cnt = 0, tot = 0;;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            cin >> g[i][j];
            if (g[i][j]) {
                filp(i, j, g[i][j]);
                tot += g[i][j] * getW(i, j);
            } else ++cnt;
        }
    dfs(cnt, tot);
    cout << ans << endl;

    return 0;
}

// 184. 虫食算


// 超时  8/10

// 从后往前逐位计算，对应a,b上的单词枚举其代表的数字
//  1）若字母与上一个相同，但枚举的数字不同，跳过
//  2）与上一个不同，枚举的数字出像过，但所对应的字母和当前字母不同，跳过
//  3）当前字母计算过，但枚举的数字没对应上，跳过


#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 30;
char a[N], b[N], c[N];
int ans[N];
char st[N];     // st[i] 数字i对应什么字符，0即为没选过
int n;
pair<int, int> add(int x, int y, int z) {
    return { (x + y + z) % n, (x + y + z) / n };
}

bool dfs(int u, int t) {
    if (u == -1 && t == 0) return true;
    if (u == -1) return false;

    // 枚举该位置可选的数字
    for (int i = 0; i < n; ++i) {
        // 当前字母计算过，但当前枚举数字没对应上
        if (ans[a[u] - 'A'] != -1 && ans[a[u] - 'A'] != i) continue;
        // 如果当前字母和上一位字母相同，但枚举的数字对应的字母不是当前字母，跳过
        if (a[u] == a[u + 1] && st[i] != a[u]) continue;
        // 如果枚举的数字出现过，但对应的不是当前字母，跳过
        if (st[i] && st[i] != a[u]) continue;
        bool newNumA = false;
        // 如果枚举的数字没出现过,设置
        if (st[i] == 0) {
            st[i] = a[u];
            ans[a[u] - 'A'] = i;
            newNumA = true;
        }

        // b同理
        for (int j = 0; j < n; ++j) {
            // 当前字母计算过，且当前枚举数字没对应上
            if (ans[b[u] - 'A'] != -1 && ans[b[u] - 'A'] != j) continue;
            if (b[u] == b[u + 1] && st[j] != b[u]) continue;
            if (st[j] && st[j] != b[u]) continue;
            bool newNumB = false;
            if (st[j] == 0) {
                st[j] = b[u];
                ans[b[u] - 'A'] = j;
                newNumB = true;
            }

            auto sum = add(i, j, t);
            // 检查和上的字母能否对上
            bool newNumC = false;
            if (st[sum.first] == 0 && ans[c[u] - 'A'] == -1) {   // 计算的和没选过，且该字母也没计算过
                st[sum.first] = c[u];
                ans[c[u] - 'A'] = sum.first;
                newNumC = true;
                if (dfs(u - 1, sum.second)) return true;
            } else if (st[sum.first] && ans[c[u] - 'A'] == sum.first) { // 计算的和选过 且 该字母对应的数字与和相同
                if (st[sum.first] == c[u]) {
                    if (dfs(u - 1, sum.second)) return true;
                }
            }
            if (newNumC) {
                st[sum.first] = 0;
                ans[c[u] - 'A'] = -1;
            }

            if (newNumB) {
                st[j] = 0;
                ans[b[u] - 'A'] = -1;
            }
        }
        if (newNumA) {       // 本次循环设置上的，回溯
            st[i] = 0;
            ans[a[u] - 'A'] = -1;
        }
    }
    return false;
}


int main()
{
    cin >> n;
    cin >> a;
    cin >> b;
    cin >> c;
    a[n] = b[n] = c[n] = 'a';
    memset(ans, -1, sizeof ans);
    auto be = clock();
    dfs(n - 1, 0);
    auto ed = clock();
    cout << ed - be << endl;
    for (int i = 0; i < n; ++i)
        cout << ans[i] << ' ';
    cout << endl;
    return 0;
}


// 上法中是从右往左枚举每个字母可以选的数字，
// 每一层最多N*N个分支往下分支数减少，共N层，时间复杂度(N*N)！，虽然上法有众多剪枝，但只能在规定时间内完成N=18以内的任务

// 所以我们改为枚举每个字母可以选的数字，再进行判断是否合法，时间为O(N!)* 26，再加上剪枝，可以1s内AC
// 教训：做之前一定不要想到啥做啥，要估算一下时间复杂度，看是否合格，有没有更好的方法

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 30;
int n;
char s[3][N];
int q[N], path[N];
bool st[N];

// 剪枝
bool check() {
    for (int i = n - 1, t = 0; i >= 0; --i) {
        int a = s[0][i] - 'A', b = s[1][i] - 'A', c = s[2][i] - 'A';        // 烫烫！！！ 注意i是列
        if (path[a] != -1 && path[b] != -1 && path[c] != -1) {  // 三个都确定了
            a = path[a], b = path[b], c = path[c];
            if (t == -1) {
                if ((a + b) % n != c && (a + b + 1) % n != c) return false;
                if (!i && a + b >= n) return false;      // 最高位不能进位
            } else {
                if ((a + b + t) % n != c) return false;
                if (!i && a + b + t >= n) return false;     // 最高位不能进位
                t = (a + b + t) / n;
            }
        } else {
            // t是进位，-1是不确定
            t = -1;
        }
    }
    return true;
}
bool dfs(int u) {
    if (u == n) return true;
    for (int i = 0; i < n; ++i) {
        if (!st[i]) {
            st[i] = true;
            path[q[u]] = i;
            if (check() && dfs(u + 1)) return true;
            st[i] = false;
            path[q[u]] = -1;
        }
    }
    return false;
}
int main()
{
    cin >> n;
    for (int i = 0; i < 3; ++i) cin >> s[i];
    // 从右往做计算，所以先从右往枚举字母
    for (int i = n - 1, k = 0; i >= 0; --i) {
        for (int j = 0; j < 3; ++j) {
            int t = s[j][i] - 'A';          // 烫烫！！！！！！注意i和j的顺序
            if (!st[t]) {
                st[t] = true;
                q[k++] = t;
            }
        }
    }
    memset(st, 0, sizeof st);
    memset(path, -1, sizeof path);
    dfs(0);
    for (int i = 0; i < n; ++i) cout << path[i] << ' ';
    cout << endl;
    return 0;
}


// 185. 玛雅游戏

// 枚举每个位置的移动
// 剪枝：1）当局面中有一些格子相同的数量为1或2时，已不可能完整，回溯，
//      2) 由于列号越小优先级越高，所以向左边移动时，不如左边的那个向右边移动
// 时间O(35*35^5)    5*7的格子，最多走5步，加上每次move,需要遍历整个局面，加上剪枝可以AC

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int g[5][7], bg[5][5][7];
int cnt[11], bcnt[5][11];
bool st[5][7];

struct node
{
    int x, y, d;
};
node path[5];

void move(int a, int b, int c) {
    swap(g[a][b], g[c][b]);

    while (true) {
        bool flag = false;
        // 消除悬空
        for (int x = 0; x < 5; ++x) {
            int z = 0;
            for (int y = 0; y < 7; ++y)
                if (g[x][y])
                    g[x][z++] = g[x][y];
            while (z < 7) g[x][z++] = 0;
        }

        memset(st, false, sizeof st);
        for (int x = 0; x < 5; ++x)
            for (int y = 0; y < 7; ++y)
                if (g[x][y]) {
                    int l = x, r = x;
                    while (l - 1 >= 0 && g[l - 1][y] == g[x][y]) l--;
                    while (r + 1 < 5 && g[r + 1][y] == g[x][y]) r++;

                    if (r - l + 1 >= 3) {
                        flag = true;
                        st[x][y] = true;
                    } else{
                        l = r = y;
                        while (l - 1 >= 0 && g[x][l - 1] == g[x][y]) l--;
                        while (r + 1 < 7 && g[x][r + 1] == g[x][y]) r++;

                        if (r - l + 1 >= 3)
                        {
                            flag = true;
                            st[x][y] = true;
                        }
                    }
                }

        if (flag) {
            for (int x = 0; x < 5; ++x)
                for (int y = 0; y < 7; ++y)
                    if (st[x][y]) {
                        --cnt[0];
                        --cnt[g[x][y]];
                        g[x][y] = 0;
                    }

        } else break;

    }

}
bool dfs(int u) {
    if (u == n) return !cnt[0];

    for (int i = 1; i <= 10; ++i)
        if (cnt[i] == 1 || cnt[i] == 2)     // 剪枝：只有1个或只有两个相同的，无法消去
            return false;
    memcpy(bg[u], g, sizeof g);
    memcpy(bcnt[u], cnt, sizeof cnt);

    // 枚举每个位置
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y < 7; ++y) {
            if (g[x][y]) {
                int nx = x + 1;
                if (nx < 5) {
                    path[u] = { x,y,1 };
                    move(x, y, nx);
                    if (dfs(u + 1))return true;
                    memcpy(cnt, bcnt[u], sizeof cnt);
                    memcpy(g, bg[u], sizeof g);
                }
                nx = x - 1;
                if (nx >= 0 && !g[nx][y]) {      // 剪枝：由于列号越小优先级越高，所以向左边移动时，不如左边的那个向右边移动
                    path[u] = { x,y,-1 };
                    move(x, y, nx);
                    if (dfs(u + 1)) return true;
                    memcpy(cnt, bcnt[u], sizeof cnt);
                    memcpy(g, bg[u], sizeof g);
                }
            }
        }
    }
    return false;
}
int main()
{
    cin >> n;
    for (int i = 0; i < 5; ++i) {
        int j = 0, y;
        while (cin >> y, y) {
            cnt[0] ++;      // 累计一共有几个格子需要消去
            cnt[y] ++;
            g[i][j++] = y;
        }
    }
    if (dfs(0)) {
        for (int i = 0; i < n; ++i)
            cout << path[i].x << ' ' << path[i].y << ' ' << path[i].d << endl;
    } else puts("-1");

    return 0;
}


// 186. 巴士

// 最多300个车，每个路线上最两个车，所以最多会有150条路线，但题目说明最多只会有17条路线，所以可以用迭代加深搜索
// 
// 题目中的路线指的是在0-59时间段中的一个完整的、元素至少为2的等差数列，每条巴士线路是一条完整的等差数列！
// 解法：先预处理出所有合法路线，所以问题就变为了最少选择多少条路线，可以将所有公交车覆盖
// 剪枝：  1）dfs时需要传入一个枚举的起点，按组合数方法搜索，不是排序数方法
//          2）优先枚举点较多的路线 
//          3）基于第2）剪枝，如果当前路线上的点数*剩余可以选则的路线数量+现在已经覆盖的车的数量<总车数量，回溯，可行性剪枝




#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

// 总路线数，等差数列，首相，公差，0~59 共60个，取2个确定一条路线C(60,2) 60*59/2大致1800左右
const int N = 2000, M = 60;

int n;
int bus[M]; // 所有时刻公交车的数量
vector<pair<int, PII>> routes;   // 合法路线

// 检查这条路线是否合法，即从首相开始，之后每个间隔d都有车
bool check(int a, int d) {
    for (int i = a; i < 60; i += d) {
        if (!bus[i])
            return false;
    }
    return true;
}
int dfs(int depth, int u, int tot) {
    if (!depth) return tot == n;

    // 枚举路线
    for (int i = u; i < routes.size(); ++i) {
        auto r = routes[i];
        // 起点，终点
        int a = r.second.first, d = r.second.second;
        if (r.first * depth + tot < n) continue;
        if (!check(a, d)) continue;
        for (int j = a; j < 60; j += d) --bus[j];

        if (dfs(depth - 1, i, tot + r.first)) return true;

        for (int j = a; j < 60; j += d) ++bus[j];
    }

    return false;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        ++bus[t];
    }
    // 枚举所有合法路线
    // 注意：：题目中的路线指的是在0-59时间段中的一个完整的、元素至少为2的等差数列，每条巴士线路是一条完整的等差数列！
    for (int a = 0; a < 60; ++a)
        for (int d = a + 1; a + d < 60; ++d)   // a是首相是第一个，所以前面需要满足a-d<0 ,即d>a
            if (check(a, d))
                routes.push_back({ (59 - a) / d + 1,{a,d} });   // 第一关键字为该路线上的数量
    sort(routes.begin(), routes.end(), greater<pair<int, PII>>());

    int depth = 0;
    while (depth != 17 && !dfs(depth, 0, 0)) ++depth;       // 做多只有17条，所以一旦要递归17层就可以不用算了，直接break
    cout << depth << endl;
    return 0;
}



// 187. 导弹防御系统

// 枚举每个导弹放在上升序列中还是下降序列中即每个导弹有两种选择，2^n,同时选择放入那个序列需要O(n)时间来遍历
// 本来是还是需要枚举放在序列集合中的那个具体序列，但是可以贪心，升序时选择小于h[u]的最大的那个放，降序时选择大于h[u]的最小的那个放
// 所以总时间O(n*2^n) n最大50，但实际上答案很小，即用到的单调序列的个数就会很小，使用迭代加深，那么代码中的剪枝就会减去很多分支
//      即代码中的if (su + sd > depth)  return false;       

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 60;
int n;
int h[N];
int up[N], down[N];

bool dfs(int depth, int u, int su, int sd) {
    if (su + sd > depth)  return false;       
    if (u == n) return true;
    // 枚举放到升序序列
    bool flag = false;
    for (int i = 1; i <= su; ++i) {
        if (up[i] < h[u]) {     //贪心，选择小于h[u]的最大的那个放
            int t = up[i];
            up[i] = h[u];
            if (dfs(depth, u + 1, su, sd)) return true;
            up[i] = t;
            flag = true;
            break;
        }
    }
    // 新开升序序列
    if (!flag) {
        up[su + 1] = h[u];
        if (dfs(depth, u + 1, su + 1, sd)) return true;
    }
    // 枚举放到下降子序列
    flag = false;
    for (int i = 1; i <= sd; ++i) {
        if (down[i] > h[u]) {       //贪心，选择大于h[u]的最小的那个放
            int t = down[i];
            down[i] = h[u];
            if (dfs(depth, u + 1, su, sd)) return true;
            down[i] = t;
            flag = true;
            break;
        }
    }
    if (!flag) {
        down[sd + 1] = h[u];
        if (dfs(depth, u + 1, su, sd + 1)) return true;
    }
    return false;
}
int main()
{
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i) cin >> h[i];
        int depth = 0;
        while (!dfs(depth, 0, 0, 0)) ++depth;
        cout << depth << endl;
    }
    return 0;
}


// 188. 武士风度的牛

// 普通的宽搜

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
const int N = 160;
int n, m;
char s[N][N];
int dist[N][N];

PII st, ed;
int bfs() {
    memset(dist, -1, sizeof dist);
    const int dx[]{ -2,-2, -1,1,2,2,1,-1 }, dy[]{ -1,1,2,2,1,-1,-2,-2 };

    queue<PII> q;
    q.push(st);
    dist[st.first][st.second] = 0;

    while (q.size()) {
        auto t = q.front(); q.pop();
        int x = t.first, y = t.second;
        if (t == ed) return dist[x][y];

        for (int i = 0; i < 8; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < n && b >= 0 && b < m && s[a][b] != '*' && dist[a][b] == -1) {
                dist[a][b] = dist[x][y] + 1;
                q.push({ a,b });
            }
        }

    }
    return -1;
}
int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (s[i][j] == 'K') st = { i,j };
            else if (s[i][j] == 'H') ed = { i,j };

    cout << bfs();
    return 0;
}



// 189. 乳草的入侵

// 普通的bfs,但注意！！！：题目中的坐标是笛卡尔坐标，注意输入时的x和y

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
const int N = 110;
int n, m;
char s[N][N];
PII st;

int dfs() {

    queue<PII> q;
    q.push(st);
    s[st.first][st.second] = '*';
    const int dx[]{ -1,-1,-1,0,1,1,1,0 }, dy[]{ -1,0,1,1,1,0,-1,-1 };

    int t = 0;
    while (q.size()) {
        int size = q.size();
        ++t;
        while (size--) {
            auto t = q.front(); q.pop();
            int x = t.first, y = t.second;
            for (int i = 0; i < 8; ++i) {
                int a = x + dx[i], b = y + dy[i];
                if (a >= 0 && a < n && b >= 0 && b < m && s[a][b] == '.') {
                    s[a][b] = '*';
                    q.push({ a,b });
                }
            }
        }
    }
    return t - 1;
}
int main()
{
    cin >> m >> n;
    cin >> st.second >> st.first;
    for (int i = 0; i < n; ++i) cin >> s[i];
    --st.first, --st.second;

    cout << dfs();
    return 0;
}



// 190. 字串变换

// 迭代加深，超时，过一半用例，时间最多每层最少N个分支，最深10层，N^10,N是每层可以进行转换的个数
// 字符串最长20个，最多可变换20个字符串，共6组规则，所以最高是120^10,导致超时


#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 22;

string a, b;
string tfa[7], tfb[7];
int n;
int cnt = 0;
bool dfs(int depth, string s) {
    if (++cnt <= 10000) return false;

    if (s == b) return true;
    if (!depth) return false;

    for (int i = 0; i < n; ++i) {   // 枚举每一种转化规则
        int pos, t = 0;;
        while (pos = s.find(tfa[i], t++), pos != s.npos) {
            int len = tfa[i].size();
            string ss = s.substr(0, pos) + tfb[i] + s.substr(pos + len);
            if (dfs(depth - 1, ss)) return true;
        }
    }

    return false;
}
int main()
{
    cin >> a >> b;
    while (cin >> tfa[n] >> tfb[n])++n;
    int depth = 0;
    while (depth <= 10 && !dfs(depth, a)) ++depth;
    if (depth <= 10) cout << depth << endl;
    else cout << "NO ANSWER!";
    return 0;
}


// 普通bfs,加上计数操作即可AC,当搜索个数达到一定数量，直接判否


#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
using namespace std;

typedef pair<string, int> PSI;
const int N = 10;
int cnt;
string a, b, from[N], to[N];
unordered_map<string, bool> exist;

int bfs() {
    int res = -1, cal = 0;
    if (a == b) return 0;
    queue<PSI> q;
    q.push({ a,0 });
    exist[a] = true;
    while (q.size() && res == -1 && ++cal <= 10000) {
        auto t = q.front();
        q.pop();
        a = t.first;
        if (t.second >= 10) break;
        for (int i = 0; i < cnt; ++i) {
            for (int st = 0; st + from[i].size() - 1 < a.size(); ++st) {
                bool success = true;
                for (int j = 0; j < from[i].size(); ++j) {
                    if (a[st + j] != from[i][j]) {
                        success = false;
                        break;
                    }
                }
                if (!success) continue;
                string c = a;
                a.replace(a.begin() + st, a.begin() + st + from[i].size(), to[i]);
                if (!exist.count(a)) {
                    exist[a] = true;
                    q.push({ a,t.second + 1 });
                    if (a == b) {
                        res = t.second + 1;
                        break;
                    }
                }
                a = c;
            }
        }
    }
    return res;
}

int main()
{
    cin >> a >> b;
    while (cin >> from[cnt] >> to[cnt]) ++cnt;
    int res = bfs();
    if (res == -1)
        cout << "NO ANSWER!" << endl;
    else
        cout << res << endl;
    return 0;
}


// 双向搜索，使得搜索空间大幅减小，k^5,k是每层的分支数


#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

const int N = 6;
int n;
string A, B;
string a[N], b[N];

int extend(queue<string>& q, unordered_map<string, int>& da, unordered_map<string, int>& db,
    string a[N], string b[N])
{
    int d = da[q.front()];  // 取出对头深度
    while (q.size() && da[q.front()] == d) {    // 搜索完d深度的空间
        auto t = q.front();
        q.pop();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < t.size(); ++j) {
                if (t.substr(j, a[i].size()) == a[i]) {
                    string r = t.substr(0, j) + b[i] + t.substr(j + a[i].size());
                    if (db.count(r)) return da[t] + db[r] + 1;  // db中有r的记录，返回深度只和
                    if (da.count(r)) continue;      // r出现过
                    da[r] = da[t] + 1;
                    q.push(r);
                }
            }
        }
    }
    return 11;

}
int bfs() {
    if (A == B) return 0;
    queue<string> qa, qb;
    unordered_map<string, int> da, db;

    qa.push(A); qb.push(B);
    da[A] = db[B] = 0;

    int step = 0;
    while (qa.size() && qb.size()) {
        int t;
        if (qa.size() < qb.size()) t = extend(qa, da, db, a, b);
        else t = extend(qb, db, da, b, a);

        if (t <= 10) return t;
        if (++step == 10) return -1;
    }
    return -1;
}

int main()
{
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) ++n;

    int t = bfs();
    if (t == -1) puts("NO ANSWER!");
    else cout << t << endl;
    return 0;
}



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



// 193. 算乘方的牛

// IDA*
// 显然可以想到一种可能不是最优解得做法：每次把最大的扩大成两倍，再用较小的数补或者减去超出的部分。
//      这样做能使数字增长得很快（其实是最快），那么最少操作步数应该不会太多。
// 那么既然有这样一种性质，迭代加深是一种很好得选择，同时延申可以作为一种估计函数，进而本题得框架可以选IDA*作为一种不错得解法

// 我们实际上只关心幂，即乘除放在幂的角度来看就变为了加减，，即一开始的两个数x和1即为 1和0
// 1） 可以考虑到，负数和0是不够优秀的，负数的加减可以用正数的减加来替代，加0和减0只会徒增操作次数   
//          因此，我们可以归定，除法操作时，总是用高幂除以低幂的，且不使用自己除以自己，乘法操作后，不保留0，即把操作的结果数放在0的位置
// 2） 估计函数：在当前深度下，如果剩下的步骤 全部都把较大的数扩为两倍 还是比目标小，剪枝
// 3）其次，对于当前的幂次（a,b),设gcd(a,b)=d,那么不管之后怎么操作，得到的次数一定是d的倍数，所以如果不满足，p%d==0,剪枝
// 4) 还有一个较弱的启发式搜索（？），每次先讨论大+大的情形，这样似乎更容易得到最优解。

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int p;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

bool IDAStart(int depth, int a, int b) {    // 保证x>=y,冗余性剪枝
    if (a == p) return true;
    if (!depth) return false;

    // 可行性剪枝
    if ((a << depth) < p) return false;     // (a<<depth） < p即是估计函数
    if (p % (gcd(a, b))) return false;

    int x, y;
    // 共8种方案
    x = a + b, y = b;   // a+b放在a上
    if (y && IDAStart(depth - 1, x, y)) return true;
    x = a + b, y = a;   // a+b放在b上
    if (y && IDAStart(depth - 1, x, y)) return true;

    x = a + a, y = b;   // a自加放自己上
    if (y && IDAStart(depth - 1, x, y)) return true;
    x = a + a, y = a;   // a自加放b上
    if (y && IDAStart(depth - 1, x, y)) return true;

    x = max(b + b, a), y = min(b + b, a);
    if (y && IDAStart(depth - 1, x, y)) return true;
    x = b + b, y = b;
    if (y && IDAStart(depth - 1, x, y)) return true;

    x = max(a - b, b), y = min(a - b, b);
    if (y && IDAStart(depth - 1, x, y)) return true;
    x = max(a - b, a), y = min(a - b, a);
    if (y && IDAStart(depth - 1, x, y)) return true;

    return false;

}

int main()
{
    cin >> p;

    int depth = 0;
    while (!IDAStart(depth, 1, 0)) ++depth;
    cout << depth << endl;
    return 0;
}

// 194. 涂满它！

/*
本题范围很小，启发我们可以用dfs搜索所有方案。但是最大是8 * 8的矩阵，方案数也很多，因此可以使用IDA*算法来优化。
估价函数：当前连通块外的颜色种数。
每次最多让一种颜色消失，因此这个估价函数一定<=实际方案
然后每次覆盖的时候使用flood fill来对周围的点染色
*/


#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int N = 10;
int g[N][N], bst[64][N][N], st[N][N]; // st数组 0 表示没搜索到，1 表示已经连通，2 表示和连通块相邻
int n;
const int dx[]{ -1,0,1,0 }, dy[]{ 0,1,0,-1 };

void flood(int x, int y, int c) {
    st[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int a = x + dx[i], b = y + dy[i];
        if (a >= 0 && a < n && b >= 0 && b < n && st[a][b] != 1) {
            if (g[a][b] == c) flood(a, b, c);   //如果是相同颜色，加入连通块
            else st[a][b] = 2;                  //否则说明是连通块的边界，和连通块相邻标记为2
        }
    }
}
//估价函数：剩余不在连通块中的颜色种数。
int f() {
    int s = 0;  // 记录剩余的颜色种数
    bool c[6] = { false };
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!c[g[i][j]] && st[i][j] != 1) {
                c[g[i][j]] = true;
                ++s;
            }

    return s;
}

bool dfs(int depth) {       // IDA*
    int t = f();
    if (!t) return true;
    if (t > depth) return false;

    memcpy(bst[depth], st, sizeof st);      // 备份状态

    for (int i = 0; i < 6; ++i) {   // 枚举6种颜色
        bool check = false;     // 连通块相邻色块中是否有色块i
        for (int x = 0; x < n; ++x)     // 
            for (int y = 0; y < n; ++y)
                if (g[x][y] == i && st[x][y] == 2) {
                    check = true;
                    flood(x, y, i);     // 对相应色块进行连通,泛洪
                }
        if (check && dfs(depth - 1)) return true;
        if (check) memcpy(st, bst[depth], sizeof st);
    }
    return false;
}
int main()
{
    while (cin >> n, n) {
        memset(st, 0, sizeof st);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> g[i][j];

        // 先找出左上角连通快
        flood(0, 0, g[0][0]);
        int depth = 0;
        while (!dfs(depth)) ++depth;
        cout << depth << endl;
    }
}

