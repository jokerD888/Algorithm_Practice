
//�ݹ� / ����

#include<iostream>
using namespace std;
#include<vector>
#include<stack>
//77. ���

//����+��֦

class Solution {
public:
    vector<int> path;
    vector<vector<int>> v;
    void BackTracking(int n, int k, int startIndex)
    {
        if (path.size() == k)
        {
            v.push_back(path);
            return;
        }
        for (int i = startIndex; i <= n-(k-path.size())+1; i++)
        {
            path.push_back(i);
            BackTracking(n, k, i + 1);
            path.pop_back();
        }

    }

    vector<vector<int>> combine(int n, int k) {
        BackTracking(n, k, 1);
        return v;
    }
};
//ʱ�临�Ӷ�O((nȡk)*k)
//�ռ临�Ӷ�O(n+k)


//�ٽ�
//����һ���ݹ�ʵ�������ö��
//�����������ö�٣�1~n��ÿ�������޷�ֻ������״̬��Ҫô������Ҫô���������
class Solution {
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int n, int k) {
        // ��֦��temp ���ȼ������� [cur, n] �ĳ���С�� k�������ܹ��������Ϊ k �� temp
        if (temp.size() + (n - cur + 1) < k) {
            return;
        }
        // ��¼�Ϸ��Ĵ�
        if (temp.size() == k) {
            ans.push_back(temp);
            return;
        }
        // ����ѡ��ǰλ��
        temp.push_back(cur);
        dfs(cur + 1, n, k);
        // ���ǲ�ѡ��ǰλ��
        temp.pop_back();
        dfs(cur + 1, n, k);
    }

    vector<vector<int>> combine(int n, int k) {
        dfs(1, n, k);
        return ans;
    }
};
//ʱ�临�Ӷ�O((nȡk)*k)
//�ռ临�Ӷ�O(n+k)

//���������ǵݹ飨�ֵ��򷨣�ʵ�������ö��
class Solution {
public:
    vector<int> temp;
    vector<vector<int>> ans;

    vector<vector<int>> combine(int n, int k) {
        // ��ʼ��
        // �� temp �� [0, k - 1] ÿ��λ�� i ����Ϊ i + 1���� [0, k - 1] �� [1, k]
        // ĩβ��һλ n + 1 ��Ϊ�ڱ�
        for (int i = 1; i <= k; ++i) {
            temp.push_back(i);
        }
        temp.push_back(n + 1);

        int j = 0;
        while (j < k) 
        {
            ans.emplace_back(temp.begin(), temp.begin() + k);
            j = 0;
            // Ѱ�ҵ�һ�� temp[j] + 1 != temp[j + 1] ��λ�� t
            // ������Ҫ�� [0, t - 1] �����ڵ�ÿ��λ�����ó� [1, t]
            while (j < k && temp[j] + 1 == temp[j + 1]) {
                temp[j] = j + 1;
                ++j;
            }
            // j �ǵ�һ�� temp[j] + 1 != temp[j + 1] ��λ��
            ++temp[j];
        }
        return ans;
    }
};


//ȫ����
//����
//ÿ�δ�����numsѡһ���������ٰ���ɾ�����飬������һ��ݹ飬�ݹ�������ٽ�ɾ����Ԫ�ػָ���ԭ����״̬����
//������һ��������飬��¼�Ƿ��Ѳ���path
class Solution {
public:
    vector<int> path;
    vector<vector<int>> v;
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        BackTracking(nums,n);
        return v;
    }
    void BackTracking(vector<int> nums,int n)
    {
        if (n == path.size())
        {
            v.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            nums.erase(nums.begin() + i);
            BackTracking(nums,n);
            nums.insert(nums.begin() + i, path[path.size() - 1]);
            path.pop_back();
        }
    }

};
//ʱ�临�Ӷ�O(N�Ľ׳ˣ�NΪԭ����nums�Ĵ�С��δ����ɾ��Ԫ�������Ԫ�ص�ʱ��
//�ռ临�Ӷ�O(N)������δ���룬�ݹ�������ҲΪ O(n)


//�ٽ����
//ͨ���������Ϊ�����֣��󲿷�Ϊ�Ѽ�¼�ģ��Ҳ���Ϊδ��¼�ģ�ͨ�������߽�֮���Ԫ����ɼ�¼
//�����˷����ɵ�ȫ���в��ǰ��ֵ�洢�����
class Solution {
public:
    void backtrack(vector<vector<int>>& res, vector<int>& output, int first, int len) {
        // ��������������
        if (first == len) {
            res.emplace_back(output);
            return;
        }
        for (int i = first; i < len; ++i) {
            // ��̬ά������
            swap(output[i], output[first]);
            // �����ݹ�����һ����
            backtrack(res, output, first + 1, len);
            // ��������
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};
//ʱ�临�Ӷ�O(N�Ľ׳ˣ�NΪԭ����nums�Ĵ�С
//�ռ临�Ӷ�O(N)������δ���룬�ݹ�������ҲΪ O(n)


//784. ��ĸ��Сдȫ����
//û����ĸ�޷�ֻ������״̬����д��Сд,ͨ���ݹ�ö���������
#include<cctype>
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> v;
        dfs(s, 0,v);
        return v;
    }
    void dfs(string s, int start, vector<string>& v)
    {
        while (!isalpha(s[start]) && start<s.size())
        {
            start++;
        }
        if (start == s.size())
        {
            v.push_back(s);
            return;
        }
        //��ĸ��Сд
        s[start] = tolower(s[start]);
        dfs(s, start + 1, v);
        //��ĸ���д
        s[start] = toupper(s[start]);
        dfs(s, start + 1, v);

    }
};
//ʱ�临�Ӷ�O(2^N*N),�����£��ַ�����ȫ����ĸ
//�ռ临�Ӷ�O(N) NΪ�ַ����������ݹ����

//��������
//��
class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> v;
        int n = 0;
        for (char c : s)
        {
            if (isalpha(c))
                n++;
        }

        for (int bits = 0; bits < 1 << n; bits++)
        {
            int b = 0;
            string str;
            for (char letter : s)
            {
                if (isalpha(letter))
                {
                    if (((bits >> b++) & 1) == 1)
                        str += tolower(letter);
                    else
                        str += toupper(letter);
                }
                else
                {
                    str+=letter;
                }
            }
            v.push_back(str);
        }
        return v;

    }
};
//�ٽ�����

int main(void)
{
    Solution s;
    s.letterCasePermutation("a1b2cd5");
}