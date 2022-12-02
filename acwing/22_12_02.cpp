
// 198. 反素数

// 由反素数的定理可知，
//  1）1~N中最大的反质数，就是1~N中约数个数最多的数中最小的一个。
// 2）1~N中任何数的不同质因子都不会超过10个，且所有质因子的指数总和不超过30。
// 3）x的质因子是连续的若干个最小的质数，并且指数单调递减。

// 综上所述,我们可以使用深度优先搜索(DFS)，尝试依次确定前10个质数的指数，并满足指数单调递减、总乘积不超过N，同时记录约数的个数。
// 在这两个限制条件下，搜索量实际上非常小。每当搜索出一个满足条件的整数时我们就按照引理1的结论更新答案，最终得到约数个数最多的数中最小的一个。

// 简单来说，1~N中最大的反质数，就是1~N中约数个数最多的数中最小的一个，所以x的质因子要连续，且指数单调递减。

#include <iostream>

using namespace std;

typedef long long LL;

int ps[]{ 2,3,5,7,11,13,17,19,23,29 };
int n;
int sum = 0, minx;
// s为约数个数，p为乘积
void dfs(int u, int last, int p, int s) {
    // 当前约数个数大于已知的最大约数个数 或 等于已知的最大约数个数且p<已知约数对应的数的话
    if (s > sum || s == sum && p < minx) {
        sum = s;
        minx = p;
    }
    for (int i = 1; i <= last; ++i) {
        if ((LL)p * ps[u] > n) break;
        p *= ps[u];
        dfs(u + 1, i, p, s * (i + 1));
    }
}
int main()
{
    cin >> n;
    dfs(0, 30, 1, 1);
    cout << minx << endl;
    return 0;
}



// 199. 余数之和

// 注意到：k mod i = k - k/i * i,故可转化为计算 n*k - 累加 k/i*i (i从1到n)
// 当i<=sqrt(k)时，因为i是1到sqrt(k)的整数，所以最多只有sqrt(k)个不同的k/i 值
// i>sqrt(k)时，k/i<=sqrt(k),又因为式子取整了，所以式子只能取1 到sqrt(k) 的整数，故最多也只有 sqrt(k) 个不同的 k/i值。
// 总上所述，对于i=1~k,k/i由不超过2*sqrt(k)段组成,每一段的值就是等差数列,若下界是 x，上界是 k / (k / x)
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    long long n, k, res;
    cin >> n >> k;
    res = n * k;
    for (int x = 1, gx; x <= n; x = gx + 1) {
        //当 k/x=0 的时候，显然这段以及后面（有单调性）已经没有贡献了，可以 break。（或者直接设右端点为 n）
        gx = k / x ? min(k / (k / x), n) : n;
        res -= (k / x) * (x + gx) * (gx - x + 1) / 2;
        //       公差    首项 尾项        个数
    }
    cout << res << endl;
    return 0;
}





// 200. Hankson的趣味题

// 从lcm(b,x)=d 可知，x一定是d的约数。于是可以立即得到一个朴素的算法
//      用试除法求出d的所有约数，逐一判断是否满足两个条件，时间复杂度为O（n * sqrt(d) * logd)
//      那么总计算量是 2000 * sqrt(2*10e9) * log(2*10e9) 大致为1e8,实际上有一个测试点超时
//      为了避免试除中不能整除的耗时，先预处理出 1~sqrt(2*10^9)间所有质数，然后用这些质数去试除b1
//      因此我们可在sqrt(bi）/ log(bi)的时间将b1分解质因数
// 整体时间复杂度为 T* log(n)* sqrt(n)/ln(sqrt(n))
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int N = 45000, M = 50;
int primes[N], cnt;
bool st[N];

PII factor[M];
int cntf;
int divider[N], cntd;

void get_primes(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

void dfs(int u, int p) {
    if (u > cntf) {       // 枚举到头了，记录 
        divider[cntd++] = p;
        return;
    }
    for (int i = 0; i <= factor[u].second; ++i) {   // 枚举每个质因数的每个次方
        dfs(u + 1, p);
        p *= factor[u].first;
    }
}
int main()
{
    get_primes(N);
    int n;
    cin >> n;
    while (n--) {       // n
        int a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;

        int d = b1;
        cntf = 0;
        // 将d分解质因数
        for (int i = 0; primes[i] <= d / primes[i]; ++i) {
            int p = primes[i];
            if (d % p == 0) {
                int s = 0;
                while (d % p == 0) ++s, d /= p;
                factor[++cntf] = { p,s };
            }
        }
        if (d > 1) factor[++cntf] = { d,1 };

        // dfs枚举出b1的所有约数
        cntd = 0;
        dfs(1, 1);

        int res = 0;
        for (int i = 0; i < cntd; ++i) {   // 平均每个数的约数各位为log(n) 个
            int x = divider[i];
            if (gcd(x, a0) == a1 && (LL)x * b0 / gcd(x, b0) == b1)      // log(n)
                ++res;
        }
        cout << res << endl;
    }

    return 0;
}



// 201. 可见的点

// 分析题目容易发现，除了(1,0)，(0,1)和(1,1)这三个钉子外，一个钉子(x, y)能被看到，当且仅当1≤X,y ≤ N，x ≠y并且 gcd(x, y) = 1。
//  其次，竖直方向和垂直方向以及45度斜上方都只有最开始的一个点

// 综上，本题的答案就是 3 + 2 * 累加phi(i) (i从2到N）, 所以本题基本上就是一个纯筛法求欧拉函数


#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
int primes[N], cnt;
int euler[N];
bool st[N];

void get_euler(int n)
{
    euler[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) {
            primes[cnt++] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; ++j) {
            int t = primes[j] * i;
            st[t] = true;
            if (i % primes[j] == 0) {
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
}

int main()
{
    // 先预处理筛法求欧拉函数

    get_euler(1000);
    int T;
    cin >> T;
    int k = 0;
    while (T--) {
        int n;
        cin >> n;
        int res = 3;
        for (int i = 2; i <= n; ++i)
            res += 2*euler[i];
        printf("%d %d %d\n", ++k, n, res);
    }
    return 0;
}