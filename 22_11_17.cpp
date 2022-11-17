
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
bool dfs(int level, int limit,int last) {
    if (level + f() > limit) return false;
    if (check()) return true;


    for (int i = 0; i < 8; ++i) {       // 向8个方向操作
        if(oppose[i]==last) continue;       // 剪枝，否则超时
        path[level]= opr[i];
        if (0 == i || 1 == i || 4 == i || 5 == i) {     // 列方向
            if (i < 2) workCol(i, 'u');
            else workCol(i, 'd');
        } else {
            if (i < 4) workRow(i, 'r');
            else workRow(i, 'l');
        }


        if (dfs(level + 1, limit,i)) return true;

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
        while (!dfs(0, depth,8)) ++depth;
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
