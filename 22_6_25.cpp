
//515. ��ÿ�������������ֵ
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};
// BFS
// ʱ��O(N)
// �ռ�O(N)
class Solution {
public:
	vector<int> largestValues(TreeNode* root) {
		vector<int> res;
		queue<TreeNode*> qu;
		if (root)
			qu.push(root);
		while (!qu.empty()) {
			int n = qu.size();
			int mx = INT_MIN;
			for (int i = 0; i < n; ++i) {
				auto r = qu.front(); qu.pop();
				mx = max(mx, r->val);
				if (r->left)
					qu.push(r->left);
				if (r->right)
					qu.push(r->right);
			}
			res.push_back(mx);
		}
		return res;
	}
};

// DFS
// ʱ��O(N)
// �ռ�O(H) HΪ���ߣ��ݹ�����ջ�ռ�
class Solution {
public:
	void dfs(vector<int>& res, TreeNode* root, int height) {
		if (height == res.size())
			res.push_back(root->val);
		else
			res[height] = max(res[height], root->val);

		if (root->left)
			dfs(res, root->left, height+1);
		if (root->right)
			dfs(res, root->right, height+1);
	}
	vector<int> largestValues(TreeNode* root) {
		vector<int> res;
		if(root)
			dfs(res, root, 0);
		return res;
	}
};

//��ָ Offer II 091. ��ˢ����
// ��̬�滮
class Solution {
public:
	int minCost(vector<vector<int>>& costs) {
		int n = costs.size();
		vector<vector<int>> dp(n, vector<int>(3));
		// dp���壺dp[i][0]��ʾǰi�������Ժ�ɫ��β����С������dp[i][1]��ʾǰi����������ɫ��β����С������dp[i][2]ͬ����ɫ
		// ���ڵ�i��λ��Ϳ��ɫ��������Ӱ�����i-1��λ�ý�βͿ��ɫ����ɫ����
		// ת�Ʒ��� dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i][0];
		dp[0] = costs[0];
		for (int i = 1; i < n; ++i) {
			dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i][0];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i][1];
			dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]) + costs[i][2];
		}
		return min({dp[n-1][0],dp[n - 1][1] ,dp[n - 1][2] });
	}
};
// ���ڵ�i��λ�õľ���ֻ���i-1��λ���йأ��ʿ���ʹ�ù�������,ʹ�ÿռ佫ΪO(1)
class Solution {
public:
	int minCost(vector<vector<int>>& costs) {
		int n = costs.size();
		vector<int> dp(3);
		dp = costs[0];
		for (int i = 1; i < n; i++) {
			vector<int> dpNew(3);
			for (int j = 0; j < 3; j++) {
				dpNew[j] = min(dp[(j + 1) % 3], dp[(j + 2) % 3]) + costs[i][j];
			}
			dp = dpNew;
		}
		return *min_element(dp.begin(), dp.end());
	}
};

