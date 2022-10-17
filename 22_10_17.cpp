// 37. 解数独

// dfs+位运算
// 题目本身是dfs,做了许多优化
// 对于每一行每一列没一个九宫格可以的选择我们用一个int二级制位上的1来表示,这样利用位运算符&，可以快速得出三种限制条件下的选择
// 我们还需要调整尽量从根减少递归分支的数量,所以要每次选出可选最小空位来进行尝试
class Solution {
public:
    static constexpr int N = 9;
    // ones[i] 为i的二级制位一共有多少个1，map[i]是i的二进制位1处于第几位
    int ones[1 << N], map[1 << N];
    int row[N], col[N], cell[3][3];
    // 求可选方案，是行，列，九宫格的交集
    inline int get(int x, int y) {
        return row[x] & col[y] & cell[x / 3][y / 3];
    }
    // 求最低位的1，如100100，返回100
    inline int lowbit(int x) {  //
        return x & -x;
    }
    void flip(int i, int j, int digit) {
        row[i] ^= (1 << digit);
        col[j] ^= (1 << digit);
        cell[i / 3][j / 3] ^= (1 << digit);
    }
    void init() {
        // 初始化为九个数都可以选
        for (int i = 0; i < N; ++i) row[i] = col[i] = (1 << N) - 1;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                cell[i][j] = (1 << N) - 1;

        for (int i = 0; i < N; ++i) map[1 << i] = i;
        for (int i = 0; i < 1 << N; ++i) {
            int s = 0;
            for (int j = i; j; j -= lowbit(j)) ++s;
            ones[i] = s;
        }
    }
    bool dfs(int cnt, vector<vector<char>>& board) {
        if (!cnt) return true;
        // 找出可选方案数最小的空格
        int minv = 10;
        int x, y;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] == '.') {
                    int t = ones[get(i, j)];
                    if (t < minv) {
                        minv = t;
                        x = i, y = j;
                    }
                }

        for (int i = get(x, y); i; i -= lowbit(i)) {        // 枚举该位置的每一种可能
            int t = map[lowbit(i)];
            // 修改状态
            flip(x, y, t);
            board[x][y] = '1' + t;

            if (dfs(cnt - 1, board)) return true;

            // 回溯还原
            flip(x, y, t);
            board[x][y] = '.';
        }

        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        init();
        int cnt = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] == '.')
                    ++cnt;
                else        // 可选集合中减去已选的
                    flip(i, j, board[i][j] - '1');


        dfs(cnt, board);
    }
};



// 295. 数据流的中位数
// 对顶堆
class MedianFinder {
public:
    priority_queue<int> big_heap;
    priority_queue<int, vector<int>, greater<int>> small_heap;

    MedianFinder() {

    }

    void addNum(int num) {
        // 若num小于小根堆的堆顶，插入大根堆
        if (big_heap.empty() || num < big_heap.top()) {
            big_heap.push(num);
        } else {
            small_heap.push(num);
        }
        // 调整两堆内的个数，使得两堆中个数相差不超过1,同时若中个数是奇数，我们让大根堆比小根堆多一个
        if (big_heap.size() < small_heap.size()) {
            big_heap.push(small_heap.top());
            small_heap.pop();
        } else if (big_heap.size() > small_heap.size() + 1) {
            small_heap.push(big_heap.top());
            big_heap.pop();
        }
    }

    double findMedian() {
        double res = 0;
        res = big_heap.top();
        if (big_heap.size() == small_heap.size()) {
            res += small_heap.top();
            res /= 2;
        }
        return res;
    }
};

// 有序集合+双指针
class MedianFinder {
    multiset<int> nums;
    multiset<int>::iterator left, right;

public:
    MedianFinder() : left(nums.end()), right(nums.end()) {}

    void addNum(int num) {
        const size_t n = nums.size();   // 取出未插入前的个数

        nums.insert(num);
        if (!n) {
            left = right = nums.begin();
        } else if (n & 1) {     // 奇数
            if (num < *left) {
                left--;
            } else {
                right++;
            }
        } else {        // 偶数
            if (num > *left && num < *right) {
                left++;
                right--;
            } else if (num >= *right) {     // 
                left++;
            } else {
                right--;    
                // 注意，因为若有相同的元素插入时，会插在连续相同序列的后面，所以这样情况需要调整左指针位置
                left = right;  
            }
        }
    }

    double findMedian() {
        return (*left + *right) / 2.0;
    }
};
/*进阶1
如果数据流中所有整数都在0到100范围内，那么我们可以利用计数排序统计每一类数的数量，并使用双指针维护中位数。
进阶2
如果数据流中99% 的整数都在0到100范围内，那么我们依然利用计数排序统计每一类数的数量，并使用双指针维护中位数。对于超出范围的数，我们可以单独进行处理，建立两个数组,
分别记录小于0的部分的数的数量和大于100的部分的数的数量即可。当小部分时间，中位数不落在区间[0, 100]中时，我们在对应的数组中暴力检查即可。*/
