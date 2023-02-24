// 56. 合并区间

// 排序
class Solution {
public:
    typedef pair<int, int> PII;
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<PII> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = { intervals[i][0],intervals[i][1] };
        }
        sort(arr.begin(), arr.end());
        vector<vector<int>> res;
        int left = arr[0].first, right = arr[0].second;
        for (auto& [begin, end] : arr) {
            if (begin > right) {
                res.push_back({ left, right });
                left = begin;
                right = max(right, end);
            } else {
                right = max(right, end);        // right要取最大值
            }
        }
        res.push_back({ left,right });

        return res;
    }
};


// 27. 移除元素
// 排序，找到val第一次出现的位置，从数组后面开始替换
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int pos = 0, tail = n;
        while (pos < n && nums[pos] != val) ++pos;
        while (pos < n && nums[pos] == val) {
            nums[pos++] = nums[--tail];
        }
        return tail;
    }
};

// 双指针

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int left = 0;
        for (int right = 0; right < n; right++) {
            if (nums[right] != val) {
                nums[left] = nums[right];
                left++;
            }
        }
        return left;
    }
};
// 优化上法，最多只遍历一遍
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size();
        while (left < right) {
            if (nums[left] == val) {        // left位置位置，把right位置的换过来
                nums[left] = nums[right - 1];
                right--;
            } else {
                left++;
            }
        }
        return left;
    }
};


// 179. 最大数

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        auto f = [](const int a, const int b) {
            string str_a = to_string(a);
            string str_b = to_string(b);
            //return str_a + str_b > str_b + str_a; 要转为数字来比较，因为有数字0
            return stoll(str_a + str_b) > stoll(str_b + str_a);

        };
        sort(nums.begin(), nums.end(), f);
        if (nums[0] == 0) return "0";

        string res;
        for (auto num : nums) {
            res += to_string(num);
        }
        return res;
    }
};