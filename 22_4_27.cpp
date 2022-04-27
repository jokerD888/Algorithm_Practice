#include <iostream>
using namespace std;
#include <queue>
#include <stack>
//101. 对称二叉树----------------------------------------
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
//递归
class Solution {
public:
	bool check(TreeNode* L, TreeNode* R) {
		if (!L && !R) return true;
		if (!L || !R) return false;
		return L->val == R->val && check(L->left, R->right) && check(L->right, R->left);
	}
	bool isSymmetric(TreeNode* root) {
		return check(root, root);
	}
};
//迭代
class Solution {
public:
	bool check(TreeNode* u, TreeNode* v) {
		queue <TreeNode*> q;
		q.push(u); q.push(v);
		while (!q.empty()) {
			u = q.front(); q.pop();
			v = q.front(); q.pop();
			if (!u && !v) continue;
			if ((!u || !v) || (u->val != v->val)) return false;

			q.push(u->left);
			q.push(v->right);

			q.push(u->right);
			q.push(v->left);
		}
		return true;
	}

	bool isSymmetric(TreeNode* root) {
		return check(root, root);
	}
};


//102. 二叉树的层序遍历--------------------------------------------------
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) {
			return {};
		}
		vector<vector<int>> ans;
		queue<TreeNode*> qu;
		qu.push(root);
		while (!qu.empty()) {
			vector<int> tmp;
			int n = qu.size();
			for (int i = 0; i < n; ++i) {
				auto ret = qu.front();
				tmp.push_back(ret->val);
				qu.pop();
				if (ret->left) qu.push(ret->left);
				if (ret->right) qu.push(ret->right);
			}
			ans.push_back(tmp);
		}
		return ans;
	}
};


//114. 二叉树展开为链表----------------------------------------------------
//方法一：前序遍历,记录节点，最后连起来
class Solution {
public:
	void flatten(TreeNode* root) {
		vector<TreeNode*> arr;
		preorderTraversal(root, arr);
		int n = arr.size();
		for (int i = 1; i < n; i++) {
			TreeNode* prev = arr[i - 1], * curr = arr[i];
			prev->left = nullptr;
			prev->right = curr;
		}
	}

	void preorderTraversal(TreeNode* root, vector<TreeNode*>& l) {
		if (root != nullptr) {
			l.push_back(root);
			preorderTraversal(root->left, l);
			preorderTraversal(root->right, l);
		}
	}
};

//迭代实现
class Solution {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr) return;
		vector<TreeNode*> arr;
		stack<TreeNode*> st;
		st.push(root);
		while (!st.empty()) {
			root = st.top();
			st.pop();
			arr.push_back(root);
			if (root->right) st.push(root->right);
			if (root->left)st.push(root->left);
		}
		for (int i = 1; i < arr.size(); ++i) {
			auto prev = arr[i - 1], cur = arr[i];
			prev->left = nullptr;
			prev->right = cur;
		}
	}
};

//方法二：前序遍历和展开同步进行
class Solution {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr) {
			return;
		}
		stack<TreeNode*> stk;
		stk.push(root);
		TreeNode* prev = nullptr;
		while (!stk.empty()) {
			TreeNode* curr = stk.top(); stk.pop();
			if (prev != nullptr) {
				prev->left = nullptr;
				prev->right = curr;
			}
			if (curr->right) stk.push(curr->right);
			if (curr->left) stk.push(curr->left);

			prev = curr;
		}
	}
};