// 437. 路径总和 III
// 暴力枚举
// 枚举遍历每个节点，查看以该节点为起始节点且向下延申的合法路径的数量
// O(N^) 遍历每个起点，对于每个起点，进行dfs
class Solution {
public:
    // 返回以root为路径根节点，和为targetSum的路径数
    int rootSum(TreeNode* root, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        if (root->val == targetSum) {
            ret++;
        }

        ret += rootSum(root->left, targetSum - root->val);
        ret += rootSum(root->right, targetSum - root->val);
        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = rootSum(root, targetSum);
        ret += pathSum(root->left, targetSum);      // 递归其他起点
        ret += pathSum(root->right, targetSum);
        return ret;
    }
};



// 前缀和
// 我们定义节点的前缀和为：由根结点到当前结点的路径上所有节点的和。
// 我们利用先序遍历二叉树，记录下根节点root 到当前节点 p 的路径上除当前节点以外所有节点的前缀和，
// 在已保存的路径前缀和中查找是否存在前缀和刚好等于当前节点到根节点的前缀和 currcurr 减去 targetSum。
class Solution {
public:
    unordered_map<long long, int> prefix;

    int dfs(TreeNode* root, long long curr, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        curr += root->val;
        if (prefix.count(curr - targetSum)) {
            ret = prefix[curr - targetSum];
        }

        prefix[curr]++;
        ret += dfs(root->left, curr, targetSum);
        ret += dfs(root->right, curr, targetSum);
        prefix[curr]--;     // 回溯

        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        prefix[0] = 1;
        return dfs(root, 0, targetSum);
    }
};



// 538. 把二叉搜索树转换为累加树

// 反序中序遍历
// 右二叉搜索树的性质，二叉搜索树的中序遍历是一个单调递增的序列，
// 我们可以反序的中序遍历该搜索二叉树，同时对该过程中的值累计，对节点重新赋值

class Solution {
public:
    int sum = 0;
    void dfs(TreeNode* root) {
        if (!root) return;
        dfs(root->right);
        sum += root->val;
        root->val = sum;
        dfs(root->left);
    }
    TreeNode* convertBST(TreeNode* root) {
        dfs(root);
        return root;
    }
};


// Morris 遍历
// Morris 遍历是利用每个子树最右边的节点的空余右指针来实现O(1)空间的遍历
// 除左子树为空的节点只会遍历一次，其他节点都会遍历两次，我们可以定义第一次遍历到就打印，即为先序遍历；第二次遍历到就打印，即为中序遍历
// 可使用Morris 遍历可以在线性时间内，只占用常数空间来实现中序遍历。
// 本题需要使用反序来遍历，那么我们相应的利用右树的最左节点
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int sum = 0;
        TreeNode* cur = root;
        TreeNode* mostLeft = nullptr;

        while (cur) {
            mostLeft = cur->right;
            if (mostLeft) {
                while (mostLeft->left && mostLeft->left != cur) {
                    mostLeft = mostLeft->left;
                }
                if (mostLeft->left) {
                    mostLeft->left = nullptr;
                } else {
                    mostLeft->left = cur;
                    cur = cur->right;
                    continue;
                }
            }
            sum += cur->val;
            cur->val = sum;
            cur = cur->left;
        }

        return root;
    }
};


