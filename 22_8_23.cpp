// 18. 四数之和
// 暴力枚举前3个数+二分第四个数
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            if (i && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n; ++j) {
                if (j != i + 1 && nums[j] == nums[j - 1]) continue;;
                for (int k = j + 1; k < n; ++k) {
                    if (k != j + 1 && nums[k] == nums[k - 1]) continue;

                    long long sum = 0LL + nums[i] + nums[j] + nums[k];
                    if (binary_search(nums.begin() + k + 1, nums.end(), target - sum)) {
                        res.push_back({ nums[i],nums[j],nums[k],target - (int)sum });
                    }
                }
            }
        }
        return res;
    }
};

// 排序+双指针
// 枚举前两个数，再双指针左右向中间靠拢
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i < n; ++i) {
            if (i && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n; ++j) {
                if (j != i + 1 && nums[j] == nums[j - 1]) continue;

                long long t = 0LL + target - nums[i] - nums[j];
                int l = j + 1, r = n - 1;
                while (l < r) {
                    long long sum = 0LL + nums[l] + nums[r];
                    if (sum == t) {
                        res.push_back({ nums[i],nums[j],nums[l],nums[r] });
                        ++l;
                        while (l < r && nums[l] == nums[l - 1])++l;
                    } else if (sum < t) {
                        ++l;
                        while (l < r && nums[l] == nums[l - 1])++l;
                    } else {
                        --r;
                        while (l < r && nums[r] == nums[r + 1])--r;
                    }
                }
            }
        }
        return res;
    }
};



// 29. 两数相除

// 快速幂原理
class Solution {
public:
    int divide(int dividend, int divisor) {
        int a[33], n;
        int res = 0;
        if (dividend == INT_MIN) {
            if (divisor == 1) return dividend;
            else if (divisor == -1)return  INT_MAX;
            else if (divisor == INT_MIN) return 1;
            else {
                dividend += abs(divisor);
                res++;
            }
        }
        if (divisor == INT_MIN) return 0;
        bool neg = (dividend < 0) ^ (divisor < 0);
        dividend = abs(dividend);
        divisor = abs(divisor);

        a[1] = divisor;
        for (n = 2; n < 33; ++n) {
            if (a[n - 1] > INT_MAX / 2) break;

            a[n] = a[n - 1] * 2;
        }

        for (int i = n - 1; i > 0; --i) {
            if (dividend >= a[i]) {
                res += pow(2, i - 1);
                dividend -= a[i];
            }
            if (dividend == 0) break;
        }

        return neg ? -res : res;
    }
};


// 30. 串联所有单词的子串
// 滑动窗口+哈希
// 我们枚举字符串的起始位置，设字符串长度为n，共需要枚举n次
// 起点固定后，我们就开始将窗口内的m个长度为n的字符串插入哈希表，再减去words中的字符串
//      若哈希表为空，说明窗口内的字符串恰好是由words中拼接出来的，记录答案，随后滑动窗口，以长度n为单位进行滑动，依次下去
class Solution {
public:
    vector<int> findSubstring(string& s, vector<string>& words) {
        vector<int> res;
        int m = words.size(), n = words[0].size(), ls = s.size();
        for (int i = 0; i < n && i + m * n <= ls; ++i) {
            unordered_map<string, int> differ;
            for (int j = 0; j < m; ++j) {       // 将窗口内的等长字符串哈希
                ++differ[s.substr(i + j * n, n)];
            }
            for (string& word : words) {        // 减去words中出现的字符串
                if (--differ[word] == 0) {
                    differ.erase(word);
                }
            }
            for (int start = i; start < ls - m * n + 1; start += n) {
                if (start != i) {   // 滑动
                    string word = s.substr(start + (m - 1) * n, n);
                    if (++differ[word] == 0) {
                        differ.erase(word);
                    }
                    word = s.substr(start - n, n);
                    if (--differ[word] == 0) {
                        differ.erase(word);
                    }
                }
                if (differ.empty()) {   // 为空，恰好窗口内的字符串是由words中拼接出来的
                    res.emplace_back(start);
                }
            }
        }
        return res;
    }
};
