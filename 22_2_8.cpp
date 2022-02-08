//1219. 黄金矿工
//回溯
class Solution {
private:
    static constexpr int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int ans = 0;

        function<void(int, int, int)> dfs = [&](int x, int y, int gold) {
            gold += grid[x][y];
            ans = max(ans, gold);

            int rec = grid[x][y];   
            grid[x][y] = 0;

            for (int d = 0; d < 4; ++d) {
                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];
                //保证路线有效
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] > 0) {
                    dfs(nx, ny, gold);
                }
            }

            grid[x][y] = rec;   //回溯
        };

        //枚举起点
        for (int i = 0; i < m; ++i) {   
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 0) {  
                    dfs(i, j, 0);   //以（i,j)为起点进行递归回溯
                }
            }
        }

        return ans;
    }
};


//1748. 唯一元素的和
//法一：数据范围小，直接统计出现次数
class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int vis[101] = { 0 };
        for (auto n : nums) {
            ++vis[n];
        }
        int ret = 0;
        for (int i = 1; i < 101; ++i) {
            if (1 == vis[i]) {
                ret += i;
            }
        }
        return ret;
    }
};

//方法二：标记状态，一次遍历
//0：尚未访问过，1：访问过一次，2：访问超过一次
class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int ans = 0;
        unordered_map<int, int> state;
        for (int num : nums) {
            if (state[num] == 0) {
                ans += num;
                state[num] = 1;
            } else if (state[num] == 1) {
                ans -= num;
                state[num] = 2;
            }
        }
        return ans;
    }
};
