// 343. 排序

// 传递闭包
// 对于i<j,令d[i,j]=1,对于i>j,看作j<i处理，除开i<j之外的情况，均有d[i,j]=0
// 一次遍历每个不等式，每次都进行一次Floyd,Floyd过程中同步判断矛盾情况，传递闭包完成之后，判断两两确定与否
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 30;
int n, m;
int d[N][N], e[N][N];
int Floyd() {
    memcpy(e, d, sizeof e);
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                e[i][j] |= e[i][k] & e[k][j];
                if (e[i][j] == e[j][i] && e[i][j]) return -1;
            }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (e[i][j] == e[j][i] && !e[i][j] && i != j) return 0;     // 不能确定
    return 1;
}
int main() {
    while (cin >> n >> m, n) {
        memset(d, 0, sizeof d);
        bool status = 1;
        for (int i = 1; i <= m; ++i) {
            char s[6];
            cin >> s;
            d[s[0] - 'A'][s[2] - 'A'] = 1;
            if (status) {
                int now = Floyd();
                if (now == -1) {        // 矛盾
                    printf("Inconsistency found after %d relations.\n", i);
                    status = 0;
                } else if (now == 1) {      // 可以确定两两关系
                    printf("Sorted sequence determined after %d relations: ", i);
                    // 大小值判断，如果i<j,就将j的权值ans[j]+1
                    pair<int, char> ans[N];
                    for (int j = 0; j < n; ++j) {
                        ans[j].first = 0;
                        ans[j].second = 'A' + j;
                    }
                    for (int j = 0; j < n; ++j) {
                        for (int k = 0; k < n; ++k) {
                            if (e[j][k])++ans[k].first;
                        }
                    }
                    sort(ans, ans + n);
                    for (int j = 0; j<n; ++j) printf("%c", ans[j].second);
                    puts(".");
                    status = 0;

                }
            }
        }
        if (status)puts("Sorted sequence cannot be determined.");

    }
    return 0;
}

