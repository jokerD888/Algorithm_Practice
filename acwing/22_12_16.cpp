
// 245. 你能回答这些问题吗

// 线段数，其中线段树节点中 sum是记录区间的和，dat是区间的最大连续和，lmax是从左端点开始的最大连续和，rmax是从右端点开始的最大连续和

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 500010;

struct node {
    int l, r, dat,sum,lmax,rmax;
}t[N*4];
int a[N];

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) {
        t[p].dat = t[p].sum = t[p].lmax = t[p].rmax = a[l];
        return;
    }

    int mid = l + r >> 1;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    
    t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
    t[p].lmax = max(t[p * 2].lmax, t[p * 2].sum + t[p * 2 + 1].lmax);
    t[p].rmax = max(t[p * 2 + 1].rmax, t[p * 2 + 1].sum + t[p * 2].rmax);
    t[p].dat = max({ t[p * 2].dat, t[p * 2 + 1].dat, t[p * 2].rmax + t[p * 2 + 1].lmax });
}
void change(int p, int x, int v) {
    if (t[p].l == t[p].r) {
        t[p].dat = t[p].sum = t[p].lmax = t[p].rmax = v;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if (x <= mid) change(p * 2, x, v);
    else change(p * 2 + 1, x, v);

    t[p].sum = t[p * 2].sum + t[p * 2 + 1].sum;
    t[p].lmax = max(t[p * 2].lmax, t[p * 2].sum + t[p * 2 + 1].lmax);
    t[p].rmax = max(t[p * 2 + 1].rmax, t[p * 2 + 1].sum + t[p * 2].rmax);
    t[p].dat = max({ t[p * 2].dat, t[p * 2 + 1].dat, t[p * 2].rmax + t[p * 2 + 1].lmax });

}


node ask(int p, int l, int r) {
    if (l <= t[p].l && r >= t[p].r) return t[p];
    int mid = t[p].l + t[p].r >> 1;

    if (r <= mid) return ask(p * 2, l, r);
    else if (l > mid) return ask(p * 2 + 1, l, r);
    else {
        auto left = ask(p * 2, l, r);                   // 烫烫！！注意最后还要结算一下
        auto right = ask(p * 2 + 1, l, r);
        node res;
        res.sum = left.sum + right.sum;
        res.lmax = max(left.lmax, left.sum + right.lmax);
        res.rmax = max(right.rmax, right.sum + left.rmax);
        res.dat = max({ left.dat, right.dat, left.rmax + right.lmax });
        return res;
    }
}
int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, 1, n);

    int q, x, y;
    while (m--) {
        cin >> q >> x >> y;
        if (q == 1) {
            if (x > y) swap(x, y);
            cout << ask(1, x, y).dat << endl;
        } else {
            change(1, x, y);
        }
    }

    return 0;
}

// 简化代码
#include <bits/stdc++.h>
using namespace std;

const int N = 500010;

int n, m;
int w[N];
struct node {
    int l, r;
    int tmax, lmax, rmax, sum;
} tr[N * 4];

void pushup(node& u, node& l, node& r) {
    u.sum = l.sum + r.sum;
    u.lmax = max(l.lmax, l.sum + r.lmax);
    u.rmax = max(r.rmax, r.sum + l.rmax);
    u.tmax = max(l.rmax + r.lmax, max(l.tmax, r.tmax));
}

void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    if (l == r) tr[u] = { l, r, w[r], w[r], w[r], w[r] };
    else {
        tr[u] = { l, r };
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) tr[u] = { x, x, v, v, v, v };
    else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}

node query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u];

    int mid = tr[u].l + tr[u].r >> 1;
    if (r <= mid) return query(u << 1, l, r);
    else if (l > mid) return query(u << 1 | 1, l, r);
    else {
        auto left = query(u << 1, l, r);
        auto right = query(u << 1 | 1, l, r);
        node res;
        pushup(res, left, right);
        return res;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];

    build(1, 1, n);


    int op, x, y;
    while (m--) {
        cin >> op >> x >> y;
        if (op == 1) {
            if (x > y) swap(x, y);
            cout << query(1, x, y).tmax << endl;
        } else {
            modify(1, x, y);
        }
    }

    return 0;
}



// 246. 区间最大公约数

// 由九章算术之更相减损术，知 gcd(x,y)=gcd(x,y-x),进一步扩展，gcd(x,y,z)=gcd(x,y-x,z-y)
// 因此我们可以构造一个长度为N的新数列B,其中，B[i]=A[i]-A[i-1],B[1]可为任意值，数列B称为A的差分序列，用线段树维护序列B的区间最大公约数
//     这样一来，Q l r ,即gcd(A[l],aks(1,l+1,r))
//      C l r d时，B[l]加d,B[r+1]减去d
// 总之就是使用差分序列，使得区间的修改变为单点修改，具体来说，利用差分序列，使得区间上增加同一个值d转变为B[l]加上d,B[r-1]减去d
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;

const int N = 500010;
struct node {
    int l, r;
    LL sum, d;
}t[N * 4];

LL a[N];
int n, m;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

void pushUp(node& p, node& l, node& r) {
    p.sum = l.sum + r.sum;
    p.d = gcd(l.d, r.d);
}
void pushUp(int p) {
    pushUp(t[p], t[p << 1], t[p << 1 | 1]);
}
void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) {
        t[p].sum = t[p].d = a[l] - a[l - 1];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushUp(p);
}
void change(int p, int x, LL v) {       // 烫烫！！注意这里的v是LL类型
    if (t[p].l == x && t[p].r == x) {
        LL b = t[p].sum + v;
        t[p] = { x,x,b,b};
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if (x <= mid) change(p << 1, x, v);
    else change(p << 1 | 1, x, v);
    pushUp(p);
}
node ask(int p, int l, int r) {
    if (l <= t[p].l && r >= t[p].r) return t[p];
    int mid = t[p].l + t[p].r >> 1;
    if (r <= mid) return ask(p << 1, l, r);
    else if (l > mid) return ask(p << 1 | 1, l, r);
    else {
        auto left = ask(p << 1, l, r);
        auto right = ask(p << 1|1, l, r);
        node res;
        pushUp(res, left, right);
        return res;
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    // char opr[2], l, r;      // 烫烫！！注意不要写一起了
    char opr[2];
    int l, r;
    LL d;
    while (m--) {
        cin >> opr >> l >> r;
        if (opr[0] == 'C') {
            cin >> d;
            change(1, l, d);
            if (r + 1 <= n) change(1, r + 1, -d);
        } else {
            node left = ask(1, 1, l), right = { 0,0,0,0 };
            if (l + 1 <= r) right = ask(1, l + 1, r);
            cout << abs(gcd(left.sum, right.d)) << endl;
        }


    }
    return 0;
}






// 247. 亚特兰蒂斯
// 扫描线，对每个长方形的左右两条边记录，即每个长方形即为两个线段，（x,y1,y2,k),k为1表长方形的左边，-1表右边，对所有边排序
// 竖直方向对纵坐标区间做线段树，节点维护着两个变量，cnt表这段区间被覆盖的次数，len表这段区间的长度，特殊的是由于扫描线的特性，不需要向下传延迟标记。
//      因为长方形一左一右相等，线段树增加的和减小的都是
// 需要注意的是，值得说明的是，四元组中的 y1,y2 都是坐标，是一个“点”。我们需要维护的是扫描线上每一段被覆盖的次数及其长度，对“点”的覆盖次数进行统计是没有意义的。
//     从左往右遍历线段，并进行结算
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100010;

int n;
struct Segment {
    double x, y1, y2;
    int k;
    bool operator<(const Segment& t) const {
        return x < t.x;
    }
}seg[N * 2];
struct node {
    int l, r;
    int cnt;
    double len;
}t[N * 8];

vector<double> ys;
int find(double y) {
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}
void pushUp(int p) {
    if (t[p].cnt) t[p].len = ys[t[p].r + 1] - ys[t[p].l];
    else if (t[p].l != t[p].r) {
        t[p].len = t[p << 1].len + t[p << 1 | 1].len;
    } else t[p].len = 0;    // 叶子
}
void build(int p, int l, int r) {
    t[p] = { l,r,0,0 };
    if (l != r) {
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
}
void change(int p, int l, int r, int k) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].cnt += k;
        pushUp(p);
    } else {
        int mid = t[p].l + t[p].r >> 1;
        if (l <= mid) change(p << 1, l, r, k);
        if (r > mid) change(p << 1 | 1, l, r, k);
        pushUp(p);
    }
}
int main()
{
    int T = 0;
    while (scanf("%d", &n), n) {
        ys.clear();
        for (int i = 0, j = 0; i < n; ++i) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[j++] = { x1,y1,y2,1 };
            seg[j++] = { x2,y1,y2,-1 };
            ys.push_back(y1), ys.push_back(y2);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        build(1, 0, ys.size() - 2);     // 点的个数是ys.size(),线段树存的是区间，所以比点个数还要小1

        sort(seg, seg + n * 2);
        double res = 0;
        for (int i = 0; i < n * 2; ++i) {
            if (i > 0) res += t[1].len * (seg[i].x - seg[i - 1].x);
            change(1, find(seg[i].y1), find(seg[i].y2) - 1, seg[i].k);  // 维护的是区间，ys[find(seg[i].y2)-1]这个段的上有端点就是seg[i].y2
        }
        printf("Test case #%d\n", ++T);
        printf("Total explored area: #%.2lf\n\n", res);

    }
    return 0;
}




// 248. 窗内的星星
//  因为矩形的大小固定，所以矩形可以由它的任意一个顶点唯一确定。我们可以考虑把矩形的右上角顶点放在什么位置，圈住的星星亮度总和最大。
//   对于一个星星 (x,y,c)，其中 x,y为坐标，c为亮度，“能圈住这颗星星的矩形右上角顶点坐标的范围”如下页图所示。该范围也是一个矩形，左下角顶点为(x, y),右上角顶点为(x +w,y + h)。
//          为了避免歧义，在接下来的讨论中，我们用“区域”一词来代指这个范围。
// 题目中说“矩形边界上的星星不算”。为了处理这种边界情况，不妨把所有星星向左、向下各移动0.5的距离，坐标从(x,y)变为(x -0.5, y -0.5)。
//      在此基础上，不妨假设圈住星星的矩形顶点坐标都是整数。于是，“区域”的左下角可看作(x, y)，右上角可看作(x +w -1,y +h-1)，边界也算在内。容易证明这些假设不会影响答案。

// 此时，问题转化为:平面上有若干个区域，每个区域都带有一个权值，求在哪个坐标上重叠的区域权值和最大。其中，每一个区域都是由一颗星星产生的，权值等于星星的亮度，把原问题中的矩形右上角放在该区域中，就能圈住这颗星星。
// 在转化后的问题中，我们使用扫描线算法,取出每个区域的左右边界，保存成两个四元组 (x，y,y +h-1,c)和(x + w,y,y + h-1，-c)。把这些四元组按照横坐标(第一维的值）排序。
//      同时，关于纵坐标建立一棵线段树，维护区间最大值 dat，起初全为零。因为我们已经平移了星星的坐标，并假设矩形只能放在整点上，所以线段树维护的相当于是若干个数值（纵坐标整点上的权值和）构成的序列。
//      逐一扫描每个四元组(x, y1yz, c)，在线段树中执行区间修改(可用延迟标记实现)，把[yuy2] 中的每个数都加 c，然后用根节点的dat值更新答案即可。


#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int N = 20010;
struct node {
    LL x, y1, y2, dat;
    bool operator<(const node& t) const {
        if (x == t.x) return dat < t.dat;//不能少了这一句，不然同一横坐标的删除和添加会先加后删，导致结果变大！！！！
        return x < t.x;
    }
}a[N * 2];
struct SegmTree {
    LL l, r;
    LL dat, add;
}t[8 * N];
vector<int> ys;
int find(LL y) {
    return lower_bound(ys.begin(), ys.end(),y) - ys.begin();
}
void build(LL p, LL l, LL r) {
    t[p] = { l,r,0,0 };
    if (l != r) {
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
    }
}
void spread(LL p) {
    t[p << 1].dat += t[p].add;
    t[p << 1 | 1].dat += t[p].add;
    t[p << 1].add += t[p].add;
    t[p << 1 | 1].add += t[p].add;
    t[p].add = 0;       // 清除标记
}
void change(LL p, LL l, LL r, LL x) {
    if (l <= t[p].l && r >= t[p].r) {
        t[p].add += x;
        t[p].dat += x;
        return;
    }
    if (t[p].add) spread(p);    // 懒不住了，下发已有懒标记
    LL mid = t[p].l + t[p].r >> 1;
    if (l <= mid) change(p << 1, l, r, x);
    if (r > mid) change(p << 1 | 1, l, r, x);
    t[p].dat = max(t[p << 1].dat, t[p << 1 | 1].dat);       // 更新节点

}


int main()
{
    LL n, w, h, x, y, c;
    while (scanf("%lld%lld%lld", &n, &w, &h)!=EOF) {
        ys.clear();
        memset(t, 0, sizeof t);
        for (int i = 0,j=0; i < n; ++i) {
            scanf("%lld%lld%lld", &x, &y, &c);
            a[j++] = { x,y,y + h - 1,c };
            a[j++] = { x + w,y,y + h - 1,-c };
            ys.push_back(y), ys.push_back(y + h - 1);
        }
        sort(ys.begin(),ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());

        sort(a, a + 2 * n);
        build(1, 0, ys.size()-1);
        LL res = 0;
        for (int i = 0; i < 2 * n; ++i) {
            change(1, find(a[i].y1), find(a[i].y2), a[i].dat);
            res = max(res, t[1].dat);
        }
        cout << res << endl;

    }
    return 0;
}
