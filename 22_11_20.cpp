
// 186. 巴士

// 最多300个车，每个路线上最两个车，所以最多会有150条路线，但题目说明最多只会有17条路线，所以可以用迭代加深搜索
// 
// 题目中的路线指的是在0-59时间段中的一个完整的、元素至少为2的等差数列，每条巴士线路是一条完整的等差数列！
// 解法：先预处理出所有合法路线，所以问题就变为了最少选择多少条路线，可以将所有公交车覆盖
// 剪枝：  1）dfs时需要传入一个枚举的起点，按组合数方法搜索，不是排序数方法
//          2）优先枚举点较多的路线 
//          3）基于第2）剪枝，如果当前路线上的点数*剩余可以选则的路线数量+现在已经覆盖的车的数量<总车数量，回溯，可行性剪枝




#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;

// 总路线数，等差数列，首相，公差，0~59 共60个，取2个确定一条路线C(60,2) 60*59/2大致1800左右
const int N = 2000, M = 60;

int n;
int bus[M]; // 所有时刻公交车的数量
vector<pair<int, PII>> routes;   // 合法路线

// 检查这条路线是否合法，即从首相开始，之后每个间隔d都有车
bool check(int a, int d) {
    for (int i = a; i < 60; i += d) {
        if (!bus[i])
            return false;
    }
    return true;
}
int dfs(int depth, int u, int tot) {
    if (!depth) return tot == n;

    // 枚举路线
    for (int i = u; i < routes.size(); ++i) {
        auto r = routes[i];
        // 起点，终点
        int a = r.second.first, d = r.second.second;
        if (r.first * depth + tot < n) continue;
        if (!check(a, d)) continue;
        for (int j = a; j < 60; j += d) --bus[j];

        if (dfs(depth - 1, i, tot + r.first)) return true;

        for (int j = a; j < 60; j += d) ++bus[j];
    }

    return false;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int t;
        cin >> t;
        ++bus[t];
    }
    // 枚举所有合法路线
    // 注意：：题目中的路线指的是在0-59时间段中的一个完整的、元素至少为2的等差数列，每条巴士线路是一条完整的等差数列！
    for (int a = 0; a < 60; ++a)
        for (int d = a + 1; a + d < 60; ++d)   // a是首相是第一个，所以前面需要满足a-d<0 ,即d>a
            if (check(a, d))
                routes.push_back({ (59 - a) / d + 1,{a,d} });   // 第一关键字为该路线上的数量
    sort(routes.begin(), routes.end(), greater<pair<int, PII>>());

    int depth = 0;
    while (depth != 17 && !dfs(depth, 0, 0)) ++depth;       // 做多只有17条，所以一旦要递归17层就可以不用算了，直接break
    cout << depth << endl;
    return 0;
}



// 187. 导弹防御系统

// 枚举每个导弹放在上升序列中还是下降序列中即每个导弹有两种选择，2^n,同时选择放入那个序列需要O(n)时间来遍历
// 本来是还是需要枚举放在序列集合中的那个具体序列，但是可以贪心，升序时选择小于h[u]的最大的那个放，降序时选择大于h[u]的最小的那个放
// 所以总时间O(n*2^n) n最大50，但实际上答案很小，即用到的单调序列的个数就会很小，使用迭代加深，那么代码中的剪枝就会减去很多分支
//      即代码中的if (su + sd > depth)  return false;       

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 60;
int n;
int h[N];
int up[N], down[N];

bool dfs(int depth, int u, int su, int sd) {
    if (su + sd > depth)  return false;       
    if (u == n) return true;
    // 枚举放到升序序列
    bool flag = false;
    for (int i = 1; i <= su; ++i) {
        if (up[i] < h[u]) {     //贪心，选择小于h[u]的最大的那个放
            int t = up[i];
            up[i] = h[u];
            if (dfs(depth, u + 1, su, sd)) return true;
            up[i] = t;
            flag = true;
            break;
        }
    }
    // 新开升序序列
    if (!flag) {
        up[su + 1] = h[u];
        if (dfs(depth, u + 1, su + 1, sd)) return true;
    }
    // 枚举放到下降子序列
    flag = false;
    for (int i = 1; i <= sd; ++i) {
        if (down[i] > h[u]) {       //贪心，选择大于h[u]的最小的那个放
            int t = down[i];
            down[i] = h[u];
            if (dfs(depth, u + 1, su, sd)) return true;
            down[i] = t;
            flag = true;
            break;
        }
    }
    if (!flag) {
        down[sd + 1] = h[u];
        if (dfs(depth, u + 1, su, sd + 1)) return true;
    }
    return false;
}
int main()
{
    while (cin >> n, n) {
        for (int i = 0; i < n; ++i) cin >> h[i];
        int depth = 0;
        while (!dfs(depth, 0, 0, 0)) ++depth;
        cout << depth << endl;
    }
    return 0;
}
