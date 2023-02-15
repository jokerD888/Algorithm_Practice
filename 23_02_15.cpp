
// 1250. 检查「好数组」
// 观察，可以发现，当数组所有的数的最大公约数不为1时即是好数组
// 裴蜀定理：若a,b是整数,且gcd(a,b)=d，那么对于任意的整数x,y,ax+by都一定是d的倍数，特别地，一定存在整数x,y，使ax+by=d成立。
//      它的一个重要推论是：a,b互质的充分必要条件是存在整数x,y使ax+by=1.
class Solution {
public:
    int gcd(int a, int b) {
        return a % b ? gcd(b, a % b) : b;
    }
  
    bool isGoodArray(vector<int>& nums) {
        int n = nums.size();
        int x = nums[0];
        
        for (int i = 1; i < n; ++i) {
            x = gcd(x, nums[i]);
        }
        return x == 1;
    }
};


// 1234. 替换子串得到平衡字符串

// 我们假设选择一个字串ss做为[待替换字串]，只有当s剩余部分的QWER出现的次数都小于n/4时，才有可能使s变为[平衡字符串]
// 从小到大枚举[待替换字串]的左端点，为使得替换长度最小，则需要找到最近的右端点r,使得去除[l，r)之后的剩余部分满足上述条件
//      不难发现，随着l的增加，r只增不减，所以使用滑动窗口来维护区间[l,r)之外的剩余部分中QWER的出现次数，
//      当其中一个字符出现次数大于n/4时，令s[r]出现的次数-1，且使r++右移一个单位，该操作一直被执行，知道满足条件或结尾
// 如果找到了使得条件被满足的r，我们使用r-l来更新答案，然后令s[l]的出现次数加1，并使得l向右移动一个单位进行下一次枚举。
// 否则，后序的l也不会有合法的r,因为l向右移动时，字母的个数只会增加，此时我们可以直接跳出循环。

class Solution {
public:
    int idx(const char& c) {
        return c - 'A';
    }
    int balancedString(string s) {
        int n = s.size();
        vector<int> cnt(26);
        for (auto c : s) {
            ++cnt[idx(c)];
        }

        int partial = n / 4;
        int res = n;
        auto check = [&]() {
            if (cnt[idx('Q')] > partial || cnt[idx('W')] > partial
                || cnt[idx('E')] > partial || cnt[idx('R')] > partial) {
                return false;
            }
            return true;
        };

        if (check()) return 0;

        for (int l = 0, r = 0; l < n; ++l) {
            while (r < n && !check()) {
                --cnt[idx(s[r])];
                ++r;
            }
            if(!check()) break;
            res = min(res, r - l);
            ++cnt[idx(s[l])];
        }
        return res;
    }
};