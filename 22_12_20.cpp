


// 数字三角形
// 由于左右步数差不超过1，所以对于奇数层数，从最低层的中间往上走，偶数层的话，中间两个往上走
//  利用缓存，去除重复性递归

#include <iostream>
using namespace std;
const int INF = -1000000;
const int N = 110;
int a[N][N];
int f[N][N];
int dfs(int r, int c, int diff) {
    if (r == 0) return abs(diff) > 1 ? INF : 0;
    if (abs(diff) > r) return INF;
    if (f[r][c]) return f[r][c];
    int res = a[r][c];
    int t = dfs(r - 1, max(1, c - 1), diff + 1);
    t = max(t, dfs(r - 1, min(r - 1, c), diff - 1));
    f[r][c] = res + t;
    return res + t;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> a[i][j];
        }
    }

    int res = 0;
    if (n & 1) {
        res = dfs(n, n / 2 + 1, 0);
    } else {
        res = max(dfs(n, n / 2, 0), dfs(n, n / 2 + 1, 0));
    }
    cout << res << endl;
    return 0;
}



// 修剪灌木
// 可以发现，一个灌木的最大高度，为从自身位置，向左或向右走一个来回再回到自身的距离的最大值
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cout << 2 * max(n - i, i - 1);
    }
    return 0;
}




// 七段码
// dfs+并查集
#include <iostream>
using namespace std;
const int N = 10;
int e[N][N], fa[N],use[N];
int res;
int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}
void merge(int x, int y) {
    fa[get(x)] = get(y);
}
// dfs遍历每个灯，每个灯只有开关两个状态
void dfs(int u) {
    if (u > 7) {
        // 并查集判断是否在同一集合
        for (int i = 1; i <= 7; ++i) fa[i] = i;

        for (int i = 1; i <= 7; ++i) {
            for (int j = 1; j <= 7; ++j) {
                if (e[i][j] && use[i] && use[j]) {  // i和j相邻且亮着
                    merge(i, j);
                }
            }
        }
        int k = 0;
        for (int i = 1; i <= 7; ++i) {
            if (use[i] && fa[i] == i) ++k;
        }
        if (k == 1) ++res;      // 如果所有亮灯都属于同一集合
        return;
    }
    use[u] = 1;
    dfs(u + 1);
    use[u] = 0;
    dfs(u + 1);
}
int main()
{
    // a b c d e f g
    // 1 2 3 4 5 6 7
    // 建立连接关系
    e[1][2] = e[1][6] = 1;
    e[2][1] = e[2][7] = e[2][3] = 1;
    e[3][2] = e[3][4] = e[3][7] = 1;
    e[4][3] = e[4][5] = 1;
    e[5][4] = e[5][6] = e[5][7] = 1;
    e[6][1] = e[6][5] = e[6][7] = 1;
    e[7][2] = e[7][3] = e[7][5] = e[7][6] = 1;

    dfs(1);
    cout << res << endl;

    return 0;
}


// 等差数列
// 排序，求每两项后一项减去前一项的最小值，即为公差
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
int a[N];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a, a + n);
    int d = 1 << 30;
    for (int i = 1; i < n; ++i)
        d = min(d, a[i] - a[i - 1]);
    if (d == 0)  cout << n << endl;
    else cout << (a[n - 1] - a[0]) / d + 1;
    return 0;

}



