
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
//120. 三角形最小路径和
// 法一：
//超时，原因：递归中有许多无效递归
//dp[i][j]=triangle[i][j]+min(dp[i+1][j],dp[i+1,j+1])
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
       
        return dp(triangle,0,0);
    }
    int dp(vector<vector<int>>& v,int row,int col)
    {
        if (row == v.size()-1)
            return v[row][col];
        return v[row][col] + min(dp(v, row + 1, col), dp(v, row + 1, col + 1));
        
    }
};
//法二：优化
//在上述解法中，添加二维数组记忆化
class Solution {
public:
    vector<vector<int>> memo;
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>>(triangle.size(), vector<int>(triangle.size())).swap(memo);
        return dp(triangle, 0, 0);
    }
    int dp(vector<vector<int>>& v, int row, int col)
    {
        if (row == v.size() - 1)
            return v[row][col];
        if (memo[row][col])
        {
            return memo[row][col];
        }
        return memo[row][col]=v[row][col] + min(dp(v, row + 1, col), dp(v, row + 1, col + 1));

    }
};
//时间复杂度：O(N ^ 2)，N 为三角形的行数。
//空间复杂度：O(N ^ 2)，N 为三角形的行数。

//法三：
//将解法二的「自顶向下的递归」改为「自底向上的递推」
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        int m = n + 1;
        //dp[i][j] 表示从点 (i, j) 到底边的最小路径和。
        int* dp = (int*)malloc(sizeof(int) * m * m);//也可以用嵌套vector
        //将最后一行初始化为0
        for (int j = 0; j <= m - 1; j++)
        {
            dp[(m - 1) * m + j] = 0;
        }
        // 从三角形的最后一行开始递推
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                dp[i*m+j] = min(dp[(i+1)*m+j], dp[(i + 1)*m+j+1]) + triangle[i][j];
            }
        }

        return dp[0];
    }
};
//解法四：对法三空间的优化
//实际不需要记录所有位置的数据，只需记录当前行的下一行数据即可

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }

        return dp[0];
    }
};
//时间复杂度：O(N ^ 2)，N 为三角形的行数。
//空间复杂度：O(N)，N 为三角形的行数。


//官解：
//方法一：动态规划,自上向下
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> f(n, vector<int>(n));
        f[0][0] = triangle[0][0];
        for (int i = 1; i < n; ++i) 
        {
            f[i][0] = f[i - 1][0] + triangle[i][0];//最左
            for (int j = 1; j < i; ++j) 
            {
                f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j];
            }
            f[i][i] = f[i - 1][i - 1] + triangle[i][i];//最右
        }
        return *min_element(f[n - 1].begin(), f[n - 1].end());
    }
};

//方法二：动态规划 + 空间优化
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) 
    {
        int n = triangle.size();
        vector<int> f(n);
        f[0] = triangle[0][0];
        for (int i = 1; i < n; ++i) 
        {
            f[i] = f[i - 1] + triangle[i][i];
            for (int j = i - 1; j > 0; --j) 
            {
                f[j] = min(f[j - 1], f[j]) + triangle[i][j];
            }
            f[0] += triangle[i][0];
        }
        return *min_element(f.begin(), f.end());
    }
};



int main(void)
{
    Solution s;
    vector<vector<int>> v = { {2},{3,4},{6,5,7},{4,1,8,3} };
    cout<<s.minimumTotal(v);
    return 0;
}