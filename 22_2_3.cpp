//1763. 最长的美好子字符串
//法一:暴力枚举
//class Solution {
//public:
//    string longestNiceSubstring(string s) {
//        int maxPos = 0, maxLen = 0;
//        int len = s.size();
//        for (int i = 1; i <= len; ++i) {    //完美字串长度
//            for (int j = 0; j <= len-i; ++j) {   //起始位置
//                int lower = 0;  //小写字母标记
//                int upper = 0;  //大写字母标记
//                for (int k = j; k < j+i && k<len; ++k) {
//                    if (islower(s[k])) {
//                        lower |= 1 << (s[k] - 'a');
//                    } else {
//                        upper |= 1 << (s[k] - 'A');
//                    }
//                    
//                }
//                if (lower == upper && i > maxLen) { //若有更长的，更新
//                    maxPos = j;
//                    maxLen = i;
//                }
//            }
//        }
//        return s.substr(maxPos, maxLen);
//    }
//};
//时间O（n^3)



//因只有26个英文字母可以用二进制位来标记
//class Solution {
//public:
//    string longestNiceSubstring(string s) {
//        int n = s.size();
//        int maxPos = 0;     //最长的完美字串出现的位置  
//        int maxLen = 0;     //最长完美字串长度
//        for (int i = 0; i < n; ++i) {
//            int lower = 0;  //小写字母标记
//            int upper = 0;  //大写字母标记
//            for (int j = i; j < n; ++j) {
//                if (islower(s[j])) {
//                    lower |= 1 << (s[j] - 'a');
//                } else {
//                    upper |= 1 << (s[j] - 'A');
//                }
//                if (lower == upper && j - i + 1 > maxLen) { //若有更长的，更新
//                    maxPos = i;
//                    maxLen = j - i + 1;
//                }
//            }
//        }
//        return s.substr(maxPos, maxLen);
//    }
//};
//时间O（N^2）
//空间O（1）


//方法二：分治
//利用非法字符（即出现一种形式的字母）做为分割，再依次再各个区间做分割，直到区间为完美字串
//class Solution {
//public:
//    void dfs(const string& s, int start, int end, int& maxPos, int& maxLen) {
//        if (start >= end) {     //base  越界
//            return;
//        }
//        int lower = 0, upper = 0;
//        for (int i = start; i <= end; ++i) {
//            if (islower(s[i])) {
//                lower |= 1 << (s[i] - 'a');
//            } else {
//                upper |= 1 << (s[i] - 'A');
//            }
//        }
//        if (lower == upper) {   //base  当前区间为一完美字串
//            if (end - start + 1 > maxLen) {
//                maxPos = start;
//                maxLen = end - start + 1;
//            }
//            return;     
//        }
//        int valid = lower & upper;    //0的位置为非法字符
//        int pos = start;
//        while (pos <= end) {
//            start = pos;
//            //分割字串
//            while (pos <= end && valid & (1 << (tolower(s[pos]) - 'a'))) {
//                ++pos;
//            }
//            dfs(s, start, pos - 1, maxPos, maxLen);
//            ++pos;
//        }
//
//        //这里也可以使用&，与之后的结果是1的位置是
//        //int valid = lower ^ upper;    
//        //int pos = start;
//        //while (pos <= end) {
//        //    start = pos;
//        //    //分割字串
//        //    while (pos <= end && !(valid & (1 << (tolower(s[pos]) - 'a')))) {  
//        //        ++pos;
//        //    }
//        //    dfs(s, start, pos - 1, maxPos, maxLen);
//        //    ++pos;
//        //}
//
//    }
//
//    string longestNiceSubstring(string s) {
//        int maxPos = 0, maxLen = 0;
//        dfs(s, 0, s.size() - 1, maxPos, maxLen);
//        return s.substr(maxPos, maxLen);
//    }
//};
//时间O（n*M) M为字符集个数，每次递归都会取消一个英文单词的大小写，递归深度最多为M/2
//空间O（M）


//方法三：滑动窗口
//class Solution {
//public:
//    string longestNiceSubstring(string s) {
//        int maxPos = 0, maxLen = 0;
//        auto check = [&](int typeNum) {     //lambda表达式
//            vector<int> lowerCnt(26);
//            vector<int> upperCnt(26);
//            int cnt = 0;
//            for (int l = 0, r = 0, total = 0; r < s.size(); ++r) {
//                int idx = tolower(s[r]) - 'a';
//                if (islower(s[r])) {
//                    ++lowerCnt[idx];
//                    if (lowerCnt[idx] == 1 && upperCnt[idx] > 0) {
//                        ++cnt;
//                    }
//                } else {
//                    ++upperCnt[idx];
//                    if (upperCnt[idx] == 1 && lowerCnt[idx] > 0) {
//                        ++cnt;
//                    }
//                }
//                total += (lowerCnt[idx] + upperCnt[idx]) == 1 ? 1 : 0;
//
//                while (total > typeNum) {
//                    idx = tolower(s[l]) - 'a';
//                    total -= (lowerCnt[idx] + upperCnt[idx]) == 1 ? 1 : 0;
//                    if (islower(s[l])) {
//                        --lowerCnt[idx];
//                        if (lowerCnt[idx] == 0 && upperCnt[idx] > 0) {
//                            --cnt;
//                        }
//                    } else {
//                        --upperCnt[idx];
//                        if (upperCnt[idx] == 0 && lowerCnt[idx] > 0) {
//                            --cnt;
//                        }
//                    }
//                    ++l;
//                }
//                if (cnt == typeNum && r - l + 1 > maxLen) {
//                    maxPos = l;
//                    maxLen = r - l + 1;
//                }
//            }
//        };
//
//        int mask = 0;
//        for (char& ch : s) {
//            mask |= 1 << (tolower(ch) - 'a');
//        }
//        int types = __builtin_popcount(mask);
//        for (int i = 1; i <= types; ++i) {
//            check(i);
//        }
//        return s.substr(maxPos, maxLen);
//    }
//};
//
//
////2000. 反转单词前缀
//
//class Solution {
//public:
//    string reversePrefix(string word, char ch) {
//        int index = 0;
//        for (int i = 0; i < word.size(); ++i) {
//            if (word[i] == ch) {
//                index = i;
//                break;
//            }
//        }
//        string ret = word;
//        int left = 0, right = index;
//        while (left < right) {
//            swap(ret[left], ret[right]);
//            ++left, --right;
//        }
//
//        return ret;
//    }
//};


//1414. 和为 K 的最少斐波那契数字数目
//1.当选取斐波那契数字数目最少时，不可能选取两个相邻的斐波那契数。
//2.一定存在一种选取斐波那契数字数目最少的方案，使得选取的每个斐波那契数字各不相同。
//3.结合1，2，必须选取不超过 k 的最大斐波那契数字，才能使得选取的斐波那契数字满足和为 k 且数目最少。
//class Solution {
//public:
//    int findMinFibonacciNumbers(int k) {
//        vector<int> f;
//        f.emplace_back(1);
//        int a = 1, b = 1;
//        while (a + b <= k) {    //找到所有不大于K的斐波那契数
//            int c = a + b;
//            f.emplace_back(c);
//            a = b;
//            b = c;
//        }
//        int ans = 0;
//        //每次贪心地选取不超过 k 的最大斐波那契数字，将 k 减去该斐波那契数字，重复该操作直到 kk 变为 00，
//        for (int i = f.size() - 1; i >= 0 && k > 0; i--) {  
//            int num = f[i];
//            if (k >= num) {
//                k -= num;
//                ans++;
//            }
//        }
//        return ans;
//    }
//};


//1. 两数之和
// 方法一：暴力枚举
//class Solution {
//public:
//    vector<int> twoSum(vector<int>& nums, int target) {
//        int n = nums.size();
//        for (int i = 0; i < n; ++i) {
//            for (int j = i + 1; j < n; ++j) {
//                if (nums[i] + nums[j] == target) {
//                    return { i,j };
//                }
//            }
//        }
//        return {};
//    }
//};

//方法二：哈希表
//class Solution {
//public:
//    vector<int> twoSum(vector<int>& nums, int target) {
//        unordered_map<int, int> hashtable;
//        for (int i = 0; i < nums.size(); ++i) {
//            auto it = hashtable.find(target - nums[i]); //先找有没有和自己配对的
//            if (it != hashtable.end()) {    //有，返回
//                return { it->second, i };
//            }
//            hashtable[nums[i]] = i; //没有，把自己和下标最为键值对插入哈希表
//        }
//        return {};
//    }
//};



//7. 整数反转
//法一：截取字串，反转字符串
//class Solution {
//public:
//    int reverse(int x) {
//        if (x == 0)
//            return 0;
//        string s = to_string(x);
//        //s=s.substr(0,s.find_last_of("123456789")+1); //从右往左找第一个非0数，截取字串
//        //或
//        s = s.substr(0, s.find_last_not_of("0") + 1);
//        if (s[0] == '-') {
//            ::reverse(s.begin()+1, s.end());
//        } else {
//            ::reverse(s.begin(), s.end());
//        }
//        int ret;
//        try {
//            ret = stoi(s);
//        }
//        catch (out_of_range) {
//            ret = 0;
//        }
//        return ret;
//    }
//};

//法二：数学
//记ret为1，类似于将x后的每一位弹出，再压入ret的尾，
//数学方法为：
//  弹出 x 的末尾数字 digit
//  digit = x % 10
//  x /= 10
//  将数字 digit 推入 rev 末尾
//  rev = rev * 10 + digit
class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            //判断是否溢出32位范围
            //如果目前已经-2^31次方要小，之后还要*10，必然溢出，正数同理
            if (rev < INT_MIN / 10 || rev > INT_MAX / 10) { 
                return 0;
            }
            int digit = x % 10;
            x /= 10;
            rev = rev * 10 + digit;
        }
        return rev;
    }
};

