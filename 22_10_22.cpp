// 779. 第K个语法符号

// 列出前5行，不难发现，i+1行的前一半等于i行，后一半是i行的取放
// 所以我们可以不断“二分”，设置一个neg作为是否取反的标志
// 1）若k处于n行的前一半，那么等同与上一行
// 2）若k处于n行的后一半，我们把它映射到前一行的位置，即下标减去长度的一半，同时neg取反

// 时间最大（NlogN) N是行数
class Solution {
public:
    long long qmi(long long x, int y) {
        int res = 1;
        while (y) {
            if (y & 1) res *= x;
            y >>= 1;
            x *= x;
        }
        return res;

    }
    int kthGrammar(int n, int k) {
        bool neg = false;
        while (k > 2) {
            int mid = qmi(2, n - 2);
            if (k > mid) {
                neg = !neg;
                k -= mid;
            }
            --n;
        }
        int res = k == 1 ? 0 : 1;
        if (neg) res = res == 1 ? 0 : 1;
        return res;
    }
};

// 优化
class Solution {
public:
    int kthGrammar(int n, int k) {
        bool neg = false;
        int mid = pow(2, n - 1);
        while (k > 1) {
            mid >>= 1;
            if (k > mid) {
                neg = !neg;
                k -= mid;
            }
        }
        return neg ? k : !k;
    }
};

// 牛逼版
// 让索引从0开始，根据上一种解法我们可以知道最后的结果，只与翻转的次数有关，若偶数则答案为0，奇数则答案为1
// 又可以知道，翻转的次数和k二进制表示的1的个数相同，因为每次需要翻转都需要消去最
// 所以问题就变为了求二进制中1的个数
class Solution {
public:
    int kthGrammar(int n, int k) {
        // return __builtin_popcount(k - 1) & 1;
        k--;        // 索引从0开始
        int res = 0;
        while (k > 0) {
            k &= k - 1;
            res ^= 1;
        }
        return res;
    }
};



// 326. 3 的幂
// 试除法，直接做，不断除3
class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n < 1) return false;
        while (n > 1) {
            if (n % 3) return false;
            n /= 3;
        }
        return true;
    }
};
class Solution {
public:
    bool isPowerOfThree(int n) {
        while (n && n % 3 == 0) {
            n /= 3;
        }
        return n == 1;
    }
};

// 进阶，不使用循环或递归

// 判断是否为最大 3 的幂的约数
// 在给定的32位有符号整型范围内，最大的3的幂为3^19=1162261467
// 所以只需要判断 n 是否是 3^19
class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};




// 341. 扁平化嵌套列表迭代器
// 递归，dfs
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
        // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger>& getList() const;
};

class NestedIterator {
public:
    queue<int> arr;
    void dfs(const NestedInteger& numlist) {
        if (numlist.isInteger())
            arr.push(numlist.getInteger());
        else {
            auto& list = numlist.getList();
            int N = list.size();
            for (int i = 0; i < N; ++i)
                dfs(list[i]);
        }

    }
    NestedIterator(vector<NestedInteger>& nestedList) {
        int N = nestedList.size();
        for (int i = 0; i < N; ++i) {
            dfs(nestedList[i]);
        }
    }

    int next() {
        int res = arr.front();
        arr.pop();
        return res;
    }

    bool hasNext() {
        return !arr.empty();
    }
};
// 或
class NestedIterator {
private:
    vector<int> vals;
    vector<int>::iterator cur;

    void dfs(const vector<NestedInteger>& nestedList) {
        for (auto& nest : nestedList) {
            if (nest.isInteger()) {
                vals.push_back(nest.getInteger());
            } else {
                dfs(nest.getList());
            }
        }
    }

public:
    NestedIterator(vector<NestedInteger>& nestedList) {
        dfs(nestedList);
        cur = vals.begin();
    }

    int next() {
        return *cur++;
    }

    bool hasNext() {
        return cur != vals.end();
    }
};
