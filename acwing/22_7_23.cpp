// 145. 超市

// 容易想到一个贪心策略:在最优解中，对于每个时间（天数) t，应该在保证不卖出过期商品的前提下，尽量卖出利润前t大的商品。
// 因此，我们可以依次考虑每个商品，动态维护一个满足上述性质的方案。

// 我们把商品按照过期时间排序，建立一个初始为空的小根堆(节点权值为商品利润)，然后扫描每个商品:
// 1.若当前商品的过期时间（天数)t等于当前堆中的商品个数，则说明在目前方案下，前t天已经安排了t个商品卖出。
// 此时，若当前商品的利润大于堆顶权值（即已安排的t个商品中的最低利润)，则替换掉堆顶（用当前商品替换掉原方案中利润最低的商品)。
// 2.若当前商品的过期时间（天数）大于当前堆中的商品个数，直接把该商品插堆。
// 最终，堆里的所有商品就是我们需要卖出的商品，它们的利润之和就是答案。该算法的时间复杂度为O(N log N)。
// 因为一天只能卖出一个商品，所以我们可以发现堆中元素个数和天数等价


//#include <iostream>
//#include <algorithm>
//#include <queue>
//using namespace std;
//
//const int N = 10010;
//typedef pair<int, int> PII;
//PII a[N];
//priority_queue<int,vector<int>,greater<int>> qu;
//int n;
//
//int main()
//{
//    while (cin >> n) {
//        for (int i = 0; i < n; ++i) {
//            cin >> a[i].second >> a[i].first;
//        }
//        sort(a, a + n);
//        for (int i = 0; i < n; ++i) {
//            //// 当前商品的过期天数>堆中已有数量，直接入堆
//            //if (a[i].first > qu.size()) {
//            //    qu.emplace(a[i].second);
//            //} else if (a[i].first == qu.size() && a[i].second>qu.top()) {
//            //    // 若当前商品利润大于堆顶利润，堆顶弹出,此商品压入
//            //    qu.pop();
//            //    qu.push(a[i].second);
//            //}
//            
//            // 简化为
//            qu.push(a[i].second);
//            if (qu.size() > a[i].first) qu.pop();
//        }
//        int res = 0;
//        while (!qu.empty()) {
//            res += qu.top();
//            qu.pop();
//        }
//        cout << res << endl;
//
//    }
//    return 0;
//}




// 146. 序列

// n路归并+堆 时间O(MNlogN)
// 共有三个数组，a,b,c。a和b合并到c。先对a进行排序，后将a[0]+b[i](0<=i<n)n个数入堆，
// b0+a0 b0+a1 b0+a2 ... b0+an
// b1+a0 b1+a1 b1+a2 ... b1+an
// ...
// bn+a0 bn+a1 bn+a2 ... bn+an
// 可以发现，由于a已经排好序，所以没一行的行头为行中最小的，那么这N^N个最小的一定在第一列中，从中选出最小的，记录到c中
// 再将选出的最小的那个抹去，相当于那行往前推一列，再次从那一列中选出最小的，依次下去，选最小的可以用堆来优化
// 所以m行，可以两两合并，合并m-1次，所以时间总体O(MNlogN)

//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <climits>
//#include <queue>
//using namespace std;
//
//typedef pair<int, int> PII;
//const int N = 2010;
//int m, n;
//int a[N], b[N], c[N];
//
//void merge() {
//    priority_queue<PII, vector<PII>, greater<PII>> heap;
//    for (int i = 0; i < n; ++i) heap.emplace(a[0] + b[i], 0);
//
//    for (int i = 0; i < n; ++i) {   // O(N)
//        auto t = heap.top();
//        heap.pop();
//        int s = t.first, p = t.second;
//        c[i] = s;
//        heap.emplace(s - a[p] + a[p + 1], p + 1);   // o(logN)
//    }
//    for (int i = 0; i < n; ++i) a[i] = c[i];
//}
//int main()
//{
//    int t;
//    cin >> t;
//    while (t--) {
//        cin >> m >> n;
//        for (int i = 0; i < n; ++i) cin >> a[i];
//        sort(a, a + n);
//        for (int i = 0; i < m - 1; ++i) {   // O(M)
//            for (int j = 0; j < n; ++j) cin >> b[j];
//            merge();
//        }
//
//        for (int i = 0; i < n; ++i) cout << a[i] << " ";
//        cout << endl;
//    }
//    return 0;
//}
//



// 147. 数据备份

// 每次选取距离最小的边，对于K=1,自然选取最小距离的边，k=2时，若选取的边和k=1选取的边有连接，则删除原先k=1选择的变,再选择k=1选取的边的右边相邻的边
// 方可达到最优解，反证法可证，当k=n，此定理依然成立
// 如果K=1，答案显然是D数列中的最小值D[i]。
// 如果K=2，答案一定是以下两种情况之一:
//  1.选择最小值D[i] ，以及除了D[i-1]，D[i] ，D[i+1]之外其他数中的最小值。
//  2.选择最小值D[i] 左右两侧的两个数，即 D[i-1]和D[i+1]
// 这很容易证明:如果 D[i-1]和 D[i+1]都没有选，那么不选最小值D; 一定不优; 如果D[i-1]和 D[i+1]选了一个，那么把选了的那个换成D[i]答案也会变小，所以最优解必定是上面两种情况之一。
// 通过上述证明，我们也可以得到一个推论 : 在最优解中，最小值左右两侧的数要么同时选, 要么都不选。

// 因此，我们可以先选上D数列中的最小值，然后把 D[i-1]，D[i] D[i+1]从D数列中除，把 D[i-1]+ D[i+1]-D[i]插入到D数列中刚才执行删除的位置。
// 最后，求解“从新D数列中选出不超过K-1个数，使它们的和最小，并且相邻两个数不能同时被选”这个子问题。

// O(NlogN)
//
//#include <iostream>
//#include <set>
//
//using namespace std;
//
//typedef long long LL;
//typedef pair<LL, int> PLI;
//
//const int N = 100010;
//
//int n, k;
//int l[N], r[N];
//LL d[N];    // d[i]为d[i]和d[i-1]之间的距离
//
//void delete_node(int p)
//{
//    r[l[p]] = r[p];
//    l[r[p]] = l[p];
//}
//
//int main()
//{
//    cin >> n >> k;
//
//    for (int i = 0; i < n; i++) cin >> d[i];
//    for (int i = n - 1; i; i--) d[i] -= d[i - 1];
//
//    set<PLI> S;
//    d[0] = d[n] = 1e15; // 哨兵
//    for (int i = 0; i <= n; i++)   // O（N) 
//    {
//        l[i] = i - 1;
//        r[i] = i + 1;
//        S.insert({ d[i], i });     // O(logN)
//    }
//
//    LL res = 0;
//    while (k--)
//    {
//        auto it = S.begin();        // 取最小
//        LL v = it->first;
//        int p = it->second, left = l[p], right = r[p];
//
//        S.erase(it);
//        S.erase({ d[left], left }), S.erase({ d[right], right });
//        delete_node(left), delete_node(right);
//        res += v;
//
//        d[p] = d[left] + d[right] - d[p];
//        S.insert({ d[p], p });
//    }
//
//    cout << res << endl;
//
//    return 0;
//}




// 148. 合并果子
//// 小根堆,二叉哈夫曼数
//#include <iostream>
//#include <queue>
//#include <vector>
//using namespace std;
//
//const int N = 10010;
//int n;
//
//int main()
//{
//    cin >> n;
//    priority_queue<int, vector<int>, greater<int>> heap;
//    int cnt;
//    for (int i = 0; i < n; ++i) {
//        cin >> cnt;
//        heap.push(cnt);
//    }
//    int res = 0;
//    while (heap.size() > 1) {
//        int a = heap.top();
//        heap.pop();
//        int b=heap.top();
//        heap.pop();
//        res += a + b;
//        heap.push(a + b);
//    }
//    cout << res << endl;
//    return 0;
//}



// 149. 荷马史诗

// k叉哈夫曼数
// 题目中所给的k进制实际就是要求的k叉哈弗树，
// 同时要求为保证最短总长度的情况下，最长字符串 si 的最短长度，这个长度其实就是整颗树的深度
// 即我们只需要在求 Huffman树时，对于权值相同的节点，优先考虑当前深度最小(已合并次数最少）的进行合并即可。
// pair的默认排序以帮我们高度，堆顶一定是满足条件的
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<LL, int> PLI;  
const int N = 100010;
int n, k;

int main()
{
    cin >> n >> k;
    LL cnt = 0;
    priority_queue<PLI, vector<PLI>, greater<PLI>> heap;
    for (int i = 0; i < n; ++i) {
        cin >> cnt;
        heap.emplace(cnt, 0);   // 第二关键字存的是当前深度
    }
    // n个节点每次选k个合并为1个，即n-m(k-1)=1,最后留一个root,那么就可以把k叉树最后一层填满
    while ((n - 1) % (k - 1)) {     
        heap.emplace(0ll, 0);
        ++n;
    }

    LL res = 0;
    while (heap.size() > 1) {
        LL sum = 0;
        int depth = 0;
        for (int i = 0; i < k; ++i) {
            sum += heap.top().first;
            depth = max(depth, heap.top().second);
            heap.pop();

        }
        res += sum;
        heap.emplace(sum, depth + 1);
    }

    cout << res << endl << heap.top().second << endl;
    return 0;

}


