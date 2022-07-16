// 41. 包含min函数的栈



// 单调栈，栈从底往上元素的大小是单调的


//class MinStack {
//public:
//	/** initialize your data structure here. */
//	stack<int> stValue,stMin;
//
//	MinStack() {
//	}
//
//	void push(int x) {
//		stValue.push(x);
//		if (stMin.empty() || x <= stMin.top())
//			stMin.push(x);
//	}
//
//	void pop() {
//		if (stValue.top() == stMin.top())
//			stMin.pop();
//		stValue.pop();
//	}
//
//	int top() {
//		return stValue.top();
//	}
//
//	int getMin() {
//		return stMin.top();
//	}
//};




// 128. 编辑器

// 堆顶栈，顾名思义，两个栈对着放
// 动态中位数也类似，适用对顶堆

//#include <iostream>
//#include <stack>
//#include <climits>
//using namespace std;
//
//const int N = 1000010;
//int stkl[N], stkr[N], topl, topr;
//int f[N], sum[N];
//
//void add(int x) {
//    stkl[++topl] = x;
//    sum[topl] = sum[topl - 1] + x;
//    f[topl] = max(f[topl - 1], sum[topl]);
//}
//
//int main()
//{
//    int n, x;
//    scanf("%d", &n);
//    char ops[2];
//    f[0] = INT_MIN;
//
//    while (n--) {
//
//        scanf("%s", &ops);
//        if (*ops == 'I') {
//            scanf("%d", &x);
//            add(x);
//        } else if (*ops == 'D') {
//            if (topl)--topl;
//        } else if (*ops == 'L') {
//            if (topl)stkr[++topr] = stkl[topl--];
//        } else if (*ops == 'R') {
//            if (topr)add(stkr[topr--]);
//        } else {
//            scanf("%d", &x);
//            printf("%d\n", f[x]);
//        }
//    }
//
//
//    return 0;
//}



// 129. 火车进栈

// 某一时刻要么出站要么入栈，那么我们就可以DFS+栈模拟

//#include <iostream>
//#include <stack>
//#include <vector>
//
//using namespace std;
//
//vector<int> path;   // 存储栈中弹出的元素
//stack<int> stk;
//int remain = 20;
//int  n;
//
//void dfs(int u) {
//    if (!remain) return;     // 前20种已输出完，return
//
//    if (path.size() == n) {     // 全部处理完
//        --remain;
//        for (auto x : path) cout << x;
//        cout << endl;
//        return;
//    }
//
//    // 弹出栈顶元素，递归，回溯
//    if (stk.size()) {
//        path.push_back(stk.top());
//        stk.pop();
//        dfs(u);
//        stk.push(path.back());  // 回溯
//        path.pop_back();
//    }
//    // 入栈，回溯
//    if (u <= n) {
//        stk.push(u);    
//        dfs(u + 1);
//        stk.pop();  // 记得还原现场
//    }
//
//}
//
//int main()
//{
//    cin >> n;
//    dfs(1);
//    return 0;
//}




// 130. 火车进出栈问题

// 卡特兰数 + 压位高精度
// 卡特兰数公式
// k(0)= 1, k(1)=1时，如果接下来的项满足︰
// k(n) = k(0) * k(n - 1) + k(1) * k(n - 2) + ... + k(n - 2) * k(1) + k(n - 1) * k(0)
// 或者
// k(n) = c(2n, n) - c(2n, n - 1)
// 或者
// k(n) = c(2n, n) / (n + 1)


//#include <iostream>
//#include <vector>
//using namespace std;
//
//typedef long long LL;
//const int N = 6000010, M = 120010;
//
//
//LL res[N], tt;  // tt 为res末尾元素下标
//int q[M];       
//bool st[M];
//    
//void multi(int b)   // 高精度乘法，压9位
//{
//    LL t = 0;
//    for (int i = 0; i <= tt; i++)
//    {
//        res[i] = res[i] * b + t;
//        t = res[i] / 1000000000;
//        res[i] %= 1000000000;
//    }
//    while (t)
//    {
//        res[++tt] = t % 1000000000;
//        t /= 1000000000;
//    }
//}
//
//void out()
//{
//    printf("%lld", res[tt]);
//    for (int i = tt - 1; i >= 0; i--) printf("%09lld", res[i]);
//    cout << endl;
//}
//
//
//int get(int n, int p)   // 计算n!有几个因子p
//{
//    int s = 0;
//    while (n) s += n / p, n /= p;
//    return s;
//}
//
//int main()
//{   
//    
//    int n;
//    cin >> n;
//    // 埃氏筛法
//    for (int i = 2; i <= 2 * n; i++)
//        for (int j = i + i; j <= 2 * n; j += i)
//            st[j] = true;
//    
//    // 计算 2*n!质因子个数-（n * 2 - n）质因子个数
//    for (int i = 2; i <= n * 2; i++)
//        if (!st[i])
//        {
//            q[i] = get(n * 2, i) - get(n * 2 - n, i) * 2;
//        }
//
//    // 再减去(n+1)!质因子个数
//    int k = n + 1;
//    for (int i = 2; i <= k; i++)
//        while (k % i == 0)
//        {
//            k /= i;
//            q[i] --;
//        }
//
//    res[0] = 1;
//
//    for (int i = 2; i <= n * 2; i++)
//        while (q[i] --)
//            multi(i);
//
//    out();
//
//    return 0;
//}
//
//
//
//// 或稍微快一些的，但本质算法流程一样
//
//#include <stdio.h>
//
//const int N = 11311;
//const int base = 1e9;  // 压 9 位
//const int basebit = 9;
//
//int n;
//int sum[N];             // 存筛出的质数及其次数的结果
//long long res[4500];    // 存答案，res[0] 存 res 的位数
//int primes[N], cnt;     // 存筛的质数
//bool st[120001];        // 筛质数用的 bool 数组
//
//inline void init()      // 线性筛质数 + 求分解质因数的结果
//{
//    for (register int i = 2; i <= n << 1; i++)
//    {
//        if (!st[i])     // 如果 st[i] == false，说明该数 i 是质数
//        {
//            primes[++cnt] = i; // 先把它存进 primes
//            for (register int j = (n << 1) / i; j; j /= i) // 加上 (2n)! 含有 i 的数量。
//                sum[cnt] += j;
//            for (register int j = n / i; j; j /= i) // 减去 (n!)^2 含有 i 的数量。
//                sum[cnt] -= j << 1; // (n!)^2 含有 i 的数量即两倍的 n! 所含有的 i 的数量，所以只用处理 n!，然后减去其所含数量两倍即可
//            for (register int j = n + 1; j % i == 0; j /= i) // 减去 n + 1 含有 i 的数量
//                sum[cnt] --;
//        }
//        for (register int j = 1; primes[j] <= (n << 1) / i; j++) // 线性筛的板子
//        {
//            st[primes[j] * i] = true;
//            if (i % primes[j] == 0) break;
//        }
//    }
//}
//
//inline int qmi(int a, int b) // 快速幂（其实并没有卵用。。大部分调用都会进到那个 if (b == 1) 里面去。。所以加了个特判，效率会更高一点）
//{
//    if (b == 1) return a;
//    int res = 1;
//    for (; b; a *= a, b >>= 1)
//        if (b & 1) res *= a;
//    return res;
//}
//
//inline void multi(int b)     // 将 res 乘 b
//{
//    register long long t = 0;
//    for (register int i = 1; i <= res[0]; i++)
//    {
//        res[i] = res[i] * b + t;
//        t = res[i] / base;
//        res[i] %= base;
//    }
//    while (t) res[++res[0]] = t % base, t /= base;
//}
//
//void print(int x, int i = basebit) // 快速输出 9 位
//{
//    if (!i) return;
//    print(x / 10, i - 1);
//    putchar(x % 10 ^ 48);
//}
//
//int main()
//{
//    scanf("%d", &n);
//    init();              // 初始化 primes + 初始化 sum
//    res[0] = res[1] = 1; // 出初始化 res，res 的长度制为 1，res 的值制成 1
//    for (register int i = 1; i <= cnt; i++) // 枚举一遍分解出来的所有的质数
//        if (sum[i]) multi(qmi(primes[i], sum[i]));
//    printf("%lld", res[res[0]]);              // 第一位不用输出 9 位
//    if (res[0] > 1)      // 如果 res 的位数大于一的话，那么输出后面的
//        for (register int i = res[0] - 1; i; i--)
//            print(res[i]);
//    return 0;
//}


// 131. 直方图中最大的矩形
// 单调栈
// 最直接的是，枚举每个矩形作为最大矩形的高，然后左扩右扩，直到左边和右边矩形的高度小于选取的高度，但时间为O(N^2)
// 利用单调栈，一次遍历找出每个元素左边离他最近的小于它的下标，右边离他最近的小于它的下标
// 在一次遍历，计算每个矩形的面积， 总体时间O(N)

#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;
typedef long long LL;
int n;


vector<int[2]> getNearLess(vector<int>& arr) {
    vector<int[2]> res(arr.size());
    stack<list<int>> stk;
    for (int i = 0; i < arr.size(); ++i) {
        // 当前元素比栈顶小
        while (!stk.empty() && arr[stk.top().front()] > arr[i]) {
            auto pos = stk.top();
            stk.pop();
            int l = stk.empty() ? -1 : stk.top().back();
            for (auto p : pos) {
                res[p][0] = l;
                res[p][1] = i;
            }
        }
        // 相等的,当前元素大于栈顶元素
        if (!stk.empty() && arr[stk.top().front()] == arr[i]) {
            stk.top().push_back(i);
        } else {
            stk.push({ i });
        }
    }

    // 栈中的全弹出
    while (!stk.empty()) {
        auto pos = stk.top();
        stk.pop();
        int l = stk.empty() ? -1 : stk.top().back();
        for (auto p : pos) {
            res[p][0] = l;
            res[p][1] = arr.size();
        }
    }
    return res;

}

int main()
{
    while (cin >> n && n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        auto pos = getNearLess(a);
        LL res=0;
        for (int i = 0; i < n; ++i) {
            res = max(res, (pos[i][1] - pos[i][0] - 1LL) * a[i]);
        }
        cout << res << endl;
    }
    return 0;
}


// 或
// 也可以分为两次算左右边界


#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100010;

//l[i], r[i]表示第i个矩形的高度可向两侧扩展的左右边界
int h[N], q[N], l[N], r[N];

typedef long long LL;

int main()
{
    int n;
    while (scanf("%d", &n), n)
    {
        for (int i = 1; i <= n; i++)  scanf("%d", &h[i]);
        h[0] = h[n + 1] = -1;

        int tt = -1;
        q[++tt] = 0;
        for (int i = 1; i <= n; i++)
        {
            while (h[q[tt]] >= h[i])  tt--;
            l[i] = q[tt];
            q[++tt] = i;
        }

        tt = -1;
        q[++tt] = n + 1;
        for (int i = n; i; i--)
        {
            while (h[q[tt]] >= h[i])  tt--;
            r[i] = q[tt];
            q[++tt] = i;
        }

        LL res = 0;
        for (int i = 1; i <= n; i++)  res = max(res, h[i] * ( r[i] -l[i] - 1LL));
        printf("%lld\n", res);
    }
    return 0;
}

