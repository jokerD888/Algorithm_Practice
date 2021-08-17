//BFS/DFS

#include<iostream>
using namespace std;
#include<stack>
#include<queue>
//�ϲ�������

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


//116. ���ÿ���ڵ����һ���Ҳ�ڵ�ָ��
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
//����ÿ���������ҽ�㣬������nextָ���ҽ�㣬�����㲻�������ߣ��ҽڵ㲻�������ߣ��ٽ�����nextָ���ҽ�㣬
//���ߵ���ײ�ʱ��������nextָ���ҽ��,��ʱ��һ����У������������,�ٵݹ���ȥ���ɽ���
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

//�ٽ�
//����һ����α���
//���ö���ʵ�ֲ�α�����ÿ��ȡ���Ľ���next��ָ���ͷ��㼴��
//ʱ�临�Ӷȣ�O(N)
//�ռ临�Ӷȣ�O(N)
class Solution {
public:
    Node* connect(Node* root) 
    {
        if (root == nullptr) 
        {
            return root;
        }

        // ��ʼ������ͬʱ����һ��ڵ��������У������ڵ�
        queue<Node*> Q;
        Q.push(root);

        // ���� while ѭ���������ǲ���
        while (!Q.empty()) 
        {

            // ��¼��ǰ���д�С
            int size = Q.size();

            // ������һ������нڵ�
            for (int i = 0; i < size; i++) 
            {

                // �Ӷ���ȡ��Ԫ��
                Node* node = Q.front();
                Q.pop();

                // ����
                if (i < size - 1) 
                {
                    node->next = Q.front();
                }

                // ��չ��һ��ڵ�
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

        // ���ظ��ڵ�
        return root;
    }
};


//��������ʹ���ѽ����� \text{ next }next ָ��
//ʱ�临�Ӷȣ�O(N)
//�ռ临�Ӷȣ�O(1)������Ҫ�洢����Ľڵ㡣
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }

        // �Ӹ��ڵ㿪ʼ
        Node* leftmost = root;

        while (leftmost->left != nullptr) {

            // ������һ��ڵ���֯�ɵ�����Ϊ��һ��Ľڵ���� next ָ��
            Node* head = leftmost;

            while (head != nullptr) {

                // CONNECTION 1
                head->left->next = head->right;

                // CONNECTION 2
                if (head->next != nullptr) {
                    head->right->next = head->next->left;
                }

                // ָ������ƶ�
                head = head->next;
            }

            // ȥ��һ�������Ľڵ�
            leftmost = leftmost->left;
        }

        return root;
    }
};

