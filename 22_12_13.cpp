
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
