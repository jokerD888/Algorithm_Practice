
// 271. 杨老师的照相排列

//从高到低依次安排每个同学的位置，那么在安排过程中，当前同学一定占据每排最靠左的连续若干个位置，
// 且从后往前每排人数单调递减。否则一定不满足“每排从左到右身高递减，从后到前身高也递减”这个要求。

// 定义f[a][b][c][d][e]为第一排站了a个人，第二排站了b个人，。。。。f[0][0][0][0][0]=1,根据最后一个人站的哪排进行划分
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int N = 31;

LL f[N][N][N][N][N];
int main()
{
    int k;
    while (cin >> k, k) {
        memset(f, 0, sizeof f);
        int s[5] = { 0 };
        for (int i = 0; i < k; ++i) cin >> s[i];

        f[0][0][0][0][0] = 1;

        for (int a = 0; a <= s[0]; ++a)
            for (int b = 0; b <= min(a, s[1]); ++b)
                for (int c = 0; c <= min(b, s[2]); ++c)
                    for (int d = 0; d <= min(c, s[3]); ++d)
                        for (int e = 0; e <= min(d, s[4]); ++e) {
                            LL& v = f[a][b][c][d][e];
                            // 站第一排
                            if (a && a - 1 >= b) v += f[a - 1][b][c][d][e];
                            // 第二排
                            if (b && b - 1 >= c) v += f[a][b - 1][c][d][e];
                            //...
                            if (c && c - 1 >= d) v += f[a][b][c - 1][d][e];
                            if (d && d - 1 >= e) v += f[a][b][c][d - 1][e];
                            if (e) v += f[a][b][c][d][e - 1];
                        }

        cout << f[s[0]][s[1]][s[2]][s[3]][s[4]] << endl;

    }
    return 0;
}




// 272. 最长公共上升子序列

// 结合LIS最长上升子序列和LCS最长公共子序列的做法
//  设f[i][j]表A1~Ai,与B1~Bj可以构成的以Bj为结尾的LCIS长度

// 首先可以根据公共子序列是否包含Ai做划分
// 当Ai!=Bi时，有f[i,j]=f[i-1,j]
// 当Ai==Bi时，有f[i,j]=max(f[i-1,k)+1  (0<=k<j,Bk<Ai) ，即枚举子序列倒数第二个元素在b[]中哪个数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 3010;
int a[N], b[N];
int f[N][N];
int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    //for (int i = 1; i <= n; ++i) {
    //    for (int j = 1; j <= n; ++j) {
    //        f[i][j] = f[i - 1][j];      // 不包含a[i]
    //        if (a[i] == b[j]) {         // 可以包含a[i]的话
    //            int maxv = 1;
    //            for (int k = 1; k < j; ++k)
    //                if (a[i] > b[k])
    //                    maxv = max(maxv, f[i - 1][k] + 1);
    //            f[i][j] = max(f[i][j], maxv);
    //        }
    //    }
    //}

    for (int i = 1; i <= n; i++) {
        int maxv = 1;
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
            if (a[i] > b[j]) maxv = max(maxv, f[i - 1][j] + 1);     // 为下一轮做准备
        }
    }

    int res = 0;
    for (int i = 1; i <= n; ++i) res = max(res, f[n][i]);
    cout << res << endl;
    return 0;
}


// 273. 分级
// 可以得知一条这样的性质，一定存在一组最优解，使得每个 Bi 都是原序列中的某个值。
// f[i,j]表给A[1~i]都分配好了且最后一个值为A'[j],A'是A排序后的值
// f[i,j]的划分类似上一题，枚举倒数第二个数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 2010;
int n;
int a[N], b[N];
int f[N][N];

int work() {
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    sort(b + 1, b + 1 + n);

    for (int i = 1; i <= n; ++i) {
        int minv = 1 << 30;
        for (int j = 1; j <= n; ++j) {
            minv = min(minv, f[i - 1][j]);
            f[i][j] = minv + abs(a[i] - b[j]);
        }
    }

    int res = 1 << 30;
    for (int i = 1; i <= n; ++i) res = min(res, f[n][i]);
    return res;

}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    int res = work();
    reverse(a + 1, a + 1 + n);
    res = min(res, work());
    cout << res << endl;
    return 0;
}