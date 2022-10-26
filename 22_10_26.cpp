// 412. Fizz Buzz

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> res(n);
        string tmp;
        for (int i = 1; i <= n; ++i) {
            if (i % 3 == 0 && i % 5 == 0) {
                tmp = "FizzBuzz";
            } else if (i % 3 == 0) {
                tmp = "Fizz";
            } else if (i % 5 == 0) {
                tmp = "Buzz";
            } else {
                tmp = to_string(i);
            }
            res[i - 1] = tmp;
        }
        return res;
    }
};



// 454. 四数相加 II
// 哈希表
// O(N^2)
// 先将前两个数组所有相加值放入哈希表，再枚举后两个数组的和，在哈希表内查找
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> mp;
        int N = nums1.size();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                ++mp[nums1[i] + nums2[j]];
        int res = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                res += mp[-(nums3[i] + nums4[j])];

        return res;
    }
};


