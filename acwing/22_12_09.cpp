
// 237. 程序自动分析

// 并查集，由于数据范围太大，做离散化。先处理相等关系，将其合并，再处理不等关系，若不等关系中，两者处于同一集合，false

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010, M = 200010;
int num[M], fa[M], cnt;
int a[N], b[N];
bool st[N];
// 找到x在fa中的下标
int cast(int x) {
    return lower_bound(num, num + cnt, x) - num;
}
int get(int x) {
    if (x != fa[x])
        fa[x] = get(fa[x]);
    return fa[x];
}
int merge(int x, int y) {
    fa[get(x)] = get(y);
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        cnt = 0;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i] >> st[i];
            num[cnt++] = a[i], num[cnt++] = b[i];
        }
        // 去重
        sort(num, num + cnt);
        cnt = unique(num, num + cnt) - num;

        for (int i = 0; i < cnt; ++i) fa[i] = i;

        bool success = true;

        /*for (int i = 0; i < n; ++i) {
            int x = cast(a[i]), y = cast(b[i]);
            int x1 = get(x), x2 = get(y);
            if (st[i]) {
                merge(x, y);
            } else {
                if (x1 == x2) {
                    success = false;
                    break;
                }
            }
        }*/
        // 烫烫！！ 注意不能向上面一样边遍历边构建，需要先将所有相等的合并，再检查不相等的，若不相等得在一个集合，false
        for (int i = 0; i < n; ++i)
            if (st[i])
                merge(cast(a[i]), cast(b[i]));


        for (int i = 0; i < n; ++i) {
            if (!st[i]) {
                int x = get(cast(a[i])), y = get(cast(b[i]));
                if (x == y) {
                    success = false;
                    break;
                }
            }
        }

        if (success) cout << "YES" << endl;
        else cout << "NO" << endl;


    }
    return 0;
}



// 238. 银河英雄传说

// 带边权并查集
// 当接收到一个Cxy指令时，分别执行get(x) 和get(y)完成查询和路径压缩。若二者的返回值相同，则说明x和y处于同一列中。因为x和y此时都已经指向
// 树根，所以d[x]保存了位于x之前的战舰数量，d[y] 保存了位于y之前的战舰数量。二者之差的绝对值再减1, 就是x和y之间间隔的战舰数量。

// 当接收到一个Mxy指令时，把x的树根作为y的树根的子节点，连接的新边的权值应该设为合并之前集合y的大小(根据题意，集合y中的全部战舰都排在集
// 合x之前)。因此，我们还需要一个size 数组在每个树根上记录集合大小

#include <iostream>
using namespace std;

const int N = 300010;
int fa[N], d[N], sz[N];

int get(int x) {
    if (x == fa[x]) return x;
    int root = get(fa[x]);
    d[x] += d[fa[x]];
    return fa[x] = root;
}
void merge(int x, int y) {
    x = get(x), y = get(y);
    fa[x] = y, d[x] = sz[y];
    sz[y] += sz[x];
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < N; ++i) fa[i] = i, sz[i] = 1;

    char opr[2];
    int a, b;
    for (int i = 0; i < n; ++i) {
        cin >> opr >> a >> b;
        int x = get(a), y = get(b);
        if (opr[0] == 'M') {
            if (x != y)
                merge(a, b);
        } else {
            if (x == y) {
                cout << max(abs(d[a] - d[b]) - 1, 0) << endl;      // 烫烫！！注意是a,b
            } else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}



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
        a[cnt++] = query[i].l - 1;
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
    for (int i = 0; i < 2 * N; ++i) fa[i] = i;
    bool success = true;
    for (int i = 0; i < m; ++i) {
        int x = cast(query[i].l - 1), y = cast(query[i].r);
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



// 240. 食物链


// 带权并查集

//还是设d[x]表示x与fa[x]的关系，0代表是同类，1代表是x吃fa[x], 根据关系图自然2就代表x被fa[x]吃。
// 需要注意的是，x与y是同一集合时，并不是表示集合内是同一种类，只是说明x和y的关系确定了，通过d[x]和d[x]即可表示x和y已经确定的关系
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 100010;
int fa[N], d[N];

int get(int x) {
    if (x == fa[x]) return x;
    int root = get(fa[x]);
    d[x] += d[fa[x]];       // 这里边权直接加，后续使用会进行模，将值偏移到0，1，2
    return fa[x] = root;
}
int main()
{

    int n, k;
    cin >> n >> k;

    for (int i = 0; i <= n; ++i) fa[i] = i;

    int a, x, y, res = 0;
    bool first = true;
    while (k--) {
        cin >> a >> x >> y;

        if (x > n || y > n || n == 2 && x == y) {
            ++res;
            continue;
        }
        // 用 rel=0,表同类，rel=1，表a吃b
        int rel = 0;
        if (a == 2) rel = 1;

        int px = get(x), py = get(y);
        if (px == py) {        // x和y同一集合,说明x和y已近确定了关系
            // 得到x和y的rel关系，若不等rel，说明是假话
            if (((d[x] - d[y]) % 3 + 3) % 3 != rel) ++res;
        } else {        // 不同集合，但问题所给关系正确
            fa[px] = py;        // 确定集合
            d[px] = d[y] - (d[x] - rel);    // 确定关系,这里画个图就可以理解，注意这里的关系传递是方向性的
        }
    }
    cout << res << endl;
    return 0;
}


// 扩展域并查集

// 把每个动物x拆成三个节点，同类域，捕食域，天敌域
// 若一句话说“x 与y是同类”，则说明“x的同类”与“y的同类”一样，“x捕食的物种”与“y捕食的物种”一样，“x的天敌”与“y的天敌”一样。
//      此时，我们合并xself与yself，Xeat与yeat，Xenemy与 yenemy
// 若一句话说“x吃y”，说明“x捕食的物种”就是“y的同类”，“x的同类”都是“y的天敌”。
//      又因为题目中告诉我们食物链是长度为3的环形，所以“x的天敌”就是“y捕食的物种”(x吃 y, y 吃z, z就吃x)。此时, 应合并 xeat与 ysetf, xself 与 yenemy，Xenemy与 yeat

// 在处理每句话之前，都要检查这句话的真假。有两种信息与“x与y是同类”矛盾:1.xeat与 yself在同一集合，说明x吃y。2.xself 与yeat在同一集合，说明y吃x。有两种信息与“x吃y”矛盾:
// 1.Xself与 ysetf在同一集合，说明x与y是同类。2.Xself 与yeat在同一集合，说明y吃x。


#include <iostream>
#include <algorithm>
using namespace std;

const int N = 300010;
int fa[N];

int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}
void merge(int x, int y) {
    fa[get(x)] = get(y);
}
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i <= 3 * n; ++i) fa[i] = i;

    int opr, x, y,res=0;
    while (k--) {
        cin >> opr >> x >> y;
        int x_eat = x + n, y_eat = y + n, x_enemy = x + 2 * n, y_enemy = y + 2 * n;

        if (x > n || y > n || opr == 2 && x == y) {
            ++res;
            continue;
        }

        if (opr == 1) {     // 如果x和y是同类
            //  x不能吃y,y不能吃x
            if (get(x_eat) == get(y) || get(y_eat) == get(x)) ++res;
            else {
                merge(x, y);
                merge(x_eat, y_eat);
                merge(x_enemy, y_enemy);
            }

        } else {        // 如果x吃y
            // x和y不能在一个集合，y不能吃x
            if (get(x) == get(y) || get(y_eat) == get(x)) ++res;
            else {
                merge(x, y_enemy);
                merge(x_enemy, y_eat);
                merge(x_eat, y);
            }
        }
    }
    cout << res << endl;

    return 0;
}


