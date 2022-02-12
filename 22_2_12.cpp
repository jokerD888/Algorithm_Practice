//1020. 飞地的数量
// dfs
//先计算出所有1的个数ret，然后从四边递归的向里走，走过的路说明可到达边缘,即可--ret，递归进行，借助vis二维数组标记走过的路
class Solution {
public:
    static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& vis, int i, int j,int& ret) {
        if (grid[i][j]==0 || vis[i][j]) {
            return;
        }
        if (grid[i][j] == 1 && !vis[i][j]) {
            --ret;
            vis[i][j] = true;
        }
        int m = grid.size();
        int n = grid[0].size();
        for (int d = 0; d < 4; ++d) {
            int x = i + dirs[d][0];
            int y = j + dirs[d][1];
            if (x >= 0 && x < m && y >= 0 && y < n) {
                dfs(grid, vis, x, y, ret);
            }
        }
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> vis(m,vector<bool>(n,false));
      
        int ret = 0;
        for (auto& r : grid) {
            for (auto num : r) {
                if (num == 1) {
                    ++ret;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            //上下
            dfs(grid, vis, 0, i,ret);//上
            dfs(grid, vis, m-1, i,ret);//下
        }
        for (int i = 0; i < m; ++i) {
            //左右
            dfs(grid, vis, i, 0, ret);//上
            dfs(grid, vis, i, n-1, ret);//下
        }

        return ret;
    }
};

//官解类似
class Solution {
public:
    vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    int numEnclaves(vector<vector<int>>& grid) {
        this->m = grid.size();
        this->n = grid[0].size();
        this->visited = vector<vector<bool>>(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++) {
            dfs(grid, i, 0);
            dfs(grid, i, n - 1);
        }
        for (int j = 1; j < n - 1; j++) {
            dfs(grid, 0, j);
            dfs(grid, m - 1, j);
        }
        int enclaves = 0;
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    enclaves++;
                }
            }
        }
        return enclaves;
    }

    void dfs(const vector<vector<int>>& grid, int row, int col) {
        if (row < 0 || row >= m || col < 0 || col >= n || grid[row][col] == 0 || visited[row][col]) {
            return;
        }
        visited[row][col] = true;
        for (auto& dir : dirs) {
            dfs(grid, row + dir[0], col + dir[1]);
        }
    }
private:
    int m, n;
    vector<vector<bool>> visited;
};

//bfs同理
//首先从网格边界上的每个陆地单元格开始广度优先搜索，访问所有和网格边界相连的陆地单元格，然后遍历整个网格，统计飞地的数量。
class Solution {
public:
    vector<vector<int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(m, vector<bool>(n, false));
        queue<pair<int, int>> qu;
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 1) {
                visited[i][0] = true;
                qu.emplace(i, 0);
            }
            if (grid[i][n - 1] == 1) {
                visited[i][n - 1] = true;
                qu.emplace(i, n - 1);
            }
        }
        for (int j = 1; j < n - 1; j++) {
            if (grid[0][j] == 1) {
                visited[0][j] = true;
                qu.emplace(0, j);
            }
            if (grid[m - 1][j] == 1) {
                visited[m - 1][j] = true;
                qu.emplace(m - 1, j);
            }
        }
        while (!qu.empty()) {
            auto [currRow, currCol] = qu.front();
            qu.pop();
            for (auto& dir : dirs) {
                int nextRow = currRow + dir[0], nextCol = currCol + dir[1];
                if (nextRow >= 0 && nextRow < m && nextCol >= 0 && nextCol < n && grid[nextRow][nextCol] == 1 && !visited[nextRow][nextCol]) {
                    visited[nextRow][nextCol] = true;
                    qu.emplace(nextRow, nextCol);
                }
            }
        }
        int enclaves = 0;
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    enclaves++;
                }
            }
        }
        return enclaves;
    }
};


//28. 实现 strStr()
//法一：暴力匹配
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        int hayLen = haystack.size();
        int needLen = needle.size();
        for (int i = 0; i <= hayLen-needLen; ++i) {

            if (haystack[i] == needle[0]) {
                int j;
                for (j = 0; j < needLen; ++j) {
                    if (haystack[i +j] != needle[j]) {
                        break;
                    }
                }
                if (j == needLen) {
                    return i;
                }
            }
        }
        return -1;
    }
};
//或KMP算法
