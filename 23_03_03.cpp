

// 328. 奇偶链表

 struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* odd=head, * even=head->next;

        ListNode* odd_cur = odd, * even_cur = even;
        while (even_cur && even_cur->next) {
            odd_cur->next = even_cur->next;
            odd_cur = odd_cur->next;
            even_cur->next = odd_cur->next;
            even_cur = even_cur->next;
        }
        odd_cur->next = even;
        return odd;
    }
};


// 225. 用队列实现栈
// 单个队列

class MyStack {
public:
    queue<int> que;
    MyStack() {

    }

    void push(int x) {
        int size = que.size();
        que.push(x);
        for (int i = 0; i < size; ++i) {
            que.push(que.front());
            que.pop();
        }

    }

    int pop() {
        int res = que.front();
        que.pop();
        return res;
    }

    int top() {
        return que.front();
    }

    bool empty() {
        return que.empty();
    }
};

// 双队列
class MyStack {
public:
    queue<int> q1, q2;
    MyStack() {

    }

    void push(int x) {
        q2.push(x);
        while (q1.size()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    int pop() {
        int res = q1.front();
        q1.pop();
        return res;
    }

    int top() {
        return q1.front();
    }

    bool empty() {
        return q1.empty();
    }
};


// 54. 螺旋矩阵
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();

        vector<int> res;
        int dire[]{ 0,1,0,-1,0 };       // 右下左上
        int x = 0, y = 0;
        while (res.size() < n * m) {
            for (int i = 0; i < 4; ++i) {
                while (x >= 0 && x < n && y >= 0 && y < m && matrix[x][y] <= 100) {
                    res.push_back(matrix[x][y]);
                    matrix[x][y] = 101;
                    x = x + dire[i];
                    y = y + dire[i + 1];
                }
                x -= dire[i];
                y -= dire[i + 1];
                x += dire[i + 1];
                y += dire[(i + 2) % 4];
            }
        }
        return res;
    }
};

// 或
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> ans;
        if (matrix.empty()) return ans; //若数组为空，直接返回答案
        int u = 0; //赋值上下左右边界
        int d = matrix.size() - 1;
        int l = 0;
        int r = matrix[0].size() - 1;
        while (true) {
            for (int i = l; i <= r; ++i) ans.push_back(matrix[u][i]); //向右移动直到最右
            if (++u > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
            for (int i = u; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
            if (--r < l) break; //重新设定有边界
            for (int i = r; i >= l; --i) ans.push_back(matrix[d][i]); //向左
            if (--d < u) break; //重新设定下边界
            for (int i = d; i >= u; --i) ans.push_back(matrix[i][l]); //向上
            if (++l > r) break; //重新设定左边界
        }
        return ans;
    }
};

// 155. 最小栈

// 辅助栈，同步记录最小值
class MinStack {
public:
    stack<int> st, min_st;
    MinStack() {
        min_st.push(INT_MAX);
    }

    void push(int val) {
        st.push(val);
        min_st.push(min(val, min_st.top()));
    }

    void pop() {
        st.pop();
        min_st.pop();
    }

    int top() {
        return st.top();

    }

    int getMin() {
        return min_st.top();
    }
};

// 不使用额外的空间
// 栈中保存差值
class MinStack {
public:
    stack<long long> st;        // 保存和最小值的差值，如是负数，说明该数使得最小数minv更新
    long long minv;     // 栈中最小值

    MinStack() {
        minv = -1;
    }

    void push(int val) {
        if (!st.size()) {
            st.push(0);     // 差值0
            minv = val;     
        } else {//这次的值减去已有的最小值
            long long diff = val - minv;
            st.push(diff);
            // diff>0,即val大于miv差值不动，<0,val小于minv,更新最小值
            minv = diff < 0 ? val : minv;
        }
    }

    void pop() {
        if (st.size()) {
            long long diff = st.top();
            st.pop();
            if (diff < 0)
                minv -= diff;
        }
    }

    int top() {
        long long diff = st.top();
        if (diff < 0)
            return minv;
        else
            return minv + diff;
    }

    int getMin() {
        return minv;
    }
};


 // 232. 用栈实现队列
// 双栈
// st1栈作为输入栈，完成push，st2作为输出栈,完成pop和peek
// 一旦st2空，就将st1倒入st2中
class MyQueue {
public:
    stack<int> st1, st2;
    MyQueue() {

    }

    void push(int x) {
        st1.push(x);
    }

    int pop() {
        int res = peek();
        if (st2.size()) {
            st2.pop();
        } else {
            while (st1.size()) {
                st2.push(st1.top());
                st1.pop();
            }
            st2.pop();
        }
        return res;
    }

    int peek() {
        if (st2.size()) {
            return st2.top();
        } else {
            while (st1.size()) {
                st2.push(st1.top());
                st1.pop();
            }
            return st2.top();
        }
    }

    bool empty() {
        return st1.empty() && st2.empty();
    }
};

