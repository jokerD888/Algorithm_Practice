// 210. 课程表 II
// 拓扑排序
// bfs
// 时间O(N+M),空间O(N+M),其中 N 为课程数，M 为先修课程的要求数。
// 构图，记录每个节点的入度，一开始将所有入度为0的点入队列，后不断出取出对头加入res，消除对头节点对其相邻节点入度的影响，
// 若入度减小到0，也入队，知道队列为空，根据res的数量是否等于节点的数量进行返回
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> map(numCourses);
        vector<int> indeg(numCourses);
        for (auto p : prerequisites) {      // p[1]->p[0]
            map[p[1]].push_back(p[0]);      // 添加边
            ++indeg[p[0]];                  // 终点入度++
        }
        queue<int> qu;
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) qu.push(i);      // 选出入度为0的节点
        }
        vector<int> res;
        while (qu.size()) {
            auto t = qu.front();
            qu.pop();
            res.push_back(t);
            for (auto node : map[t]) {      // 消除t节点对其他相邻节点入度的影响
                if (--indeg[node] == 0) qu.push(node);      // 入度为0，入对
            }
        }
        return res.size() == numCourses ? res : vector<int>();
    }
};


// dfs
//  时间O(N+M),空间O(N+M),其中 N 为课程数，M 为先修课程的要求数。
// 构图完成后，设每个节点有三种状态，未搜索，搜索中，已完成
// 「未搜索」：我们还没有搜索到这个节点；
//「搜索中」：我们搜索过这个节点，但还没有回溯到该节点，即该节点还没有入栈，还有相邻的节点没有搜索完成）；
//「已完成」：我们搜索过并且回溯过这个节点，即该节点已经入栈，并且所有该节点的相邻节点都出现在栈的更底部的位置，满足拓扑排序的要求。
// 我们从任一节点出发dfs，标记为搜索中，如果dfs过程中搜索到了搜索中的节点，那么说明成环，return {}
// 如果成功搜素完所有相邻节点，成功回溯，那么该点即为已完成，加入栈
// 这样以来，我们对图进行一遍深度优先搜索。当每个节点进行回溯的时候，我们把该节点放入栈中。最终从栈顶到栈底的序列就是一种拓扑排序。
// 深度优先搜索是一种「逆向思维」：最先被放入栈中的节点是在拓扑排序中最后面的节点。

class Solution {
private:
    // 存储有向图
    vector<vector<int>> edges;
    // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
    vector<int> visited;
    // 用数组来模拟栈，下标 0 为栈底，n-1 为栈顶
    vector<int> result;
    // 判断有向图中是否有环
    bool valid = true;

public:
    void dfs(int u) {
        // 将节点标记为「搜索中」
        visited[u] = 1;
        // 搜索其相邻节点
        // 只要发现有环，立刻停止搜索
        for (int v : edges[u]) {
            // 如果「未搜索」那么搜索相邻节点
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            // 如果「搜索中」说明找到了环
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        // 将节点标记为「已完成」
        visited[u] = 2;
        // 将节点入栈
        result.push_back(u);
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info : prerequisites) {
            edges[info[1]].push_back(info[0]);
        }
        // 每次挑选一个「未搜索」的节点，开始进行深度优先搜索
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        if (!valid) {
            return {};
        }
        // 如果没有环，那么就有拓扑排序
        // 注意下标 0 为栈底，因此需要将数组反序输出
        reverse(result.begin(), result.end());
        return result;
    }
};



// 801. 使序列递增的最小交换次数
// 硬憋版
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int N = nums1.size();
        int inf = INT_MAX / 2;
        // dpY[i] 表示前i-1个数且i位置上进行了交换所能造成的最小交换次数
        // dpN[i] 表示前i-1个数且i位置上不进行交换所能造成的最小交换次数
        vector<int> dpY(N, inf), dpN(N, inf);
        dpY[0] = 1;
        dpN[0] = 0;
        int n1 = nums2[0], n2 = nums1[0];
        for (int i = 1; i < N; ++i) {
            // 可以不换
            if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]) {      // 前一个没换
                dpN[i] = dpN[i - 1];
                // 如果可以换的话
                if (nums2[i] > nums1[i - 1] && nums1[i] > nums2[i - 1])
                    dpY[i] = dpN[i - 1] + 1;
            }
            if (nums1[i] > n1 && nums2[i] > n2) {   // 前一个换了
                dpN[i] = min(dpN[i], dpY[i - 1]);
                // 如果可以换的话
                if (nums2[i] > n1 && nums1[i] > n2)
                    dpY[i] = min(dpY[i], dpY[i - 1] + 1);
            }
            // 换
            // 不得不换
            if (nums1[i] <= nums1[i - 1] || nums2[i] <= nums2[i - 1]) {     // 前一个没换
                dpY[i] = dpN[i - 1] + 1;
            }
            if (nums1[i] <= n1 || nums2[i] <= n2) {           // 前一个换了
                dpY[i] = min(dpY[i], dpY[i - 1] + 1);
            }
            n1 = nums2[i], n2 = nums1[i];

        }
        return min(dpY[N - 1], dpN[N - 1]);
    }
};

// 正版
// 题目保证题目用例可以实现操作。因为每次只能交换相同位置的两个数，所以位置i一定至少满足以下两种情况中的一种:
// 1.nums1[i] > nums1[i-1] 且 nums2[i] > nums2[i - 1]
// 2.nums1[i] > nums2[i - 1] 且 nums2[i] > nums1[i-1]
// 否则无论是否交换nums1[i]和nums2[i]都不可能使数组nums1和nums2最终严格递增。
// 因为对于某一个位置来说只有交换和不交换两种情况，所以我们可以设dp[i][0]表示到位置i为止使数组nums1和nums2满足严格递增并且位置i不进行交换操作的最小操作数，
// 设dp[i][1]表示到位置i为止使数组nums1和nums2满足严格递增并且位置i进行交换操作的最小操作数。我们思考如何求解各个状态:
// 
//  1）只满足情况1： 位置 i 的交换情况需要和位置 i−1 的情况保持一致：
//                  dp[i][0]=dp[i-1][0]     dp[i][1]=dp[i-1][1]+1
//  2) 只满足情况2：位置 i 的交换情况需要和位置 i−1 的情况相反：
//                  dp[i][0]=dp[i-1][1]     dp[i][1]=dp[i-1][0]+1
// 3）同时满足两种情况
//                  dp[i][0]=min(dp[i-1][0],dp[i-1][1])     dp[i][1]=min(dp[i-1][1],dp[i-1][0])+1

// 初始化 dp[0][0]=0  dp[0][1]=1
// 有因为每一个状态只和前面的一个状态相关，所以可以用滚动数组
class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int a = 0, b = 1;
        for (int i = 1; i < n; i++) {
            int at = a, bt = b;
            a = b = n;
            if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]) {
                a = min(a, at);
                b = min(b, bt + 1);
            }
            if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
                a = min(a, bt);
                b = min(b, at + 1);
            }
        }
        return min(a, b);
    }
};
