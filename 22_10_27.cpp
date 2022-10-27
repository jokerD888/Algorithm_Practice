// 934. 最短的桥

// 暴力搜
// 先区分出两个岛，将其中一个岛置为2，随后从岛小的那个岛出发，对其每个点做bfs搜索大岛
// 超时
class Solution {
public:
    int n;
    int source, target;
    int res;
    const int dire[5]{ -1,0,1,0,-1 };

    inline int isvalid(int x, int y) {
        return x >= 0 && x < n&& y >= 0 && y < n;
    }
    void dfs(vector<vector<int>>& grid, int r, int c) {
        if (!isvalid(r, c) || grid[r][c] != 1) return;
        grid[r][c] = 2;
        for (int i = 0; i < 4; ++i) {
            dfs(grid, r + dire[i], c + dire[i + 1]);
        }
    }
    void bfs(vector<vector<int>> grid, int r, int c) {
        queue<pair<int, int>> qu;
        for (int i = 0; i < 4; ++i) {
            int x = r + dire[i], y = c + dire[i + 1];
            if (isvalid(x, y) && grid[x][y] == 0) {
                qu.emplace(x, y);
                grid[x][y] = -1;
            }
        }

        int level = 0;
        while (qu.size()) {
            ++level;
            int k = qu.size();
            for (int i = 0; i < k; ++i) {
                auto t = qu.front();
                qu.pop();
                for (int j = 0; j < 4; ++j) {
                    int x = t.first + dire[j], y = t.second + dire[j + 1];
                    if (isvalid(x, y)) {
                        if (grid[x][y] == target) {
                            res = min(res, level);
                            return;
                        }
                        if (grid[x][y] == 0) {
                            qu.emplace(x, y);
                            grid[x][y] = -1;
                        }
                    }
                }
            }
        }

    }
    int shortestBridge(vector<vector<int>>& grid) {
        n = grid.size();
        for (int i = 0; i < n; ++i) {
            int j = 0;
            for (; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j);
                    break;
                }
            }
            if (j < n) break;
        }

        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1)
                    ++cnt1;
                else if (grid[i][j] == 2)
                    ++cnt2;
            }
        source = cnt1 < cnt2 ? 1 : 2;
        target = cnt1 < cnt2 ? 2 : 1;

        res = 10000;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == source) {
                    bfs(grid, i, j);
                }
            }
        }
        return res;
    }
};


// 优化

// 上法超时主要原因为对小岛的每个点单独做bfs时会有重复的情况
// 我们将小岛上所有点同时进行bfs

class Solution {
public:
    int n;
    int source, target;
    const int dire[5]{ -1,0,1,0,-1 };

    inline int isvalid(int x, int y) {
        return x >= 0 && x < n&& y >= 0 && y < n;
    }
    void dfs(vector<vector<int>>& grid, int r, int c) {
        if (!isvalid(r, c) || grid[r][c] != 1) return;
        grid[r][c] = 2;
        for (int i = 0; i < 4; ++i) {
            dfs(grid, r + dire[i], c + dire[i + 1]);
        }
    }
    int bfs(vector<vector<int>> grid) {
        queue<pair<int, int>> qu;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == source) {
                    qu.emplace(i, j);
                }
            }
        }
        int level = 0;
        while (qu.size()) {
            ++level;
            int k = qu.size();
            for (int i = 0; i < k; ++i) {
                auto t = qu.front();
                qu.pop();
                for (int j = 0; j < 4; ++j) {
                    int x = t.first + dire[j], y = t.second + dire[j + 1];
                    if (isvalid(x, y)) {
                        if (grid[x][y] == target) {
                            return level - 1;
                        }
                        if (grid[x][y] == 0) {
                            qu.emplace(x, y);
                            grid[x][y] = -1;
                        }
                    }
                }
            }
        }
        return -1;

    }
    int shortestBridge(vector<vector<int>>& grid) {
        n = grid.size();
        for (int i = 0; i < n; ++i) {
            int j = 0;
            for (; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dfs(grid, i, j);
                    break;
                }
            }
            if (j < n) break;
        }

        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1)
                    ++cnt1;
                else if (grid[i][j] == 2)
                    ++cnt2;
            }
        source = cnt1 < cnt2 ? 1 : 2;
        target = cnt1 < cnt2 ? 2 : 1;

        return bfs(grid);

    }
};

// 或
// 其实，回过头来想，无论是大岛找小岛，还是小岛找大岛，优化的很有限，而且还要通过O(N^2)时间区分大岛和小岛
// 反而正常写，不在区分，会好写


// 将dfs和bfs写在一个for里面
class Solution {
public:
    void dfs(int x, int y, vector<vector<int>>& grid, queue<pair<int, int>>& qu) {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size() || grid[x][y] != 1) {
            return;
        }
        qu.emplace(x, y);
        grid[x][y] = -1;
        dfs(x - 1, y, grid, qu);
        dfs(x + 1, y, grid, qu);
        dfs(x, y - 1, grid, qu);
        dfs(x, y + 1, grid, qu);
    }

    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    queue<pair<int, int>> qu;
                    dfs(i, j, grid, qu);
                    int step = 0;
                    while (!qu.empty()) {
                        int sz = qu.size();
                        for (int i = 0; i < sz; i++) {
                            auto [x, y] = qu.front();
                            qu.pop();
                            for (int k = 0; k < 4; k++) {
                                int nx = x + dirs[k][0];
                                int ny = y + dirs[k][1];
                                if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                                    if (grid[nx][ny] == 0) {
                                        qu.emplace(nx, ny);
                                        grid[nx][ny] = -1;
                                    } else if (grid[nx][ny] == 1) {
                                        return step;
                                    }
                                }
                            }
                        }
                        step++;
                    }
                }
            }
        }
        return 0;
    }
};


// 862. 和至少为 K 的最短子数组

//前缀和 + 单调双端队列 
// 使用前缀和的差来计算子数组的和；
// 使用一种数据结构，将当前前缀和i与最前面的前缀和j作差，如果满足 >= k的条件，那么j在之后就可以不用看了。
// 【因为即使后面也有满足条件的，长度也会更长，所以需要将j从前面弹出】；
// 第2步完成了之后，当前的i也要放入数据结构，那么如果数据结构中有前缀和j比前缀和i大，j也可以不用看了。
// 【因为即使后面有满足条件的，与i作差肯定也满足条件，并且长度更短，所以需要将大于等于i的从后面弹出】。
// 前面后面都要弹出，压入的元素满足单调性，所以使用单调队列。

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> sum(n + 1);        // 前缀和
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + nums[i];
        }
        int res = n + 1;
        deque<int> qu;
        for (int i = 0; i <= n; i++) {
            long curSum = sum[i];
            // 前端弹出，并保持队列中和>=k
            while (!qu.empty() && curSum - sum[qu.front()] >= k) {
                res = min(res, i - qu.front());
                qu.pop_front();
            }
            // 后端弹出，并保持队尾前缀和小于当前和
            while (!qu.empty() && sum[qu.back()] >= curSum) {
                qu.pop_back();
            }
            qu.push_back(i);
        }
        return res < n + 1 ? res : -1;
    }
};
