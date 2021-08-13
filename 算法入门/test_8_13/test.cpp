
#include<iostream>
using namespace std;


//344. 反转字符串
class Solution {
public:
    void reverseString(vector<char>& s)
    {
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;
            ++left;
            --right;
        }
    }
};

//557. 反转字符串中的单词 III
//(优于官方解）
//双指针找空格，逆序空格间单的词
class Solution 
{
public:
    void Reverse(string& s, int left, int right)
    {
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            char tmp = s[left];
            s[left] = s[right];
            s[right] = tmp;
            ++left;
            --right;
        }
    }
    string reverseWords(string s)
    {
        int space1 = 0, space2 = 0;
        
        while (space2 < s.size())
        {
            if (s[space2] != ' ')
            {
                space2++;
            }
            else
            {
                Reverse(s, space1, space2 - 1);
                space1 = space2 + 1;
                space2++;
            }
        }
        Reverse(s, space1, s.size()-1);
        return s;
    }
};


//官解1
//额外开辟一数组，找单词，再把单词逆着插入
class Solution {
public:
    string reverseWords(string s) {
        string ret;
        int length = s.length();
        int i = 0;
        while (i < length) {
            int start = i;
            while (i < length && s[i] != ' ') {
                i++;
            }
            for (int p = start; p < i; p++) {
                ret.push_back(s[start + i - 1 - p]);
            }
            while (i < length && s[i] == ' ') {
                i++;
                ret.push_back(' ');
            }
        }
        return ret;
    }
};

//官解2
//与上基本相同，不同的是原地修改，不用额外开辟数组
class Solution {
public:
    string reverseWords(string s) {
        int length = s.length();
        int i = 0;
        while (i < length) {
            int start = i;
            while (i < length && s[i] != ' ') {
                i++;
            }

            int left = start, right = i - 1;
            while (left < right) {
                swap(s[left], s[right]);
                left++;
                right--;
            }
            while (i < length && s[i] == ' ') {
                i++;
            }
        }
        return s;
    }
};



//876. 链表的中间结点

  struct ListNode 
  {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
 //使用快慢指针，phead一次走一个，tail一次走两个，当tail走到尾，phand即为中间结点位置
class Solution {
public:
    ListNode* middleNode(ListNode* head) 
    {
        ListNode* phead = head, *tail = head;
        while (tail->next != nullptr)
        {
            phead = phead->next;
            tail = tail->next;
            if (tail->next != nullptr)
            {
                tail = tail->next;

            }
        }

        return phead;
    }
};

//官解
//使用数组记录各结点地址，通过数组的大小/2得到中间结点
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        vector<ListNode*> A = { head };
        while (A.back()->next != NULL)
            A.push_back(A.back()->next);
        return A[A.size() / 2];
    }
};

//单指针，先遍历一遍，得到结点各数N，再遍历到第N/2个结点即可
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int n = 0;
        ListNode* cur = head;
        while (cur != nullptr) {
            ++n;
            cur = cur->next;
        }
        int k = 0;
        cur = head;
        while (k < n / 2) {
            ++k;
            cur = cur->next;
        }
        return cur;
    }
};



//19. 删除链表的倒数第 N 个结点

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
//还是用双指针，phead,tail,先让tail走n个结点，再phead,tail一起走，当tail走到尾，phead即为要删除结点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        //设置一哨兵结点
        ListNode* p = new ListNode(0, head);
        head = p;
        ListNode* phead = head, * tail = head;
        for (int i = 0; i < n; i++)
        {
            tail = tail->next;
        }
       
        while (tail->next != nullptr)
        {
            phead = phead->next;
            tail = tail->next;
        }
        

        //删除结点
        ListNode* dv = phead->next;
        phead->next = dv->next;
        delete dv;
        
        //去掉哨兵结点
        dv = head;
        head = head->next;
        delete dv;
        dv = nullptr;

        return head;
    }
};


//官解
//
//1.还是可以跟上题一样，用数组，记录结点个数L，再遍历删除L-n+1个结点的下一个结点

//2.利用栈，先全部入栈，再一个一个出栈，弹出的第n个即为要删除的结点，且目前栈顶的节点就是待删除节点的前驱节点

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        ListNode* dummy = new ListNode(0, head);
        stack<ListNode*> stk;
        ListNode* cur = dummy;
        while (cur) {
            stk.push(cur);
            cur = cur->next;
        }
        for (int i = 0; i < n; ++i) {
            stk.pop();
        }
        ListNode* prev = stk.top();
        prev->next = prev->next->next;
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};

//3.与本人解法相同

