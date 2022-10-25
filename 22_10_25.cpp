// 347. 前 K 个高频元素

// 优先队列
// 先用哈希表统计各个元素的频率，再使用优先队列维持K个大小空间
class Solution {
public:
    static bool cmp(pair<int, int>& m, pair<int, int>& n) {
        return m.second > n.second;
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto& v : nums) {
            occurrences[v]++;
        }

        // pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
        for (auto& [num, count] : occurrences) {
            if (q.size() == k) {
                if (q.top().second < count) {
                    q.pop();
                    q.emplace(num, count);
                }
            } else {
                q.emplace(num, count);
            }
        }
        vector<int> ret;
        while (!q.empty()) {
            ret.emplace_back(q.top().first);
            q.pop();
        }
        return ret;
    }
};


// 快排思想
class Solution {
public:
    void qsort(vector<pair<int, int>>& v, int start, int end, vector<int>& ret, int k) {
        int picked = rand() % (end - start + 1) + start;
        swap(v[picked], v[start]);

        int pivot = v[start].second;
        int index = start;
        for (int i = start + 1; i <= end; i++) {
            if (v[i].second >= pivot) {     // 大的在前面
                swap(v[++index], v[i]);
            }
        }
        swap(v[start], v[index]);

        if (k <= index - start) {
            qsort(v, start, index - 1, ret, k);
        } else {
            for (int i = start; i <= index; i++) {
                ret.push_back(v[i].first);
            }
            if (k > index - start + 1) {
                qsort(v, index + 1, end, ret, k - (index - start + 1));
            }
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto& v : nums) {
            occurrences[v]++;
        }

        vector<pair<int, int>> values;
        for (auto& kv : occurrences) {
            values.push_back(kv);
        }
        vector<int> ret;
        qsort(values, 0, values.size() - 1, ret, k);
        return ret;
    }
};


// 395. 至少有 K 个重复字符的最长子串
// 分治
// 时间O(N*M) N是长度，M是字符集
// 我们先对于给定的字符粗统计出现的次数，以个数小于k的位置作为分割点，进行分治
// 因为给字符在整个字符串中出现的个数都为<K，所以只要字符串中出现该字符串都不能满足要求
// 所以问题可以根据分割点进行分治
class Solution {
public:

    int divide(const string& s, int start, int end, int k) {
        if (start >= s.size()) return 0;
        int freq[26]{ 0 };
        for (int i = start; i <= end; ++i) ++freq[s[i] - 'a'];
        int l = start, r = start;
        int res = 0;
        while (l <= end) {
            while (l <= end && freq[s[l] - 'a'] < k) ++l;   // 找左区间
            r = l + 1;
            while (r <= end && freq[s[r] - 'a'] >= k) ++r;  // 找右区间
            if (r > end && l == start)
                return r - l;
            else
                res = max(res, divide(s, l, r - 1, k));
            l = r;
        }
        return res;

    }
    int longestSubstring(string s, int k) {
        return divide(s, 0, s.size() - 1, k);
    }
};



// 滑动窗口
// 枚举最长字串中的字符种类数目
class Solution {
public:
    int longestSubstring(string s, int k) {
        int ret = 0;
        int n = s.length();
        for (int t = 1; t <= 26; t++) {
            int l = 0, r = 0;
            vector<int> cnt(26, 0);
            int tot = 0;    // 字符种类
            int less = 0;   // 当前出现次数小于 k 的字符的数量
            while (r < n) {
                cnt[s[r] - 'a']++;
                if (cnt[s[r] - 'a'] == 1) {     // 首次遇见该类字符
                    tot++;
                    less++;
                }
                if (cnt[s[r] - 'a'] == k) {     // 小于k的个数--
                    less--;
                }

                while (tot > t) {       // 保持窗口中字符种类数等于t
                    cnt[s[l] - 'a']--;
                    if (cnt[s[l] - 'a'] == k - 1) {
                        less++;
                    }
                    if (cnt[s[l] - 'a'] == 0) {
                        tot--;
                        less--;
                    }
                    l++;
                }
                if (less == 0) {        // 窗口内字符串满足条件
                    ret = max(ret, r - l + 1);
                }
                r++;
            }
        }
        return ret;
    }
};
