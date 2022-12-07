// 239. 奇偶游戏

// 如果我们用sum数组表示序列 S的前缀和， 那么在每个回答中 :
// 1.S[l~r]有偶数个1，等价于sum[l - 1]与sum[r] 奇偶性相同。
// 2. S[l~r]有奇数个1，等价于sum[l - 1]与sum[r] 奇偶性不同。
// 继续观察，还有如下传递关系
//  1.若x1与X2奇偶性相同，X2与X3奇偶性也相同，那么X1与X3奇偶性相同。这种情况与“程序自动分析”中的等于关系一样。
//  2.若X1与X2奇偶性相同，x2与X3奇偶性不同，那么x1与X3奇偶性不同。
//  3.若x1与x2奇偶性不同，x2与X3奇偶性也不同，那么x1与x3奇偶性相同。
// 上面三条奇偶性的传递结果为 x3=x1^x2       

// 此外，序列长度N很大，但问题数M较小，需要使用离散化方法将每个问题的两个整数l-1和r缩小到等价的1~2M以内的范围

// 本题使用“边带权”的并查集
// 边权d[x]=0,表x与fa[x]奇偶性相同，为1，不同。路径压缩时进行时对边权做xor运算即可，即可得到x与树根的奇偶性关系
// 
// 先检查x和y是否在同一个集合内(奇偶关系是否已知)。get(x)、 get(y) 都执行完成后, d[x] xord[y]即为x和y的奇偶性关系(如下图)。若d[x] xord[y]≠ans
//      (该关系与回答矛盾)，则在该问题之后即可确定小A撒谎。
// 若x和y不在同一个集合内，则合并两个集合。此时应该先通过get操作得到
//       两个集合的树根(设为p和q)，令p为q的子节点。如下图所示。已知d[x] 与d[y]分别表示路径x~p与y~q之间所有边权的xor 和”，p~q之间的边权d[p]是待求的值。
//       显然，路径x~y由路径x~P，p~q与q~y组成，因此x与y的奇偶性关系ans = d[x] xor d[y] xor d[p]。进而推出新连接的边权d[p] = d[x]xor d[y]xor ans 。
// 通俗来说，若x和y是一个集合，通过根节点这个中间值，来判断x和y的奇偶性，不是一个集合，则合并
//


#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 10010;

struct { int l, r, ans; } query[N];
int a[2 * N], fa[2 * N], d[20010], n, m, cnt;

void read_discrete() {
    cin >> n >> m;
    char str[5];
    for (int i = 0; i < m; ++i) {
        cin >> query[i].l >> query[i].r >> str;
        query[i].ans = (str[0] == 'o' ? 1 : 0);     // 1奇0偶
        a[cnt++] = query[i].l - 1;              // -1 因为本题使用的是类似前缀和的概念又同时-1可以认为两个紧邻的片段是一个集合
        a[cnt++] = query[i].r;
    }
    sort(a, a + cnt);
    cnt = unique(a, a + cnt) - a;
}
int get(int x) {
    if (x == fa[x]) return x;
    int root = get(fa[x]);
    d[x] ^= d[fa[x]];
    return fa[x] = root;
}
// 求离散化后的值
int cast(int x) {
    return lower_bound(a, a + cnt, x) - a;
}
int main()
{
    read_discrete();
    for (int i = 0; i < cnt; ++i) fa[i] = i;
    bool success = true;
    for (int i = 0; i < m; ++i) {
        int x = cast(query[i].l - 1), y = cast(query[i].r);
        int px = get(x), py = get(y);
        if (px == py) {     // 同一集合
            if ((d[x] ^ d[y]) != query[i].ans) {
                success = false;
                cout << i << endl;
                break;
            }
        } else {        // 合并
            fa[px] = py, d[px] = d[x] ^ d[y] ^ query[i].ans;
        }
    }
    if (success) cout << m << endl;
    return 0;
}


//或 使用“扩展域”并查集
// 把每个变量x拆成两个节点Xodd和Xeven,其中Xodd表示sum[x]是奇数，
// Xeven表示sum[x]是偶数。我们也经常把这两个节点称为x的“奇数域”和“偶数域”
// 对于每个问题，设在离散化后l - 1和r的值分别是x和y, 设ans表示该问题的回答(0 代表偶数个，1代表奇数个)。
//  1.若ans = 0, 则合并Xodd与Yodd, Xeven与Yeven。这表示“x为奇数”与“y为奇数”可以互相推出，“x 为偶数”与“y为偶数”也可以互相推出，
//      它们是等价的信息。
//  2.若ans = 1, 则合并Xodd 与Yeven, Xeven与Yoddo 这表示“x为奇数”与“y为偶数”可以互相推出，“x为偶数”与“y为奇数”也可以互相推出，
//      它们是等价的信息。
//上述合并同时还维护了关系的传递性。试想，在处理完(x, y, 0) 和(y, z, 1)两个
// 回答之后，x和z之间的关系也就已知了，如下图所示。这种做法就相当于在无向图
// 上维护节点之间的连通情况，只是扩展了多个域来应对多种传递关系。
// 
// 在处理每个问题之前，我们当然也要先检查是否存在矛盾。若两个变量x和y对应的Xodd和yodd节点在同一集合内，则已知二者奇偶性相同。
//  若两个变量x和y对应的Xodd和Yeven节点在同一集合内，则已知二者奇偶性不同。



#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 10010;

struct { int l, r, ans; } query[N];
int a[2 * N], fa[2 * N], n, m, cnt;

void read_discrete() {
    cin >> n >> m;
    char str[5];
    for (int i = 0; i < m; ++i) {
        cin >> query[i].l >> query[i].r >> str;
        query[i].ans = (str[0] == 'o' ? 1 : 0);    
        a[cnt++] = query[i].l-1;            
        a[cnt++] = query[i].r;
    }
    sort(a, a + cnt);
    cnt = unique(a, a + cnt) - a;
}
int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}
// 求离散化后的值
int cast(int x) {
    return lower_bound(a, a + cnt, x) - a;
}
int main()
{
    read_discrete();
    for (int i = 0; i <2*N; ++i) fa[i] = i;
    bool success = true;
    for (int i = 0; i < m; ++i) {
        int x = cast(query[i].l-1), y = cast(query[i].r);
        int x_odd = x, x_even = x + N;
        int y_odd = y, y_even = y + N;
        if (query[i].ans == 0) {
            if (get(x_odd) == get(y_even)) {
                cout << i << endl;
                success = false;
                break;
            }
            fa[get(x_odd)] = get(y_odd);
            fa[get(x_even)] = get(y_even);
        } else {
            if (get(x_odd) == get(y_odd)) {
                cout << i << endl;
                success = false;
                break;
            }
            fa[get(x_odd)] = get(y_even);
            fa[get(x_even)] = get(y_odd);
        }
    }
    if (success) cout << m << endl;
    return 0;
}