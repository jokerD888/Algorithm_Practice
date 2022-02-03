//1763. ����������ַ���
//��һ:����ö��
//class Solution {
//public:
//    string longestNiceSubstring(string s) {
//        int maxPos = 0, maxLen = 0;
//        int len = s.size();
//        for (int i = 1; i <= len; ++i) {    //�����ִ�����
//            for (int j = 0; j <= len-i; ++j) {   //��ʼλ��
//                int lower = 0;  //Сд��ĸ���
//                int upper = 0;  //��д��ĸ���
//                for (int k = j; k < j+i && k<len; ++k) {
//                    if (islower(s[k])) {
//                        lower |= 1 << (s[k] - 'a');
//                    } else {
//                        upper |= 1 << (s[k] - 'A');
//                    }
//                    
//                }
//                if (lower == upper && i > maxLen) { //���и����ģ�����
//                    maxPos = j;
//                    maxLen = i;
//                }
//            }
//        }
//        return s.substr(maxPos, maxLen);
//    }
//};
//ʱ��O��n^3)



//��ֻ��26��Ӣ����ĸ�����ö�����λ�����
//class Solution {
//public:
//    string longestNiceSubstring(string s) {
//        int n = s.size();
//        int maxPos = 0;     //��������ִ����ֵ�λ��  
//        int maxLen = 0;     //������ִ�����
//        for (int i = 0; i < n; ++i) {
//            int lower = 0;  //Сд��ĸ���
//            int upper = 0;  //��д��ĸ���
//            for (int j = i; j < n; ++j) {
//                if (islower(s[j])) {
//                    lower |= 1 << (s[j] - 'a');
//                } else {
//                    upper |= 1 << (s[j] - 'A');
//                }
//                if (lower == upper && j - i + 1 > maxLen) { //���и����ģ�����
//                    maxPos = i;
//                    maxLen = j - i + 1;
//                }
//            }
//        }
//        return s.substr(maxPos, maxLen);
//    }
//};
//ʱ��O��N^2��
//�ռ�O��1��


//������������
//���÷Ƿ��ַ���������һ����ʽ����ĸ����Ϊ�ָ�������ٸ����������ָֱ������Ϊ�����ִ�
//class Solution {
//public:
//    void dfs(const string& s, int start, int end, int& maxPos, int& maxLen) {
//        if (start >= end) {     //base  Խ��
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
//        if (lower == upper) {   //base  ��ǰ����Ϊһ�����ִ�
//            if (end - start + 1 > maxLen) {
//                maxPos = start;
//                maxLen = end - start + 1;
//            }
//            return;     
//        }
//        int valid = lower & upper;    //0��λ��Ϊ�Ƿ��ַ�
//        int pos = start;
//        while (pos <= end) {
//            start = pos;
//            //�ָ��ִ�
//            while (pos <= end && valid & (1 << (tolower(s[pos]) - 'a'))) {
//                ++pos;
//            }
//            dfs(s, start, pos - 1, maxPos, maxLen);
//            ++pos;
//        }
//
//        //����Ҳ����ʹ��&����֮��Ľ����1��λ����
//        //int valid = lower ^ upper;    
//        //int pos = start;
//        //while (pos <= end) {
//        //    start = pos;
//        //    //�ָ��ִ�
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
//ʱ��O��n*M) MΪ�ַ���������ÿ�εݹ鶼��ȡ��һ��Ӣ�ĵ��ʵĴ�Сд���ݹ�������ΪM/2
//�ռ�O��M��


//����������������
//class Solution {
//public:
//    string longestNiceSubstring(string s) {
//        int maxPos = 0, maxLen = 0;
//        auto check = [&](int typeNum) {     //lambda���ʽ
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
////2000. ��ת����ǰ׺
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


//1414. ��Ϊ K ������쳲�����������Ŀ
//1.��ѡȡ쳲�����������Ŀ����ʱ��������ѡȡ�������ڵ�쳲���������
//2.һ������һ��ѡȡ쳲�����������Ŀ���ٵķ�����ʹ��ѡȡ��ÿ��쳲��������ָ�����ͬ��
//3.���1��2������ѡȡ������ k �����쳲��������֣�����ʹ��ѡȡ��쳲��������������Ϊ k ����Ŀ���١�
//class Solution {
//public:
//    int findMinFibonacciNumbers(int k) {
//        vector<int> f;
//        f.emplace_back(1);
//        int a = 1, b = 1;
//        while (a + b <= k) {    //�ҵ����в�����K��쳲�������
//            int c = a + b;
//            f.emplace_back(c);
//            a = b;
//            b = c;
//        }
//        int ans = 0;
//        //ÿ��̰�ĵ�ѡȡ������ k �����쳲��������֣��� k ��ȥ��쳲��������֣��ظ��ò���ֱ�� kk ��Ϊ 00��
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


//1. ����֮��
// ����һ������ö��
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

//����������ϣ��
//class Solution {
//public:
//    vector<int> twoSum(vector<int>& nums, int target) {
//        unordered_map<int, int> hashtable;
//        for (int i = 0; i < nums.size(); ++i) {
//            auto it = hashtable.find(target - nums[i]); //������û�к��Լ���Ե�
//            if (it != hashtable.end()) {    //�У�����
//                return { it->second, i };
//            }
//            hashtable[nums[i]] = i; //û�У����Լ����±���Ϊ��ֵ�Բ����ϣ��
//        }
//        return {};
//    }
//};



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
class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            //�ж��Ƿ����32λ��Χ
            //���Ŀǰ�Ѿ�-2^31�η�ҪС��֮��Ҫ*10����Ȼ���������ͬ��
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

