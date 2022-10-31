// 481. 神奇字符串

// 模拟
// 实时生成神奇的字符串
class Solution {
public:
    int magicalString(int n) {
        string s = "122";
        int res = 1;
        int c = 2;
        for (int i = 3; i < n; ++i) {
            if (c < n) {        // 优化，使得生成的字符串长度达到n即可
                char target = s.back() == '1' ? '2' : '1';
                s += target;
                if (s[c] == '2')
                    s += target;
                ++c;
            }

            if (s[i] == '1')
                ++res;
        }
        return res;
    }
};


// 235. 二叉搜索树的最近公共祖先

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val > q->val) swap(p, q);
        TreeNode* cur = root;
        while (cur) {
            if (p == cur || q == cur) {
                return p == cur ? p : q;
            }
            if (p->val<cur->val && q->val>cur->val) {   // p和q分布在cur节点两侧
                return cur;
            }
            if (p->val < cur->val && q->val < cur->val) {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
        }
    }
};

// 进一步简洁
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p->val > q->val) swap(p, q);    // 保证p的值小于q的值
        TreeNode* cur = root;
        while (cur) {
            if (p->val < cur->val && q->val < cur->val) {
                cur = cur->left;
            } else if(p->val > cur->val && q->val > cur->val){
                cur = cur->right;
            } else {
                break;
            }
        }
        return cur;
    }
};


// 292. Nim 游戏
// 通过下面打表找规律，发现每连续的3个为true,后跟一个false
class Solution {
public:
    bool dfs(int rest) {
        if (rest <= 3) return true;
        for (int i = 1; i <= 3; ++i) {
            if (!dfs(rest - i)) return true;
        }
        return false;
    }
    bool canWinNim(int n) {
        for(int i=1;i<n;++i)
            if (dfs(i)) {
                cout << i << ' ' << "true" << endl;
            } else {
                cout << i << ' ' << "falst" << endl;
            }
        return true;
    }
};


class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
    }
};