// 124. 二叉树中的最大路径和
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};

// 递归，设maxGain(node)为以node的为根节点的最大路径和，maxGain(node)=node->val+maxGain(node->left)+maxGain(node->right)
// 因为一条路径不论是什么走势，最高点一定是根节点，所以我们就dfs,对每个节点当作根节点做计算
// 我们的maxGain递归函数主要做两件事，递归左右子树并计算更新答案，以及返回以node做根节点的一条递减路径（即该路径是从根往下走的）
class Solution {
private:
    int maxSum = INT_MIN;

public:
    int maxGain(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int leftGain = max(maxGain(node->left), 0);
        int rightGain = max(maxGain(node->right), 0);

        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        int priceNewpath = node->val + leftGain + rightGain;

        // 更新答案
        maxSum = max(maxSum, priceNewpath);

        // 返回节点的最大贡献值
        return node->val + max(leftGain, rightGain);
    }

    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};




// 146. LRU 缓存
// 哈希表+双链表
class LRUCache {
private:
    struct node {
        int k, v;
        node* prev, * next;
        node(int key, int value) :k(key), v(value), prev(nullptr), next(nullptr) {}
    };
public:

    LRUCache(int capacity) :m_capacity(capacity) {
        front = new node(-1, -1);
        back = new node(-1, -1);
        front->next = back;
        back->prev = front;
    }

    int get(int key) {
        if (m_hash.find(key) == m_hash.end()) return -1;
        int value = m_hash[key]->v;
        erase(m_hash[key]);
        push_front(new node(key, value));
        return value;
    }


    void put(int key, int value) {
        if (m_hash.find(key) == m_hash.end()) {
            if (m_hash.size() == m_capacity) erase(back->prev);
            push_front(new node(key, value));
        } else {
            erase(m_hash[key]);
            push_front(new node(key, value));
        }
    }
private:
    void push_front(node* cur) {
        cur->next = front->next;
        front->next->prev = cur;
        cur->prev = front;
        front->next = cur;

        m_hash[cur->k] = cur;
    }
    void erase(node* cur) {
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;

        m_hash.erase(cur->k);
        delete cur;
    }
private:

    unordered_map<int, node*> m_hash;
    node* front, * back;

    int m_capacity;
};
