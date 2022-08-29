// 239. 滑动窗口最大值

// 优先队列
// 使用优先队列，即大根堆，value使用pair<int,int> 第一个关键字存num[i],第二个关键字存i
// 每次从大根堆选出一个堆顶的入答案，再断弹出second小于窗口左边界的
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> nums, int k) {
        vector<int> res;
        priority_queue<pair<int, int>> heap;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            heap.emplace(nums[i], i);
            if (i >= k - 1) {
                res.push_back(heap.top().first);
                while (heap.size() && heap.top().second <= i - (k - 1)) heap.pop();
            }
        }
        return res;
    }
};


// 单调队列
// 使用双向队列，队列中保证单调下降，对头是最大值
// 每次遍历到一个元素，若该元素值大于队尾，那么弹出，直到满足条件
// 为什么可以一直弹出呢？因为在窗口内，后面的元素大于前面的，那么窗口内的最大值自然与前面哪些较小的无关了
// 
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int> nums, int k) {
        vector<int> res;
        deque<int> q;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            while (q.size() && nums[i] >= nums[q.back()]) q.pop_back();
            q.push_back(i);
            if (i >= k - 1) {
                res.push_back(nums[q.front()]);
                if (q.front() == i - (k - 1)) q.pop_front();
            }
        }
        return res;
    }
};


// 分块+预处理
// 我们k个k个进行分组
// 若i是k的倍数，那么窗口正好在某一个分组，如果步数，那么就会在两个分组中，
// 前一个分块被窗口包住后面n个，后一个分块被窗口包住前面m个
// 所以我们预先处理处每个分块的前缀和后缀的最大值
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefixMax(n), suffixMax(n);
        for (int i = 0; i < n; ++i) { 
            if (i % k == 0) {     // k个一组，处理前缀
                prefixMax[i] = nums[i];
            } else {
                prefixMax[i] = max(prefixMax[i - 1], nums[i]);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            if (i == n - 1 || (i + 1) % k == 0) {   // k个一组，处理后缀
                suffixMax[i] = nums[i];
            } else {
                suffixMax[i] = max(suffixMax[i + 1], nums[i]);
            }
        }

        vector<int> ans;
        for (int i = 0; i <= n - k; ++i) {  // 求前缀和后缀的最大值
            ans.push_back(max(suffixMax[i], prefixMax[i + k - 1]));
        }
        return ans;
    }
};



// 279. 完全平方数

// 动态规划
// f[i] 表示最少需要多少个数的平方来表示整数 i。一般的，对于数i,这些数一定落在[1,根号n]间，
// 我们可以枚举这些数，假设当前枚举到j，那么我们还需要取若干数的平方，构成 i-j^2
// 此时我们发现该子问题和原问题类似，只是规模变小了。符合动态规划的要求
// 时间O(N*根号N)
class Solution {
public:
    int numSquares(int n) {
        vector<int> f(n + 1);
        for (int i = 1; i <= n; i++) {
            int minn = INT_MAX;
            for (int j = 1; j * j <= i; j++) {
                minn = min(minn, f[i - j * j]);
            }
            f[i] = minn + 1;
        }
        return f[n];
    }
};

// 数学，四平方和定理
// 同时四平方和定理包含了一个更强的结论：当且仅当 n!=4^k*(8m+7)时，n可以被表示为至多三个正整数的平方和
// 当 n=4^k*(8m+7)时，n只能表示为四个正整数的平方和
// 当n!=4^k*(8m+7)时，我们需要判断到底多少个完全平方数能够表示 nn，我们知道答案只会是 1,2,3 中的一个：
//      答案为 1 时，则必有 n 为完全平方数，这很好判断；
//      答案为 2 时，则有 n=a^2+b^2，我们只需要枚举所有的a，判断n-a^2是否为完全平方数即可

class Solution {
public:
    // 判断是否为完全平方数
    bool isPerfectSquare(int x) {
        int y = sqrt(x);
        return y * y == x;
    }

    // 判断是否能表示为 4^k*(8m+7)
    bool checkAnswer4(int x) {
        while (x % 4 == 0) {
            x /= 4;
        }
        return x % 8 == 7;
    }

    int numSquares(int n) {
        if (isPerfectSquare(n)) {
            return 1;
        }
        if (checkAnswer4(n)) {
            return 4;
        }
        for (int i = 1; i * i <= n; i++) {
            int j = n - i * i;
            if (isPerfectSquare(j)) {
                return 2;
            }
        }
        return 3;
    }
};
