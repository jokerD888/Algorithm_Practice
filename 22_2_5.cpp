
//7. ������ת
//��һ����ȡ�ִ�����ת�ַ���
//class Solution {
//public:
//    int reverse(int x) {
//        if (x == 0)
//            return 0;
//        string s = to_string(x);
//        //s=s.substr(0,s.find_last_of("123456789")+1); //���������ҵ�һ����0������ȡ�ִ�
//        //��
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

//��������ѧ
//��retΪ1�������ڽ�x���ÿһλ��������ѹ��ret��β��
//��ѧ����Ϊ��
//  ���� x ��ĩβ���� digit
//  digit = x % 10
//  x /= 10
//  ������ digit ���� rev ĩβ
//  rev = rev * 10 + digit
//class Solution {
//public:
//    int reverse(int x) {
//        int rev = 0;
//        while (x != 0) {
//            //�ж��Ƿ����32λ��Χ
//            //���Ŀǰ�Ѿ�-2^31�η�ҪС��֮��Ҫ*10����Ȼ���������ͬ��
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


////1725. �����γ���������εľ�����Ŀ
////��һ��ɸѡ������������С�ıߣ���������м�����ͬ�ļ�Ϊ����
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
////������һ�α���
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




//6. Z ���α任
//��һ��ģ��
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


//����
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


//���������з��ʣ�����
//��һ��: k(2*(numRows-1))+0λ�õ��ַ�   k=0,1,2,3..
//���һ�У�k(2*(numRows-1))+numRows-1λ��     k=0,1,2,3...
//�м���λ�ã�k(2*(numRows-1))+i ����k+1)*(2*(numRows-1))-iλ��   k=0,1,2,3....
class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1) return s;

        string ret;
        int n = s.size();
        int cycleLen = 2 * numRows - 2;

        for (int i = 0; i < numRows; i++) {     //����
            for (int j = 0; j + i < n; j += cycleLen) {     //�൱�ڽ����е�k����
                ret += s[j + i];    //����β��
                if (i != 0 && i != numRows - 1 && j + cycleLen - i < n) //�м���
                    ret += s[j + cycleLen - i];
            }
        }

        return ret;
    }
};



//9. ������
//��һ��תΪ�ַ�������β�Ƚ�
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

//��������ת����
class Solution {
public:
    bool isPalindrome(int x) {
        // ���������
        // ������������ x < 0 ʱ��x ���ǻ�������
        // ͬ���أ�������ֵ����һλ�� 0��Ϊ��ʹ������Ϊ���ģ�
        // �����һλ����ҲӦ���� 0
        // ֻ�� 0 ������һ����
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        
        //��תһ�����֣���֮�������ֱ�ӷ�תҲ���ԣ���׽���
        int revertedNumber = 0;
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }

        // �����ֳ���Ϊ����ʱ�����ǿ���ͨ�� revertedNumber/10 ȥ��������λ�����֡�
        // ���磬������Ϊ 12321 ʱ���� while ѭ����ĩβ���ǿ��Եõ� x = 12��revertedNumber = 123��
        // ���ڴ�����λ�����ֲ�Ӱ����ģ����������Լ���ȣ����������ǿ��Լ򵥵ؽ���ȥ����
        return x == revertedNumber || x == revertedNumber / 10;
    }
};

