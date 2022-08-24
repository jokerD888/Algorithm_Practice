// 42. 接雨水


// 动态规划
// 我们只考虑每个位置上方能放几个水的话，这个值取决与其左边和右边柱子的最高值，
// 所以我们先预处理每个位置左边和右边的最高值，而后进行遍历累计即可


class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int left[20010], right[20010];
        int max_height = height[0];
        for (int i = 1; i < n; ++i) {
            left[i] = max_height;
            max_height = max(max_height, height[i]);
        }
        max_height = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right[i] = max_height;
            max_height = max(max_height, height[i]);
        }
        int res = 0;
        for (int i = 1; i < n - 1; ++i) {
            res += max((min(left[i], right[i]) - height[i]), 0);
        }
        return res;

    }
};
// 略作优化
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int left[20010], right[20010];
        left[0] = height[0];
        for (int i = 1; i < n; ++i) {
            left[i] = max(left[i - 1], height[i]);
        }
        right[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right[i] = max(right[i + 1], height[i]);
        }
        int res = 0;
        for (int i = 1; i < n - 1; ++i) {
            res += min(left[i], right[i]) - height[i];
        }
        return res;

    }
};


// 左右指针

// 左右指针l，r以及维持指针左边和右边的最大值lmax,rmax，左右两边最大值固定后，左右指针所指的值的左/右最大高度已经固定，那么就可以直接结算了
// 如lmax=6 rmax=12 ，那么l的左边最大就是6了，中间再高也没用了，就可直接确定l位置上水的最大数量，r同理
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int res = 0;
        int l = 0, r = n - 1, lmax = 0, rmax = 0;
        while (l <= r) {
            lmax = max(lmax, height[l]);
            rmax = max(rmax, height[r]);

            if (lmax < rmax) {
                res += min(lmax, rmax) - height[l++];
            } else {
                res += min(lmax, rmax) - height[r--];
            }
        }

        return res;

    }
};



// 单调栈
// 积水只能在低洼处形成，当后面的柱子高度比前面的低时，是无法接雨水的。
// 所以使用单调递减栈储存可能储水的柱子，当找到一根比前面高的柱子，就可以计算接到的雨水。
// 我们使用单调栈维持从栈底到栈顶高度递增，从左往右遍历，跟以上两种做法不同，此做法结算的不单是某一个位置，而是一块矩形面积
// 我们从左往右位置单调栈，来到了位置i，即说明位置i左边的高度限制已经确定，
// 然后如果遇到大于栈顶元素的情况，就需要结算了，结算方式为，
// 先弹出栈顶元素t,计算结算的宽：i-t-1，这是两个柱子间的距离
// 再计算高，这里的高不是最终的高，只是局限与当前栈顶的高度和t以及当前位置i的高度，结算的高：min(h[i],h[st.top])-h[t]
// 为什么这样算？因为右 h[st.top]>=h[t],h[i]>s[t],所以st.top~i直接就可能形成了水坑，就可以先计算这局部的小水坑了，
// 我们的计算是横着来的，所以可以认为局部小水坑计算完后就相当于填起来了（因为出栈了，没有影响了）
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        stack<int> st;
        int res = 0;
        for (int i = 0; i < n; ++i) {
            while (st.size() && height[i] > height[st.top()]) {
                int t = st.top();
                st.pop();
                if (st.empty()) break;
                res += (i - st.top() - 1) * (min(height[i], height[st.top()]) - height[t]);
            }
            st.push(i);
        }

        return res;
    }
};


// 407. 接雨水 II

// 小根堆 Dijkstra
// 和接雨水类似，不过是一维变二维，同样，我们也是从“桶”的短板入手
// 先计算最外围的一圈，利用小根堆找出短板，即最小高度
// 然后从这个短板处向四周进行搜索，每次取堆顶进行扩展，同时用short_board记录搜索过程中的最大短板
// 只要短板的值不变，可以认为搜素一直处于同一个水坑，若短板的值变了，说明内层有更长的短板形成了另外的水坑
class Solution {
public:
    struct node {
        int v, x, y;
        node(int value, int i, int j) :v(value), x(i), y(j) {}
        bool operator<(const node& rhs) const {
            return v > rhs.v;
        }
    };
    int trapRainWater(vector<vector<int>>& heightMap) {
        priority_queue<node, vector<node>> heap;
        int n = heightMap.size(), m = heightMap[0].size();
        bool vis[210][210] = { false };
        // 计算最外围一圈
        for (int i = 0; i < n; ++i) {
            heap.emplace(heightMap[i][0], i, 0);
            heap.emplace(heightMap[i][m-1], i, m-1);
            vis[i][0] = vis[i][m - 1] = true;
        }
        for (int i = 1; i < m - 1; ++i) {
            heap.emplace(heightMap[0][i], 0, i);
            heap.emplace(heightMap[n-1][i],n-1 , i);
            vis[0][i] = vis[n - 1][i] = true;
        }
        int dire[]{ -1,0,1,0,-1 };
        int res = 0,short_board;

        // 边界检测函数
        auto check = [&](int x, int y) {
            return x >= 0 && x < n&& y >= 0 && y < m && !vis[x][y]; };

        // 向四周扩展
        while (heap.size()) {
            auto t = heap.top();
            heap.pop();
            short_board = max(short_board, t.v);    
            
            for (int i = 0; i < 4; ++i) {
                int x = t.x + dire[i], y = t.y + dire[i + 1];
                if (check(x, y)) {
                    
                    res += max(0, short_board - heightMap[x][y]);
                    vis[x][y] = true;
                    heap.emplace(heightMap[x][y], x, y);
                }
            }
        }
        return res;
    }
};
// O(MN(log(MN))



// 广度优先搜索
// 我们先假设每个位置的水高度均为所以柱子的最高值，然后从最外一圈向内bfs
// 如果外围水的高度小于内维水的高度且内维水的值大于柱子高度，更新，这样每个位置上的水都为受到来自四周的更新
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        int maxHeight = 0;
        int dirs[] = { -1, 0, 1, 0, -1 };

        for (int i = 0; i < m; ++i) {
            maxHeight = max(maxHeight, *max_element(heightMap[i].begin(), heightMap[i].end()));
        }
        vector<vector<int>> water(m, vector<int>(n, maxHeight));    // 初始全为最大值
        queue<pair<int, int>> qu;
        // 最外围一圈更新
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    if (water[i][j] > heightMap[i][j]) {
                        water[i][j] = heightMap[i][j];
                        qu.push(make_pair(i, j));
                    }
                }
            }
        }
        while (!qu.empty()) {
            int x = qu.front().first, y = qu.front().second;
            qu.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i], ny = y + dirs[i + 1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                    continue;
                }
                // 外围水的值小于于内维水的值且内维的值大于柱子高度
                if (water[x][y] < water[nx][ny] && water[nx][ny] > heightMap[nx][ny]) {
                    water[nx][ny] = max(water[x][y], heightMap[nx][ny]);
                    qu.push(make_pair(nx, ny));
                }
            }
        }

        // 结算
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res += water[i][j] - heightMap[i][j];
            }
        }
        return res;
    }
};
// 时间复杂度为O(M^2 * N^2)每次发现有水面高度需要调整时，可能需要调整整个矩阵
