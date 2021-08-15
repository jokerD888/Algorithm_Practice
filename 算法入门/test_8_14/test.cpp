//��������


//3. ���ظ��ַ�����Ӵ�
#include<iostream>
#include<unordered_set>
using namespace std;

//���ε�����ö���Ӵ�����ʼλ�ã���ʼѰ�����ִ����ַ���ͬ���ַ���λ�ã�����Ϊ���ִ����ұ߽磬
//Ȼ��ʼѰ������ִ���2���ַ���ͬ���ַ���λ�ã��ٴθ��ݲ��ҵ�λ���޸��ұ߽磬ֱ��ѭ�������������ظ�Ԫ�ص��ִ��ĳ��ȼ�Ϊ�ұ߽�-�ִ���Ԫ���±�
//���ε��� ��ȥ��Ѱ�����ֵ
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

            while (us.find(s[right]) == us.end() && right < n)//Ҫ�����Ԫ���ڼ����в����ڣ�˵����Ԫ�ز������Ȼ���ظ�Ԫ��
            {
                us.insert(s[right]);
                ++right;
            }
            //�ߵ��ⲽ��˵����s[i]Ϊ��Ԫ�ص����ظ��ִ����������
            maxStr = max(maxStr, right - i);
        }

        return maxStr;

    }
};

//����
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
//�ٽ�
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // ��ϣ���ϣ���¼ÿ���ַ��Ƿ���ֹ�
        unordered_set<char> occ;
        int n = s.size();
        // ��ָ�룬��ʼֵΪ -1���൱���������ַ�������߽����࣬��û�п�ʼ�ƶ�
        int rk = -1, ans = 0;
        // ö����ָ���λ�ã���ʼֵ���Եر�ʾΪ -1
        for (int i = 0; i < n; ++i) 
        {
            if (i != 0) 
            {
                // ��ָ�������ƶ�һ���Ƴ�һ���ַ�
                occ.erase(s[i - 1]);
            }
            while (rk + 1 < n && !occ.count(s[rk + 1])) 
            {
                // ���ϵ��ƶ���ָ��
                occ.insert(s[rk + 1]);
                ++rk;
            }
            // �� i �� rk ���ַ���һ�����������ظ��ַ��Ӵ�
            ans = max(ans, rk - i + 1);
        }
        return ans;
    }
};


//567. �ַ���������   


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
//��ʱ������������
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


//�ٽ�

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
//�Ż�
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
