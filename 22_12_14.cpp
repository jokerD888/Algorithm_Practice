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

