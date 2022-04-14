
//64. 最小路径和-------------------------------------------------------------------------

// 法一：DFS
// 递归途中记录到达当前点的最小路径，剪枝
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

// 法二：动态规划

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



//96. 不同的二叉搜索树--------------------------------------------------------

// 法一：dp
//给定一个有序序列1.…n，为了构建出一棵二叉搜索树，我们可以遍历每个数字i，将该数字作为树根，将1.…(i一1)序列作为左子树，将(i＋1).…n序列作为右子树。接着我们可以按照同样的方式递归构建左子树和右子树。
//在上述构建的过程中，由于根的值不同，因此我们能保证每棵二叉搜索树是唯一的。
//由此可见，原问题可以分解成规模较小的两个子问题，且子问题的解可以复用。因此，我们可以想到使用动态规划来求解本题。

class Solution {
public:
	int numTrees(int n) {
		vector<int> G(n + 1, 0);
		G[0] = 1;
		G[1] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) {	//枚举不同根节点
				G[i] += G[j - 1] * G[i - j];
			}
		}
		return G[n];
	}
};

// 法二：数学
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