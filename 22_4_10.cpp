
// 78. �Ӽ�

// ��һ���ݹ�ö��
// ÿ��Ԫ�ض���ֻ�м���򲻼�����������
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

// ���������ö�����λ����ö��
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



//62. ��ͬ·��

// DFS����ʱ��
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
		// �������е�λ���ϣ�����ʼ��Ϊ1
		for (int i = 0; i < m; ++i) {
			dp[i][0] = 1;
		}
		for (int j = 0; j < n; ++j) {
			dp[0][j] = 1;
		}

		//����λ�õ���Ϣ������ߺ��ϱߵ���Ϣ�� 
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];
	}
};

// �����ѧ
// �ӣ�0��0��λ���ߵ���m-1,n-1)��һ����Ҫ��m+n-2��������m-1�����£�n-1������
// ����ȫ���Ŀ����Ծ�Ϊ ��m+n-2��ȡm-1�������
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


//79. ��������
// �躯��check(i, j,k)��ʾ�ж��������(i,j)λ�ó������ܷ�����������word[k..]��
// ����word[k..]��ʾ�ַ���word �ӵ�k���ַ���ʼ�ĺ�׺�Ӵ�����������������򷵻�true����֮����false
class Solution {
public:

	bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k) {
		// ��ǰ�ַ���ƥ�䣬Υ��
		if (board[i][j] != s[k]) {
			return false;
		} else if (k == s.length() - 1) {	//���һ������ƥ��ɹ���base
			return true;
		}
		visited[i][j] = true;
		vector<pair<int, int>> directions{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
		bool result = false;
		for (const auto& dir : directions) {
			int newi = i + dir.first, newj = j + dir.second;
			if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) {	// �жϱ߽�
				if (!visited[newi][newj]) {
					bool flag = check(board, visited, newi, newj, s, k + 1);
					if (flag) {
						result = true;	// ������һ��·���У��������
						break;
					}
				}
			}
		}
		visited[i][j] = false;	//����
		return result;
	}

	bool exist(vector<vector<char>>& board, string word) {
		int h = board.size(), w = board[0].size();
		vector<vector<int>> visited(h, vector<int>(w));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				bool flag = check(board, visited, i, j, word, 0);
				if (flag) {
					return true;	// ��������·���У�return����
				}
			}
		}
		return false;
	}
};
