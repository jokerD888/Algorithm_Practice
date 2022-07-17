// 132. 小组队列

// 本题与普通队列操作不同的是，若队列中有同队元素，则直接插入到其同队元素的后面，否则插入到前面
// 所以，可以得知，不论什么时刻，同一对的元素总是紧挨着的，所以同一对的可以再用一个队列存储起来，可以看做一个整体

//
//#include <iostream>
//#include <queue>
//using namespace std;
//
//const int N = 1010, M = 1000010;
//
//int team_id[M];     // 成员的队伍号映射
//
//int main()
//{
//    int n, c = 0;
//    while (cin >> n, n) {
//        queue<int> team;
//        queue<int> person[N];
//        cout << "Scenario #" << ++c << endl;
//        for (int i = 0; i < n; ++i) {
//            int cnt;
//            cin >> cnt;
//            while (cnt--) {
//                int x;
//                cin >> x;
//                team_id[x] = i;
//            }
//        }
//
//        string command;
//        while (cin >> command, command != "STOP") {
//            if (command == "ENQUEUE") {
//                int x;
//                cin >> x;
//                int tid = team_id[x];
//                if (person[tid].empty()) team.push(tid);
//                person[tid].push(x);
//            } else {
//                int tid = team.front();
//                auto& q = person[tid];
//                cout << q.front() << endl;
//                q.pop();
//                if (q.empty())team.pop();
//            }
//        }
//        cout << endl;
//
//    }
//    return 0;
//}




// AcWing 133. 蚯蚓

// 若使用优先队列+全局偏移值 O(NlogN) 超时
// 但题目中有隐藏的单调性，假设有两条蚯蚓x1，x2,x1>=x2, x1分成l1,r1,x2分成l2,r2,有l1>=l2 ,r1>=r2;
// 所以可以用两个队列来存储切分的左边和右边，即可O(1)找出当前最大，和O(1)插入分成的两个新蚯蚓,做到O(N)解决


//#include <iostream>
//#include <algorithm>
//#include <climits>
//using namespace std;
//
//const int N = 100010, M = 7000010;
//int n, m, q, u, v, t;
//int qu[N], ql[M], qr[M];
//int hh, hl, hr, tt, tl = -1, tr = -1; // 队头，队顶
//int delta;
//
//int get_max() {
//    int x = INT_MIN;
//    if (hh <= tt) x = max(x, qu[hh]);
//    if (hl <= tl) x = max(x, ql[hl]);
//    if (hr <= tr) x = max(x, qr[hr]);
//
//    if (hh <= tt && x == qu[hh]) ++hh;
//    else if (hl <= tl && x == ql[hl])++hl;
//    else ++hr;
//
//    return x;
//}
//int main()
//{
//    cin >> n >> m >> q >> u >> v >> t;
//    for (int i = 0; i < n; ++i) cin >> qu[i];
//    sort(qu, qu + n, greater<int>());
//    tt = n - 1;
//
//    for (int i = 1; i <= m; ++i) {
//        int x = get_max();
//        x += delta;
//        int left = x * 1ll * u / v;
//        int right = x - left;
//        if (i % t == 0) cout << x << " ";
//        delta += q;
//        ql[++tl] = left - delta;
//        qr[++tr] = right - delta;
//    }
//    cout << endl;
//
//    for (int i = 1; i <= n + m; ++i) {
//        int x = get_max();
//        if (i % t == 0) cout << x + delta << " ";
//    }
//    cout << endl;
//
//
//    return 0;
//}


// 134. 双端队列

//#include <iostream>
//#include <climits>
//#include <deque>
//#include <algorithm>
//using namespace std;
//const int N = 200010;
//
//typedef pair<int, int> PII;
//PII a[N];
//int n,number;
//
//int main()
//{
//    cin >> n;
//    for (int i = 0; i < n; ++i) {
//        cin >> a[i].first;
//        a[i].second = i;
//    }
//    // 利用稳定排序，使得第二关键字，也从小到大排序，也可以自己定义排序规则。甚至也可以不用排序，只要在相同数值区间内找到最小最大坐标即可
//    stable_sort(a, a + n);  
//
//    bool down = true;   // 处于下降趋势
//    int res = 0,last=INT_MAX;
//    for (int i = 0; i < n; ++i) {
//        int r = i;
//        while (r<n && a[r].first == a[i].first) ++r;
//        --r;        // 找出相同元素的右区间
//        if (down) {     // 下降趋势
//            if (a[r].second < last) {
//                last = a[i].second;
//            } else {
//                down = false;       // 谷点
//                ++res;
//                last = a[r].second;
//            }
//
//        } else {        // 上升趋势
//            if (a[i].second > last) {
//                last = a[r].second;
//            } else {
//                down = true;
//                last = a[i].second;
//            }
//        }
//        i = r;
//    }
//    if (down) ++res;        // 若上一段处于下降状态，虽然无法再到达谷点，但也算一段
//    cout << res << endl;
//
//    return 0;
//}
//
//
//// 或，y总是res一开始设为1，且规定从上升状态变为下降状态时res++,就不用最后特判了
//
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//typedef pair<int, int> PII;
//const int N = 200010;
//
//int n;
//PII a[N];
//
//int main()
//{
//    cin >> n;
//    for (int i = 0; i < n; i++)
//    {
//        cin >> a[i].first;
//        a[i].second = i;
//    }
//    sort(a, a + n);
//    int res = 1;
//    for (int i = 0, last = n + 1, dir = -1; i < n; )
//    {
//        int j = i;
//        while (j < n && a[j].first == a[i].first) j++;
//        int minx = a[i].second, maxx = a[j - 1].second;
//        if (dir == -1)
//        {
//            if (last > maxx) last = minx;
//            else dir = 1, last = maxx;
//        } else
//        {
//            if (last < minx) last = maxx;
//            else
//            {
//                res++;
//                last = minx;
//                dir = -1;
//            }
//        }
//        i = j;
//    }
//
//    cout << res << endl;
//
//    return 0;
//}




// 135. 最大子序和

// 需要求区间和，那么用前缀和来计算，暴力的话O(N^2), 但我们可以枚举右端点，用单调队列O(1)求出左端点，达到O(N)
// 单调队列，每个元素入队一次，出队一次，用队列维护集合，删除队列中一定不是最优解的选择。
// 每次固定有端点i，那么在i-m
#include <iostream>
#include <climits>
using namespace std;
typedef long long LL;
const int N = 300010;
LL sum[N];
int q[N];
int n, m;
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }

    LL res = INT_MIN, l = 1, r = 1;
    q[1] = 0;
    for (int i = 1; i <= n; ++i) {
        while (l <= r && q[l] < i - m) ++l;     // 对头与i的距离超过M,这里是最多使得队头的元素下标q[l]==i-m，因为求和时，sum[r]-sum[l-1]
        res = max(res, sum[i] - sum[q[l]]);     // 此时对头就是最优左端点，抉择答案
        while (l <= r && sum[q[r]] >= sum[i]) --r;        // 要将当前元素入队列，那么比其大的都要弹出
        q[++r] = i;                             // 入队
    }

    cout << res << endl;
    return 0;
}