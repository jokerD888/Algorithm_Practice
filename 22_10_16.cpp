// 227. 基本计算器 II
// 优先计算乘除，同时记录前一个符号的位置，如果是乘除立马计算，否则入栈。遍历完后，栈中数据累计即可
class Solution {
public:
    int calculate(string s) {
        vector<int> stk;
        char preSign = '+';
        int num = 0;
        int n = s.length();
        for (int i = 0; i < n; ++i) {
            if (isdigit(s[i])) {
                num = num * 10 + int(s[i] - '0');
            }
            // 遇到操作符 或 走到了终点进行结尾 ， 这个if语句很巧妙
            if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1) {
                switch (preSign) {
                case '+':
                    stk.push_back(num);
                    break;
                case '-':
                    stk.push_back(-num);
                    break;
                case '*':
                    stk.back() *= num;
                    break;
                default:
                    stk.back() /= num;
                }
                preSign = s[i];
                num = 0;
            }
        }
        return accumulate(stk.begin(), stk.end(), 0);
    }
};


// 对于表达式计算的通用计算方法是
// 使用双栈nums,opt  一个存数组，一个存操作符
// 对于数字字符，连续取出完整数字，加入nums栈中
// 对于（,入opt
// 对于）,使用nums,opt双栈中的数据进行结算，直到opt弹出的过程中遇到（
// 对于运算符，放入opt栈前，把能结算的结算，即若要当前运算符等级小于等于opt栈中运算符的等级时进行计算，直到没有操作符或遇到（,将计算结果放到nums中

// 一些特殊情况，为防止开头是负数，nums中先加一个0
// 将一些空格去掉，将（- 替换为（0- ，将（+ 替换为 （0+
// 最好使用long long防止可能的溢出
// 大体流程如下
class Solution {
public:
    unordered_map<char, int> oper_pri = {
            {'+',1},
            {'-',1},
            {'*',2},
            {'/',2},
            {'%',2},
            {'^',3}
    };
    stack<char> opers;
    stack<long long> nums;
    int calculate(string s) {
        nums.push(0);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] == ' ') continue;
            else if (s[i] == '(') {
                opers.push('(');
                if (s[i + 1] == '-') {
                    i++;
                    nums.push(0);
                    opers.push('-');
                }
            } else if (s[i] == ')') {
                while (opers.top() != '(') {
                    cal();
                }
                opers.pop();
            } else if ('0' <= s[i] && s[i] <= '9') {
                int l = i;
                while (i + 1 < n && '0' <= s[i + 1] && s[i + 1] <= '9')
                    i++;
                nums.push(stoll(s.substr(l, i - l + 1)));
            } else {
                while (!opers.empty() && opers.top() != '(' && oper_pri[opers.top()] >= oper_pri[s[i]]) {
                    cal();
                }
                opers.push(s[i]);
            }
        }
        while (!opers.empty() && opers.top() != '(') {
            cal();
        }
        return nums.top();
    }
    void cal() {
        long long b = nums.top(); nums.pop();
        long long a = nums.top(); nums.pop();
        char oper = opers.top(); opers.pop();
        long long res;
        switch (oper) {
        case '+':   res = a + b; break;
        case '-':   res = a - b; break;
        case '*':   res = a * b; break;
        case '/':   res = a / b; break;
        case '%':   res = a % b; break;
        case '^':   res = pow(a, b); break;
        }
        nums.push(res);
    }
};


// 237. 删除链表中的节点
// 这里的删除节点并不是传统意义上的在内存上进行删除，这里没有给头节点，我们就只能将node之后节点的值赋给前一个

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* next_node = node->next;
        while (next_node) {
            node->val = next_node->val;
            next_node = next_node->next;
            if (next_node)
                node = node->next;
        }
        node->next = nullptr;
    }
};
// 但其实，只需要进行一次赋值即可，随后将指针指向下下个节点即可
class Solution {
public:
    void deleteNode(ListNode* node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};



// 289. 生命游戏

// 将右边第二位作为下一个状态，随后整体遍历完再修改过来
class Solution {
public:
    static constexpr int dx[]{ -1,0,1,0,-1,-1,1,1 };
    static constexpr int dy[]{ 0,1,0,-1,-1,1,1,-1 };
    void gameOfLife(vector<vector<int>>& board) {
        int N = board.size(), M = board[0].size();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) {
                int cnt = 0;
                for (int k = 0; k < 8; ++k) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 0 && x < N && y >= 0 && y < M) {
                        if (board[x][y] & 1) ++cnt;
                    }
                }
                // 只要周围活细胞数=3，那么该位置一定活  或  若该位置原是活细胞且周围活细胞数为2，依然活
                if ((board[i][j] & 1) && cnt == 2 || cnt == 3) board[i][j] |= 2;
            }
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                board[i][j] >>= 1;
    }
};