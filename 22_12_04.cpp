
// 203. 同余方程

// 根据线性同余方程的相关概念
// a*x 同余 b(mod m) 等价于 a*x-b 是m的倍数，不妨设为-y倍，于是改方程可改写为a*x+m*y=b，根据斐蜀定理及其证明过程，线性同余方程有解当且仅当gcd(a,m) | b
// 有解时，先用欧几里得算法求出一组整数x0,y0,满足a*x0+m*y0=gcd(a,m),然后，x=x0*b/gcd(a,m)就是原线性同余方程的一个解，方程的通解则是所有模 m/gcd(a,m)与x同余的整数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

int main()
{
    int a, b;
    cin >> a >> b;
    int x, y;
    int d = exgcd(a, b, x, y);
    x = x / d;        
    cout << (x % b/d + b/d) % b/d << endl;      // 要求最小的正整数，调整到合适位置
    return 0;
}




// 204. 表达整数的奇怪方式

#include <cstdio>
#include <iostream>
using namespace std;
typedef long long LL;
int n;
LL exgcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
LL inline mod(LL a, LL b) {
    return ((a % b) + b) % b;
}
int main() {
    scanf("%d", &n);
    LL a1, m1;
    scanf("%lld%lld", &a1, &m1);
    for (int i = 1; i < n; i++) {
        LL a2, m2, k1, k2;
        scanf("%lld%lld", &a2, &m2);
        LL d = exgcd(a1, -a2, k1, k2);
        if ((m2 - m1) % d) { puts("-1"); return 0; }
        k1 = mod(k1 * (m2 - m1) / d, abs(a2 / d));
        m1 = k1 * a1 + m1;
        a1 = abs(a1 / d * a2);
    }
    printf("%lld\n", m1);
    return 0;
}
