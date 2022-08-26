// 84. 柱状图中最大的矩形
// 单调栈
// 找每个位置，左边最近的比它小的，右边最近的比它小的
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (st.size() && heights[st.top()] >= heights[i]) st.pop();
            left[i] = st.size() ? st.top() : -1;
            st.push(i);
        }
        st = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (st.size() && heights[st.top()] >= heights[i]) st.pop();
            right[i] = st.size() ? st.top() : n;
            st.push(i);
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, (right[i] - left[i] - 1) * heights[i]);
        }
        return res;
    }
};
// 数组模拟栈

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n), st(n + 1);
        int tt = 0;
        for (int i = 0; i < n; ++i) {
            while (tt && heights[st[tt]] >= heights[i])--tt;
            left[i] = tt ? st[tt] : -1;
            st[++tt] = i;
        }
        tt = 0;
        for (int i = n - 1; i >= 0; --i) {
            while (tt && heights[st[tt]] >= heights[i]) --tt;
            right[i] = tt ? st[tt] : n;
            st[++tt] = i;
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, (right[i] - left[i] - 1) * heights[i]);
        }
        return res;
    }
};

// 以上做法左右边界我们分别求了两次，也可以合并为一次完成
// 即栈弹出时，谁迫使其弹出的即为右边的最近的比它小的

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n, n);

        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = (st.empty() ? -1 : st.top());
            st.push(i);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
};




// 85. 最大矩形
// 单调栈
// 我们可以把矩阵看作柱状图，枚举柱状图的底边，从下往上看，连续为1的看为柱子，只要出现一个0,就不再往上看了
class Solution {
public:
    int process(const vector<int>& h) {
        int res = 0, n = h.size() - 2;
        vector<int> l(n + 2), r(n + 2), q(n + 2);
        int tt = -1;
        q[++tt] = 0;
        for (int i = 1; i <= n; ++i) {
            while (h[q[tt]] >= h[i]) --tt;
            l[i] = q[tt];
            q[++tt] = i;
        }
        tt = -1;
        q[++tt] = n + 1;
        for (int i = n; i; --i) {
            while (h[q[tt]] >= h[i])--tt;
            r[i] = q[tt];
            q[++tt] = i;
        }
        for (int i = 1; i <= n; ++i) {
            res = max(res, (r[i] - l[i] - 1) * h[i]);
        }
        return res;


    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> h(n + 1, vector<int>(m + 2, -1));

        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= m; ++j) {
                h[i][j] = matrix[i][j - 1] == '1' ? (i ? h[i - 1][j] + 1 : 1) : 0;
            }
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, process(h[i]));
        }
        return res;
    }
};



// 或使用直方图的暴力优化方案
// left[i][j] 为矩阵第 i 行第 j 列元素的左边连续 1 的数量。
// 我们枚举矩阵的每一个位置作为答案矩阵的右下角并向上扩展高
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        vector<vector<int>> left(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
                }
            }
        }

        int ret = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '0') {
                    continue;
                }
                int width = left[i][j];
                int area = width;
                for (int k = i - 1; k >= 0; k--) {  // 向上扩展高
                    width = min(width, left[k][j]);
                    area = max(area, (i - k + 1) * width);
                }
                ret = max(ret, area);
            }
        }
        return ret;
    }
};

