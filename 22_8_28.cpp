// 226. 翻转二叉树
// 递归
class Solution {
public:
    TreeNode* reverse_node(TreeNode* root) {
        if (!root) return root;
        auto* left = root->left;
        root->left = reverse_node(root->right);
        root->right = reverse_node(left);
        return root;
    }
    TreeNode* invertTree(TreeNode* root) {
        return reverse_node(root);
    }
};



// 234. 回文链表
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
// 快慢指针
// 时间O(N)，空间O(1)
// 先使用快慢指针寻找链表中点，再前链表的前半部分反转，再使用双指针，一个从头，一个从中点向后遍历，需要不同return fasle
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode* fast = head, * slow = head;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* mid = slow;
        if (fast->next) {    // 偶数个节点，中间插入一个哨兵节点
            ListNode* node = new ListNode;
            node->next = slow->next;
            slow->next = node;
            mid = node;
        } 
        ListNode* left= head;
        while (left->next != mid) {
            auto next_node = left->next;
            left->next = next_node->next;
            next_node->next = head;
            head = next_node;
        }
        mid = mid->next;
        while (mid) {
            if (head->val != mid->val)
                return false;
            mid = mid->next;
            head = head->next;
        }
        return true;
    }
};
// 简单粗暴的话，直接将节点信息复制到数组中，进行遍历即可

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> a;
        while (head) {
            a.push_back(head->val);
            head = head->next;
        }
        int n = a.size();
        for (int i = 0; i < n / 2; ++i) {
            if (a[i] != a[n - 1 - i]) return false;
        }
        return true;
    }
};

// 或使用递归
// 使用递归反向迭代节点，同时使用函数外变量向前迭代
class Solution {
    ListNode* frontPointer;
public:
    bool recursivelyCheck(ListNode* currentNode) {
        if (currentNode != nullptr) {
            if (!recursivelyCheck(currentNode->next)) {
                return false;
            }
            if (currentNode->val != frontPointer->val) {
                return false;
            }
            frontPointer = frontPointer->next;
        }
        return true;
    }

    bool isPalindrome(ListNode* head) {
        frontPointer = head;
        return recursivelyCheck(head);
    }
};
