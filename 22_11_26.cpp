
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