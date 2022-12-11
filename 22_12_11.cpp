
//
// 241. 楼兰图腾

// 逆序对
// 数据范围较小，利用树状数据求逆序对
// 分别求出右边比a[i]小的,以及右边比a[i]大的，左边比a[i]小的,以及左边比a[i]大的, 并计算结果

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;
const int N = 200010;
int a[N], c[N];
int low[N], high[N];


void add(int x, int y) {
    for (; x <= N; x += x & -x) c[x] += y;
}
int ask(int x) {
    int res = 0;
    for (; x; x -= x & -x) res += c[x];
    return res;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    // 统计右边比a[i]小的,以及右边比a[i]大的
    for (int i = n - 1; i >= 0; --i) {
        low[i] += ask(a[i] - 1);
        high[i] += ask(n) - ask(a[i]);
        add(a[i], 1);
    }

    LL resA = 0, resV = 0;
    memset(c, 0, sizeof c);
    // 统计左边比a[i]小的,以及左边比a[i]大的, 并计算结果
    for (int i = 0; i < n; ++i) {
        resA += ask(a[i] - 1) * (LL)low[i];
        resV += (LL)high[i] * (ask(n) - ask(a[i]));
        add(a[i], 1);
    }
    cout << resV << ' ' << resA << endl;
    return 0;
}




// 242. 一个简单的整数问题

// 树状数组擅长的是 区间的查询和单点修改，我们把“维护数列的具体值”转化为“维护指令的累加影响”。
//      每次修改的影响在 l 处产生，在 r+1 处消除，“影响”的前缀和b[1~x]就代表了数组a[x]的变化情况
//   巧妙的把“区间增加” + “单点查询” 变为 树状树状擅长的 “单点修改” + “区间查询”

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 100010;

LL a[N], b[N];

int n, k;

void add(int x, int y) {
    for (; x <= n; x += x & -x) b[x] += y;
}
int ask(int x) {
    int res = 0;
    for (; x; x -= x & -x) res += b[x];
    return res;
}
int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    char opr[2];
    int l, r, x;
    while (k--) {
        cin >> opr;
        if (opr[0] == 'C') {
            cin >> l >> r >> x;
            add(l, x);
            add(r + 1, -x);
        } else {
            cin >> x;
            cout << (ask(x) + a[x]) << endl;
        }
    }
    return 0;
}


// 243. 一个简单的整数问题2

// 对于上一个问题，我们使用数组b来维护指令的累加影响，累加 b[i] (i从0到x) ,就是经过这些指令后a[x]增加的结果
//   那么序列a的前缀和a[1~x]，整体增加的值为：
//      累加（累加 i从1到x) b[j](j从1到i) = (b[1]) + (b[1] + b[2]) + (b[1]+b[2]+b[3]) +... =  （x+1)累加(i从1到x)b[i] - 累加（i从1到x)i*b[i]

// 所以再开一个树状数组用于维护（i*b[i])的前缀和

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100010;
typedef long long LL;
int a[N];
LL sum[N], c[2][N];
int n, m;


void add(int k, int x, int y) {
    for (; x <= n; x += x & -x) c[k][x] += y;
}
LL ask(int k, int x) {
    LL res = 0;
    for (; x; x -= x & -x) res += c[k][x];
    return res;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    
    char opr[2];
    int l, r, x;
    while (m--) {
        cin >> opr >> l >> r;
        if (opr[0] == 'C') {
            cin >>x;
            add(0, l, x);
            add(0, r + 1, -x);
            add(1, l, l * x);
            add(1, r + 1, -(r + 1) * x);

        } else {
            LL res = sum[r] + (r + 1) * ask(0, r) - ask(1, r);
            res -= sum[l - 1] + l * ask(0, l - 1) - ask(1, l - 1);
            cout << res << endl;
        }

    }
    return 0;
}