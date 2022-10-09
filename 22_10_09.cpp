// 202. 快乐数

// 模拟，我们对于计算过程中得到的每个新数入哈希表，如果得到的新数在哈希表出现过，break;
// 如果新数为1,break  , 最后根据n==1进行返回
// 若不是快乐数，说明有环,可以用快慢指针做到O（1）空间
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> set;
        while (n != 1) {
            int sum = 0;
            while (n) {
                int r = n % 10;
                sum += r * r;
                n /= 10;
            }
            n = sum;
            if (set.count(sum)) break;
            set.insert(sum);
        }
        return n == 1;
    }
};

// 其次通过数学可以得出，计算的过程中总会要么出现1，返回true,要么出现4，一定到达不了1，进行一个环
class Solution {
public:
    bool isHappy(int n) {
        while (n != 1 && n != 4) {
            int sum = 0;
            while (n) {
                sum += (n % 10) * (n % 10);
                n /= 10;
            }
            n = sum;
        }
        return n == 1;
    }

};



// 204. 计数质数

// 最暴力的方法即是对于每个数进行质数的判断 时间为（O(N* N^0.5)

// 可以使用埃氏筛，做到O(N*loglogN)
// 简单来说就是就是根据已知的结果，提前筛出结果
class Solution {
public:
    int countPrimes(int n) {
        if (n < 3) return 0;
        vector<bool> isPrime(n, true);
        int ans = 1;
        for (int i = 3; i < n; i += 2) {    //自增2,每次跳过偶数
            if (isPrime[i]) {
                ans += 1;
                if ((long long)i * i < n) {
                    for (int j = i * i; j < n; j += 2 * i) {    // 自增2倍，跳过偶数
                        isPrime[j] = false;
                    }
                }
            }
        }
        return ans;
    }
};

// 线性筛
// 埃氏筛法仍有优化空间，它会将一个合数重复多次标记。如果能让每个合数都只被标记一次，那么时间复杂度就可以降到 O(N)了
// 相较于埃氏筛，我们多维护一个 primes 数组表示当前得到的质数集合。
// 我们从小到大遍历，如果当前的数 x 是质数，就将其加入 primes 数组。
// 另一点与埃氏筛不同的是，「标记过程」不再仅当 x 为质数时才进行，而是对每个整数 x 都进行。
// 对于整数 x，我们不再标记其所有的倍数,而是只标记质数集合中的数与 x 相乘的数.且在发现 x% primse[i]==0 的时候结束当前标记
// 核心点在于:如果x可以被primes[i] 整除，那么对于合数y = x*primes[i+1]而言，
// 它一定在后面遍历到 (x/peimes[i])*peimes[i+1] 这个数的时候会被标记，其他同理，
// 这保证了每个合数只会被其「最小的质因数」筛去，即每个合数被标记一次。

class Solution {
public:
    int countPrimes(int n) {
        vector<int> primes;
        vector<bool> isPrime(n, true);
        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) {
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && i * primes[j] < n; ++j) {
                isPrime[i * primes[j]] = false;
                if (i % primes[j] == 0) {
                    break;
                }
            }
        }
        return primes.size();
    }
};


// 190. 颠倒二进制位
// 分治
// 32位中前16位和后16位交换
// 每16位中前8位和后8位交换,依次......
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        // 注意n是无符号数，所以都是逻辑位移
        n = (n >> 16) | (n << 16); //低16位与高16位交换
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8); //每16位中低8位和高8位交换; 1111是f
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4); //每8位中低4位和高4位交换;
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2); //每4位中低2位和高2位交换; 1100是c,0011是3
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1); //每2位中低1位和高1位交换; 1010是a,0101是5
        return n;
    }
};

// 191. 位1的个数
// 直接的我们从右往左，不断找最右边的1，在减去，依次迭代下去
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int ret = 0;
        while (n) {
            //n &= n - 1;     // n & (n - 1)可以消去最右边的1
            // 或下面的方式也可以消去最右边的1
            n ^= n & (-n);
            ret++;
        }
        return ret;
    }
};

// 分治
// 我们一开始，对于每个位，使用单个二进制位的1表示十进制形式1的个数，即 二进制 0 -> 0个1， 二进制 1 -> 1个1
// 随后两个一组，表示，如 00 -> 00  , 01 -> 01 , 10 -> 01 , 11 -> 10
// 再四个一组表示， 如 0000 -> 0000 , 1111 -> 0100 ....
// 那么如果表示呢？以两个两个一组表示， xx -> ((xx>>1) & 0x01 + (xx & 0x01))
// 四个一组                     xxxx -> ((xxxx>>1) & 0x0011 + (xxxx & 0x0011))
// 以这种形式来表示，即是将左右两个二进制数进行相加得到新的结果来表示这个组合的1的个数
class Solution {
public:
    int hammingWeight(uint32_t n) {
        n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
        n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
        n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
        n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
        return n;
    }
};