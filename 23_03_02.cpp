
// 206. 反转链表

 struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
 // 迭代
 class Solution {
 public:
     ListNode* reverseList(ListNode* head) {
         if (!head) return head;
         ListNode* cur = head;
         while (cur->next) {
             cur = cur->next;
         }
         ListNode* next_node;
         while (head != cur) {
             next_node = head->next;
             head->next = cur->next;
             cur->next = head;
             head = next_node;
         }
         return cur;
     }
 };
 class Solution {
 public:
     ListNode* reverseList(ListNode* head) {
         ListNode* prev = nullptr;
         ListNode* cur = head;
         while (cur) {
             ListNode* next = cur->next;
             cur->next = prev;
             prev = cur;
             cur = next;
         }
         return prev;
     }
 };

 
// 递归

 class Solution {
 public:
     ListNode* reverseList(ListNode* head) {
         if (!head || !head->next) return head;
         ListNode* new_head = reverseList(head->next);
         head->next->next = head;
         head->next = nullptr;
         return new_head;
     }
 };





 // 876. 链表的中间结点

 class Solution {
 public:
     ListNode* middleNode(ListNode* head) {
         ListNode* fast = head, * low = head;
         while (fast && fast->next && fast->next->next) {
             fast = fast->next->next;
             low = low->next;
         }
         if (fast->next)
             low = low->next;
         return low;
     }
 };


 // 160. 相交链表
 // 时间复杂度 O(m + n) 、仅用 O(1) 内存

 class Solution {
 public:
     ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
         if (headA == nullptr || headB == nullptr) {
             return nullptr;
         }
         ListNode* pA = headA, * pB = headB;
         while (pA != pB) {
             pA = pA == nullptr ? headB : pA->next;
             pB = pB == nullptr ? headA : pB->next;
         }
         return pA;
     }
 };


 // 142. 环形链表 II
 // 快慢指针

 class Solution {
 public:
     ListNode* detectCycle(ListNode* head) {
         ListNode* low = head, * fast = head;
         if (!fast || !fast->next || !fast->next->next) return nullptr;
         do 
         {
             low = low->next;
             fast = fast->next->next;
         } while (fast && fast->next && fast->next->next && low!=fast);

         if (!fast || !fast->next || !fast->next->next) return nullptr;
         ListNode* res = head;
         while (res != low) {
             res = res->next;
             low = low->next;
         }
         return res;
     }
 };

 // 或
 class Solution {
 public:
     ListNode* detectCycle(ListNode* head) {
         ListNode* slow = head, * fast = head;
         while (fast != nullptr) {
             slow = slow->next;
             if (fast->next == nullptr) {
                 return nullptr;
             }
             fast = fast->next->next;
             if (fast == slow) {
                 ListNode* ptr = head;
                 while (ptr != slow) {
                     ptr = ptr->next;
                     slow = slow->next;
                 }
                 return ptr;
             }
         }
         return nullptr;
     }
 };



 // 92. 反转链表 II

 class Solution {
 public:
     ListNode* reverseBetween(ListNode* head, int left, int right) {
         ListNode* dummy = new ListNode(0, head);   // 呀节点，方便边界处理
         ListNode* cur = dummy, *left_half;     // left_half 上半段的尾
         // l走到反转链表的开头
         for (int i = 0; i < left; ++i) {
             left_half = cur;
             cur = cur->next;
         }

         ListNode* prev = nullptr;      
         ListNode* tail = cur;        // 保存反转后的链表尾
         for (int i = 0; i <= right - left; ++i) {      // 从cur开始反转right - left+1个节点
             ListNode* next = cur->next;
             cur->next = prev;
             prev = cur;
             cur = next;
         }
         // prev是反转后的头，cur是后半段的头
         left_half->next = prev;
         tail->next = cur;

         return dummy->next;
     }
 };

 // 或
 // 头插
 class Solution {
 public:
     ListNode* reverseBetween(ListNode* head, int left, int right) {
  
         ListNode* dummyNode = new ListNode(-1);
         dummyNode->next = head;
         ListNode* pre = dummyNode;
         for (int i = 0; i < left - 1; i++) {
             pre = pre->next;
         }
         // pre是上半段的尾
         ListNode* cur = pre->next;
         ListNode* next;
         //cur：指向待反转区域的第一个节点 left；
         // next：永远指向 cur 的下一个节点，循环过程中，cur 变化以后 next 会变化；
         //pre：永远指向待反转区域的第一个节点 left 的前一个节点，在循环过程中不变
         // 头插
         for (int i = 0; i < right - left; i++) {
             next = cur->next;
             cur->next = next->next;
             next->next = pre->next;
             pre->next = next;
         }
         return dummyNode->next;
     }
 };

