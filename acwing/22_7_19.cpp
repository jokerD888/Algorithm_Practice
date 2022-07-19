
// 137. 雪花雪花雪花

// 找循环同构串的最小表示法，然后排序比较

//#include <cstdio>
//#include <cstring>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//const int N = 100010;
//
//int n;
//int snows[N][6], idx[N];
//
//// 求循环同构串的最小表示法
//void get_min(int* b)
//{
//    static int a[12];
//    for (int i = 0; i < 12; i++) a[i] = b[i % 6];   // 将b串复制两份到a
//
//    int i = 0, j = 1, k;
//    while (i < 6 && j < 6)
//    {
//        for (k = 0; k < 6 && a[i + k] == a[j + k]; k++);    // 找不同
//        if (k == 6) break;  // 找完了还没找到，break
//
//        if (a[i + k] > a[j + k])    
//        {
//            i += k + 1;  
//            if (i == j) i++;    // 两个串得错开，要是一直相等，就找不出来了
//        } else
//        {
//            j += k + 1;
//            if (i == j) j++;
//        }
//    }
//
//    k = min(i, j);
//    // 将最小表示复制到b
//    for (i = 0; i < 6; i++) b[i] = a[i + k];
//}
//// 返回字典序a<b
//bool cmp(int a, int b)
//{
//    for (int i = 0; i < 6; i++)
//        if (snows[a][i] < snows[b][i])
//            return true;
//        else if (snows[a][i] > snows[b][i])
//            return false;
//    return false;
//}
//
//// 按字典序排序
//bool cmp2(int a[], int b[])
//{
//    for (int i = 0; i < 6; i++)
//        if (a[i] < b[i])
//            return true;
//        else if (a[i] > b[i])
//            return false;
//    return false;
//}
//
//int main()
//{
//    scanf("%d", &n);
//    int snow[6], isnow[6];
//    for (int i = 0; i < n; i++)
//    {
//        for (int j = 0, k = 5; j < 6; j++, k--)
//        {
//            scanf("%d", &snow[j]);  // 正序
//            isnow[k] = snow[j];     // 逆序
//        }
//        get_min(snow);
//        get_min(isnow);
//        // 将最小的复制到数组
//        if (cmp2(snow, isnow)) memcpy(snows[i], snow, sizeof snow);
//        else memcpy(snows[i], isnow, sizeof isnow);
//
//        idx[i] = i; //记录下标，后续用于排序
//    }
//
//    sort(idx, idx + n, cmp);
//
//    for (int i = 1; i < n; i++)
//    {
//        // 两个相同的
//        if (!cmp(idx[i], idx[i - 1]) && !cmp(idx[i - 1], idx[i]))
//        {
//            puts("Twin snowflakes found.");
//            return 0;
//        }
//    }
//
//    puts("No two snowflakes are alike.");
//    return 0;
//}


// 138. 兔子与兔子


// 字符串哈希
// 字符串hash函数把任意一个长度的字符串映射成一个非负整数，并且其冲突概率机会为0
// 具体做法：取一固定值p(经验值取131或13331），并且给每个字符分配一个大于0的数值，一般来说，我们分配的数值都远小于P。
// 例如，对于小写字母构成的字符串，可以令a = 1,b = 2,…,z= 26。取一固定值M，求出该Р进制数对M的余数，作为该字符串的Hash 值。
// 一般来说，我们取P=131或P= 13331，此时 Hash值产生冲突的概率极低,只要Hash值相同，我们就可以认为原字符串是相等的。
// 通常我们取M= 264，即直接使用unsigned long long类型存储这个Hash值，在计算时不处理算术溢出问题，产生溢出时相当于自动对2^64取模，这样可以避免低效的取模(mod)运算。

//
//#include <iostream>
//#include <cstring>
//using namespace std;
//
//typedef unsigned long long ULL;
//const int N = 1000010, base = 131;
//
//char str[N];
//ULL h[N], p[N];
//
//ULL get(int l, int r) {
//    return h[r] - h[l - 1] * p[r - l + 1];
//}
//
//int main()
//{
//    scanf("%s", str + 1);
//    int n = strlen(str + 1);
//
//    p[0] = 1;
//    for (int i = 1; i <= n; ++i) {
//        h[i] = h[i - 1] * 131 + str[i] - 'a' + 1;
//        p[i] = p[i - 1] * base;
//    }
//    int m;
//    scanf("%d", &m);
//    while (m--) {
//        int l1, r1, l2, r2;
//        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
//        if (get(l1, r1) == get(l2, r2)) {
//            puts("Yes");
//        } else {
//            puts("No");
//        }
//    }
//    return 0;
//}
//
//
//
//// 139. 回文子串的最大长度
//
//// 法一：二分+字符串哈希
//
//// 思路：利用字符串哈希可以O(1)对比两个串是否相同，先正序对S求一遍前缀哈希，再逆序求一遍，
//// 随后我们枚举回文串中点,回文串的终点可以是某一个数字,也可以是某一个间隙，所以我们枚举回文串中点的出现位置，再用二分求回文串的“半径”
//// O(NlogN)
//#include <iostream>
//#include <cstring>
//using namespace std;
//
//typedef unsigned long long ULL;
//const int N = 1000010, base = 131;
//char str[N];
//ULL h[N], rh[N], q[N];
//int n;
//
//ULL get1(int l, int r) {
//    return h[r] - h[l - 1] * q[r - l + 1];
//}
//ULL get2(int l, int r) {
//    int tmp = r;
//    r = n - l + 1;      // 坐标对称翻转
//    l = n - tmp + 1;
//    return rh[r] - rh[l - 1] * q[r - l + 1];
//
//}
//// index位置左边mid长度和右边mid长度不构成回文串，返回true,
//bool check1(int len, int index) {
//    return get1(index - len, index - 1) != get2(index + 1, index + len);
//}
//bool check2(int len, int index) {
//    return get1(index - len + 1, index) != get2(index + 1, index + len);
//}
//int main()
//{
//    q[0] = 1;
//    int cnt = 0;
//    while (scanf("%s", str + 1), strcmp(str + 1, "END")) {
//        n = strlen(str + 1);
//        for (int i = 1, j = n; i <= n; ++i, --j) {
//            h[i] = h[i - 1] * base + str[i] - 'a' + 1;
//            rh[i] = rh[i - 1] * base + str[j] - 'a' + 1;
//            q[i] = q[i - 1] * base;
//        }
//        int res = 1;
//
//        for (int i = 1; i <= n; ++i) {
//            int l = 0, r = min(i - 1, n - i);     // 奇数，终点是str[i]
//            while (l < r) {
//                int mid = l + r + 1 >> 1;
//                if (check1(mid, i))
//                    r = mid - 1;
//                else
//                    l = mid;
//            }
//            res = max(res, l * 2 + 1);
//
//            l = 0, r = min(i, n - i);      // 偶数,终点是str[i]后的间隙
//            while (l < r) {
//                int mid = l + r + 1 >> 1;
//                if (check2(mid, i))
//                    r = mid - 1;
//                else
//                    l = mid;
//            }
//            res = max(res, l * 2);
//        }
//        printf("Case %d: %d\n", ++cnt, res);
//
//    }
//
//    return 0;
//
//}
//// 也可以先预处理，在每个间隙插入一个字符，这样不管原来是奇数还是偶数个，最终都会变为奇数，这样就不用判断奇偶的问题了
//// 如下
//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//typedef unsigned long long ULL;
//const int N = 2000010, base = 131;
//
//char str[N];
//ULL hl[N], hr[N], p[N];
//
//ULL get(ULL h[], int l, int r)
//{
//    return h[r] - h[l - 1] * p[r - l + 1];
//}
//
//int main()
//{
//    int T = 1;
//    while (scanf("%s", str + 1), strcmp(str + 1, "END"))
//    {
//        int n = strlen(str + 1);
//        for (int i = n * 2; i; i -= 2)  // 从后往前插入
//        {
//            str[i] = str[i / 2];
//            str[i - 1] = 'a' + 26;      // 间隙插入字符
//        }
//        n *= 2;
//        str[++n] = 'a' + 26;    // 若不加此步，字符串的最后边没有插入‘#’，而最前面加了‘#’，后续结果需要特判
//        p[0] = 1;
//        for (int i = 1, j = n; i <= n; i++, j--)
//        {
//            hl[i] = hl[i - 1] * base + str[i] - 'a' + 1;
//            hr[i] = hr[i - 1] * base + str[j] - 'a' + 1;
//            p[i] = p[i - 1] * base;
//        }
//
//        int res = 0;
//        for (int i = 1; i <= n; i++)
//        {
//            int l = 0, r = min(i - 1, n - i);
//            while (l < r)
//            {
//                int mid = l + r + 1 >> 1;
//                if (get(hl, i - mid, i - 1) != get(hr, n - (i + mid) + 1, n - (i + 1) + 1)) r = mid - 1;
//                else l = mid;
//            }
//            // 若最后面不加‘#',需要特判
//            //if (str[i - l] <= 'z')  // 若回文串最左边不是‘#’，数量+1
//            //    res = max(res, l + 1);
//            //else
//            //    res = max(res, l);
//            res = max(res, l);
//        }
//
//        printf("Case %d: %d\n", T++, res);
//    }
//
//    return 0;
//}
//
//
//// 法二：字符串哈希优化
//// 我们发现：一旦第以 i 个字符为中心的最大回文串的长度为 res，则后面字符回文串长度若是小于 res 则不会更新解。
////所以我们不用浪费时间去二分答案，可以从以上一个字符为中心求出的最大回文串长度的基础上，进行判断下一个字符是否可能成为最大回文串的对称中心。
////因为每次判断的回文串长度都是非递减的，所以总的时间复杂度为 O(n)
//
//#include <iostream>
//#include <cstring>
//#include <algorithm>
//#include <cstdio>
//#include <cmath>
//using namespace std;
//
//#define ull unsigned long long
//const int N = 2000010, P = 131;
//
//char s[N];
//ull h1[N], h2[N], p[N];
//
//ull get(ull h[], ull l, ull r)
//{
//    return h[r] - h[l - 1] * p[r - l + 1];
//}
//
//int main()
//{
//    int cnt = 0;
//    while (scanf("%s", s + 1) && strcmp(s + 1, "END"))
//    {
//        int n = strlen(s + 1) * 2;
//        for (int i = n; i; i -= 2)
//        {
//            s[i] = s[i / 2];
//            s[i - 1] = 'z' + 1;
//        }
//        s[++n] = 'z' + 1;
//        p[0] = 1;
//        for (int i = 1, j = n; i <= n; i++, j--)
//        {
//            h1[i] = h1[i - 1] * P + s[i] - 'a' + 1;
//            h2[i] = h2[i - 1] * P + s[j] - 'a' + 1;
//            p[i] = p[i - 1] * P;
//        }
//        ull ans = 1;
//        // 以下最多循环2*n次，i从0到n,ans最多为n/2,整体O(N)
//        for (int i = 1; i <= n; i++)
//        {
//            ull r = min(i - 1, n - i);
//            if (ans >= r || get(h1, i - ans, i - 1) != get(h2, n - (i + ans) + 1, n - i))
//            {
//                continue;
//            }
//            while (ans <= r && get(h1, i - ans, i - 1) == get(h2, n - (i + ans) + 1, n - i))
//            {
//                ans++;
//            }
//            ans--;
//        }
//        printf("Case %d: %d\n", ++cnt, ans);
//    }
//    return 0;
//}
//
//
//
//// 法三：Manacher(马拉车）算法
//#include <iostream>
//#include <cstring>
//#include <algorithm>
//#include <cstdio>
//#include <cmath>
//using namespace std;
//
//const int N = 2000010, P = 131;
//
//char s[N];
//int p[N];
//
//int main()
//{
//    int cnt = 0;
//    while (scanf("%s", s + 1) && strcmp(s + 1, "END"))
//    {
//        int n = strlen(s + 1) * 2;
//        for (int i = n; i; i -= 2)
//        {
//            s[i] = s[i / 2];
//            s[i - 1] = 'z' + 1;
//        }
//        s[++n] = 'z' + 1;
//        int c = 0, r = 0, res = 0;   // 下标从0开始的话，就得初始化为-1
//        for (int i = 1; i <= n; ++i) {
//            // 先算i位置扩出来的位置起码有多大
//            p[i] = r > i ? min(p[2 * c - i], r - i) : 1;
//
//            // 左右两边扩，如果可以的话
//            while (i + p[i] <= n && i - p[i] > 0) {     // 左侧右侧不越界的话
//                if (s[i + p[i]] == s[i - p[i]])
//                    ++p[i];
//                else
//                    break;
//            }
//
//            if (i + p[i] > r) {
//                r = i + p[i];
//                c = i;
//            }
//            res = max(res, p[i] - 1);
//        }
//
//        printf("Case %d: %d\n", ++cnt, res);
//    }
//    return 0;
//}



// 140. 后缀数组

// 快排，字符串哈希，二分
// 直接快排是比较O(NlogN)次，每次最坏比较需要O(N)次，所以总体O(N^2logN)
// 快排是没办法优化，可以利用二分和字符串哈希来优化比较操作达到O(logN) 总体即可达到O(Nlog^2N)



#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

typedef unsigned long long ULL;
const int N = 300010, base = 131;
int sa[N];
ULL h[N], q[N];
char s[N];
int n;

ULL get(int l, int r) {
    // 这里的r是长度，实际的r是l+r-1
    return h[r - 1] - h[l - 1] * q[r - l];
}
// a!=b
bool check(int a, int b, int i) {
    return get(a, a + i) != get(b, b + i);
}

int binary(int a, int b) {
    int l = 0, r = min(n - a, n - b) + 1;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (check(a, b, mid))
            r = mid - 1;
        else
            l = mid;
    }
    return l;
}
// a<b
bool cmp(int a, int b) {
    int i = binary(a, b);   // 查找其最长公共子序列的长度
    //if (a + i <= n && b + i <= n) {   // 其后还有位置
    //    return s[a + i] < s[b + i];
    //}
    //return b + i <= n;  // a后面没位置了，b后面还有位置的话，true

    // 或
    int av = a + i > n ? INT_MIN : s[a + i];
    int bv = b + i > n ? INT_MIN : s[b + i];
    return av < bv;
}
int main()
{

    scanf("%s", s + 1);
    n = strlen(s + 1);
    q[0] = 1;
    for (int i = 1; i <= n; ++i) {
        h[i] = h[i - 1] * base + s[i] - 'a' + 1;
        q[i] = q[i - 1] * base;
    }
  
    for (int i = 1; i <= n; ++i) sa[i] = i;
    sort(sa + 1, sa + 1 + n, cmp);
    for (int i = 1; i <= n; ++i) printf("%d ", sa[i] - 1);
    puts("");

    printf("0 ");
    for (int i = 2; i <= n; ++i) {
        printf("%d ", binary(sa[i], sa[i - 1]));
    }
    puts("");

    return 0;
}