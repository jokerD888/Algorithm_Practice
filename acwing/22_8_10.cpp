
//167. 木棒

// dfs+剪枝
// 思路：将木棍长度从大到小排序（减少递归分支和排除等效冗余），然后枚举答案，但答案一定是所有长度和的约数，因len*cnt=sum；
// dfs(cnt,cur,start)含义：已近拼好了cnt根，正在拼的一根已经拼好了cur的长度，且拼当前根的时候前start根已近考虑过了
// 剪枝：1）如果有一段连续相同长度的木棍的话,若失败一个,这一段相同的跳过
//      2）如果在拼的是某一根木棒的第一段且后续操作失败了，直接false
//      3) 如果在拼的是某一根木棒的最后一段且后续操作失败了，直接false
// 证： 1）很明显了，可以用反证法，交换两个木棍
//      2）反证，放在第一个位置失败的话，我们就放在其他木棒中，这个其他木棒和当前木棒等效，都是还没来得及拼都是空的，所以不论放在其他那个木棒都会失败
//      3）反证，放在最后一个位置失败的话，我们就选其他木棍b来拼接，而这个失败的木棍a放入其他木棒，假设成功的话，那木棍a和木棍b长度相等，可以交换，那就与原结果冲突

//#include <cstring>
//#include <algorithm>
//#include <iostream>
//using namespace std;
//
//const int N = 70;
//int a[N];
//bool st[N];
//int sum, len, n;
//
//// 已近拼好了cnt根，正在拼的一根已近拼了cur的长度,且前面的start根已经考虑完了
//bool dfs(int cnt, int cur, int start) {
//    if (cnt * len == sum) return true;              // 所有的已经拼好了，true
//    if (cur == len) return dfs(cnt + 1, 0, 0);      // 当前这根也已经拼好了，拼下一根
//
//    for (int i = start; i < n; ++i) {
//        if (st[i]) continue;                        // 选过了
//        int l = a[i];
//        if (cur + l > len) continue;                 // 当前所尝试木棍的太长
//
//        st[i] = true;
//        if (dfs(cnt, cur + l, i + 1)) return true;  // 若选择当前木棍，且后续操作正好拼完，true
//        st[i] = false;                              // 回溯
//
//        if (!cur || cur + l == len) return false;     // 如果第一个木棍或最后一个失败，则一定失败
//
//        int j = i;                                  
//        while (j < n && a[j] == l) ++j;                 // 跳过连续相同的
//        i = j - 1;
//    }
//    return false;
//}
//
//int main()
//{
//    while (cin >> n, n) {
//        sum = 0, len = 0;
//        memset(st, 0, sizeof st);
//
//        for (int i = 0; i < n; ++i) {
//            cin >> a[i];
//            sum += a[i];
//            len = max(len, a[i]);
//        }
//        sort(a, a + n, greater<int>());
//
//        while (true) {
//            if (sum % len == 0 && dfs(0, 0, 0)) {
//                cout << len << endl;
//                break;
//            }
//            ++len;
//        }
//    }
//    return 0;
//}



// 168. 生日蛋糕

// dsf+剪枝
// 从下往上枚举每层的半径和高
// 思路：预处理每层的最小体积和面积，dfs(u,v,s):当前来到了第u层，累计确定了体积v,面积s
//      三个剪枝：当前体积加上此层的最小体积还要大于n的话，当前面积加上此层面积还要大于等于res的话,若s加上剩余最小面积大于等于res的话
//      
//#include<iostream>
//#include<cmath>
//using namespace std;
//
//const int N = 24, INF = 1e9;
//
//int n, m;
//int minv[N], mins[N];   // 每层最小的体积，最小的面积
//int res = INF;
//
////记录每层的半径和高，因为会用到上一层的高度
//int R[N], H[N];
//
////u当前层次，v当前处理的体积和，s当前处理的面积和
//void dfs(int u, int v, int s)
//{
//    if (v + minv[u] > n) return;                    // 当前体积加上此层的最小体积还要大于n的话，return
//    if (s + mins[u] >= res) return;                 // 当前面积加上此层面积还要大于等于找到的可能答案的话，return
//    if (s + 2 * (n - v) / R[u + 1] >= res) return;  // 最优性剪枝，通过剩余体积能推断出剩余最小面积，若s加上剩余最小面积大于等于res的话，retrun
//
//    if (!u)                         // 搜到最顶层的话，若v==n的话，找到了更小的res
//    {
//        if (v == n) res = s;
//        return;
//    }
//
//    //搜索顺序，先R后H，从大到小
//    int q = sqrt((n - v - minv[u - 1]) / u);
//    for (int r = min(R[u + 1] - 1, q); r >= u; r--)
//        for (int h = min(H[u + 1] - 1, (n - v - minv[u - 1]) / r / r); h >= u; h--)
//        {
//            H[u] = h, R[u] = r;
//
//            //最底层的时候需要加上r*r
//            int t = u == m ? r * r : 0;
//
//            dfs(u - 1, v + r * r * h, s + 2 * r * h + t);
//        }
//}
//
//int main()
//{
//    cin >> n >> m;
//    // 没层从上往下，半径和高度需要单调递增，所以r和h最小就是层数
//    for (int i = 1; i <= m; i++)
//    {
//        minv[i] = minv[i - 1] + i * i * i;  // r^2 * h
//        mins[i] = mins[i - 1] + 2 * i * i;  // 2*r * h
//    }
//
//    //m+1层不存在，作为哨兵，减少边界情况的判断
//    R[m + 1] = H[m + 1] = INF;
//
//    dfs(m, 0, 0);
//
//    if (res == INF) res = 0;
//    cout << res << endl;
//
//
//    return 0;
//}



// 169. 数独2
// 思路：每次找到一个空格，枚举该空格选择那个字母，往下递归
// 状态存储：state[x][y]: x行y列这个格子可以填哪些数（0-15），用该数字的二进制位来表示
// 优化：1）对于每个格子，若不能填任何一个字符，return;若只能填一个字符，那直接填上
//      2） 对于每一行，若某个字母不能出现在任何一个位置，无解，return;若某个字母只有一个位置可以填，直接填上
//      3） 对于每一列，若某个字母不能出现在任何一个位置，无解，return;若某个字母只有一个位置可以填，直接填上
//      4） 对于每一个16宫格，与行列类似
//      5） 每次选择空格是，选择备选方案数最少的格子来填


#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 16, M = N * N + 1;

int ones[1 << N], Log[1 << N];
int state[N][N];
char str[N][N + 1];

int bstate[M][N][N], bstate2[M][N][N];  // M是递归层数，最多N*N层
int bstr[M][N][N + 1];

inline int lowbit(int x) {      // 返回x的最低位1及后面的0
    return x & -x;
}
// 给（x,y)位置画上t
void draw(int x, int y, int t) {
    str[x][y] = t + 'A';

    // 行列去除方案t
    for (int i = 0; i < N; ++i) {
        state[x][i] &= ~(1 << t);
        state[i][y] &= ~(1 << t);
    }

    // 16宫格去除方案t
    int dx = x / 4 * 4, dy = y / 4 * 4;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            state[dx + i][dy + j] &= ~(1 << t);
        }

    state[x][y] = 1 << t;   // 添上该字符串状态
}

bool dfs(int cnt) {

    if (!cnt) return true;

    // 备份
    int bcnt = cnt;     // 记得cnt也要备份！！！！
    memcpy(bstate[bcnt], state, sizeof state);
    memcpy(bstr[bcnt], str, sizeof str);


    // 查找所有格子，若有格子什么都填不了，false,若只能填一个字母，直接填
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (str[i][j] == '-') {
                int t = state[i][j];
                if (ones[t] == 0) {
                    memcpy(state, bstate[bcnt], sizeof state);
                    memcpy(str, bstr[bcnt], sizeof str);
                    return false;
                } else if (ones[t] == 1) {
                    draw(i, j, Log[t]);
                    --cnt;      // 别忘了cnt-- ！！！！！
                }
            }



    // 查找行是否有某个字母在任何位置都不能填，若是，false,若有字母只能填在一个位置，那么就直接填上
    for (int i = 0; i < N; ++i) {
        int sor = 0, sand = (1 << N) - 1;   // sor是哪些字母可以填，sand是哪些字母只能填一个位置
        int drawed = 0;                     // 已经填过的字母
        for (int j = 0; j < N; ++j) {
            int t = state[i][j];
            sand &= ~(t & sor);
            sor |= t;
            if (str[i][j] != '-') drawed |= state[i][j];
        }
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[bcnt], sizeof state);
            memcpy(str, bstr[bcnt], sizeof str);
            return false;
        }

        // 填上只能填一个位置的字母
        for (int j = sand; j; j -= lowbit(j)) {       // 枚举每个只能填一个位置的字母
            int t = lowbit(j);
            // 要判断该字母是否已经被填过！！！！！！
            if (!(drawed & t)) {                      // 如果该字母还没被填过
                for (int k = 0; k < N; ++k) {               // 枚举位置
                    if (state[i][k] & t) {       // 如果该位置可以填该字母，填上
                        draw(i, k, Log[t]);
                        --cnt;
                        break;
                    }
                }
            }
        }
    }

    // 查找列是否有某个字母在任何位置都不能填，若是，false,若有字母只能填在一个位置，那么就直接填上
    for (int i = 0; i < N; ++i) {
        int sor = 0, sand = (1 << N) - 1;   // sor是哪些字母可以填，sand是哪些字母只能填一个位置
        int drawed = 0;                     // 已经填过的字母
        for (int j = 0; j < N; ++j) {
            int t = state[j][i];
            sand &= ~(t & sor);
            sor |= t;
            if (str[j][i] != '-') drawed |= state[j][i];
        }
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[bcnt], sizeof state);
            memcpy(str, bstr[bcnt], sizeof str);
            return false;
        }

        // 填上只能填一个位置的字母
        for (int j = sand; j; j -= lowbit(j)) {       // 枚举每个只能填一个位置的字母
            int t = lowbit(j);
            if (!(drawed & t)) {                           // 如果该字母还没被填过
                for (int k = 0; k < N; ++k) {               // 枚举位置
                    if (state[k][i] & t) {       // 如果该位置可以填该字母，填上
                        draw(k, i, Log[t]);
                        --cnt;
                        break;
                    }
                }
            }
        }

    }



    // 查找16宫格是否有某个字母在任何位置都不能填，若是，false,若有字母只能填在一个位置，那么就直接填上
    for (int i = 0; i < N; ++i) {       // 枚举16个宫格
        int sor = 0, sand = (1 << N) - 1;   // sor是哪些字母可以填，sand是哪些字母只能填一个位置
        int drawed = 0;                     // 已经填过的字母
        int x = i / 4 * 4, y = i % 4 * 4;   // x是该宫格在第几行，y是该宫格在第几列,*4是该宫格的左上角坐标
        for (int j = 0; j < N; ++j) {   // 16个位置
            int dx = j / 4, dy = j % 4;
            int t = state[x + dx][y + dy];
            sand &= ~(t & sor);
            sor |= t;
            if (str[x + dx][y + dy] != '-') drawed |= state[x + dx][y + dy];
        }
        if (sor != (1 << N) - 1) {
            memcpy(state, bstate[bcnt], sizeof state);
            memcpy(str, bstr[bcnt], sizeof str);
            return false;
        }

        // 填上只能填一个位置的字母
        for (int j = sand; j; j -= lowbit(j)) {       // 枚举每字母
            int t = lowbit(j);
            if (!(drawed & t)) {
                for (int k = 0; k < N; ++k) {               // 枚举位置
                    int dx = k / 4, dy = k % 4;
                    if (state[x + dx][y + dy] & t) {       // 如果该位置可以填该字母，填上
                        draw(x + dx, y + dy, Log[t]);
                        --cnt;
                        break;
                    }
                }
            }
        }
    }


    if (!cnt) return true;

    // 备份优化完的状态
    memcpy(bstate2[bcnt], state, sizeof state);
    // 找出最小方案
    int x, y, s = 20;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (str[i][j] == '-' && ones[state[i][j]] < s) {
                x = i;
                y = j;
                s = ones[state[i][j]];
            }
        }

    for (int i = state[x][y]; i; i -= lowbit(i)) {
        int t = lowbit(i);
        memcpy(state, bstate2[bcnt], sizeof state);     // 别忘了恢复现场！！！！！！
        draw(x, y, Log[t]);

        if (dfs(cnt - 1)) return true;
    }

    memcpy(state, bstate[bcnt], sizeof state);          // 还原
    memcpy(str, bstr[bcnt], sizeof str);
    return false;

}
int main()
{
    for (int i = 0; i < N; ++i) Log[1 << i] = i;
    for (int i = 0; i < 1 << N; ++i) {
        for (int j = i; j; j -= lowbit(j)) ++ones[i];
    }

    while (cin >> str[0]) {

        for (int i = 1; i < N; ++i) cin >> str[i];

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                state[i][j] = (1 << N) - 1;

        int cnt = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (str[i][j] != '-')
                    draw(i, j, str[i][j] - 'A');
                else
                    ++cnt;

        dfs(cnt);
        for (int i = 0; i < N; ++i) cout << str[i] << endl;
        cout << endl;
    }

    return 0;
}







