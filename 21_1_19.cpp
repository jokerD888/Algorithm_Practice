//每日一题 539. 最小时间差//排序----------------------------------------------------------------------
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minute;
        transform(timePoints.begin(), timePoints.end(), back_inserter(minute), [](const string& a)
                                                  {return stoi(a) * 60 + stoi(a.substr(3)); });
        sort(minute.begin(), minute.end());
        int minTime = INT_MAX;
        for (int i = 1; i < minute.size(); ++i) {
            minTime = minTime < minute[i] - minute[i - 1] ? minTime : minute[i] - minute[i - 1];
        }
        int lastTime = 24 * 60;
        lastTime = lastTime - minute.back() + minute.front();
        return minTime < lastTime? minTime : lastTime;
    }
};
//精简版
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minute;
        transform(timePoints.begin(), timePoints.end(), back_inserter(minute), [](const string& a)
            {return stoi(a) * 60 + stoi(a.substr(3)); });
        sort(minute.begin(), minute.end());
        int minTime = INT_MAX;
        for (int i = 1; i < minute.size(); ++i) 
            minTime = min(minTime, minute[i] - minute[i - 1]);
        return min(minTime, 1440 - minute.back() + minute.front());
    }
};
//官解
class Solution {
    int getMinutes(string& t) {
        return (int(t[0] - '0') * 10 + int(t[1] - '0')) * 60 + int(t[3] - '0') * 10 + int(t[4] - '0');
    }

public:
    int findMinDifference(vector<string>& timePoints) {
        sort(timePoints.begin(), timePoints.end());
        int ans = INT_MAX;
        int t0Minutes = getMinutes(timePoints[0]);
        int preMinutes = t0Minutes;
        for (int i = 1; i < timePoints.size(); ++i) {
            int minutes = getMinutes(timePoints[i]);
            ans = min(ans, minutes - preMinutes); // 相邻时间的时间差
            preMinutes = minutes;
        }
        ans = min(ans, t0Minutes + 1440 - preMinutes); // 首尾时间的时间差
        return ans;
    }
};


//鸽巢原理----------------------------------------------------
//加了个判断，因为一天最多右24*60=1440，若数组大小超出1440，说明必定有重复时间
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        if (timePoints.size() > 1440)
            return 0;
        vector<int> minute;
        transform(timePoints.begin(), timePoints.end(), back_inserter(minute), [](const string& a)
            {return stoi(a) * 60 + stoi(a.substr(3)); });
        sort(minute.begin(), minute.end());
        int minTime = INT_MAX;
        for (int i = 1; i < minute.size(); ++i)
            minTime = min(minTime, minute[i] - minute[i - 1]);
        return min(minTime, 1440 - minute.back() + minute.front());
    }
};


//219. 存在重复元素 II
//哈希表
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, vector<int>> ans;
        
        for (int i = 0; i < nums.size(); ++i) {
            ans[nums[i]].push_back(i);
        }
        for (auto kv : ans) {            
            if (kv.second.size() > 1) {
                for (int i = 1; i < kv.second.size(); ++i) {
                    if (kv.second[i] - kv.second[i - 1] <= k)
                        return true;
                }
            }
        }
        return false;
    }
};

//上法效率太低，改进后，与官解相同
//时间O（N）
//空间O（N）
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> ans;

        for (int i = 0; i < nums.size(); ++i) {
            auto it = ans.find(nums[i]);
            if (it != ans.end() && i - it->second <= k) {
                return true;
            }
            ans[nums[i]] = i;
        }

        return false;
    }
};


//滑动窗口
//时间O（N）
//空间O（K）
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> s;
        int length = nums.size();
        for (int i = 0; i < length; i++) {
            if (i > k) {    //保持滑动窗口的长度，去除窗口第一个元素
                s.erase(nums[i - k - 1]);
            }
            if (s.count(nums[i])) {
                return true;
            }
            s.emplace(nums[i]);
        }
        return false;
    }
};
