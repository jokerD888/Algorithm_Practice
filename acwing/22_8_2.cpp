
//150. 括号画家

// 栈模拟，从左往右依次遍历，若当前元素和栈顶元素可匹配，弹出，此时的最大长度即为当前下标减去栈顶元素下标
// 若栈为空，则最大长度为i+1

//#include <iostream>
//#include <stack>
//#include <cstring>
//using namespace std;
//
//const int N = 100010;
//char str[N];
//
//int main()
//{
//
//    scanf("%s", str);
//    int n = strlen(str);
//    stack<int> st;
//    int res = 0;
//    for (int i = 0; i < n; ++i) {
//        char c = str[i];
//        if (c == ')' && st.size() && str[st.top()] == '(') st.pop();
//        else if (c == ']' && st.size() && str[st.top()] == '[') st.pop();
//        else if (c == '}' && st.size() && str[st.top()] == '{') st.pop();
//        else st.push(i);
//
//        if (st.size()) res = max(res, i - st.top());
//        else res = max(res, i + 1);
//    }
//    cout << res << endl;
//
//    return 0;
//}



//151. 表达式计算4
//当前的运算符优先级 小于等于 栈顶的运算符优先级，也可以说， 栈顶的运算符优先级 大于等于 当前的运算符优先级， 
// 则符号栈弹出一个符号，数字栈弹出两个数字， 对运算符和数字进行运算，把结果压入数字栈，再把当前运算符压入符号栈。
// 如果遇到括号：如果是左括号，直接入栈。如果是右括号，弹出栈中第一个左括号前所有的操作符，并将左括号弹出。
// 细节较多。
//#include <iostream>
//#include <stack>
//#include <string>
//using namespace std;
//
//stack<char> ops;    // 存操作符
//stack<int> nums;    // 存操作数
//
//void cal() {
//    int a = nums.top(); nums.pop();
//    int b = nums.top(); nums.pop();
//    char c = ops.top(); ops.pop();
//
//    int res;
//    if ('+' == c) res = b + a;
//    else if ('-' == c) res = b - a;
//    else if ('*' == c) res = b * a;
//    else if ('/' == c) res = b / a;
//    else {
//        res = 1;
//        while (a--) res *= b;
//    }
//    nums.push(res);
//}
//int main()
//{
//    string s;
//    cin >> s;
//    if (s[0] == '-') s = '0' + s;     // 确保 number operator number
//
//    // 处理多余括号,左括号多余不影响，但右括号多余会影响，所以我们在左边补充足够的左括号
//    string left;
//    for (int i = 0; i < s.size(); ++i) left += '(';
//    s = left + s + ')';     // 右边再加一个右括号便于直接算出结果
//
//
//    for (int i = 0; i < s.size(); ++i) {
//        // 如果‘-’前面是不是数字 或者 不是‘）’，则‘-’是一个负号
//        bool neg = false;
//        if (s[i] == '-' && !(isdigit(s[i - 1]) || s[i - 1] == ')')) {   // 是负号的话
//            neg = true;
//            ++i;
//            if (s[i] == '(') {  // 将-(...) 变为 -1*(...)
//                nums.push(-1);
//                ops.push('*');
//            }
//        }
//
//        if (isdigit(s[i])) {    // 是数字
//            int t=0;
//            while (isdigit(s[i])) t = t * 10 + s[i++] - '0';
//            --i;
//            if (neg) t = -t;
//            nums.push(t);
//        } else {
//            char c = s[i];        // 栈中的操作符优先级一定是递增的，优先级高的先算
//            if (c == ')') {
//                while (ops.top() != '(') cal();
//                ops.pop();
//                continue;
//            }
//
//            if (c == '+' || c == '-') {
//                while (ops.top() != '(') cal(); //遇到括号，直接算到括号里面的就行
//            } else if (c == '*' || c == '/') {
//                while (ops.top() == '*' || ops.top() == '/' || ops.top() == '&') cal();
//            } else if (c == '^') {
//                while (ops.top() == '^') cal();
//            } 
//            ops.push(c);
//        }
//    }
//    while (ops.size()) {    // 栈中有多余的（，其下面可能还有其他操作符，弹出无用（
//        if (ops.top() == '(') ops.pop();
//        else cal();
//    }
//    cout << nums.top();
//    return 0;
//}







//#include <iostream>
//#include <stack>
//
//using namespace std;
//
//stack<int> nums;
//stack<char> ops;
//
//int qmi(int a, int k)
//{
//    int res = 1;
//    while (k--) res *= a;
//    return res;
//}
//
//void cal()
//{
//    int a = nums.top(); nums.pop();
//    int b = nums.top(); nums.pop();
//    char c = ops.top(); ops.pop();
//    int d;
//
//    if (c == '+') d = b + a;
//    else if (c == '-') d = b - a;
//    else if (c == '*') d = b * a;
//    else if (c == '/') d = b / a;
//    else d = qmi(b, a);
//
//    nums.push(d);
//}
//
//int main()
//{
//    string str;
//    cin >> str;
//
//    if (str[0] == '-') str = '0' + str;
//    string left;
//    for (int i = 0; i < str.size(); i++) left += '(';
//    str = left + str + ')';
//
//    for (int i = 0; i < str.size(); i++)
//    {
//        if (str[i] >= '0' && str[i] <= '9')
//        {
//            int j = i, t = 0;
//            while (str[j] >= '0' && str[j] <= '9')
//            {
//                t = t * 10 + str[j] - '0';
//                j++;
//            }
//            nums.push(t);
//            i = j - 1;
//        } else
//        {
//            char c = str[i];
//            if (c == '(') ops.push(c);
//            else if (c == '+' || c == '-')
//            {
//                if (c == '-' && i && !(str[i - 1] >= '0' && str[i - 1] <= '9') && str[i - 1] != ')')
//                {
//                    if (str[i + 1] == '(')  // 将-(...)变成-1 * (...)
//                    {
//                        nums.push(-1);
//                        ops.push('*');
//                    } else
//                    {
//                        int j = i + 1, t = 0;
//                        while (str[j] >= '0' && str[j] <= '9')
//                        {
//                            t = t * 10 + str[j] - '0';
//                            j++;
//                        }
//                        nums.push(-t);
//                        i = j - 1;
//                    }
//                } else
//                {
//                    while (ops.top() != '(') cal();
//                    ops.push(c);
//                }
//            } else if (c == '*' || c == '/')
//            {
//                while (ops.top() == '*' || ops.top() == '/' || ops.top() == '^') cal();
//                ops.push(c);
//            } else if (c == '^')
//            {
//                while (ops.top() == '^') cal();
//                ops.push(c);
//            } else if (c == ')')
//            {
//                while (ops.top() != '(') cal();
//                ops.pop();
//            } else cout << "invalid operator!" << endl;
//        }
//    }
//
//    cout << nums.top() << endl;
//    return 0;
//}



// 152. 城市游戏

// 单调栈，枚举每一行作为矩阵的底，固定底边后，问题就转化为直方图中最大的矩形

//#include <iostream>
//using namespace std;
//
//const int N = 1010;
//int a[N][N];
//int q[N], l[N], r[N];
//int n, m;
//
//int main()
//{
//    cin >> n >> m;
//    char c[2];
//    for (int i = 1; i <= n; ++i)
//        for (int j = 1; j <= m; ++j) {
//            cin >> c;
//            a[i][j] = c[0] == 'F' ? 1 + a[i - 1][j] : 0;
//        }
//    for (int i = 0; i <= n; ++i) a[i][0] = a[i][m + 1] = -1;    //两边做哨兵处理
//
//    int res = 0;
//    for (int i = 1; i <= n; ++i) {
//        int tt = 0;
//        q[0] = 0;
//        for (int j = 1; j <= m; ++j) {
//            while (a[i][q[tt]] >= a[i][j]) --tt;
//            l[j] = q[tt];
//            q[++tt] = j;
//        }
//
//        tt = 0;
//        q[0] = m + 1;
//        for (int j = m; j; --j) {
//            while (a[i][q[tt]] >= a[i][j]) --tt;
//            r[j] = q[tt];
//            q[++tt] = j;
//        }
//
//        for (int j = 1; j <= m; ++j) {
//            res = max(res, a[i][j] * (r[j] - l[j] - 1));
//        }
//    }
//    cout << 3 * res << endl;
//    return 0;
//}



// 154. 滑动窗口

// 单调队列，从左往右遍历，若当前元素<=队尾元素，队尾元素弹出，直到当前元素>队尾元素，插入队尾，这样，队列从头到尾呈现单调递增，窗口最小值即为对头
//#include <iostream>
//#include <stack>
//using namespace std;
//
//const int N = 1000010;
//int n, k;
//int q[N], a[N];
//
//int main()
//{
//    cin >> n >> k;
//    for (int i = 0; i < n; ++i) cin >> a[i];
//
//    int hh = 0, tt = -1;
//    for (int i = 0; i < n; ++i) {
//        if (hh <= tt && q[hh] <= i - k) ++hh;       // 保持窗口长度，队头弹出
//        while (hh <= tt && a[q[tt]] >= a[i]) --tt;  // 队尾元素>=a[i],队尾弹出
//        q[++tt] = i;                                // 入队尾
//        if (i >= k - 1) cout << a[q[hh]] << " ";    // 窗口长度满足k
//    }
//    puts("");
//    hh = 0, tt = -1;
//    for (int i = 0; i < n; ++i) {
//        if (hh <= tt && q[hh] <= i - k) ++hh;
//        while (hh <= tt && a[q[tt]] <= a[i])--tt;
//        q[++tt] = i;
//        if (i >= k - 1) cout << a[q[hh]] << " ";
//    }
//    puts("");
//
//    return 0;
//}
//
//
//
////155. 内存分配
//
//// 数据结构：
////等待队列：(内存长度, 占用时间)：queue  
////内存使用情况：(起始下标，长度)
////线性扫描、删除、插入：set
////小根堆：（释放时间key，起始下标），priority_queue
//// 算法流程：
////新来一个请求：（T, M, P)
////释放掉所有 释放时间 <= T 的内存，每次释放之后，都要判断等待队列的队头是否可以满足
////判断（T，M，P)是否可以满足，如果不可以，则插入等待队列
//
//#include <iostream>
//#include <algorithm>
//#include <queue>
//#include <set>
//#include <vector>
//
//using namespace std;
//
//typedef pair<int, int> PII;
//
//int n;
//queue<PII> waits;       // (first: 内存长度，second: 占用时间)
//set<PII> runs;        // (first: 起始下标，sercond：长度)
//priority_queue<PII, vector<PII>, greater<PII>> endts;       // (first: 释放时间，second: 起始下标)
//int tm, cnt;
//
//bool give(int t, int m, int p)
//{
//    for (auto it = runs.begin(); it != runs.end(); it++)
//    {
//        auto jt = it;
//        jt++;
//        if (jt != runs.end())
//        {
//            if (m <= jt->first - (it->first + it->second - 1) - 1)  // 如果it和jt之间有空间可分配的话
//            {
//                int start = it->first + it->second;     // 分配的起始地址
//                runs.insert({ start, m });              // 入使用集合
//                endts.push({ t + p, start });           // 入结束集合
//                return true;                            // 分配成功
//            }
//        }
//    }
//
//    return false;
//}
//
//void finish(int t)
//{
//    while (endts.size() && endts.top().first <= t)  // 确保使用完的内存都释放掉
//    {
//        int f = endts.top().first;      // 当前最早结束使用的内存
//        while (endts.size() && endts.top().first == f)      // 释放一批用一时间点需要释放的内存
//        {
//            auto top = endts.top();
//            endts.pop();
//            auto it = runs.lower_bound({ top.second, 0 });  // 从run中删除
//            runs.erase(it);
//        }
//
//        tm = f;
//        while (waits.size())    // 若等待队列中有内存等待的话
//        {
//            // 尝试分配
//            auto front = waits.front();     
//            if (give(f, front.first, front.second))
//            {
//                waits.pop();
//            } else break;       // 一定是对头优先分配，分配不了的话，break
//        }
//    }
//}
//
//int main()
//{
//    cin >> n;
//    int t, m, p;
//
//    runs.insert({ -1, 1 }), runs.insert({ n, 1 });  // 哨兵
//
//    while (cin >> t >> m >> p, t || m || p)     
//    {
//        finish(t);  // 释放应该释放的内存
//        if (!give(t, m, p))     // 如果当前所需内存无法分配，进入等待队列
//        {
//            waits.push({ m, p });
//            cnt++;
//        }
//    }
//
//    finish(2e9);    // 释放所有内存，因为要计算最后使用完的时间
//
//    cout << tm << endl << cnt << endl;
//
//    return 0;
//}




// 156. 矩阵

// 二维字符串hash
// N*M的矩阵里找a*b的矩阵，将N*M里的可能a*b的矩阵hash起来，共（N-a+1)+(N-b+1)个
// 对于每个询问的矩阵，求其hash，在N*M里的hash进行查找

//#include <iostream>
//#include <algorithm>
//#include <unordered_set>
//
//using namespace std;
//
//typedef unsigned long long ULL;
//
//const int N = 1010, M = N * N, P = 131;
//
//int n, m, a, b;
//ULL hashv[N][N], p[M];
//char str[N];
//
//ULL calc(ULL f[], int l, int r)
//{
//    return f[r] - f[l - 1] * p[r - l + 1];
//}
//
//int main()
//{
//    scanf("%d%d%d%d", &n, &m, &a, &b);
//
//    // 计算每一位权值
//    p[0] = 1;
//    for (int i = 1; i <= n * m; i++) p[i] = p[i - 1] * P;
//
//    // 计算哈希值
//    for (int i = 1; i <= n; i++)
//    {
//        scanf("%s", str + 1);
//        for (int j = 1; j <= m; j++) hashv[i][j] = hashv[i][j - 1] * P + str[j] - '0';
//    }
//
//    unordered_set<ULL> S;
//    for (int i = b; i <= m; i++)    // 按列来做
//    {
//        int l = i - b + 1, r = i;   // 左右边界
//        ULL s = 0;
//        for (int j = 1; j <= n; j++)
//        {
//            s = s * p[b] + calc(hashv[j], l, r);
//            if (j - a > 0) s -= calc(hashv[j - a], l, r) * p[a * b];
//            if (j >= a) S.insert(s);
//        }
//    }
//
//    int Q;
//    scanf("%d", &Q);
//    while (Q--)
//    {
//        ULL s = 0;
//        for (int i = 0; i < a; i++)
//        {
//            scanf("%s", str);
//            for (int j = 0; j < b; j++) s = s * P + str[j] - '0';
//        }
//        if (S.count(s)) puts("1");
//        else puts("0");
//    }
//
//    return 0;
//}


// 157. 树形地铁系统

// 树的最小表示   
// 同构的树，最小表示都相同

//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//const int N = 3010;
//
//string dfs(string& seq, int& u) {
//    vector<string> seqs;
//    ++u;    // 走下一步，因为调用函数传进来的u是上一步的0
//    while (seq[u] == '0') seqs.push_back(dfs(seq, u));  // 还有儿子
//    ++u;    // 把往上走的标志过掉，即相当于函数返回，往上走
//
//    sort(seqs.begin(), seqs.end());
//    // 叶子节点需要包一层‘0’‘1’进行标识，所以不妨全部包一层
//    string res = "0";
//    for (auto s : seqs) res += s;
//    res += '1';
//    return res;
//}
//
//int main()
//{
//    int T;
//    cin >> T;
//    while (T--) {
//        string a, b;
//        cin >> a >> b;
//        a = '0' + a + '1';  // 将头节点上再加入一个节点，为了不处理边界
//        b = '0' + b + '1';
//        int ua = 0, ub = 0;
//        if (dfs(a, ua) == dfs(b, ub))
//            puts("same");
//        else
//            puts("different");
//    }
//    return 0;
//}



// 158. 项链

// 循环同构串的最小表示法
//
//#include <iostream>
//#include <cstring>
//using namespace std;
//
//const int N = 2000010;
//char t[N], q[N], s[N];
//
//void get_min(char str[]) {
//    int n = strlen(str);
//    // 拷贝双份
//    for (int i = 0; i <= 2 * n; ++i) t[i] = str[i % n ];
//    int i = 0, j = 1, k;
//    while (i < n && j < n) {
//        for (k = 0; k < n && t[i + k] == t[j + k]; ++k);    // 找不同
//        if (k == n) break; // 找完了，还没找到不同，break;
//        if (t[i + k] > t[j + k]) {
//            i = i + k + 1;
//            if (i == j)++i;
//        } else {
//            j = j + k + 1;
//            if (i == j) ++j;
//        }
//    }
//    k = min(i, j);
//    // 将最小表示复制会原串
//    for (int i = 0; i < n; ++i) str[i] = t[i + k];
//}
//
//int main()
//{
//    scanf("%s", s);
//    scanf("%s", q);
//
//    get_min(s);
//    get_min(q);
//    if (strcmp(s, q) == 0) {
//        printf("Yes\n%s\n",s);
//    } else {
//        printf("No");
//    }
//
//    return 0;
//}




// 159. 奶牛矩阵

// kmp求循环节长度
// 我们先求行方向上的循环节长度，由于每行的字符串可能都不同，所以无法使用kmp求多个字符串的公共循环节长度，
// 但是每行最多75个字符，可以暴力枚举循环节的长度，这个过程时间O(N*M*M) 大概5e7 ，可接受
// 对于列方向上的循环节长度，我么上一步以求得行的最小值width，所以我们就可以将一行w个字串看作一个字符，相等于求列上一条字符串的循环节长度height
// 有没有可能，我们选一个较大的width，会出现一个较小height呢，那是不可能的，
// 如果有一个较大w2，那么较小的w1肯定包含在内，那在行上进行字符串的匹配，w1长度匹配成功后，w1~w2的后续字符可能会失败，即w1的匹配难度要小于w2,h2必然>=h1

//#include <iostream>
//#include <algorithm>
//#include <string.h>
//
//using namespace std;
//
//const int N = 10010, M = 80;
//
//int n, m;
//char str[N][M];
//bool st[M];
//int ne[N];
//
//int main()
//{
//    cin >> n >> m;
//    memset(st, true, sizeof st);
//    for (int i = 1; i <= n; i++)    
//    {
//        scanf("%s", str[i]);
//        for (int j = 1; j <= m; j++)    // 枚举循环节的长度
//        {
//            if (st[j]) {    // 如果该长度失败过，跳过
//                for (int k = j; k < m; k += j)
//                {
//                    for (int u = 0; u < j && k + u < m; u++)
//                        if (str[i][u] != str[i][k + u])
//                        {
//                            st[j] = false;
//                            break;
//                        }
//                    if (!st[j]) break;
//                }
//            }
//            
//        }
//    }
//
//    int width;
//    for (int i = 1; i <= m; i++)
//        if (st[i])
//        {
//            width = i;
//            break;
//        }
//
//    for (int i = 1; i <= n; i++) str[i][width] = 0;
//
//    // kmp求循环节长度
//    for (int j = 0, i = 2; i <= n; i++)
//    {
//        while (j && strcmp(str[j + 1], str[i])) j = ne[j];
//        if (!strcmp(str[j + 1], str[i])) j++;
//        ne[i] = j;
//    }
//
//    int height = n - ne[n];
//
//    cout << width * height << endl;
//
//    return 0;
//}



// 160. 匹配统计

// kmp的匹配
// 思路:先对b求next数组，然后a和b进行匹配
// 首先，以i结尾的a串与b串的前缀的最大匹配长度是可以算的，在kmp的匹配过程中这个长度就是j(详细见代码），
// 那么以i结尾的a串与b串的长度ne[j]显然也是匹配的，那么建立f数组，f[i]含义：a与b匹配的长度至少是i的情况下的后缀个数
// 以i结尾的长度为j,ne[j],ne[ne[j]],..显然都是可以与b匹配的,那么f[[ne[j]]=f[ne[j]]+f[j],f[ne[ne[j]]]=f[ne[ne[j]]]+f[[ne[j]],...
// 即相当于一个拓扑序，那么我们可后往前做，即从大往小做，使得每一个都了存前驱节点的值。

//#include <iostream>
//#include <cstring>
//using namespace std;
//
//const int N = 200010;
//char a[N], b[N];
//int ne[N], f[N];    //f[i]含义：a与b匹配的长度至少是i的情况下的后缀个数
//int n, m, q;
//
//int main()
//{
//    cin >> n >> m >> q;
//    scanf("%s%s", a + 1, b + 1);
//
//    for (int i = 2, j = 0; i <= m; ++i) {
//        while (j && b[i] != b[j + 1]) j = ne[j];
//        if (b[i] == b[j + 1])++j;
//        ne[i] = j;
//    }
//
//    for (int i = 1, j = 0; i <= n; ++i) {
//        while (j && a[i] != b[j + 1]) j = ne[j];
//        if (a[i] == b[j + 1]) ++j;
//        // 对于每一个a[i]结尾的后缀都能求出b的前缀匹配的长度就是j 
//        ++f[j];
//    }
//
//    // 从大往小做，拓扑序
//    for (int i = m; i; --i)f[ne[i]] += f[i];
//
//    while (q--) {
//        int x;
//        cin >> x;
//        cout << f[x] - f[x + 1] << endl;    // 最少是x的减去最少是x+1的就是匹配长度为x的个数
//    }
//    return 0;
//}
//时间O（N+M+Q)


// 或

// 字符串哈希+二分
// 时间O(NlogN+M+Q)

// 将a和b进行字符串hash,二分匹配长度

//#include <iostream>
//using namespace std;
//
//typedef unsigned long long ULL;
//
//const int N = 200010, base = 131;
//
//char a[N], b[N];
//int n, m, q;
//ULL ha[N], hb[N], p[N];
//int cnt[N];
//
//ULL get(ULL h[], int l, int r) {
//    return h[r] - h[l - 1] * p[r - l + 1];
//}
//int main()
//{
//    cin >> n >> m >> q;
//    scanf("%s%s", a + 1, b + 1);
//    p[0] = 1;
//    // 字符串hash
//    for (int i = 1; i <= max(n, m); ++i) p[i] = p[i - 1] * base;
//    for (int i = 1; i <= n; ++i) ha[i] = ha[i - 1] * base + a[i];
//    for (int i = 1; i <= m; ++i) hb[i] = hb[i - 1] * base + b[i];
//
//    // 预处理匹配长度，二分加速,求a的每一个后缀和b匹配的最大长度
//    for (int i = 1; i <= n; ++i) {  // 枚举每一个后缀的起点
//        // 二分匹配的长度
//        int l = 0, r = min(n - i + 1, m);
//        while (l < r) {
//            int mid = l + r + 1 >> 1;
//            if (get(ha, i, i+mid-1) == get(hb, 1, mid)) {
//                l = mid;
//            } else {
//                r = mid - 1;
//            }
//        }
//        ++cnt[l];   // 匹配长度恰好为l个数加1
//    }
//
//    while (q--) {
//        int x;
//        cin >> x;
//        cout << cnt[x] << endl;
//    }
//    return 0;
//}
//



// 161. 电话列表

//// 前缀树
//
//#include <iostream>
//#include <cstring>
//using namespace std;
//
//const int N = 1000100;
//int trie[N][10], tot = 1;
//bool en[N];
//char s[15];
//bool insert(char str[]) {
//    int len = strlen(str), p = 1;
//    for (int i = 0; i < len; ++i) {
//        int ch = str[i] - '0';
//        if (trie[p][ch] == 0) trie[p][ch] = ++tot;
//        p = trie[p][ch];
//        if (en[p]) return true; //有前缀，true
//    }
//    en[p] = true;
//
//    for (int i = 0; i < 10; ++i)    // 它后面还有路，说明它是个前缀
//        if (trie[p][i]) return true;
//    return false;
//}
//int main()
//{
//    int T;
//    cin >> T;
//    while (T--) {
//        memset(en, 0, sizeof en);
//        memset(trie, 0, sizeof trie);
//        tot = 1;
//        int n;
//        bool yes = true;
//        cin >> n;
//        while (n--) {
//            scanf("%s", s);
//            if (insert(s))
//                yes = false;
//        }
//        cout << (yes ? "YES" : "NO") << endl;
//    }
//    return 0;
//}
//
//// 或
//#include <cstring>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//const int N = 100010;
//
//int n;
//int son[N][10], idx;
//bool f[N];
//
//bool insert(char* str)
//{
//    int p = 0;
//    bool has_new = false;
//    bool has_found = false;
//    for (int i = 0; str[i]; i++)
//    {
//        int u = str[i] - '0';
//        if (!son[p][u])
//        {
//            son[p][u] = ++idx;
//            has_new = true;     // 产生过新的路径的话，目前必然不是个前缀
//        }
//        p = son[p][u];
//        if (f[p]) has_found = true;     // 这个点被人结尾过，是当前字符串的前缀
//    }
//
//    f[p] = true;
//
//    return has_new && !has_found;
//}
//
//int main()
//{
//    int T;
//    cin >> T;
//    while (T--)
//    {
//        cin >> n;
//        memset(son, 0, sizeof son);
//        memset(f, false, sizeof f);
//        idx = 0;
//
//        bool res = true;
//
//        char str[20];
//        for (int i = 0; i < n; i++)
//        {
//            cin >> str;
//            if (!insert(str)) res = false;
//        }
//
//        if (res) puts("YES");
//        else puts("NO");
//    }
//
//    return 0;
//}


// 162. 黑盒子

// 对顶堆
// 大根堆放前i个小的，其余放小根堆

//
//#include <iostream>
//#include <queue>
//#include <vector>
//using namespace std;
//
//const int N = 30010;
//int n, m;
//int add[N], g[N];
//
//int main()
//{
//    cin >> n >> m;
//    for (int i = 0; i < n; ++i) cin >> add[i];
//    for (int i = 0; i < m; ++i) cin >> g[i];
//
//    priority_queue<int, vector<int>, greater<int>> small;
//    priority_queue<int> big;
//    
//    big.push(add[0]);
//    for (int i = 0, j = 1; i < m; ++i) {
//        for (; j < g[i]; ++j) {
//            if (add[j] < big.top())
//                big.push(add[j]);
//            else
//                small.push(add[j]);
//        }
//        // 将大根堆多余放到小根堆中去
//        while (big.size() > i + 1) {
//            small.push(big.top());
//            big.pop();
//        }
//        // 如果大根堆个数不够i+1个，从小根堆取出放入
//        while (big.size() < i + 1) {
//            big.push(small.top());
//            small.pop();
//        }
//        cout << big.top() << endl;
//
//    }
//
//    return 0;
//}
//
//
//// 或
//
//#include <iostream>
//#include <algorithm>
//#include <queue>
//#include <vector>
//
//using namespace std;
//
//const int N = 30010;
//
//int n, m;
//int a[N], b[N];
//
//int main()
//{
//    cin >> n >> m;
//    for (int i = 1; i <= n; i++) cin >> a[i];
//    for (int i = 1; i <= m; i++) cin >> b[i];
//
//    priority_queue<int> big;
//    priority_queue<int, vector<int>, greater<int>> small;
//
//    int k = 0;
//    for (int i = 1, j = 1; i <= m; i++)
//    {
//        while (j <= b[i])
//        {
//            if (big.empty() || a[j] >= big.top()) small.push(a[j]);
//            else
//            {
//                // 维持大根堆大小不变
//                small.push(big.top());
//                big.pop();
//                big.push(a[j]);
//            }
//            j++;
//        }
//        // 只在最后从小根堆拿一个放入大根堆
//        big.push(small.top());
//        small.pop();
//        cout << big.top() << endl;
//    }
//    return 0;
//}



// 163. 生日礼物


// 思路：将连续的正数和负数看作一个段，那么正段和负段一定是连续交替的，记正段数据cnt,
// 若m>=cnt, 直接选这cnt个正段即可
// 若m<cnt,我们也先选这cnt个正段，在减去cnt-m段即可
//      减少一个段有两种方法，1）直接减去一个正段 2）在连续的两个不相交的正段中间加上一个负段，这样就合成了一个段
//      我们给负段的值记为绝对值，这样就也就变为了中间减去一个负端，正段和负段就统一了
//      这样我们的问题就变为了147. 数据备份的类似问题，选取k个不相邻的连续线段使和最小（保证元素大于等于0），我们这里用的绝对值，满足条件
// 所以问题就变为了选取k个不相邻的连续线段使和最小，使用双向链表+小根堆解决，对于删除一个段,可以删除其自身和左右两个段，左右两个段加到此段上，再入堆
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 100010;

int n, m;
int a[N], l[N], r[N];
bool st[N];

void remove(int p)
{
    // 从链表中删去

    l[r[p]] = l[p];
    r[l[p]] = r[p];

    // 从heap里删去
    st[p] = true;
}

int main()
{
    cin >> n >> m;

    int k = 1;
    // 将连续的正数和负数记做一个段
    for (int i = 0; i < n; i++)     
    {
        int x;
        cin >> x;
        if ((long long)a[k] * x < 0) a[++k] = x;    //小于0，说明前后符号相异，常数了新的段
        else a[k] += x;
    }

    n = k;  // n记为段数

    int cnt = 0, res = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] > 0)
        {
            cnt++;      // 记正数段个数
            res += a[i];    // 正数段累加和
        }

    priority_queue<PII, vector<PII>, greater<PII>> heap;    // 小根堆

    for (int i = 1; i <= n; i++)
    {
        l[i] = i - 1;               // 双向链表建立关系
        r[i] = i + 1;

        heap.push({ abs(a[i]), i });    // 同时插入堆
    }

    while (cnt > m)
    {
        while (st[heap.top().second]) heap.pop();   // 弹出已经认为删除了的段

        auto t = heap.top();
        heap.pop();

        int v = t.first, p = t.second;

        if (l[p] != 0 && r[p] != n + 1 || a[p] > 0)     // 边界不能负数，边界是负数的话，左右两边就合并不了了
        {
            cnt--;
            res -= v;   

            int left = l[p], right = r[p];
            a[p] += a[left] + a[right];

            heap.push({ abs(a[p]), p });    // 新段入段堆
            remove(left);   // 删除左右段
            remove(right);
        }
    }

    cout << res << endl;

    return 0;
}
