
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
//120. ��������С·����
// ��һ��
//��ʱ��ԭ�򣺵ݹ����������Ч�ݹ�
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
//�������Ż�
//�������ⷨ�У���Ӷ�ά������仯
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
//ʱ�临�Ӷȣ�O(N ^ 2)��N Ϊ�����ε�������
//�ռ临�Ӷȣ�O(N ^ 2)��N Ϊ�����ε�������

//������
//���ⷨ���ġ��Զ����µĵݹ项��Ϊ���Ե����ϵĵ��ơ�
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        int m = n + 1;
        //dp[i][j] ��ʾ�ӵ� (i, j) ���ױߵ���С·���͡�
        int* dp = (int*)malloc(sizeof(int) * m * m);//Ҳ������Ƕ��vector
        //�����һ�г�ʼ��Ϊ0
        for (int j = 0; j <= m - 1; j++)
        {
            dp[(m - 1) * m + j] = 0;
        }
        // �������ε����һ�п�ʼ����
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
//�ⷨ�ģ��Է����ռ���Ż�
//ʵ�ʲ���Ҫ��¼����λ�õ����ݣ�ֻ���¼��ǰ�е���һ�����ݼ���

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
//ʱ�临�Ӷȣ�O(N ^ 2)��N Ϊ�����ε�������
//�ռ临�Ӷȣ�O(N)��N Ϊ�����ε�������


//�ٽ⣺
//����һ����̬�滮,��������
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> f(n, vector<int>(n));
        f[0][0] = triangle[0][0];
        for (int i = 1; i < n; ++i) 
        {
            f[i][0] = f[i - 1][0] + triangle[i][0];//����
            for (int j = 1; j < i; ++j) 
            {
                f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j];
            }
            f[i][i] = f[i - 1][i - 1] + triangle[i][i];//����
        }
        return *min_element(f[n - 1].begin(), f[n - 1].end());
    }
};

//����������̬�滮 + �ռ��Ż�
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