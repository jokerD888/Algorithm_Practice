
//64. ��С·����-------------------------------------------------------------------------

// ��һ��DFS
// �ݹ�;�м�¼���ﵱǰ�����С·������֦
class Solution {
public:
	int ans;
	void DFS(vector<vector<int>>& grid, vector<vector<int>>& minPath, int path, int x, int y) {
		int n = grid.size(), m = grid[0].size();
		if (x == n || y == m || path + grid[x][y] >= minPath[x][y]) {
			return;
		}
		path += grid[x][y];


		minPath[x][y] = path;
		if (x == n - 1 && y == m - 1) {
			ans = min(ans, path);
			return;
		}

		DFS(grid, minPath, path, x + 1, y);
		DFS(grid, minPath, path, x, y + 1);
	}

	int minPathSum(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size();
		vector<vector<int>> minPath(n, vector<int>(m, INT_MAX));
		ans = INT_MAX;
		DFS(grid, minPath, 0, 0, 0);
		return ans;
	}
};

// ��������̬�滮

class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size();
		vector<vector<int>> dp(n, vector<int>(m));
		dp[0][0] = grid[0][0];
		for (int i = 1; i < m; ++i) {
			dp[0][i] = dp[0][i - 1] + grid[0][i]; ;
		}
		for (int i = 1; i < n; ++i) {
			dp[i][0] = dp[i - 1][0] + grid[i][0];
		}
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
			}
		}
		return dp[n - 1][m - 1];
	}
};



//96. ��ͬ�Ķ���������--------------------------------------------------------

// ��һ��dp
//����һ����������1.��n��Ϊ�˹�����һ�ö��������������ǿ��Ա���ÿ������i������������Ϊ��������1.��(iһ1)������Ϊ����������(i��1).��n������Ϊ���������������ǿ��԰���ͬ���ķ�ʽ�ݹ鹹������������������
//�����������Ĺ����У����ڸ���ֵ��ͬ����������ܱ�֤ÿ�ö�����������Ψһ�ġ�
//�ɴ˿ɼ���ԭ������Էֽ�ɹ�ģ��С�����������⣬��������Ľ���Ը��á���ˣ����ǿ����뵽ʹ�ö�̬�滮����Ȿ�⡣

class Solution {
public:
	int numTrees(int n) {
		vector<int> G(n + 1, 0);
		G[0] = 1;
		G[1] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) {	//ö�ٲ�ͬ���ڵ�
				G[i] += G[j - 1] * G[i - j];
			}
		}
		return G[n];
	}
};

// ��������ѧ
class Solution {
public:
	int numTrees(int n) {
		long long C = 1;
		for (int i = 0; i < n; ++i) {
			C = C * 2 * (2 * i + 1) / (i + 2);
		}
		return (int)C;
	}
};