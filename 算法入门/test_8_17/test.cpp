//BFS/DFS

#include<iostream>
using namespace std;
#include<stack>
#include<queue>
//合并二叉树

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

//DFS
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2)
    {
        if(root2)
          Helper(root1, root2);
        return root1;
    }
    void Helper(TreeNode*& root1, TreeNode*& root2)
    {
        if (!root1)
        {
            root1 = new TreeNode(0,nullptr,nullptr);
        }
        root1->val += root2->val;
        if (root2->left)
            Helper(root1->left, root2->left);
        if (root2->right)
            Helper(root1->right, root2->right);
        
    }
};

//BFS
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) 
    {
        if (!root2)
            return root1;
        if (!root1)
            return root2;
        queue < pair< TreeNode*&, TreeNode*&>> q;
        root1->val += root2->val;
        if (root2->left)
        {
            q.emplace(root1->left, root2->left);
        }
        if (root2->right)
        {
            q.emplace(root1->right, root2->right);

        }
        while (!q.empty())
        {
            TreeNode*& r1 = q.front().first, *& r2 = q.front().second;
            if (!r1)
            {
                r1 = new TreeNode(0, nullptr, nullptr);
            }
            r1->val += r2->val;
            q.pop();
            if (r2->left)
            {
                q.emplace(r1->left, r2->left);
            }
            if (r2->right)
            {
                q.emplace(r1->right, r2->right);
            }
 

        }

        return root1;
    }
};


//116. 填充每个节点的下一个右侧节点指针
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

//DFS
//对于每个结点的左右结点，先左结点next指向右结点，让左结点不断向右走，右节点不断向左走，再将左结点next指向右结点，
//当走到最底部时，将左结点next指向右结点,此时这一纵深（列）就链接完成了,再递归下去即可解题
class Solution {
public:
    Node* connect(Node* root) 
    {
        Helper(root);
        return root;
    }
    void Helper(Node*& root)
    {
        if (!root)
        {
            return;
        }
        Node* left = root->left, * right = root->right;
        while (left)
        {
            left->next = right;
            left = left->right;
            right = right->left;
        }
        Helper(root->left);
        Helper(root->right);

    }
};

//官解
//方法一：层次遍历
//利用队列实现层次遍历，每次取出的结点的next即指向对头结点即可
//时间复杂度：O(N)
//空间复杂度：O(N)
class Solution {
public:
    Node* connect(Node* root) 
    {
        if (root == nullptr) 
        {
            return root;
        }

        // 初始化队列同时将第一层节点加入队列中，即根节点
        queue<Node*> Q;
        Q.push(root);

        // 外层的 while 循环迭代的是层数
        while (!Q.empty()) 
        {

            // 记录当前队列大小
            int size = Q.size();

            // 遍历这一层的所有节点
            for (int i = 0; i < size; i++) 
            {

                // 从队首取出元素
                Node* node = Q.front();
                Q.pop();

                // 连接
                if (i < size - 1) 
                {
                    node->next = Q.front();
                }

                // 拓展下一层节点
                if (node->left != nullptr) 
                {
                    Q.push(node->left);
                }
                if (node->right != nullptr) 
                {
                    Q.push(node->right);
                }
            }
        }

        // 返回根节点
        return root;
    }
};


//方法二：使用已建立的 \text{ next }next 指针
//时间复杂度：O(N)
//空间复杂度：O(1)，不需要存储额外的节点。
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }

        // 从根节点开始
        Node* leftmost = root;

        while (leftmost->left != nullptr) {

            // 遍历这一层节点组织成的链表，为下一层的节点更新 next 指针
            Node* head = leftmost;

            while (head != nullptr) {

                // CONNECTION 1
                head->left->next = head->right;

                // CONNECTION 2
                if (head->next != nullptr) {
                    head->right->next = head->next->left;
                }

                // 指针向后移动
                head = head->next;
            }

            // 去下一层的最左的节点
            leftmost = leftmost->left;
        }

        return root;
    }
};

