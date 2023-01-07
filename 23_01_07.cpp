
// 344. 观光之旅


//考虑 Floyd 算法的过程。当外层循环 k 刚开始时，d[i,j] 保存着“经过编号不超过 k-1的节点”从到的最短路长度。
// 于是，min{d[i, j] + a[j, k] + a[k, i]}(1<=i<j<k) 就是满足以下两个条件的最小环长度 : 
//    1.由编号不超过 k 的节点构成
//    2.经过节点 k。
//  上式中的 i,j 相当于枚举了环上与 k 相邻的两个点。故以上结论显然成立。
// 所有的k 属于[1, n]，都对上式进行计算，取最小值，即可得到整张图的最小环。
// 在该算法中，我们对每个k只考虑了由编号不超过 k 的节点构成的最小环，没有考虑编号大于 k 的节点。事实上，由对称性可知，这样做并不会影响结果。
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 10010;

int a[N][N], d[N][N], pos[N][N];    //pos记录当前状态由哪个点转移过来
int n, m, ans = 0x3f3f3f3f;
vector<int> path;       // 具体方案

// 将点x到点y的经过的点加入到path中，(不包括x和y)
void get_path(int x, int y) {
    if (pos[x][y] == 0) return;     // x和y是直接相连的，中间没有点
    // x->pos[x][y]->y
    get_path(x, pos[x][y]);             // 递归x->pos[x][y]
    path.push_back(pos[x][y]);          
    get_path(pos[x][y], y);             // 递归pos[x][y]->y
}
int main() {
    cin >> n >> m;
    memset(a, 0x3f, sizeof a);
    for (int i = 1; i <= n; ++i) a[i][i] = 0;
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        a[x][y] = a[y][x] = min(a[x][y], z);
    }
    memcpy(d, a, sizeof a);

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i) 
            for (int j = i + 1; j < k; ++j) 
                if ((long long)d[i][j] + a[j][k] + a[k][i] < ans) {     // 初始化默认值较大，需要long long
                    ans = d[i][j] + a[j][k] + a[k][i];
                    path.clear();
                    path.push_back(i);
                    get_path(i, j);
                    path.push_back(j);
                    path.push_back(k);
                }
            
        

        for (int i = 1; i <= n; ++i) 
            for (int j = 1; j <= n; ++j) 
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k;      // 记录由i到j是经过那个点来的
                }
            
        
    }

    if (ans == 0x3f3f3f3f) {
        puts("No solution.");
    } else {
        for (auto i : path)
            cout << i << ' ';
        cout << endl;
    }
    return 0;
}
// 对于有向图的最小环问题，可枚举起点 s = 1~n，执行堆优化的 Diikstra 算法求解单源最短路径。
// s一定是第一个被从堆中取出的节点，我们扫描 s 的所有出边，当扩展、更新完成后，令 d[s] = +oo，然后继续求解。
//当 s 第二次被从堆中取出时，d[s]就是经过点 s 的最小环长度。