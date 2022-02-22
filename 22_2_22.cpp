/450. ɾ�������������еĽڵ�
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};



//1.��ɾ��Ҷ�ӽ�㣬ֱ��ɾ��
//2.Ҫɾ���Ľڵ㲻��Ҷ�ӽڵ���ӵ���ҽڵ㣬��ýڵ�����ɸýڵ�ĺ�̽ڵ�������
//3.Ҫɾ���Ľڵ㲻��Ҷ�ӽڵ㣬��û���ҽڵ㵫������ڵ㡣
class Solution {
public:

    //�����������Һ�̣�root�����ң���һֱ����
    int successor(TreeNode* root) {
        root = root->right;
        while (root->left) {
            root = root->left;
        }
        return root->val;
    }

    //������������ǰ����root�����󣬺�һֱ����
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
        //Ҫɾ��������������
        if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else if (key < root->val) {
            //Ҫɾ��������������
            root->left = deleteNode(root->left, key);
        } else {
            //Ҫɾ���Ľ����Ҷ�ӽ��
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;
            } else if (root->right) {
                //�������������ֵ���
                root->val = successor(root);
                root->right = deleteNode(root->right, root->val);
            } else {
                //��������������ֵ���
                root->val = predecssor(root);
                root->left = deleteNode(root->left, root->val);
            }
        }

        return root;
    }
};


//230. �����������е�KС��Ԫ��

//�����������
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
    //���ö������������������k����Ϊ����
    int kthSmallest(TreeNode* root, int k) {
        vector<int> ans;
        inorder(root,ans);
        return ans[k - 1];
    }
};
//�Ϸ��е�k��֮��Ľ����������ڱ������Ľ��Ż����£���ʱ��ֹ�ݹ�
class Solution {
public:

    int inorder(TreeNode* root, int& index) {
        //��k�����Ѿ��ҵ�����ʱ��ֹ�ݹ�
        if (index <= 0) {
            return -101;    //��С��ֵ-100
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
        //����
        return max(ret1, ret2);
    }
    //���ö������������������k����Ϊ����
    int kthSmallest(TreeNode* root, int k) {
        return inorder(root, k);
    }
};

//�����stack����ݹ�
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




//����������¼�����Ľ����
class MyBst {
public:
    MyBst(TreeNode* root) {
        this->root = root;
        countNodeNum(root);
    }

    // ���ض����������е�kС��Ԫ��
    int kthSmallest(int k) {
        TreeNode* node = root;
        while (node != nullptr) {
            int left = getNodeNum(node->left);
            //������������С��k,������������
            if (left < k - 1) {
                node = node->right;
                k -= left + 1;
            } else if (left == k - 1) {
                break;
            } else {
                //������������
                node = node->left;
            }
        }
        return node->val;
    }

private:
    TreeNode* root;
    unordered_map<TreeNode*, int> nodeNum;

    // ͳ����nodeΪ�����������Ľ����
    int countNodeNum(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        nodeNum[node] = 1 + countNodeNum(node->left) + countNodeNum(node->right);
        return nodeNum[node];
    }

    // ��ȡ��nodeΪ�����������Ľ����
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



//173. ����������������
//��һ����ƽ��
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


//������������
class BSTIterator {
private:
    TreeNode* cur;
    stack<TreeNode*> stk;
public:
    BSTIterator(TreeNode* root) : cur(root) {}

    int next() {
        //һֱ����
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

