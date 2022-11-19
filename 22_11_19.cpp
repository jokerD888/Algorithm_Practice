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
