// 621. 任务调度器
// 优先队列
// 先统计各个字符出现的个数，再将其全部入栈，按照个数从大到小排序，一次处理n个
class Solution {
public:
    typedef pair<char, int> CI;
    int leastInterval(vector<char>& tasks, int n) {
        auto cmp = [](const CI& a, const CI& b) {return a.second < b.second; };
        priority_queue <CI, vector<CI>, decltype(cmp)> qu(cmp);
        unordered_map<char, int> map;

        for (auto c : tasks) {
            ++map[c];
        }
        for (auto& kv : map) {
            qu.push({ kv.first,kv.second });
        }

        int res = 0;
        while (qu.size()) {
            vector<CI> tmp; // 缓存
            for (int i = 0; i < n; ++i) {
                if (qu.size()) {    // 任务器还有任务
                    auto t = qu.top();
                    if (t.second > 1)
                        tmp.push_back({ t.first,t.second });
                    qu.pop();
                } else if (tmp.empty()) {   // 任务器没任务了，缓冲区也没任务了，及时退出
                    break;
                }
                ++res;
            }
            for (auto i : tmp) {    // 再将缓存区里的也加入任务器
                qu.push(i);
            }
        }
        return res;
    }
};

// 同上法类似
//我们按照时间顺序，依次给每一个时间单位分配任务。
//那么如果当前有多种任务不在冷却中，那么我们应该如何挑选执行的任务呢？
//直觉上，我们应当选择剩余执行次数最多的那个任务，将每种任务的剩余执行次数尽可能平均，使得 CPU 处于待命状态的时间尽可能少。
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> freq;
        for (char ch : tasks) {
            ++freq[ch];
        }

        // 任务总数
        int m = freq.size();
        // nextValid[i] 第i个任务的下一个起始时间
        vector<int> nextValid, rest;        
        for (auto [_, v] : freq) {
            nextValid.push_back(1);
            rest.push_back(v);
        }

        int time = 0;
        for (int i = 0; i < tasks.size(); ++i) {    // 每次确定一个任务的执行时间
            ++time;
            int minNextValid = INT_MAX;
            for (int j = 0; j < m; ++j) {
                if (rest[j]) {      // 该类任务还没完结
                    minNextValid = min(minNextValid, nextValid[j]);
                }
            }
            time = max(time, minNextValid); // 下一个任务可以执行的时间
            int best = -1;      // 选择一个最好的选择，即选择一个剩余执行次数最多的任务
            for (int j = 0; j < m; ++j) {
                if (rest[j] && nextValid[j] <= time) {
                    if (best == -1 || rest[j] > rest[best]) {
                        best = j;
                    }
                }
            }
            nextValid[best] = time + n + 1;
            --rest[best];
        }

        return time;
    }
};


// 可以发现，对于需要执行最多次数的任务，其时间分布一定至少是n个步长执行一次，对于哪些执行次数较少的就放在中间
// 若有多个任务执行次数都是最多的，那这些任务可捆版在一起看待，若不是最多次数的任务的个数超过了n的步长，那么也放在中间的空隙中(这种情况下就没有空闲，答案就是任务个数）
// 这种处理方式就是让中间的空位置尽可能少
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> freq;
        for (char ch : tasks) {
            ++freq[ch];
        }

        // 最多的执行次数
        int maxExec = max_element(freq.begin(), freq.end(), [](const auto& u, const auto& v) {
            return u.second < v.second;
            })->second;
        // 具有最多执行次数的任务数量
        int maxCount = accumulate(freq.begin(), freq.end(), 0, [=](int acc, const auto& u) {
            return acc + (u.second == maxExec);
            });

        return max((maxExec - 1) * (n + 1) + maxCount, static_cast<int>(tasks.size()));
    }
};
// 或
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int cnt[256] = { 0 };
        int maxCnt = 0;
        for (char c : tasks) {
            ++cnt[c];
            maxCnt = max(maxCnt, cnt[c]);
        }

        int maxKinds = 0;
        for (int i = 0; i < 256; ++i)
            if (cnt[i] == maxCnt) ++maxKinds;

        return max((maxCnt - 1) * (n + 1) + maxKinds, (int)tasks.size());
    }
};



// 647. 回文子串

// 暴力
// 枚举每个位置，从中间向两边扩，注意，需要这每个字符间隙插入任意字符，便于处理中心字符的位置
// 实际操作不同真的在空隙插入字符，只需主观的认为插入了即可。插入完后字符串长度变为了2*n+1
// 随后遍历[0,2n+1),对于普遍的i，我们可以映射其左右指针l = i / 2， r = i / 2 + i % 2，
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size(), ans = 0;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int l = i / 2, r = i / 2 + i % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
                ++ans;
            }
        }
        return ans;
    }
};

// Manacher 算法
// Manacher 算法是在线性时间内求解最长回文子串的算法

class Solution {
public:
    int countSubstrings(string s) {
        string t = "#";    // 前面多加一个’#‘是为了让下标从1开始
        for (auto c : s) {
            t += c;
            t += '#';
        }
        int N = t.size();
        vector<int> radius(N);
        // cur是让r扩张的回文中心，r是最右的扩展成功位置的下一个位置
        int cur = -1, r = -1,res=0;
        for (int i = 0; i < N; ++i) {
            // 先根据对称点确定可能的半径
            radius[i] = r > i ? min(radius[2 * cur - i], r - i) : 1;    
            // 中心扩展
            while (i + radius[i]<N && i - radius[i]>-1) {
                if (t[i + radius[i]] == t[i - radius[i]]) {
                    ++radius[i];
                } else {
                    break;
                }
            }
            // 如果最右边界扩张了，更新
            if (i + radius[i] > r) {
                r = i + radius[i];
                cur = i;
            }
            res += radius[i] / 2;
        }
        return res;
    }
};
