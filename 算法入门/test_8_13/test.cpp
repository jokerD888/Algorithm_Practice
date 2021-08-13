
#include<iostream>
using namespace std;


//344. ��ת�ַ���
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

//557. ��ת�ַ����еĵ��� III
//(���ڹٷ��⣩
//˫ָ���ҿո�����ո�䵥�Ĵ�
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


//�ٽ�1
//���⿪��һ���飬�ҵ��ʣ��ٰѵ������Ų���
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

//�ٽ�2
//���ϻ�����ͬ����ͬ����ԭ���޸ģ����ö��⿪������
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



//876. ������м���

  struct ListNode 
  {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
 //ʹ�ÿ���ָ�룬pheadһ����һ����tailһ������������tail�ߵ�β��phand��Ϊ�м���λ��
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

//�ٽ�
//ʹ�������¼������ַ��ͨ������Ĵ�С/2�õ��м���
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        vector<ListNode*> A = { head };
        while (A.back()->next != NULL)
            A.push_back(A.back()->next);
        return A[A.size() / 2];
    }
};

//��ָ�룬�ȱ���һ�飬�õ�������N���ٱ�������N/2����㼴��
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



//19. ɾ������ĵ����� N �����

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
//������˫ָ�룬phead,tail,����tail��n����㣬��phead,tailһ���ߣ���tail�ߵ�β��phead��ΪҪɾ�����
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        //����һ�ڱ����
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
        

        //ɾ�����
        ListNode* dv = phead->next;
        phead->next = dv->next;
        delete dv;
        
        //ȥ���ڱ����
        dv = head;
        head = head->next;
        delete dv;
        dv = nullptr;

        return head;
    }
};


//�ٽ�
//
//1.���ǿ��Ը�����һ���������飬��¼������L���ٱ���ɾ��L-n+1��������һ�����

//2.����ջ����ȫ����ջ����һ��һ����ջ�������ĵ�n����ΪҪɾ���Ľ�㣬��Ŀǰջ���Ľڵ���Ǵ�ɾ���ڵ��ǰ���ڵ�

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

//3.�뱾�˽ⷨ��ͬ

