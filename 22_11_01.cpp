
// 剑指 Offer 03. 数组中重复的数字

// 哈希表
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_set<int> set;
        for (auto i : nums) {
            if (set.find(i) != set.end())
                return i;
            set.insert(i);
        }
        return -1;
    }
};

// 原地交换
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (i == nums[i]) continue;
            if (nums[nums[i]] == nums[i]) return nums[i];
            swap(nums[i], nums[nums[i]]);
            --i;
        }
        return -1;
    }
};



// 剑指 Offer 04. 二维数组中的查找

// 利用行列的单调性，从右上往左下滑
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        if (n == 0) return false;
        int m = matrix[0].size();
        int x = 0, y = m - 1;
        while (x < n && y >= 0) {
            if (matrix[x][y] == target) {
                return true;
            } else if (matrix[x][y] < target) {
                ++x;
            } else {
                --y;
            }
        }
        return false;
    }
};


// 剑指 Offer 05. 替换空格

class Solution {
public:
    string replaceSpace(string s) {
        string res;
        string block = "%20";
        for (auto c : s) {
            if (c == ' ')
                res += block;
            else
                res += c;
        }
        return res;
    }
};


// 剑指 Offer 06. 从尾到头打印链表

// 遍历+翻转
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        while (head) {
            res.push_back(head->val);
            head = head->next;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};


// 剑指 Offer 07. 重建二叉树

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}

};
class Solution {
public:
    unordered_map<int, int> inorderTree;
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int pre_l, int pre_r, int in_l, int in_r) {
        if (pre_l > pre_r) return nullptr;

        int pre_root = pre_l;       // 根节点位置
        int in_root = inorderTree[preorder[pre_root]];    // 中序中找根节点位置

        TreeNode* root = new TreeNode(preorder[pre_root]);
        // 左子树中节点个数
        int size_left = in_root - in_l;
        // 递归构造左子树
        root->left = build(preorder, inorder, pre_l + 1, pre_l + size_left, in_l, in_root - 1);
        // 递归构造右子树
        root->right = build(preorder, inorder, pre_l + size_left + 1, pre_r, in_root + 1, in_r);
        return  root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = inorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i) {
            inorderTree[inorder[i]] = i;
        }
        return build(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};

// 或非递归形式
// 迭代法
// 对于前序遍历中的任意两个"连续"节点u和v，根据前序遍历的流程，我们可以知道u和v只有两种可能的关系:
// 1）v是u的左儿子。这是因为在遍历到u之后，下一个遍历的节点就是u的左儿子，即v
// 2）u没有左儿子，并且v是u的某个祖先节点(或者u本身)的右儿子。
//      如果u没有左儿子，那么下一个遍历的节点就是u的右儿子。
//      如果u没有右儿子，我们就会向上回溯，直到遇到第一个有右儿子(且u不在它的右儿子的子树中）的节点ua，那么v就是 ua的右儿子。

// 算法流程
// 我们用一个栈stack来维护「当前节点的所有还没有考虑过右儿子的祖先节点」，栈顶就是当前节点。
// 也就是说，只有在栈中的节点才可能连接一个新的右儿子。同时，我们用一个指针index指向中序遍历的某个位置，初始值为0。
// index对应的节点是「当前节点不断往左走达到的最终节点」，这也是符合中序遍历的
// 
// 1）我们用一个栈和一个指针辅助进行二叉树的构造。初始时栈中存放了根节点(前序遍历的第一个节点)，指针指向中序遍历的第一个节点;
// 2）我们依次枚举前序遍历中除了第一个节点以外的每个节点。如果index恰好指向栈顶节点，那么我们不断地弹出栈顶节点并向右移动 index，
//      并将当前节点作为最后一个弹出的节点的右儿子;如果 index和栈顶节点不同，我们将当前节点作为栈顶节点的左儿子;
// 3)无论是哪一种情况，我们最后都将当前的节点入栈。
//  最后得到的二叉树即为答案。


class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex]) {       // 一直往左构建树左子树
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            } else {        // 到左下角了，往上构建右子树
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {   // 栈中弹出的顺序和中序顺序相同
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};
