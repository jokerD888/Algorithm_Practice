
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
//class Solution {
//public:
//    int reverse(int x) {
//        int rev = 0;
//        while (x != 0) {
//            //判断是否溢出32位范围
//            //如果目前已经-2^31次方要小，之后还要*10，必然溢出，正数同理
//            if (rev < INT_MIN / 10 || rev > INT_MAX / 10) { 
//                return 0;
//            }
//            int digit = x % 10;
//            x /= 10;
//            rev = rev * 10 + digit;
//        }
//        return rev;
//    }
//};

 

//int main()
//{
//    Solution s;
//    cout << s.reverse(-1230);
//}
//


////1725. 可以形成最大正方形的矩形数目
////法一：筛选出各个矩形最小的边，排序，最后有几个相同的即为所求
//class Solution {
//public:
//    int countGoodRectangles(vector<vector<int>>& rectangles) {
//        vector<int> lens;
//        for (auto& rec : rectangles) {
//            lens.push_back(min(rec[0], rec[1]));
//        }
//        sort(lens.begin(), lens.end());
//
//        int ret = 1;
//        for (int i = lens.size() - 2; i >= 0; --i) {
//            if (lens[i] == lens[i + 1]) {
//                ++ret;
//            } else {
//                break;
//            }
//        }
//        return ret;
//    }
//};
//
////法二：一次遍历
//class Solution {
//public:
//    int countGoodRectangles(vector<vector<int>>& rectangles) {
//        int ret = 0;
//        int maxlen = 0;
//        for (auto& rec : rectangles) {
//            int len = min(rec[0], rec[1]);
//            if (len = maxlen) {
//                ++ret;
//            } else {
//                ret = 1;
//                maxlen = len;
//            }
//        }
//        return ret;
//    }
//};




//6. Z 字形变换
//法一：模拟
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1)
            return s;
        vector<string> ret(numRows);
        int i = 0;
        bool path = false;
        for (auto c : s) {

            ret[i].push_back(c);

            if (i == 0 || i == numRows - 1) {
                path = !path;
            }


            if (path) {
                ++i;
            } else {
                --i;
            }

  
        }

        string ans;
        for (auto& s : ret) {
            ans += s;
        }
        return ans;
    }
};


//类似
class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1) return s;

        vector<string> rows(min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        string ret;
        for (string row : rows) ret += row;
        return ret;
    }
};


//法二：按行访问，规律
//第一行: k(2*(numRows-1))+0位置的字符   k=0,1,2,3..
//最后一行：k(2*(numRows-1))+numRows-1位置     k=0,1,2,3...
//中间行位置：k(2*(numRows-1))+i 及（k+1)*(2*(numRows-1))-i位置   k=0,1,2,3....
class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1) return s;

        string ret;
        int n = s.size();
        int cycleLen = 2 * numRows - 2;

        for (int i = 0; i < numRows; i++) {     //按行
            for (int j = 0; j + i < n; j += cycleLen) {     //相当于解释中的k递增
                ret += s[j + i];    //首行尾行
                if (i != 0 && i != numRows - 1 && j + cycleLen - i < n) //中间行
                    ret += s[j + cycleLen - i];
            }
        }

        return ret;
    }
};



//9. 回文数
//法一：转为字符串，首尾比较
class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        int left = 0;
        int right = s.size() - 1;
        while (left < right) {
            if (s[left++] != s[right--])
                return false;
        }
        return true;
    }
};

//法二：翻转数字
class Solution {
public:
    bool isPalindrome(int x) {
        // 特殊情况：
        // 如上所述，当 x < 0 时，x 不是回文数。
        // 同样地，如果数字的最后一位是 0，为了使该数字为回文，
        // 则其第一位数字也应该是 0
        // 只有 0 满足这一属性
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        
        //翻转一半数字，反之溢出，或直接翻转也可以，捕捉溢出
        int revertedNumber = 0;
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }

        // 当数字长度为奇数时，我们可以通过 revertedNumber/10 去除处于中位的数字。
        // 例如，当输入为 12321 时，在 while 循环的末尾我们可以得到 x = 12，revertedNumber = 123，
        // 由于处于中位的数字不影响回文（它总是与自己相等），所以我们可以简单地将其去除。
        return x == revertedNumber || x == revertedNumber / 10;
    }
};

