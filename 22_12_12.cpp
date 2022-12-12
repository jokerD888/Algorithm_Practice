// 244. 谜一样的牛
// 很容易想到，1~n n个数一个集合s，从后往前遍历数字a,a[i]这头牛的身高就是集合中第a[i]+1小的数，随后从集合中去除a[i]+1
//  但是并没有一种现成的集合，使其查询第k小和删除都快速的结构

// 所以转而使用树状数组+二分达成这个目的
// 具体来说，我们建立一个长度为n 的01序列b，起初全部为1。然后，从n到1倒序扫描每个A，对每个A;执行以下两个操作:
//  1.查询序列b中第A; +1个1在什么位置, 这个位置号就是第i头奶牛的身高H; 。
//  2.把 b[H]减1（从1变为0)。
//      也就是说，我们需要实时维护一个01序列，支持查询第k 个1的位置(k 为任意整数)，以及修改序列中的一个数值。
//  用树状数组c维护01序列b 的前缀和,在每次查询时二分答案,通过 ask(mid)即可得到前mid个数中有多少个1，与k比较大小，即可确定二分上下界的变化。
// 

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010;
int a[N], c[N];

int n;

int ask(int x) {
    int res = 0;
    for (; x; x -= x & -x) res += c[x];
    return res;
}
void add(int x, int y) {
    for (; x <= n; x += x & -x) c[x] += y;
}
int main()
{
    cin >> n;

    for (int i = 1; i <= n; ++i) add(i, 1);

    for (int i = 1; i < n; ++i) cin >> a[i];


    for (int i = n - 1; i >= 0; --i) {
        int l = a[i], r = n;
        while (l < r) {
            int mid = l + r >> 1;
            if (ask(mid) < a[i] + 1) l = mid + 1;
            else r = mid;
        }
        a[i] = l;
        add(l, -1);
    }
    for (int i = 0; i < n; ++i)
        cout << a[i] << endl;

    return 0;
}


// 上法单次操作确定一头牛的身高需要O(logn * logn) 
//  可以使用树状数组+倍增，使得单词操作实际达到O(logn)
// 具体的：
//   用树状数组c维护01序列b 的前缀和，在每次查询时 :
//      1.初始化两个变量ans = 0和 sum = 0。
//      2.从 logn（下取整）到0倒序考虑每个整数p。
//          对于每个 p, 若 ans + 2^P≤n且 sum + c[ans + 2^P] < k, 则令 sum += c[ans + 2^P]，ans += 2^P。
//      3.最后，Hi = ans + 1即为所求。
//      思想是以2的整数次幂为步长，能累加则累加


#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 100010;
int a[N], c[N];

int n;

int ask(int x) {
    int res = 0;
    for (; x; x -= x & -x) res += c[x];
    return res;
}
void add(int x, int y) {
    for (; x <= n; x += x & -x) c[x] += y;
}
int main()
{
    cin >> n;

    for (int i = 1; i <= n; ++i) add(i, 1);

    for (int i = 1; i < n; ++i) cin >> a[i];

    int maxP = log2(n);
    for (int i = n - 1; i >= 0; --i) {
        int ans = 0, sum = 0;
        for (int p = maxP; p >= 0; --p) {       // p为步长
            if (ans + (1 << p) <= n && sum + c[ans + (1 << p)] < a[i] + 1) {
                sum += c[ans + (1 << p)], ans += (1 << p);
            }
        }
        a[i] = ans + 1;
        add(ans + 1, -1);
    }
    for (int i = 0; i < n; ++i)
        cout << a[i] << endl;

    return 0;
}
