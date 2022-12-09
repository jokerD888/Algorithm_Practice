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

