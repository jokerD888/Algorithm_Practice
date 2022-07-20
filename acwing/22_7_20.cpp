//141. 周期
// KMP next数组概念
// next数组的含义是next[i]表示以i结尾的非前缀字串与前缀字串的最大匹配长度
// 求完next数组后，循环节的长度即为i - Next[i]，实际证明可以画图，个人认为就是相同的一段一直传递，即Next[i]至少要是i的一半
// 否则前缀和后缀没有交集，就没有传递关系，也就没有循环节关系。
// 且i - Next[i]就是最小的循环节长度，若还有更小的，则说明还有更大的Next[i],显然与Next数组的概念相冲突
//
#include <iostream>
#include <cstring>
using namespace std;

const int N = 1000010;
char s[N];
int n;
int Next[N];

void get_next() {
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j && s[i] != s[j + 1]) j = Next[j];
        if (s[i] == s[j + 1])++j;
        Next[i] = j;
    }
}

int main()
{
    int cnt = 0;
    while (scanf("%d", &n), n) {
        scanf("%s", s + 1);
        get_next();

        printf("Test case #%d\n", ++cnt);
        for (int i = 2; i <= n; ++i) {
            int t = i - Next[i];    // t就是循环节的长度
            if (t != i && i % t == 0)
                printf("%d %d\n", i, i / t);
        }
        puts("");
    }
    return 0;
}