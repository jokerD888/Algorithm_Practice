// 165. 小猫爬山

// dfs,尝试把每一只猫分配到已有的缆车上，或者新开一个缆车放
// 优化：若已有缆车数>=res,return
//      将猫从大到小排序，使得重量大的猫选择比重量小的猫小，减少递归分支的数量，
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//const int N = 20;
//int cats[N],w[N];
//int n, m, res = N;
//
//// 选好了u只猫，共用了cnt个缆车
//void dfs(int u, int cnt) {
//    if (cnt >= res) return;
//    if (u == n) {
//        res = cnt;
//        return;
//    }
//    for (int i = 0; i < cnt; ++i) {
//        if (w[i] + cats[u] <= m) {  // 能装下的话
//            w[i] += cats[u];
//            dfs(u + 1, cnt);
//            w[i] -= cats[u];    // 还原
//        }
//    }
//    // 新租一个缆车
//    w[cnt] = cats[u];
//    dfs(u + 1, cnt+1);
//    w[cnt] = 0;     // 还原
//   
//}
//int main()
//{
//    cin >> n >> m;
//    for (int i = 0; i < n; ++i)cin >> cats[i];
//    sort(cats, cats + n,greater<int>());
//    dfs(0, 0);
//    cout << res << endl;
//}




//166. 数独

// dfs+位运算
// 题目本身是dfs,但数据较严格，需要做许多优化
// 对于每一行每一列没一个九宫格可以的选择我们用一个int二级制位上的1来表示,这样利用位运算符&，可以快速得出三种限制条件下的选择
// 我们还需要调整尽量从根减少递归分支的数量,所以要每次选出可选最小空位来进

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 9;

int ones[1 << N], map[1 << N];  // ones[i]位i的二级制位一共有多少个1，map[i]是i的二进制位1处于第几位
int row[N], col[N], cell[3][3];
char str[100];

// 求最低位的1，如100100，返回100
inline int lowbit(int x) {
    return x & -x;
}
void init() {
    for (int i = 0; i < N; ++i) row[i] = col[i] = (1 << N) - 1; // 初始化，所有数都可以选
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cell[i][j] = (1 << N) - 1;
}
// 求可选方案，是行，列，九宫格的交集
inline int get(int x, int y) {
    return row[x] & col[y] & cell[x / 3][y / 3];
}
bool dfs(int cnt) {
    if (!cnt) return true;

    // 找出可选方案数最小的空格
    int minv = 10;
    int x, y;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (str[i * 9 + j] == '.') {
                int t = ones[get(i, j)];
                if (t < minv) {
                    minv = t;
                    x = i, y = j;
                }
            }
    for (int i = get(x, y); i; i -= lowbit(i)) {
        int t = map[lowbit(i)];

        // 修改状态
        row[x] -= 1 << t;
        col[y] -= 1 << t;
        cell[x / 3][y / 3] -= 1 << t;
        str[x * 9 + y] = '1' + t;

        if (dfs(cnt - 1)) return true;
        
        // 还原
        row[x] += 1 << t;
        col[y] += 1 << t;
        cell[x / 3][y / 3] += 1 << t;
        str[x * 9 + y] = '.';
    }

    return false;
}
int main()
{
    for (int i = 0; i < N; ++i) map[1 << i] = i;
    for (int i = 0; i < 1 << N; ++i) {
        int s = 0;
        for (int j = i; j; j -= lowbit(j)) ++s; // 计算二进制1的个数
        ones[i] = s;
    }
    while (cin >> str, str[0] != 'e') {
        init();

        int cnt = 0;
        for (int i = 0, k = 0; i < N; ++i)
            for (int j = 0; j < N; ++j, ++k) {
                if (str[k] != '.') {
                    int t = str[k] - '1';   // 将1到9,转为0到8,便于位处理
                    // 当前位置已近填了t,那么当前行，列，九宫格就需要减去t这个选择
                    row[i] -= 1 << t;
                    col[j] -= 1 << t;
                    cell[i / 3][j / 3] -= 1 << t;       // i/3,j/3将x,y映射到对应的九宫格
                } else {
                    ++cnt;  // 空位数量+1
                }
            }
        dfs(cnt);
        cout << str << endl;
    }
}



