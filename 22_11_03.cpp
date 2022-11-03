// 剑指 Offer 12. 矩阵中的路径

// dfs
class Solution {
public:

    bool dfs(vector<vector<char>>& board, string& word, int r, int c, int cur) {
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size()) return false;
        if (board[r][c] != word[cur]) return false;
        if (cur == word.size() - 1) return true;


        char tmp = board[r][c];
        board[r][c] = '1';
        const int dire[]{ -1,0,1,0,-1 };
        for (int i = 0; i < 4; ++i) {
            int x = r + dire[i], y = c + dire[i + 1];
            if (dfs(board, word, x, y, cur + 1)) {
                board[r][c] = tmp;
                return true;
            }
        }
        board[r][c] = tmp;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
};



// 25. K 个一组翻转链表

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 时间复杂度为O(N) 除开最后不足k的节点需要遍历两次，其他都只需要遍历一次
// 空间O(1)
class Solution {
public:
    bool full_k = true;

    // 翻转链表
    // 返回头，同时通过传入传出参数返回下一个段的头
    ListNode* reverseList(ListNode*& head, int k) {
        ListNode* cur = head->next;
        head->next = nullptr;
        int i;
        for (i = 0; i < k - 1 && cur; ++i) {
            ListNode* ne = cur->next;
            cur->next = head;
            head = cur;
            cur = ne;
        }
        if (i < k - 1) full_k = false;

        ListNode* ret = head;
        head = cur;
        return ret;

    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* cur = head;
        ListNode* dummy = new ListNode(0, head);   // 利用哑节点，可避免头节点的特殊考虑
        ListNode* cur_head = nullptr;
        ListNode* prev_tail = dummy;
        while (cur) {
            ListNode* cur_tail = cur;     // 此为翻转后的段尾
            cur_head = reverseList(cur, k);     // cur传的是引用，返回值将指向一下段的头
            if (!full_k)        // 不足k个，再翻转一次
                cur_head = reverseList(cur_head, k);

            prev_tail->next = cur_head;     // 上一个尾巴指向当前头
            prev_tail = cur_tail;   // 尾巴更新
        }

        ListNode* ret = dummy->next;
        delete dummy;
        return ret;
    }
};


// 或
// 此法比上法稍慢，除开后面不足k个的，每个节点需要遍历两次
class Solution {
public:
    // 翻转一个子链表，并且返回新的头与尾
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail) {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return { tail, head };
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0);   
        dummy->next = head;
        ListNode* pre = dummy;

        while (head) {
            ListNode* tail = pre;
            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    return dummy->next;
                }
            }
            ListNode* nex = tail->next;
            // 这里是 C++17 的写法，也可以写成
            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
            // head = result.first;
            // tail = result.second;
            tie(head, tail) = myReverse(head, tail);
            // 把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }

        return dummy->next;
    }
};

// 与上法类似

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1)
            return head;

        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy, * cur = dummy;
        while (cur) {
            ListNode* tmp = cur->next;
            int n = k;
            while (n--) {

                cur = cur->next;
                if (!cur)
                    return dummy->next;
            }
            prev->next = cur;


            ListNode* before = cur->next, * next;
            cur = tmp, n = k;
            while (n--) {
                next = cur->next;
                cur->next = before;
                before = cur;
                cur = next;
            }

            cur = prev = tmp;

        }

        return dummy->next;
    }
};