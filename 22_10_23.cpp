// 371. 两整数之和
// 位运算模拟
class Solution {
public:
    int getSum(int a, int b) {
        long long res = 0;  // 需要使用long long，因为若是负数，且需要进位时会溢出
        for (int i = 0; i < 32; ++i) {
            int bita = a & (1 << i);    // 取出a的当前位
            int bitb = b & (1 << i);    // 取出b的当前位
            if (bita & bitb)  // 当前位都是1，进位
                res |= 1ll << (i + 1);
            else if (bita || bitb) {      // 当前位有一个1
                if (res & (1 << i)) {   // 如果res当前位本就有一个1
                    res &= ~(1 << i);       // 消去当前位上的1
                    res |= 1ll << (i + 1);    // 进位
                } else {
                    res |= 1 << i;
                }
            }
        }
        return (int)res;
    }
};

// 进一步优化考虑
// 若不需要进位，其无进位加法的结果位 a^b
// 而所有需要进位的位为 a&b,进位后的结果为(a&b)<<1

// 于是，我们可以将整数α和b的和，拆分为α和b的无进位加法结果与进位结果的和。
// 因为每一次拆分都可以让需要进位的最低位至少左移一位，又因为α和b可以取到负数，
// 所以我们最多需要log(maz_int)次拆分即可完成运算。
// 因为有符号整数用补码来表示，所以以上算法也可以推广到0和负数。

//在C++的实现中，当我们赋给带符号类型一个超出它表示范围的值时，结果是undefined;
// 而当我们赋给无符号类型一个超出它表示范围的值时，结果是初始值对无符号类型表示数值总数取模的余数。因此，我们可以使用无符号类型来防止溢出。



class Solution {
public:
    int getSum(int a, int b) {
        while (b != 0) {
            unsigned int carry = (unsigned int)(a & b) << 1;
            a ^= b;
            b = carry;
        }
        return a;
    }
};


// 378. 有序矩阵中第 K 小的元素
// n路归并，利用每行有序的特点
class Solution {
public:
    typedef pair<int, int> PII;
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        
        auto fun = [&](const PII& a, const PII& b) {return matrix[a.first][a.second] > matrix[b.first][b.second]; };
        // decltype(）里面需要传函数指针，若是函数的话，需要取地址，若是lamda，则直接传，因为lamda返回的时函数指针
        priority_queue<PII, vector<PII>, decltype(fun)> qu(fun);
        int N = matrix.size(), cnt = k;
        for (int i = 0; i < N; ++i)
            qu.push({ i,0 });
        while (--k) {
            auto t = qu.top();
            qu.pop();
            if (t.second != N - 1)
                qu.push({ t.first,t.second + 1 });
        }
        return matrix[qu.top().first][qu.top().second];
    }
};


// 二分查找
// 矩阵中最小值在左上角，最大值在右下角，我们不断在这中间二分答案
// 其中我们可以从右上角往左下角滑动，统计比mid小的的数的个数
//      具体的， if matrix[i][j] > num，向左走
//             else 向下走，同时统计上行中小于num的个数，为j+1
class Solution {
public:
    int check(vector<vector<int>>& matrix, int num) {
        int N = matrix.size();
        int i = 0, j = N - 1;       // 从右上角往左下角滑
        int cnt = 0;
        while (i < N && j >= 0) {
            if (matrix[i][j] > num) {
                --j;
            } else {
                cnt += j + 1;
                ++i;
            }
        }
        return cnt;
    }
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int N = matrix.size();
        int l = matrix[0][0], r = matrix[N - 1][N - 1];

        while (l < r) {
            int mid = l + r >> 1;
            if (check(matrix, mid) < k)
                l = mid + 1;
            else
                r = mid;
        }
        return l;
    }
};

