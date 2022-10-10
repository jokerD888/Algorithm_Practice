// 856. 括号的分数
// 分治，可以发现大问题内有相同的子问题，可以用递归解决
class Solution {
public:
    // dfs(s,index) 返回字符串s从index开始的一个括号内的分数及其最右边界下标+1
    pair<int,int> dfs(string& s, int index) {
        if (s[index] == '(' && s[index + 1] == ')') return { 1,index + 2 };
        int res=0;
        ++index;
        while (s[index] == '(') {
            auto t = dfs(s, index);
            index = t.second;
            res += t.first;
        }
       
        return { 2*res,index + 1 };
    }
    int scoreOfParentheses(string s) {
        int N = s.size();
        s = '(' + s + ')';
        return dfs(s, 0).first/2;
    }
};

// 栈
//我们把平衡字符串s看作是一个空字符串加上s本身，并且定义空字符串的分数为0。使用栈st记录平衡字符串的分数，在开始之前要压入分数0，表示空字符串的分数。
//在遍历字符串s的过程中:
//  遇到左括号，那么我们需要计算该左括号内部的子平衡括号字符串A的分数，我们也要先压入分数0，表示A前面的空字符串的分数。
//  遇到右括号，说明该右括号内部的子平衡括号字符串A的分数已经计算出来了，我们将它弹出栈，并保存到变量v中。如果v = 0，那么说明子平衡括号字符串A是空串，(A)的分数
//  为1，否则(A)的分数为2v，然后将(A)的分数加到栈顶元素上。
//    遍历结束后，栈顶元素保存的就是s的分数。

class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);
        for (auto c : s) {
            if (c == '(') {
                st.push(0);
            } else {
                int v = st.top();
                st.pop();
                st.top() += max(2 * v, 1);
            }
        }
        return st.top();
    }
};


// 或
// 根据题意，s的分数与1分的()有关。对于每个()，它的最终分数与它所处的深度有关，如果深度为bal，那么它的最终分数为2^bal。
// 我们统计所有()的最终分数和即可。

class Solution {
public:
    int scoreOfParentheses(string s) {
        int bal = 0, n = s.size(), res = 0;
        for (int i = 0; i < n; i++) {
            bal += (s[i] == '(' ? 1 : -1);
            if (s[i] == ')' && s[i - 1] == '(') {
                res += 1 << bal;
            }
        }
        return res;
    }
};



//，217. 存在重复元素
// 哈希表
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> set;
        for (auto num : nums) {
            if (set.count(num)) return true;
            set.insert(num);
        }
        return false;
    }
};
