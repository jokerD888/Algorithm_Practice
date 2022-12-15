
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
struct Segment{
    double x, y1, y2;
    int k;
    bool operator<(const Segment& t) const {
        return x < t.x;
    }
}seg[N*2];
struct node {
    int l, r;
    int cnt;
    double len;
}t[N*8];

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
        if(r>mid) change(p << 1 | 1, l, r, k);
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