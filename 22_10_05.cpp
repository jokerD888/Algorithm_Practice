// 921. 使括号有效的最少添加
// 从左往右遍历，遇到'(',sum++,遇到')'，sum--
// 当sum<0说明，当前右括号多于左括号，需要添加一左括号（++t)
// 最后返回t+sum (最后的，t可以代表，需要添加左括号的数量，sum可以代表添加右括号的数量）
class Solution {
public:
    int minAddToMakeValid(string s) {
        int N = s.size(), sum = 0, t = 0;
        for (int i = 0; i < N; ++i) {
            if (s[i] == '(') ++sum;
            else --sum;
            if (sum < 0) {
                ++t;
                sum = 0;
            }
        }
        return t + sum;
    }
};


// 149. 直线上最多的点数

// 枚举每个点作为直线必经过的点，后以此点与其他点进行斜率判断，使用哈希表统计斜率上的个数
// 由于浮点数精度的缺失，我们使用最简分数的形式来表示斜率
class Solution {
public:
    int gcd(int a, int b) {     
        return b ? gcd(b, a % b) : a;
    }

    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) {
            return n;
        }
        int ret = 0;
        for (int i = 0; i < n; i++) {
            if (ret >= n - i || ret > n / 2) {      // 优化，当
                break;
            }
            unordered_map<int, int> mp;
            for (int j = i + 1; j < n; j++) {
                int x = points[i][0] - points[j][0];    
                int y = points[i][1] - points[j][1];
                if (x == 0) {       // 斜率为0，水平横线
                    y = 1;
                } else if (y == 0) {        // 斜率不存在，垂直竖线
                    x = 1;
                } else {                    // 若斜率是负数，我们规定分子为负数
                    if (y < 0) {
                        x = -x;
                        y = -y;
                    }
                    int gcdXY = gcd(abs(x), abs(y));
                    x /= gcdXY, y /= gcdXY;
                }
                // 由于x和y的范围都是1e4内，所以我们可以用一个整数来表示斜率
                // 把x乘上20001加上y即可表示
                mp[y + x * 20001]++;        
            }
            int maxn = 0;
            for (auto& [_, num] : mp) {
                maxn = max(maxn, num + 1);
            }
            ret = max(ret, maxn);
        }
        return ret;
    }
};
