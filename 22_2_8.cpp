//1219. �ƽ��
//����
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
                //��֤·����Ч
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] > 0) {
                    dfs(nx, ny, gold);
                }
            }

            grid[x][y] = rec;   //����
        };

        //ö�����
        for (int i = 0; i < m; ++i) {   
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 0) {  
                    dfs(i, j, 0);   //�ԣ�i,j)Ϊ�����еݹ����
                }
            }
        }

        return ans;
    }
};


//1748. ΨһԪ�صĺ�
//��һ�����ݷ�ΧС��ֱ��ͳ�Ƴ��ִ���
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

//�����������״̬��һ�α���
//0����δ���ʹ���1�����ʹ�һ�Σ�2�����ʳ���һ��
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
