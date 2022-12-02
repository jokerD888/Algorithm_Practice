
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