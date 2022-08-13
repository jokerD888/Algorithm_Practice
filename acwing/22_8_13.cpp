// 170. 加成序列

// 迭代加深+判重剪枝
// 递归深度很深,但结果深度较浅，那么就可以用迭代加深，每次固定一个dfs的深度，一旦超过这个深度就返回,若找不到，就深度+1，再重新dfs一遍
// 对于每个位置k，我们枚举相加的两个数i,j
// 对于一个位置的和，可能由不同的两组数构成，我们只关心最终的和，所以用某个和一旦搜过了，就跳过


//#include <iostream>
//using namespace std;
//
//const int N = 110;
//int n;
//int path[N];
//
//bool dfs(int u, int depth) {
//    if (u == depth) return path[u - 1] == n;
//    
//    bool st[N] = { false };
//
//    for(int i=u-1;i>=0;--i)
//        for (int j = i; j >= 0; --j) {
//            int s = path[i] + path[j];
//            if (s >= path[u - 1] && s <= n && !st[s]) {
//                st[s] = true;
//                path[u] = s;
//                if (dfs(u + 1, depth)) return true;
//            }
//        }
//    return false;
//}
//
//int main()
//{
//    while (cin >> n, n) {
//        int depth = 1;
//        path[0] = 1;
//        while (!dfs(1, depth))++depth;
//
//        for (int i = 0; i < depth; ++i) cout << path[i] << ' ';
//        cout << endl;
//
//    }
//    return 0;
//}


// 171. 送礼物

// 双向搜索
// 类似背包问题，但背包问题时间复杂度为O(NV) N是个数，V是体积，但本题V是INT_MAX，超时，但N较小只有46，可以暴力
// 直接暴力的话也是2^45，超时，所以我们双向搜索
// 先搜索前N/2个物品可以凑出来的所以重量，存到数组中，对所有重量排序，去重
// 再搜索后一半物品可以凑出来的重量，假设当前的搜出来的重量是x，可以在前面排好序的一半中二分出一个y，使得x+y<=w,且x+y最大
// 优化：从大到小枚举所有重量，然后微调两次搜索的数量，因为后一般搜索完还需二分，所以让前面多搜几个，后面少搜几个
// 但本题，前一半搜索完后，还需要排序，NlogN，所以就不需要进行搜索数量的微调了，直接N/2一半一半来

// #pragma GCC optimize (3)
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 50;
int n, w, res, k;
int a[N];
int weights[1 << 23], cnt;        //双向搜索，最多2^23个状态

void dfs_1(int u, int s) {
    if (u == k) {
        weights[cnt++] = s;
        return;
    }
    if ((LL)s + a[u] <= w) dfs_1(u + 1, s + a[u]);  // 当前位置要
    dfs_1(u + 1, s);                                   // 不要
}
void dfs_2(int u, int s) {
    if (u == n) {
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = l + r + 1 >> 1;
            if ((LL)s + weights[mid] > w) r = mid - 1;
            else l = mid;
        }

        if ((LL)s + weights[l] <= w) res = max(res, weights[l] + s);
        return;
    }
    if ((LL)s + a[u] <= w) dfs_2(u + 1, s + a[u]);
    dfs_2(u + 1, s);
}
int main()
{
    cin >> w >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n, greater<int>());

    k = n / 2;
  

    dfs_1(0, 0);

    sort(weights, weights + cnt);
    cnt = unique(weights, weights + cnt) - weights;

    dfs_2(k, 0);

    cout << res << endl;
    return 0;
}