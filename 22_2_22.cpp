/450. 删除二叉搜索树中的节点
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};



//1.若删除叶子结点，直接删除
//2.要删除的节点不是叶子节点且拥有右节点，则该节点可以由该节点的后继节点进行替代
//3.要删除的节点不是叶子节点，且没有右节点但是有左节点。
class Solution {
public:

    //有右子树，找后继，root先往右，后一直往左
    int successor(TreeNode* root) {
        root = root->right;
        while (root->left) {
            root = root->left;
        }
        return root->val;
    }

    //有左子树，找前驱，root先往左，后一直往右
    int predecssor(TreeNode* root) {
        root = root->left;
        while (root->right) {
            root = root->right;
        }
        return root->val;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) {
            return nullptr;
        }
        //要删除结点的在右子树
        if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else if (key < root->val) {
            //要删除结点的在左子树
            root->left = deleteNode(root->left, key);
        } else {
            //要删除的结点是叶子结点
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;
            } else if (root->right) {
                //找其后续结点进行值替代
                root->val = successor(root);
                root->right = deleteNode(root->right, root->val);
            } else {
                //找其先续结点进行值替代
                root->val = predecssor(root);
                root->left = deleteNode(root->left, root->val);
            }
        }

        return root;
    }
};


//230. 二叉搜索树中第K小的元素

//常规中序遍历
class Solution {
public:

    void inorder(TreeNode* root, vector<int>& ans) {
        if (!root) {
            return;
        }
        inorder(root->left, ans);
        ans.push_back(root->val);
        inorder(root->right, ans);
    }
    //利用二叉树的中序遍历，第k个即为所求
    int kthSmallest(TreeNode* root, int k) {
        vector<int> ans;
        inorder(root,ans);
        return ans[k - 1];
    }
};
//上法中第k个之后的结点根本不用在遍历，改进优化如下，及时终止递归
class Solution {
public:

    int inorder(TreeNode* root, int& index) {
        //第k个数已经找到，及时终止递归
        if (index <= 0) {
            return -101;    //最小数值-100
        }
        int ret1=INT_MIN, ret2=INT_MIN;
        if (root->left) {
            ret1=inorder(root->left, index);
        }

        --index;
        if (index == 0) {
            return root->val;
        }

        if (root->right) {
            ret2=inorder(root->right,index);
        }
        //返回
        return max(ret1, ret2);
    }
    //利用二叉树的中序遍历，第k个即为所求
    int kthSmallest(TreeNode* root, int k) {
        return inorder(root, k);
    }
};

//或借助stack替代递归
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        while (!st.empty() || root) {
            if (root) {
                st.push(root);
                root = root->left;
            } else {
                root = st.top();
                st.pop();
                if (--k == 0) {
                    return root->val;
                }
                root = root->right;
            }
        }

        return 0;
    }
};




//方法二：记录子树的结点数
class MyBst {
public:
    MyBst(TreeNode* root) {
        this->root = root;
        countNodeNum(root);
    }

    // 返回二叉搜索树中第k小的元素
    int kthSmallest(int k) {
        TreeNode* node = root;
        while (node != nullptr) {
            int left = getNodeNum(node->left);
            //左子树结点个数小于k,答案在右子树上
            if (left < k - 1) {
                node = node->right;
                k -= left + 1;
            } else if (left == k - 1) {
                break;
            } else {
                //答案在左子树上
                node = node->left;
            }
        }
        return node->val;
    }

private:
    TreeNode* root;
    unordered_map<TreeNode*, int> nodeNum;

    // 统计以node为根结点的子树的结点数
    int countNodeNum(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        nodeNum[node] = 1 + countNodeNum(node->left) + countNodeNum(node->right);
        return nodeNum[node];
    }

    // 获取以node为根结点的子树的结点数
    int getNodeNum(TreeNode* node) {
        if (node != nullptr && nodeNum.count(node)) {
            return nodeNum[node];
        } else {
            return 0;
        }
    }
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        MyBst bst(root);
        return bst.kthSmallest(k);
    }
};



//173. 二叉搜索树迭代器
//法一：扁平化
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        inorder(root);
        index = 0;
    }
    
    int next() {
        return li[index++]->val;
    }
    
    bool hasNext() {
        return (index < li.size());
    }
private:
    void inorder(TreeNode* root) {
        if (!root) {
            return;
        }
        inorder(root->left);
        li.push_back(root);
        inorder(root->right);
    }
    vector<TreeNode*> li;
    int index = 0;
};


//方法二：迭代
class BSTIterator {
private:
    TreeNode* cur;
    stack<TreeNode*> stk;
public:
    BSTIterator(TreeNode* root) : cur(root) {}

    int next() {
        //一直往左
        while (cur != nullptr) {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        int ret = cur->val;
        cur = cur->right;
        return ret;
    }

    bool hasNext() {
        return cur != nullptr || !stk.empty();
    }
};

