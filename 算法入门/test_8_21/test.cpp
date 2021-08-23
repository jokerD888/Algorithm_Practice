
//递归 / 回溯

#include<iostream>
using namespace std;
#include<vector>
#include<stack>
//77. 组合

//回溯+剪枝

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
//时间复杂度O((n取k)*k)
//空间复杂度O(n+k)


//官解
//方法一：递归实现组合型枚举
//类似与二进制枚举，1~n的每个数组无非只有两种状态，要么在组合里，要么不在组合里
class Solution {
public:
    vector<int> temp;
    vector<vector<int>> ans;

    void dfs(int cur, int n, int k) {
        // 剪枝：temp 长度加上区间 [cur, n] 的长度小于 k，不可能构造出长度为 k 的 temp
        if (temp.size() + (n - cur + 1) < k) {
            return;
        }
        // 记录合法的答案
        if (temp.size() == k) {
            ans.push_back(temp);
            return;
        }
        // 考虑选择当前位置
        temp.push_back(cur);
        dfs(cur + 1, n, k);
        // 考虑不选择当前位置
        temp.pop_back();
        dfs(cur + 1, n, k);
    }

    vector<vector<int>> combine(int n, int k) {
        dfs(1, n, k);
        return ans;
    }
};
//时间复杂度O((n取k)*k)
//空间复杂度O(n+k)

//方法二：非递归（字典序法）实现组合型枚举
class Solution {
public:
    vector<int> temp;
    vector<vector<int>> ans;

    vector<vector<int>> combine(int n, int k) {
        // 初始化
        // 将 temp 中 [0, k - 1] 每个位置 i 设置为 i + 1，即 [0, k - 1] 存 [1, k]
        // 末尾加一位 n + 1 作为哨兵
        for (int i = 1; i <= k; ++i) {
            temp.push_back(i);
        }
        temp.push_back(n + 1);

        int j = 0;
        while (j < k) 
        {
            ans.emplace_back(temp.begin(), temp.begin() + k);
            j = 0;
            // 寻找第一个 temp[j] + 1 != temp[j + 1] 的位置 t
            // 我们需要把 [0, t - 1] 区间内的每个位置重置成 [1, t]
            while (j < k && temp[j] + 1 == temp[j + 1]) {
                temp[j] = j + 1;
                ++j;
            }
            // j 是第一个 temp[j] + 1 != temp[j + 1] 的位置
            ++temp[j];
        }
        return ans;
    }
};


//全排列
//回溯
//每次从数组nums选一个出来，再把其删除数组，进入下一层递归，递归回来后再将删除的元素恢复到原处，状态重置
//或者用一个标记数组，记录是否已插入path
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
//时间复杂度O(N的阶乘）N为原数组nums的大小，未考虑删除元素与插入元素的时间
//空间复杂度O(N)答案数组未计入，递归调用深度也为 O(n)


//官解回溯
//通过把数组分为两部分，左部分为已记录的，右部分为未记录的，通过交换边界之后的元素完成记录
//不过此法生成的全排列不是按字典存储输出的
class Solution {
public:
    void backtrack(vector<vector<int>>& res, vector<int>& output, int first, int len) {
        // 所有数都填完了
        if (first == len) {
            res.emplace_back(output);
            return;
        }
        for (int i = first; i < len; ++i) {
            // 动态维护数组
            swap(output[i], output[first]);
            // 继续递归填下一个数
            backtrack(res, output, first + 1, len);
            // 撤销操作
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};
//时间复杂度O(N的阶乘）N为原数组nums的大小
//空间复杂度O(N)答案数组未计入，递归调用深度也为 O(n)


//784. 字母大小写全排列
//没个字母无非只有两种状态，大写或小写,通过递归枚举所有情况
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
        //字母变小写
        s[start] = tolower(s[start]);
        dfs(s, start + 1, v);
        //字母变大写
        s[start] = toupper(s[start]);
        dfs(s, start + 1, v);

    }
};
//时间复杂度O(2^N*N),最坏情况下，字符串中全是字母
//空间复杂度O(N) N为字符个数，即递归深度

//二分掩码
//妙
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
//官解类似

int main(void)
{
    Solution s;
    s.letterCasePermutation("a1b2cd5");
}