// 337. 打家劫舍 III

// 递归+记忆化搜索
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
// dfs(root) 含义：返回root为根的二叉数的最大金额
// 明显我们可以得知，每次盗取后需要隔着一代
// 要么盗取root的，随后盗取root->left->left,root->left->left,root->right->right,root->right->left,
// 要么不盗取root的，随后即可盗取root->left和root->right的

class Solution {
public:
    unordered_map<TreeNode*, int> vis;      // 缓存表
  
    int dfs(TreeNode* root) {
        if (!root) return 0;
        if (vis.find(root) != vis.end()) return vis[root];
        int res1 = root->val;
        if (root->left) res1 += dfs(root->left->left) + dfs(root->left->left);
        if (root->right) res1 += dfs(root->right->right) + dfs(root->right->left);

        int res2 = dfs(root->left) + dfs(root->right);

        vis[root] = max(res1, res2);
        return vis[root];
    }
    int rob(TreeNode* root) {
        return dfs(root);
    }
};


// 缓存优化，我们可以发现，从下往上只会用到几个有限变量
// 这里dfs的返回值是一个pair<int,int> 第一关键字表示选root所能盗取的最大金额，第二关键字表示不选root所能盗取的最大金额
class Solution {
public:
    pair<int, int> dfs(TreeNode* root) {
        if (!root) return { 0,0 };
        auto l = dfs(root->left);
        auto r = dfs(root->right);

        int fir = root->val + l.second + r.second;                  //选root
        int sec = max(l.first, l.second) + max(r.first, r.second);  // 不选root

        return { fir,sec };
    }
    int rob(TreeNode* root) {
        auto res = dfs(root);
        return max(res.first, res.second);
    }
   
};


// 394. 字符串解码
// process(string& s, int i) 作用是返回字符串s从i开始的合法字符串解码信息（解码字符串，终止位置）
class Solution {
public:
    pair<string, int> process(string& s, int i) {
        string ans;
        int num = 0;
        while (i < s.size() && s[i] != ']') {   // 每个递归只会处理一个解码信息
            if (isalpha(s[i])) {    
                ans += s[i++];
            } else if (isdigit(s[i])) {
                num = num * 10 + s[i++] - '0';
            } else {    // 左括号
                auto next = process(s, i + 1);
                for (int j = 0; j < num; ++j) ans += next.first;
                num = 0;
                i = next.second + 1;
            }
        }
        
        return { ans,i };
    }
    string decodeString(string s) {
        return process(s, 0).first;
    }
};
