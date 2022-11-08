

// 164. 可达性统计

// 利用拓扑排序的先后关系，边（x,y)在拓扑序中x出现在y的前面
// 所以可以利用拓扑序的倒序进行计算，f[x]=1+f[x1]+f[x2]+f[x3]...其中xi是x的终点
// 可以利用bitset进行位压缩，bitset<N> f[N]，这样我们可以使用一个N位二进制存储每个f(x),
// 其中第i位是1表示x能到i，0表示不能到，这样一来，对若干个集合求并，即相当于求或运算
// 时间O(N+M)/32;

#include <iostream>
#include <bitset>
#include <algorithm>
#include <queue>
using namespace std;


const int N = 30100;
int n, m;
int ver[N], head[N], Next[N],deg[N];
int tot,cnt;
int seq[N],res[N];
bitset<N> f[N];

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
    deg[y]++;
}

void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 0)
            q.push(i);
    }
    while (q.size()) {
        int x = q.front(); q.pop();
        seq[++cnt] = x;
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (--deg[y] == 0)
                q.push(y);
        }
    }
    
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
    }
    topsort();
    for (int i = cnt; i; --i) {
        int j = seq[i];
        f[j][j] = 1;
        for (int p = head[j]; p; p = Next[p]) {
            f[j] |= f[ver[p]];
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", f[i].count());
    }

    return 0;
}


// 165. 小猫爬山

 //dfs(now, cnt) 表示 处理第now只小猫时，目前已经租了cnt个缆车
 //两个优化，1.从体重大小猫排在前面，减少搜索树的分支，因为重的猫“难”运输，能选择的少
 //         2. 进入递归后，先判断当前的缆车数是否大于等于目前已获得的可能的答案，若是即刻马上回溯return,

#include <algorithm>
#include <iostream>
using namespace std;

const int N = 20;
int n, c;
int w[N], cab[N];
int res;
// 处理第now只小猫时，目前已经租了cnt个缆车
void dfs(int now, int cnt) {
    if (cnt >= res) return;
    if (now == n + 1) {
        res = min(res, cnt);
        return;
    }
    for (int i = 1; i <= cnt; ++i) {
        if (cab[i] + w[now] <= c) {
            cab[i] += w[now];
            dfs(now + 1, cnt);
            cab[i] -= w[now];
        }
    }
    cab[cnt + 1] = w[now];
    dfs(now + 1, cnt + 1);
    cab[cnt + 1] = 0;
}

int main()
{
    cin >> n >> c;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    sort(w + 1, w + 1 + n, greater<int>());
    res = n;
    dfs(1, 0);
    cout << res << endl;
    return 0;
}



// 166. 数独



#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 9;
string s, res;
int row[N], col[N], cell[3][3];
int bitpos[1 << N], ones[1 << N];
int cnt;
inline int lowbit(int x) {
    return x & (-x);
}
void init() {
    res.clear();
    for (int i = 0; i < N; ++i) {
        row[i] = (1 << N) - 1;
        col[i] = (1 << N) - 1;
    }
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cell[i][j] = (1 << N) - 1;
}
void dfs() {
    if (res.size()) return;
    if (cnt == 0) {
        res = s;
        return;
    }
    int x = -1, y = -1;
    int mi = 10;
    // 找出选择最少的点
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s[i * N + j] != '.') continue;
            int rest = row[i] & col[j] & cell[i / 3][j / 3];
            int t = ones[rest];

            if (t < mi) {
                x = i;
                y = j;
                mi = t;
            }
        }
    }

    --cnt;
    int t = row[x] & col[y] & cell[x / 3][y / 3];
    for (int i = t; i; i -= lowbit(i)) {
        int bit = bitpos[lowbit(i)];
        s[x * N + y] = '1' + bit;
        row[x] &= ~(1 << bit);
        col[y] &= ~(1 << bit);
        cell[x / 3][y / 3] &= ~(1 << bit);
        dfs();
        row[x] |= 1 << bit;
        col[y] |= 1 << bit;
        cell[x / 3][y / 3] |= 1 << bit;
        s[x * N + y] = '.';
    }
    ++cnt;


}
int main()
{
    for (int i = 0; i <= 9; ++i)
        bitpos[1 << i] = i;
    for (int i = 0; i < 1 << N; ++i) {
        int s = 0;
        for (int j = i; j; j -= lowbit(j)) ++s;
        ones[i] = s;
    }
    while (cin >> s && s != "end") {
        init();
        cnt = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (s[i * N + j] != '.') {
                    int t = s[i * N + j] - '1';
                    row[i] &= ~(1 << t);
                    col[j] &= ~(1 << t);
                    cell[i / 3][j / 3] &= ~(1 << t);
                } else {
                    ++cnt;
                }
            }
        }
        dfs();
        cout << res << endl;
    }
    return 0;
}


// 简洁化

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 9;
string s, res;
int row[N], col[N], cell[3][3];
int bitpos[1 << N],ones[1<<N];      // bitpos[i]时计算i的二级制位上的1在第几位，onee[i]表示i二机制一共几位1
int cnt;
inline int lowbit(int x) {
    return x & (-x);
}
void filp(int i, int j,int t) {
    row[i] ^= 1 << t;
    col[j] ^= 1 << t;
    cell[i / 3][j / 3] ^= 1 << t;
}
void init() {
    res.clear();
    for (int i = 0; i < N; ++i) 
        cell[i/3][i%3]=row[i]=col[i]= (1 << N) - 1;
}
inline int getbits(int i, int j) {
    return  row[i] & col[j] & cell[i / 3][j / 3];
}
void dfs() {
    if (res.size()) return;
    if (cnt == 0) {
        res = s;
        return;
    }
    int x=-1, y=-1;
    int mi = 10;
    // 找出选择最少的点
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s[i * N + j] != '.') continue;
            int t = ones[getbits(i,j)];
            if (t < mi) {
                x = i;
                y = j;
                mi = t;
            }
        }
    }
      
    --cnt;
    for (int i = getbits(x,y); i; i -= lowbit(i)) {
        int bit = bitpos[lowbit(i)];
        s[x * N + y] = '1' + bit;
        filp(x, y, bit);
        dfs();
        filp(x, y, bit);
        s[x * N + y] = '.';
    }
    ++cnt;


}
int main()
{
    for (int i = 0; i <= 9; ++i)
        bitpos[1 << i] = i;
    for (int i = 0; i < 1 << N; ++i) {
        int s = 0;
        for (int j = i; j; j -= lowbit(j)) ++s;
        ones[i] = s;
    }
    while (cin >> s &&  s != "end") {
        init();
        cnt = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (s[i * N + j] != '.') {
                    int t = s[i * N + j] - '1';
                    filp(i, j, t);
                } else {
                    ++cnt;
                }
            }
        }
        dfs();
        cout << res << endl;
    }
    return 0;
}


// 或，将dfs返回值改为bool
// 将string改为char可以块一些

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 9;
char s[100];
int row[N], col[N], cell[3][3];
int bitpos[1 << N], ones[1 << N];      // bitpos[i]时计算i的二级制位上的1在第几位，onee[i]表示i二机制一共几位1
inline int lowbit(int x) {
    return x & (-x);
}
void filp(int i, int j, int t) {
    row[i] ^= 1 << t;
    col[j] ^= 1 << t;
    cell[i / 3][j / 3] ^= 1 << t;
}
void init() {
    for (int i = 0; i < N; ++i)
        cell[i / 3][i % 3] = row[i] = col[i] = (1 << N) - 1;
}
inline int getbits(int i, int j) {
    return  row[i] & col[j] & cell[i / 3][j / 3];
}
bool dfs(int cnt) {
    
    if (cnt == 0) return true;
    int x = -1, y = -1;
    int mi = 10;
    // 找出选择最少的点
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (s[i * N + j] != '.') continue;
            int t = ones[getbits(i, j)];
            if (t < mi) {
                x = i;
                y = j;
                mi = t;
            }
        }
    }

    for (int i = getbits(x, y); i; i -= lowbit(i)) {
        int bit = bitpos[lowbit(i)];
        s[x * N + y] = '1' + bit;
        filp(x, y, bit);
        if (dfs(cnt-1)) return true;
        filp(x, y, bit);
        s[x * N + y] = '.';
    }
    return false;

}
int main()
{
    for (int i = 0; i <= 9; ++i)
        bitpos[1 << i] = i;
    for (int i = 0; i < 1 << N; ++i) {
        int s = 0;
        for (int j = i; j; j -= lowbit(j)) ++s;
        ones[i] = s;
    }
    while (cin >> s , s[0] != 'e') {
        init();
        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (s[i * N + j] != '.') {
                    int t = s[i * N + j] - '1';
                    filp(i, j, t);
                } else {
                    ++cnt;
                }
            }
        }
        dfs(cnt);
        cout << s << endl;
    }
    return 0;
}