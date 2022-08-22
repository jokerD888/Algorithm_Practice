// 14. 最长公共前缀

// 纵向扫描
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 1) return strs[0];
        string res;
        int len = 0;
        while (true) {
            for (int i = 1; i < strs.size(); ++i) {
                if (strs[i].size() <= len || strs[i][len] != strs[i - 1][len]) {
                    return res;
                }
            }
            res += strs[0][len++];
        }

        return res;
    }
};


// 32. 最长有效括号
// 从左往右遍历，若当前元素和栈顶元素可以匹配，栈顶弹出，此时最大长度为，当前下标减去栈顶元素下标
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        int res = 0;
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i];

            if (c == ')' && st.size() && s[st.top()] == '(')st.pop();
            else st.push(i);

            if (st.size()) res = max(res, i - st.top());
            else res = max(res, i + 1);
        }
        return res;
    }
};

// 两次遍历
// 从左往右遍历，遇到'(',l++,遇到')',r++,当l==r,结算长度，当r>l是，l和r都清零
// 不过若‘(’数量始终大于‘)’数量，就会导致无法结算，这时候再从右往左遍历一边即可
class Solution {
public:
    int process(string& s, char c) {
        int l = 0, r = 0, res = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == c) ++l;
            else {
                ++r;
                if (l == r) res = max(res, l);
                else if (r > l) l = 0, r = 0;
            }
        }
        return res;
    }
    int longestValidParentheses(string s) {
        int res = process(s, '(');
        reverse(s.begin(), s.end());
        res = max(res, process(s, ')'));
        return res * 2;
    }
};


// 16. 最接近的三数之和
// 枚举第一和第二个数+二分第三个数
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int res = 1e9;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                int t = target - nums[i] - nums[j];
                int l = 0, r = nums.size() - 1;
                while (l < r) {         // 二分大于等于target的数
                    int mid = l + r >> 1;
                    if (nums[mid] >= t)
                        r = mid;
                    else
                        l = mid + 1;
                }
                int left = l - 1, right = l;
                if (right == i) right++;
                if (right == j)right++;
                if (left == j)left--;
                if (left == i) left--;

                if (left >= 0) {
                    if (t - nums[left] < abs(target - res))
                        res = nums[i] + nums[j] + nums[left];
                }
                if (right < nums.size()) {
                    if (nums[right] - t < abs(target - res))
                        res = nums[i] + nums[j] + nums[right];
                }
            }
        }
        return res;
    }
};

// 排序+双指针
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());


        int res = 1e9, n = nums.size();
        auto check = [&](int cur) {
            if (abs(target - cur) < abs(target - res))
                res = cur;
        };

        for (int i = 0; i < n; ++i) {
            int a = nums[i];
            int l = i + 1, r = n - 1;

            while (l < r) {
                if (a + nums[l] + nums[r] < target) {
                    check(a + nums[l] + nums[r]);
                    ++l;
                } else {
                    check(a + nums[l] + nums[r]);
                    --r;
                }
            }
        }

        return res;
    }
};
// 优化，对于相同的元素可以跳过
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());


        int res = 1e9, n = nums.size();
        auto check = [&](int cur) {
            if (abs(target - cur) < abs(target - res))
                res = cur;
        };

        for (int i = 0; i < n; ++i) {
            if (i && nums[i] == nums[i - 1]) continue;    // 优化一，避免枚举相同元素

            int a = nums[i];
            int l = i + 1, r = n - 1;

            while (l < r) {
                int sum = a + nums[l] + nums[r];
                check(sum);
                if (sum < target) {
                    ++l;
                    while (l < r && nums[l] == nums[l - 1]) ++l;  // 优化三：在左右指针合法的情况下，跳过相同元素
                } else if (sum > target) {
                    --r;
                    while (l < r && nums[r] == nums[r + 1])--r;
                } else {
                    return target;              // 优化二:和target相同，直接return
                }
            }
        }

        return res;
    }
};

