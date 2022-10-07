// 171. Excel 表列序号
// 26进制数
class Solution {
public:
    int titleToNumber(string columnTitle) {
        long long res = 0;
        int N = columnTitle.size();
        for (int i = 0; i < N; ++i) {
            res = res * 26 + columnTitle[i] - 'A' + 1;
        }
        return res;
    }
};

// 166. 分数到小数
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        string res;
        res += ((numerator < 0) ^ (denominator < 0)) ? "-" : "";
        long long num = abs(numerator);
        long long den = abs(denominator);
        res += to_string(num / den);
        num %= den;
        if (num == 0) return res;
        res += '.';
        unordered_map<long long, int> map;  // 记录分子k出现的位置v
        map[num] = res.size();
        while (num) {
            num *= 10;
            res += to_string(num / den);
            num %= den;
            if (map.count(num)) {       // 出现过之前出现过的分子，循环节开始了
                int index = map[num];   // 找到之前出现过的位置，并插入（
                res.insert(index, "(");
                res += ")";
                break;
            }
            map[num] = res.size();
        }
        return res;

    }
};




// 172. 阶乘后的零

// 数学
// n!尾零的数量即为 n! 中因子 10 的个数，而 10=2×5，因此转换成求 n! 中质因子 2 的个数和质因子 5 的个数的较小值。
// 由于质因子5的个数不会大于质因子2的个数，我们可以仅考虑质因子5的个数。因为若把每个数都拆分为质因子，2的数量一定大于等于5
// 而n!中质因子5的个数等于[1, n]的每个数的质因子5的个数之和，我们可以通过遍历[1, n]的所有5的倍数求出。

class Solution {
public:
    int trailingZeroes(int n) {
        int ans = 0;
        for (int i = 5; i <= n; i += 5) {
            for (int x = i; x % 5 == 0; x /= 5) {
                ++ans;
            }
        }
        return ans;
    }
};

// 优化计算
// 我们可以发现每5个至少有一个因子5，每25个一定至少再有一个5，每125个至少再有一个5
// 所以我么们可以计算每个步长因子5的个数，累计即可
class Solution {
public:
    int trailingZeroes(int n) {
        int ans = 0;
        while (n) {
            n /= 5;
            ans += n;
        }
        return ans;
    }
};
