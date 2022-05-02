//148. 排序链表-------------------------------------------------------
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 法一：利用multimap对链表进行插入，随后遍历进行串连
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        multimap<int, ListNode*> list_map;
        auto tmp = head;
        while (tmp) {
            list_map.insert(make_pair(tmp->val, tmp));
            tmp = tmp->next;
        }
        ListNode node;
        auto ans = &node;
        for (auto kv : list_map) {
            ans->next = kv.second;
            ans = ans->next;
        }
        ans->next = nullptr;
        return node.next;
    }
};

// 法二：自顶向下归并排序归并排序，时间达到O(nlogn)，空间O（logn）
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return sortList(head, nullptr);
    }

    ListNode* sortList(ListNode* head, ListNode* tail) {
        //空链表，return
        if (head == nullptr) {
            return head;
        }
        //只有一个节点，return
        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }
        //通过快慢指针找到链表中点
        ListNode* slow = head, * fast = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) {
                fast = fast->next;
            }
        }
        ListNode* mid = slow;
        return merge(sortList(head, mid), sortList(mid, tail));
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* temp = dummyHead, * temp1 = head1, * temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;
            } else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        } else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummyHead->next;
    }
};

// 法三：自底向上归并排序,时间达到O(nlogn)，空间O（1）
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        int length = 0;
        ListNode* node = head;
        //计算链表长度
        while (node != nullptr) {
            length++;
            node = node->next;
        }
        ListNode* dummyHead = new ListNode(0, head);
        for (int subLength = 1; subLength < length; subLength <<= 1) {
            //枚举所要合并的两条链表的长度，从1开始，长度为1自然有序
            ListNode* prev = dummyHead, * curr = dummyHead->next;
            //获取两条长度为sublength的链表
            while (curr != nullptr) {
                // 第一条
                ListNode* head1 = curr;
                for (int i = 1; i < subLength && curr->next != nullptr; i++) {
                    curr = curr->next;
                }
                ListNode* head2 = curr->next;
                curr->next = nullptr;
                //第二条
                curr = head2;
                if (curr) {
                    for (int i = 1; i < subLength && curr->next != nullptr; i++) {
                        curr = curr->next;
                    }
                }

                ListNode* next = nullptr;
                if (curr != nullptr) {
                    next = curr->next;
                    curr->next = nullptr;
                }
                //归并
                ListNode* merged = merge(head1, head2);
                //合并结果连接到dummyHead后
                prev->next = merged;
                while (prev->next != nullptr) {
                    prev = prev->next;
                }
                curr = next;
            }
        }
        return dummyHead->next;
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* temp = dummyHead, * temp1 = head1, * temp2 = head2;
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->val <= temp2->val) {
                temp->next = temp1;
                temp1 = temp1->next;
            } else {
                temp->next = temp2;
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
        if (temp1 != nullptr) {
            temp->next = temp1;
        } else if (temp2 != nullptr) {
            temp->next = temp2;
        }
        return dummyHead->next;
    }
};


//152. 乘积最大子数组-------------------------------------------------------------
//dp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        //由于数组元素可能为负数，所以单独一个最大乘积子数组dp搞不定，当负负得正，可能会更大，所以需要再记录最小乘积子数组
        //maxF[i]表示已i结尾的乘积最大子数组，minF[i]表示以i结尾的乘积最小子数组
        vector <int> maxF(nums), minF(nums);
        for (int i = 1; i < nums.size(); ++i) {
            maxF[i] = max({ maxF[i - 1] * nums[i], nums[i], minF[i - 1] * nums[i] });
            minF[i] = min({ minF[i - 1] * nums[i], nums[i], maxF[i - 1] * nums[i] });
        }
        return *max_element(maxF.begin(), maxF.end());
    }
};
//由于第i 个状态只和第 i−1 个状态相关，采取滚动数组
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxF = nums[0], minF = nums[0], ans = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            int mx = maxF, mn = minF;
            maxF = max({ mx * nums[i], nums[i], mn * nums[i] });
            minF = min({ mn * nums[i], nums[i], mx * nums[i] });
            ans = max(maxF, ans);
        }
        return ans;
    }
};
