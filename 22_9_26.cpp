// 50. Pow(x, n)
// 快速幂
class Solution {
public:
    double myPow(double x, int n) {
        double res = 1;
        long long m = n;
        bool neg = m < 0;
        m = abs(m);
        while (m) {
            if (m & 1) res *= x;
            m >>= 1;
            x *= x;
        }
        return neg ? 1 / res : res;
    }
};
// 递归
class Solution {
public:
    double quickMul(double x, long long N) {
        if (N == 0) {
            return 1.0;
        }
        double y = quickMul(x, N / 2);
        return N % 2 == 0 ? y * y : y * y * x;      // 根据N的奇偶性来计算总终结果
    }

    double myPow(double x, int n) {
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};


// 54. 螺旋矩阵

// 模拟，每次走到走到头，每走到头一次，N或M便会-1，使用步长dist==N || dist==M来判断是否走到头
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>> matrix) {
        int N = matrix.size(), M = matrix[0].size();
        int K = N * M;
        vector<int> res(K);
        int index = -1, d = 1, dist = 0;
        int i = 0, j = -1;
        int dire[]{ -1,0,1,0,-1 };  // 上 右 下 左
        --N;

        while (K--) {
            i += dire[d],j += dire[d + 1];
            res[++index] = matrix[i][j];
            ++dist;     // 步数+1
            if ((d == 1 || d == 3) && dist == M || (d == 0 || d == 2) && dist == N) {
                if (d == 1 || d == 3) --M;
                if (d == 0 || d == 2) --N;
                d = (d + 1) % 4;        // 利用模运算调转方向
                dist = 0;
            }

        }
        return res;

    }
};

// 或一次完成一条直线
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> ans;
        if (matrix.empty()) return ans; //若数组为空，直接返回答案
        int u = 0; //赋值上下左右边界
        int d = matrix.size() - 1;
        int l = 0;
        int r = matrix[0].size() - 1;
        while (true)
        {
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
