// 平衡树（set)
// 对于当前数i,要么找左边最大的比i小的，要么找左边最小的比i大的，即在排序上，其两者相邻，这样二者的差值才可能最小，
// 利用set，其内部根据迭代器的递增，其元素值也是递增。其插入是O(logN)，但其找左找右皆是O(1）的，算法整体（NlogN)

#include <iostream>
#include <set>
using namespace std;

const int N = 100010;
typedef pair<int, int> PII;
PII a[N];
int n;


int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }

    set<PII> s;

    s.insert(a[1]);
    for (int i = 2; i <= n; ++i) {
        s.insert(a[i]);
        auto it = s.find(a[i]);
        PII res{ 0x3f3f3f3f,-1 };
        if (++it != s.end()) {  // 先判断大于i的
            res = { it->first - a[i].first,it->second };
        }
        --it;
        if (it-- != s.begin() && res.first >= a[i].first - it->first) {  // 再判断小于i的，这样的顺序自然使得两个选择相同时，选择小的那个
            res = { a[i].first - it->first,it->second };
        }
        cout << res.first << " " << res.second << endl;
    }

    return 0;
}


// 链表

// 思路，对原链表排序，在用一索引数值,索引记录原序列的点在双链表中的位置，然后按原序列位置，从后往前遍历，遍历完当前元素后从链表中删除

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long LL;
typedef pair<LL, int> PII;
const int N = 100010;

int n;
int l[N], r[N];
int p[N];   // 记录原序列的点在双链表中的位置
PII a[N], ans[N];



int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(a + 1, a + 1 + n);

    a[0].first = -4e9, a[n + 1].first = 4e9;     // 哨兵
    for (int i = 1; i <= n; ++i) {
        l[i] = i - 1, r[i] = i + 1;
        p[a[i].second] = i;
    }

    for (int i = n; i > 1; --i) {
        int j = p[i], left = l[j], right = r[j];
        LL lv = a[j].first - a[left].first;
        LL rv = a[right].first - a[j].first;
        if (lv <= rv) {
            ans[i] = { lv,a[left].second };
        } else {
            ans[i] = { rv,a[right].second };
        }
        r[left] = right, l[right] = left;       // 链表断开，修改指向
    }
    for (int i = 2; i <= n; ++i)
        cout << ans[i].first << " " << ans[i].second << endl;

    return 0;
}