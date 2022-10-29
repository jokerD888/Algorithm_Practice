// 1773. 统计匹配检索规则的物品数量

class Solution {
public:
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
        int res = 0;
        int N = items.size();
        int target = 0;
        if (ruleKey == "color") target = 1;
        if (ruleKey == "name") target = 2;
        for (auto& ss : items) {
            if (ss[target] == ruleValue)
                ++res;
        }
        return res;
    }
};



// 61. 旋转链表


struct ListNode {
   int val;
   ListNode* next;
   ListNode() : val(0), next(nullptr) {}
   ListNode(int x) : val(x), next(nullptr) {}
   ListNode(int x, ListNode* next) : val(x), next(next) {}
   
};
// 寻找倒数第k个节点，拼接
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next || !k) return head;
        int cnt = 1;
        ListNode* tail = head;
        // 计算节点个数，同时让tail指向最后一个节点
        while (tail->next) {
            ++cnt;
            tail = tail->next;
        }

        k %= cnt;       // 取模，减去k大于节点个数造成的重复工作
        if (k == 0) return head;        // 当k==0时，直接返回头即可
        k = cnt - k;

        ListNode* k_node = head;
        // 找到第k个节点
        for (int i = 0; i < k - 1; ++i)
            k_node = k_node->next;
        ListNode* new_head = k_node->next;
        k_node->next = nullptr;
        tail->next = head;
        return new_head;
    }
};


// 闭合为环
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next) return head;
        int cnt = 1;
        ListNode* cur = head;
        while (cur->next) {
            ++cnt;
            cur = cur->next;
        }
        k %= cnt;
        if (k == 0) return head;
        k = cnt - k;
        cur->next = head;
        while (--k) {
            head = head->next;
        }
        ListNode* new_head = head->next;
        head->next = nullptr;
        return new_head;
    }
};