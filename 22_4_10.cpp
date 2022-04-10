
// 78. 子集

// 法一：递归枚举
// 每个元素都有只有加入或不加入两中做法
class Solution {
public:
	vector<int> t;
	vector<vector<int>> ans;

	void dfs(int cur, vector<int>& nums) {
		if (cur == nums.size()) {
			ans.push_back(t);
			return;
		}
		t.push_back(nums[cur]);
		dfs(cur + 1, nums);
		t.pop_back();
		dfs(cur + 1, nums);
	}

	vector<vector<int>> subsets(vector<int>& nums) {
		dfs(0, nums);
		return ans;
	}
};

// 法二：利用二进制位迭代枚举
class Solution {
public:
	vector<int> t;
	vector<vector<int>> ans;

	vector<vector<int>> subsets(vector<int>& nums) {
		int n = nums.size();
		for (int mask = 0; mask < (1 << n); ++mask) {
			t.clear();
			for (int i = 0; i < n; ++i) {
				if (mask & (1 << i)) {
					t.push_back(nums[i]);
				}
			}
			ans.push_back(t);
		}
		return ans;
	}
};



//62. 不同路径

// DFS（超时）
class Solution {
public:

	int DFS(int x, int y, int r, int c) {
		if (x == r || y == c) return 0;
		if (x == r - 1 && y == c - 1) {
			return 1;
		}
		return DFS(x + 1, y, r, c) + DFS(x, y + 1, r, c);
	}
	int uniquePaths(int m, int n) {
		return DFS(0, 0, m, n);
	}
};

// dp
class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m, vector<int>(n));
		// 首行首列的位置上，都初始化为1
		for (int i = 0; i < m; ++i) {
			dp[i][0] = 1;
		}
		for (int j = 0; j < n; ++j) {
			dp[0][j] = 1;
		}

		//其余位置的信息由其左边和上边的信息和 
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};

// 组合数学
// 从（0，0）位置走到（m-1,n-1)，一共需要走m+n-2步，其中m-1步向下，n-1步向右
// 所以全部的可能性就为 从m+n-2中取m-1的组合数
class Solution {
public:
	int uniquePaths(int m, int n) {
		long long ans = 1;
		for (int x = n, y = 1; y < m; ++x, ++y) {
			ans = ans * x / y;
		}
		return ans;
	}
};


//79. 单词搜索
// 设函数check(i, j,k)表示判断以网格的(i,j)位置出发，能否搜索到单词word[k..]，
// 其中word[k..]表示字符串word 从第k个字符开始的后缀子串。如果能搜索到，则返回true，反之返回false
class Solution {
public:

	bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k) {
		// 当前字符不匹配，违规
		if (board[i][j] != s[k]) {
			return false;
		} else if (k == s.length() - 1) {	//最后一个单词匹配成功，base
			return true;
		}
		visited[i][j] = true;
		vector<pair<int, int>> directions{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
		bool result = false;
		for (const auto& dir : directions) {
			int newi = i + dir.first, newj = j + dir.second;
			if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {	// 判断边界
				if (!visited[newi][newj]) {
					bool flag = check(board, visited, newi, newj, s, k + 1);
					if (flag) {
						result = true;	// 若其中一条路可行，整体可行
						break;
					}
				}
			}
		}
		visited[i][j] = false;	//回溯
		return result;
	}

	bool exist(vector<vector<char>>& board, string word) {
		int h = board.size(), w = board[0].size();
		vector<vector<int>> visited(h, vector<int>(w));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				bool flag = check(board, visited, i, j, word, 0);
				if (flag) {
					return true;	// 若发现有路可行，return即可
				}
			}
		}
		return false;
	}
};
