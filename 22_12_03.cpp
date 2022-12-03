// 202. 最幸运的数字
// 题目中x个8的整数可表示为 (10^x-1)/9*8，于是这个问题相当于求解最小的x满足(10^x-1)/9*8 同余 0（mod L)
// 整理得，8(10^x-1) 同余 0（mod 9L) ,将8移到右边，即10^x-1 同余 0（mod 9L/gcd(L,8))
// 即10^x 同余 1（mod 9L/gcd(L,8))    
// 令 p=9L/gcd(L,8)，考虑到x和p不一定互质，所以应用欧拉定理，得出一个可行解， 令 x=phi(p) , 10^phi(p) 同余 1（mod p)
// 由于phi(p)不一定是满足条件得最小自然数，但是可以证明满足上式的x一定是phi(p)的因子，于是我们枚举phi(p)的因子判断是否满足条件即可
//      
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
// 龟速乘，避免大数乘大数溢出
LL mul(LL a, LL b, LL p) {
    LL res = 0, t = a % p;
    while (b) {
        if (b & 1) res = (res + t) % p;
        t = (t + t) % p;
        b >>= 1;
    }
    return res;
}
// 快速幂
LL qmi(LL m, LL k, LL p) {
    LL res = 1, t = m % p;
    while (k) {
        if (k & 1) res = mul(res, t, p);
        t = mul(t, t, p);
        k >>= 1;
    }
    return res;
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
// 求欧拉函数，分解质因数基础上同时计算欧拉函数
LL get_euler(LL x) {
    auto res = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) res = res / x * (x - 1);
    return res;
}
int main()
{
    LL l;
    for (int T = 1;; ++T) {
        cin >> l;
        if (!l) break;
        l = l * 9 / gcd(l, 8);
        auto euler = get_euler(l);

        LL res = 1e18;
        for (LL i = 1; i * i <= euler; ++i) {
            if (euler % i == 0) {
                if (qmi(10, i, l) == 1) res = min(res, i);
                if (qmi(10, euler / i, l) == 1) res = min(res, euler / i);
            }
        }
        if (res > 1e16) res = 0;

        printf("Case %d: %d\n", T, res);

    }
    return 0;
}