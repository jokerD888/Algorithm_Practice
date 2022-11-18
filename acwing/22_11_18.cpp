
// AcWing 180. 排书

// IDA*算法
// 把估计函数与迭代加深的DFS算法结合，形成IDA*算法
// 以迭代加深DFS的框架为基础，把原来简单的深度的限制加强为:若当前深度+未来估计步数 > 深度限制，则立即从当前分支回溯

// 在目标状态下，第i本书后面是第i+1本书，称i+1是i的正确后续
// 在某个状态下，错误后续总个数为tot,在最理想的情况下，每次操作都能把某3个错误后续全部改对，消除所有错误后续的操作次数也至少需要tot/3上取整次
//      所有可以将这个值作为每个状态的估计函数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 15;
int seq[N];
int tmp[5][N];
int n;

int f() {
    int tot = 0;
    for (int i = 0; i < n - 1; ++i)
        if (seq[i] + 1 != seq[i + 1])
            ++tot;
    return (tot + 2) / 3;
}
bool check() {
    for (int i = 0; i < n; ++i)
        if (seq[i] != i + 1) return false;
    return true;
}
bool dfs(int depth, int limit) {
    if (depth + f() > limit) return false;
    if (check()) return true;

    for (int len = 1; len < n; ++len) {       // 长度
        for (int l = 0; l + len - 1 < n; ++l) {     // 左端点
            int r = l + len - 1;        // 右端点
            for (int i = r + 1; i < n; ++i) {       // 插入的位置
                memcpy(tmp[depth], seq, sizeof seq);
                int x, y;
                for (x = r + 1, y = l; x <= i; ++x, ++y) seq[y] = tmp[depth][x];
                for (x = l; x <= r; ++x, ++y) seq[y] = tmp[depth][x];
                if (dfs(depth + 1, limit)) return true;
                memcpy(seq, tmp[depth], sizeof seq);

            }
        }
    }
    return false;
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> seq[i];
        int depth = 0;
        while (depth < 5 && !dfs(0, depth)) ++depth;
        if (depth < 5)
            cout << depth << endl;
        else
            cout << "5 or more" << endl;

    }
    return 0;
}



// 181. 回转游戏

// 每层8个分支，递归越深分支越多，故可以使用IDA*算法
// 估计函数的设计：每一次操作最多只能放对一个数字，所以估计值设为8-max(中间8个位置相同数字次数）

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10;
int arr[N][N], R;
char path[N];

const char* opr = "ABCDEFGH";
const int pos[] = { 2,4,2,4,4,2,4,2 };
const int oppose[] = { 5,4,7,6,1,0,3,2,-1 };   // 相反操作关系映射

void readCol() {
    cin >> arr[R][2] >> arr[R++][4];
}
void readRow() {
    for (int i = 0; i < 7; ++i)
        cin >> arr[R][i];
    ++R;
}
int f() {
    int cnt[4] = { 0 };
    for (int i = 2; i <= 4; ++i)
        for (int j = 2; j <= 4; ++j)
            ++cnt[arr[i][j]];
    return 8 - max({ cnt[1],cnt[2],cnt[3] });
}
bool check() {
    int cnt[4] = { 0 };
    for (int i = 2; i <= 4; ++i)
        for (int j = 2; j <= 4; ++j)
            ++cnt[arr[i][j]];
    return max({ cnt[1],cnt[2],cnt[3] }) == 8;
}
void workCol(int k, char dire) {
    int idx = pos[k];
    if (dire == 'u') {        // 向上移动
        int tmp = arr[0][idx];
        for (int i = 0; i < 6; ++i)
            arr[i][idx] = arr[i + 1][idx];
        arr[6][idx] = tmp;
    } else {            // 向下移动
        int tmp = arr[6][idx];
        for (int i = 6; i > 0; --i)
            arr[i][idx] = arr[i - 1][idx];
        arr[0][idx] = tmp;
    }

}
void workRow(int k, char dire) {
    int idx = pos[k];
    if (dire == 'r') {        // 右移
        int tmp = arr[idx][6];
        for (int i = 6; i > 0; --i)
            arr[idx][i] = arr[idx][i - 1];
        arr[idx][0] = tmp;
    } else {            // 左移
        int tmp = arr[idx][0];
        for (int i = 0; i < 6; ++i)
            arr[idx][i] = arr[idx][i + 1];
        arr[idx][6] = tmp;
    }
}
bool dfs(int level, int limit, int last) {
    if (level + f() > limit) return false;
    if (check()) return true;


    for (int i = 0; i < 8; ++i) {       // 向8个方向操作
        if (oppose[i] == last) continue;       // 剪枝，否则超时
        path[level] = opr[i];
        if (0 == i || 1 == i || 4 == i || 5 == i) {     // 列方向
            if (i < 2) workCol(i, 'u');
            else workCol(i, 'd');
        } else {
            if (i < 4) workRow(i, 'r');
            else workRow(i, 'l');
        }


        if (dfs(level + 1, limit, i)) return true;

        if (0 == i || 1 == i || 4 == i || 5 == i) {     // 列方向
            if (i < 2) workCol(i, 'd');
            else workCol(i, 'u');
        } else {
            if (i < 4) workRow(i, 'l');
            else workRow(i, 'r');
        }
    }
    return false;
}
int main()
{
    int a;
    while (cin >> a, a) {
        R = 0;
        arr[R][2] = a;
        cin >> arr[R++][4];
        readCol();
        readRow();
        readCol();
        readRow();
        readCol();
        readCol();
        int depth = 1;
        while (!dfs(0, depth, 8)) ++depth;
        if (depth == 1)
            cout << "No moves needed" << endl;
        else {
            for (int i = 0; i < depth; ++i) printf("%c", path[i]);
            cout << endl;
        }
        cout << arr[2][2] << endl;
    }

    return 0;
}


// 或
// 打表映射，简化编码

/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/


#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 24;

int q[N];
// 映射每一种操作，所对应的数
int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};
int center[8] = { 6, 7, 8, 11, 12, 15, 16, 17 };
int opposite[8] = { 5, 4, 7, 6, 1, 0, 3, 2 };

int path[100];

int f()
{
    static int sum[4];
    memset(sum, 0, sizeof sum);
    for (int i = 0; i < 8; i++) sum[q[center[i]]] ++;

    int s = 0;
    for (int i = 1; i <= 3; i++) s = max(s, sum[i]);
    return 8 - s;
}

bool check()
{
    for (int i = 1; i < 8; i++)
        if (q[center[i]] != q[center[0]])
            return false;
    return true;
}

void operation(int x)
{
    int t = q[op[x][0]];
    for (int i = 0; i < 6; i++) q[op[x][i]] = q[op[x][i + 1]];
    q[op[x][6]] = t;
}

bool dfs(int depth, int max_depth, int last)
{
    if (depth + f() > max_depth) return false;
    if (check()) return true;

    for (int i = 0; i < 8; i++)
    {
        if (opposite[i] == last) continue;
        operation(i);
        path[depth] = i;
        if (dfs(depth + 1, max_depth, i)) return true;
        operation(opposite[i]);
    }

    return false;
}

int main()
{
    while (scanf("%d", &q[0]), q[0])
    {
        for (int i = 1; i < N; i++) scanf("%d", &q[i]);
        int depth = 0;
        while (!dfs(0, depth, -1))
        {
            depth++;
        }
        if (!depth) printf("No moves needed");
        for (int i = 0; i < depth; i++) printf("%c", 'A' + path[i]);
        printf("\n%d\n", q[6]);
    }

    return 0;
}



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