//滑动窗口


//3. 无重复字符的最长子串
#include<iostream>
#include<unordered_set>
using namespace std;

//依次递增地枚举子串的起始位置，开始寻找与字串首字符相同的字符的位置，设置为该字串的右边界，
//然后开始寻找与该字串第2个字符相同的字符的位置，再次根据查找的位置修改右边界，直到循环结束，该无重复元素的字串的长度即为右边界-字串首元素下标
//依次递增 下去，寻找最大值
class Solution 
{
public:
    int lengthOfLongestSubstring(string s) 
    {
        int num = 0, maxStr = 0;
        int n = s.size();
        for (int i = 0; i < s.size(); i++)
        {
            bool repeat = false;
            int ret = s.find(s[i], i+1);
            if (ret == -1)
            {
                ret = n;
            }
            for (int j = i+1; j < ret; j++)
            {
                int tmp = s.find(s[j], j + 1);
                if (tmp != -1 && tmp < ret)
                {
                    ret = tmp;
                }
            }
            num = ret - i;
            if (num > maxStr)
                maxStr = num;
        }
        return maxStr;
    }
};

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size();
        unordered_set<char> us;
        int maxStr = 0, right = 0;
        for (int i = 0; i < n; i++)
        {
            if (i != 0)
            {
                us.erase(s[i-1]);
            }

            while (us.find(s[right]) == us.end() && right < n)//要插入的元素在集合中不存在，说明此元素插入后依然无重复元素
            {
                us.insert(s[right]);
                ++right;
            }
            //走到这步即说明以s[i]为首元素的无重复字串到达了最长；
            maxStr = max(maxStr, right - i);
        }

        return maxStr;

    }
};

//网解
class Solution {
public:
    int lengthOfLongestSubstring(string s) 
    {
        if (s.size() == 0) return 0;
        unordered_set<char> lookup;
        int maxStr = 0;
        int left = 0;
        for (int i = 0; i < s.size(); i++) 
        {
            while (lookup.find(s[i]) != lookup.end()) 
            {
                lookup.erase(s[left]);
                left++;
            }
            maxStr = max(maxStr, i - left + 1);
            lookup.insert(s[i]);
        }
        return maxStr;

    }
};
//官解
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // 哈希集合，记录每个字符是否出现过
        unordered_set<char> occ;
        int n = s.size();
        // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
        int rk = -1, ans = 0;
        // 枚举左指针的位置，初始值隐性地表示为 -1
        for (int i = 0; i < n; ++i) 
        {
            if (i != 0) 
            {
                // 左指针向右移动一格，移除一个字符
                occ.erase(s[i - 1]);
            }
            while (rk + 1 < n && !occ.count(s[rk + 1])) 
            {
                // 不断地移动右指针
                occ.insert(s[rk + 1]);
                ++rk;
            }
            // 第 i 到 rk 个字符是一个极长的无重复字符子串
            ans = max(ans, rk - i + 1);
        }
        return ans;
    }
};


//567. 字符串的排列   


class Solution 
{
public:
    bool checkInclusion(string s1, string s2)
    {
        unordered_set<char> us;
        int maxStr=0;
        
        us.insert(s2)

    }
};
//超时。。。。。。
class Solution
{
public:
    bool checkInclusion(string s1, string s2)
    {
        int n1 = s1.size();
        int n2 = s2.size();
        for (int i = 0; i <= n2 - n1; i++)
        {
            vector<int> v(n1);
            if (s1.find(s2[i]) != -1)
            {
                int j = 0;
                for (j=i; j < i+n1; j++)
                {
                    int ret = s1.find(s2[j]);
                    if (ret != -1)
                    {
                        int k = 0;
                        for (int k = ret; k < n1; k++)
                        {
                            if (s1[k] == s2[j] && v[k]!=1)
                            {
                                v[k] = 1;
                                break;
                            }
                        }
                        if (k == n1)
                            break;
                    }
                    else
                        break;
                }
                if (j == i+n1)
                {
                    int k = 0;
                    for (; k < n1; k++)
                    {
                        if (v[k] != 1)
                            break;
                    }
                    if (k == n1)
                        return true;
                }

            }

        }
        return false;

    }
};


//官解

class Solution {
public:
    bool checkInclusion(string s1, string s2) 
    {
        int n = s1.length(), m = s2.length();
        if (n > m) 
        {
            return false;
        }
        vector<int> cnt1(26), cnt2(26);
        for (int i = 0; i < n; ++i) 
        {
            ++cnt1[s1[i] - 'a'];
            ++cnt2[s2[i] - 'a'];
        }
        if (cnt1 == cnt2)
        {
            return true;
        }
        for (int i = n; i < m; ++i) 
        {
            ++cnt2[s2[i] - 'a'];
            --cnt2[s2[i - n] - 'a'];
            if (cnt1 == cnt2) 
            {
                return true;
            }
        }
        return false;
    }
};
//优化
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        if (n > m) {
            return false;
        }
        vector<int> cnt(26);
        for (int i = 0; i < n; ++i) {
            --cnt[s1[i] - 'a'];
            ++cnt[s2[i] - 'a'];
        }
        int diff = 0;
        for (int c : cnt) {
            if (c != 0) {
                ++diff;
            }
        }
        if (diff == 0) {
            return true;
        }
        for (int i = n; i < m; ++i) {
            int x = s2[i] - 'a', y = s2[i - n] - 'a';
            if (x == y) {
                continue;
            }
            if (cnt[x] == 0) {
                ++diff;
            }
            ++cnt[x];
            if (cnt[x] == 0) {
                --diff;
            }
            if (cnt[y] == 0) {
                ++diff;
            }
            --cnt[y];
            if (cnt[y] == 0) {
                --diff;
            }
            if (diff == 0) {
                return true;
            }
        }
        return false;
    }
};



class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        if (n > m) {
            return false;
        }
        vector<int> cnt(26);
        for (int i = 0; i < n; ++i) {
            --cnt[s1[i] - 'a'];
        }
        int left = 0;
        for (int right = 0; right < m; ++right) {
            int x = s2[right] - 'a';
            ++cnt[x];
            while (cnt[x] > 0) {
                --cnt[s2[left] - 'a'];
                ++left;
            }
            if (right - left + 1 == n) {
                return true;
            }
        }
        return false;
    }
};
