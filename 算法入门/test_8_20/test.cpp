
//递归、回溯

#include<iostream>
using namespace std;

//21. 合并两个有序链表

//法一，在l1原地对l2插入
 struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1)
            return l2;
        if (!l2)
            return l1;

        ListNode* phead = new ListNode(0, nullptr);
        phead->next = l1;

        ListNode* cur1 = phead, * cur2 = l2;

        while (cur2 && cur1->next)
        {
            if (cur2->val < cur1->next->val)//cur2小于cur1后面的结点，插入cur1后面
            {
                ListNode* tmp = cur2;
                cur2 = cur2->next;
                tmp->next = cur1->next;
                cur1->next = tmp;
            }
            else
                cur1 = cur1->next;
        }
        if (cur2)
        {
            cur1->next = cur2;
        }
        l1 = phead->next;
        delete phead; phead = nullptr;
        return l1;
    }
};

//法二：新建链表，每次找小，插入
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1)
            return l2;
        if (!l2)
            return l1;
        ListNode* head = nullptr, * tail = nullptr;
        head = tail = new ListNode;

        //取小尾插
        while (l1 && l2)
        {
            if (l1->val < l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        if (l1)
        {
            tail->next = l1;
        }
        else
        {
            tail->next = l2;
        }

        ListNode* realHead = head->next;
        delete head;
        head = nullptr;
        return realHead;
    }
};

//官解递归
//妙啊
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        else if (l2 == nullptr) {
            return l1;
        }
        else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};



//206. 反转链表
//依次取结点进行头插,也可以借助队列
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next)
            return head;

        ListNode* phead = new ListNode;
        phead->next = nullptr;

        while (head)
        {
            ListNode* tmp = head;
            head = head->next;
            tmp->next = phead->next;
            phead->next = tmp;
        }
        ListNode* realHead = phead->next;
        delete phead;
        phead = nullptr;
        return realHead;
    }

};



//官解
//两两结点之间改变指向  1->2->3   变为 1<-2<-3
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};

//递归
class Solution
{
public:
    ListNode* reverseList(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        head->next->next = head;
        ListNode* phead = head->next;
        head->next = nullptr;
        return reverseList(phead);

    }
};


