// 179. 最大数

// 自定义排序规则
// 对于任意两个数字a,b，我们一前一后进行拼接，形成两个数字ab,ba，随后我们比较ab,ba这两个数字，据此进行排序
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](const int& x, const int& y) {
            string sx = to_string(x);
            string sy = to_string(y);
            return stoi(sx + sy) > stoi(sy + sx);
            });
        if (nums[0] == 0) {
            return "0";
        }
        string ret;
        for (int& x : nums) {
            ret += to_string(x);
        }
        return ret;
    }
};

// 或，直接算，更快些
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](const int& x, const int& y) {
            long sx = 10, sy = 10;
            while (sx <= x) {
                sx *= 10;
            }
            while (sy <= y) {
                sy *= 10;
            }
            return sy * x + y > sx * y + x;
            });
        if (nums[0] == 0) {
            return "0";
        }
        string ret;
        for (int& x : nums) {
            ret += to_string(x);
        }
        return ret;
    }
};


// 870. 优势洗牌
// 使用索引排序，对两数组进行升序排序
// 从左往右遍历，1) 若num1[i]>nums2[i],建立优势，进行匹配，因为两数组都是升序，所以可以用尽可能小的num1去大于num2
//              2) 若num1[i]<=num[i],无法建立优势，与nums中最大的进行匹配，因为num1[i]连对方最小的都搞定不了，不如牺牲自己去匹配对方最大的
class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> idx1(n), idx2(n);
        iota(idx1.begin(), idx1.end(), 0);
        iota(idx2.begin(), idx2.end(), 0);
        sort(idx1.begin(), idx1.end(), [&](int i, int j) { return nums1[i] < nums1[j]; });
        sort(idx2.begin(), idx2.end(), [&](int i, int j) { return nums2[i] < nums2[j]; });

        vector<int> ans(n);
        int left = 0, right = n - 1;
        for (int i = 0; i < n; ++i) {
            if (nums1[idx1[i]] > nums2[idx2[left]]) {
                ans[idx2[left]] = nums1[idx1[i]];
                ++left;
            } else {
                ans[idx2[right]] = nums1[idx1[i]];
                --right;
            }
        }
        return ans;
    }
};
