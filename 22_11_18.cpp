// 182. 破坏正方形


// 建立二维数组，行对应每个正方形，列对应每个火柴，于是
//      按行看，可以得知该火柴组成了哪些正方形，按列看，可以得知该正方形由哪些火柴组成

// 所以我们的目标就是最少的边，使得每个正方形中至少被选出一条，这是一个经典的重复覆盖问题，可以用Dancing links求解
// 这里使用IDA*直接求解

// 搜索顺序优化：找出最小的正方形，依次枚举删除那条边
// 估计函数：借助Dancing links的估计函数，枚举所有未被删掉的正方形，将其所有边全部删掉，只记删除一条边。这样估计出的值一定不大于真实值，满足IDA*对估价函数的要求。


#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 61;   // 最大 5*5的正方形， 2*n*(n+1)共60根

int n, m;
bool st[N];
vector<int> square[N];

// 检查一个正方形是否完整
bool check(vector<int>& sq) {
    for (int i = 0; i < sq.size(); ++i)
        if (st[sq[i]])
            return false;
    return true;
}
// 枚举所有未被删掉的正方形，将其所有边全部删掉，只记删除一条边，看一共需要几次
int f() {
    static bool state[N];
    memcpy(state, st, sizeof st);
    
    int res = 0;
    for (int i = 0; i < m; ++i) {
        vector<int>& sq = square[i];
        if (check(sq)) {
            ++res;
            for (int j = 0; j < sq.size(); ++j)
                st[sq[j]] = true;
        }
    }
    memcpy(st, state, sizeof st);
    return res;
}

bool dfs(int depth, int limit) {
    if (depth + f() > limit) return false;
    
    for (int i = 0; i < m; ++i) {   
        auto& sq = square[i];
        if (check(sq)) {
            for (int j = 0; j < sq.size(); ++j) {       // 枚举删除那条边
                int x = sq[j];
                st[x] = true;
                if (dfs(depth + 1, limit)) return true;
                st[x] = false;
            }
            return false;   
        }
    }
    return true;
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        m = 0;

        // 找出每个正方形，确定长度和左上角坐标 后将组成该正方形的火柴记录
        for (int i = 1; i <= n; ++i) {      // 长度从小到大，搜索时按顺序搜既可满足正方形从小到大
            for (int a = 1; a + i - 1 <= n; ++a) {   // 横坐标
                for (int b = 1; b + i - 1 <= n; ++b) {      //  纵坐标
                    auto& q = square[m++];
                    q.clear();
                    int d = 2 * n + 1;      // 公差
                    for (int j = 0; j < i; ++j) {       // 枚举i次，每次找到4个对应的木棍
                        q.push_back((a - 1) * d + b + j);       // 上
                        q.push_back((a - 1 + i) * d + b + j);   // 下
                        q.push_back(n + 1 + (a - 1) * d + b - 1 + j * d);   // 左
                        q.push_back(n + 1 + (a - 1) * d + b - 1 + j * d + i);   // 右
                    }
                }
            }
        }

        memset(st, 0, sizeof st);
        int k;
        cin >> k;
        for (int i = 0, t; i < k; ++i) {
            cin >> t;
            st[t] = true;
        }
        int depth = 0;
        while (!dfs(0, depth)) ++depth;

        cout << depth << endl;
    }
    return 0;
}



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