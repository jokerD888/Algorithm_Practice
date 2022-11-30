
// 196. 质数距离

// 由于N最大时2^31,所以不论什么已知算法，直接算出1~2^31-1是否是素数，时间空间都不够

// 但我们可以发现一个核心的性质：任何一个合数x，它都一定存在一个质因子 <= sqrt(x)
// 所以我们可以向将1~sqrt(2^31-1)间的质因数筛出来，那么此时[U,L]上的所有合数都存在一个1~sqrt(2^31-1)间的质因子
// 所以我们可以使用筛法的思想，将[U,L]将的合数筛出来

// 所以本题的核心点，我们要抓住[U,L]上的所有合数都存在一个1~sqrt(2^31-1)间的质因子，所以我们要先筛出这个范围上的质数，
//      再根据l和r的范围，根据所有先前已筛出的质因子，再筛出其相应倍数的合数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000010;

int primes[N], cnt;
bool st[N];

void get_primes(int n) {
    memset(st, false, sizeof st);
    cnt = 0;
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; i * primes[j] <= n; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
int main()
{
    long long l, r;
    while (cin >> l >> r) {
        get_primes(50000);
        memset(st, false, sizeof st);
        for (int i = 0; i < cnt; ++i) {
            int p = primes[i];

            // 要根据p把[l,r]上p的倍数筛掉，所以要从 大于>=l上最小的p的倍数开始筛，即从l/p上取整开始
            // 把[l,r]中所有p的倍数筛掉，p不能被筛掉，所以最小从2*p开始
            for (long long j = max((l + p - 1) / p * p, 2ll * p); j <= r; j += p) {
                st[j - l] = true;       // j-l做个偏移，因为l,r的取值太大，但l到r之间的范围可以接收
            }
        }
        // 重新记录[l,r]上的素数
        cnt = 0;
        for (int i = 0; i <= r - l; ++i) {
            if (!st[i] && i + l > 1)
                primes[cnt++] = i + l;
        }
        if (cnt < 2)puts("There are no adjacent primes.");
        else {
            int minp = 0, maxp = 0;
            for (int i = 0; i + 1 < cnt; ++i) {
                int d = primes[i + 1] - primes[i];
                if (d < primes[minp + 1] - primes[minp])minp = i;
                if (d > primes[maxp + 1] - primes[maxp])maxp = i;
            }
            printf("%d,%d are closest, %d,%d are most distant.\n", primes[minp], primes[minp + 1], primes[maxp], primes[maxp + 1]);
        }

    }
    return 0;
}




// 197. 阶乘分解


// 直接暴力分解每个数，最后一个超时

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000100;
int primes[N], cnt;
bool st[N];
int num[N];

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; i * primes[j] <= n; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
int main()
{
    int m;
    cin >> m;
    get_primes(m);
    for (int n = 2; n <= m; ++n) {
        for (int i = 0, k = n; k != 1; ++i) {
            int s = 0;
            while (k % primes[i] == 0) {
                ++s;
                k /= primes[i];
            }
            num[i] += s;
        }
    }
    vector<pair<int, int>> res;
    for (int i = 0; num[i]; ++i) {
        res.push_back({ primes[i],num[i] });
    }
    for (auto PII : res) {
        cout << PII.first << ' ' << PII.second << endl;
    }
    return 0;
}



// 我们实际上就是寻找 n!里多少个质因子p,即从大到小枚举每个质数的次数是多少
//  进而，我们要求的就是1~n中有多少个p的倍数，可以得知共有n/p下取整，其次，某些数里不知有一个p的倍数，
//      所以还需要求多少个p^2的倍数，多少个p^3的倍数.....


#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1000100;
int primes[N], cnt;
bool st[N];

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; i * primes[j] <= n; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
int main()
{
    int n;
    cin >> n;
    get_primes(n);

    for (int i = 0; i < cnt; ++i) {
        int p = primes[i];
        int s = 0, t = n;
        while (t)s += t / p, t /= p;
        cout << p << ' ' << s << endl;
    }

    return 0;
}
