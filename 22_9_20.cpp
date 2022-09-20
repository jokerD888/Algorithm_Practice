// 739. 每日温度
// 暴力，TLE
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int N = temperatures.size();
        vector<int> res(N);
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (temperatures[j] > temperatures[i]) {
                    res[i] = j - i;
                    break;
                }
            }
        }
        return res;
    }
};

// 单调栈
// 从右往左
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int N = temperatures.size();
        vector<int> res(N);
        stack<int> st;
        for (int i = N - 1; i >= 0; --i) {
            while (st.size() && temperatures[st.top()] <= temperatures[i])
                st.pop();
            if (st.empty()) res[i] = 0;
            else res[i] = st.top() - i;
            st.push(i);
        }
        return res;
    }
};
// 从左往右
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                int previousIndex = s.top();
                ans[previousIndex] = i - previousIndex;
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};


// 543. 二叉树的直径
// dfs,递归每个节点作为路径的根节点，路径长度即为左子树深度+右子树深度
class Solution {
public:
    int ans;
    int dfs(TreeNode* root) {
        if (!root) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        ans = max(ans, l + r + 1);
        return max(l, r) + 1;

    }
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans - 1;
    }
};