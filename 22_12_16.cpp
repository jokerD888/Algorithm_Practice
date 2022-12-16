

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
