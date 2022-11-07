
// 136. 邻值查找
// 链表

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<LL, int> PII;
const int N = 100010;

int n;
int l[N], r[N];
int p[N];       // 记录原序列的点在双链表中的位置
PII a[N], res[N];


int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a + 1, a + 1 + n);

    a[0].first = -4e9, a[n + 1].first = 4e9;
    for (int i = 1; i <= n; ++i) {
        l[i] = i - 1, r[i] = i + 1;
        p[a[i].second] = i;     // 记录原序列的点在双链表中的位置
    }

    // 以原序列从后往前，找到之后，就删掉该节点，以满足j<i的条件
    for (int i = n; i > 1; --i) {
        // 以原序列的顺序遍历找答案
        int j = p[i], left = l[j], right = r[j];
        LL lv = a[j].first - a[left].first;
        LL rv = a[right].first - a[j].first;
        if (lv <= rv) {
            res[i] = { lv,a[left].second };
        } else {
            res[i] = { rv,a[right].second };
        }
        // 删除该节点
        r[left] = right;
        l[right] = left;
    }

    for (int i = 2; i <= n; ++i) {
        cout << res[i].first << ' ' << res[i].second << endl;
    }

    return 0;
}



// 106. 动态中位数
// 链表
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

typedef pair<int, int> PII;
const int N = 100010;
int n;
int p[N];       // 记录原序列在链表中位置
int l[N], r[N];
int res[N];
PII a[N];

int main()
{
    int t;
    cin >> t;
    int times = 0;
    while (t--) {

        cin >> times >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a + 1, a + 1 + n);

        //a[0].first = INT_MIN, a[n + 1].first = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            l[i] = i - 1, r[i] = i + 1;
            p[a[i].second] = i;
        }
        int mid = (n + 1) / 2;

        // 从后往前，因为要求的是动态中位数，所以需要以原序列从后往前的顺序进行答案的查找
        int idx = (n + 1) / 2;
        for (int i = n; i >= 1; --i) {
            int j = p[i], left = l[j], right = r[j];
            int v = a[j].first;
            if (i & 1) {        // 奇数结算
                res[idx--] = a[mid].first;
                // 奇数时，要删除的大于或等于中位数,左移，小于不动，使得删后偶数时，中位数指向左半边的有边界的位置
                if (v >= a[mid].first) {
                    mid = l[mid];
                }
            } else {
                // 偶数时，要删除的小于或等于中位数时，右移
                if (v <= a[mid].first)
                    mid = r[mid];
            }

            l[right] = left;
            r[left] = right;

        }
        int sum = (n + 1) / 2;
        printf("%d %d\n", times, sum);
        //cout << times << ' ' << sum << endl;
        for (int i = 1; i <= sum; ++i) {
            printf("%d ", res[i]);
            //cout << res[i];
            
            //if (i % 10 == 0) cout << endl;
            if (i % 10 == 0) printf("\n");
        }
        if (sum % 10)
            printf("\n");


    }
    return 0;
}

