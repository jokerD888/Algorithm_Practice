

// 178. 第K短路

// A*算法
// 关于估计函数优化搜索的顺序，进而更准确的找到最优路径
// 关于估计函数f, f(x)<=g(x) g(x)是点x到目标点的实际距离，即要求估计值不得大于实际值
// 题目要求第K短的路径，所以根据数学归纳法，某个点第K次出栈时，即为原点到该点距离的第K小值
// 所以我们可以使用一次dijkstra求出“反图”从目标点到其他点距离，作为A*算法中的估计值
// 随后进行A*算法，A*算法关于堆的调整是根据该点的实际值+该点估计值

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;
const int N = 1100, M = 20100;

struct node {
    int dd, d, u;
    bool operator<(const node& b)const {
        return dd > b.dd;
    }

};
int head[N], rh[N], e[M], ne[M], w[M], idx;  //rh是方向图
int n, m;
int S, T, K;
int dist[N];
int st[N];


void add(int h[], int x, int y, int z) {
    e[++idx] = y, w[idx] = z, ne[idx] = h[x], h[x] = idx;
}
void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({ 0,T });
    dist[T] = 0;

    while (q.size()) {
        auto t = q.top(); q.pop();
        int distan = t.first, u = t.second;
        if (st[u]) continue;
        st[u] = true;

        for (int i = rh[u]; i; i = ne[i]) {
            int y = e[i], z = w[i];
            if (dist[y] > distan + z) {
                dist[y] = distan + z;
                q.push({ dist[y],y });
            }
        }
    }
}
int AStart() {
    memset(st, 0, sizeof st);
    priority_queue<node> q;
    q.push({ dist[S], 0,S });

    while (q.size()) {
        auto t = q.top(); q.pop();

        if (st[t.u] >= K) continue;
        ++st[t.u];
        if (st[t.u] == K && t.u == T) return t.d;


        for (int i = head[t.u]; i; i = ne[i]) {
            int y = e[i];
            if (st[y] < K)
                q.push({ t.d + w[i] + dist[y],t.d + w[i],y });
        }
    }
    return -1;
}
int main()
{
    cin >> n >> m;
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
        add(head, x, y, z);          // ！！！！！！！！！！！注意这里需要建反图
        add(rh, y, x, z);
    }
    cin >> S >> T >> K;
    if (S == T) ++K;        // 注意： 每条最短路中至少要包含一条边。
    if (m == 0) cout << -1 << endl;
    else {
        dijkstra();
        cout << AStart();
    }
    return 0;
}


// 179. 八数码
// 奇数码，给你两个游戏局面，计算两个局面是否可达
// 标准n*n奇数码：可达条件->当且仅当逆序对个数奇偶性相同
//  n为偶数，可达条件-> 当且仅当逆序对数之差 和 两个局面下空格所在行数之差 的奇偶性相同
// 对于n*m， 根据列可以符号上面的两个条件之一

// 本题的A*中的估计值可以用每个点到其应放入的位置的曼哈顿距离来充当

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <string>
#include <cmath>
#include <unordered_map>
using namespace std;

int f(string s) {
    int res = 0;
    for (int i = 0; i < 9; ++i) {
        if (s[i] != 'x') {
            int t = s[i] - '1';
            res += abs(i / 3 - t / 3) + abs(i % 3 - t % 3);
        }
    }
    return res;
}

string bfs(string start) {

    const int dx[]{ -1,0,1,0 }, dy[]{ 0,1,0,-1 };
    const char* op = "urdl";
    string end = "12345678x";
    unordered_map<string, int> dist;
    unordered_map<string, bool> st;
    unordered_map<string, pair<string, char>> prev;
    priority_queue <pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> q;

    q.push({ f(start),start });
    dist[start] = 0;

    while (q.size()) {
        auto t = q.top(); q.pop();

        string state = t.second;
        if (state == end) break;

        if (st[state]) continue;
        st[state] = true;

        int step = dist[state];
        int x, y;
        for (int i = 0; i < state.size(); ++i)
            if (state[i] == 'x') {
                x = i / 3, y = i % 3;
                break;
            }

        string source = state;
        for (int i = 0; i < 4; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && b >= 0 && a < 3 && b < 3) {
                swap(state[a * 3 + b], state[x * 3 + y]);
                if (!dist.count(state) || dist[state] > step + 1) {
                    dist[state] = step + 1;
                    prev[state] = { source,op[i] };
                    q.push({ dist[state] + f(state),state });
                }
                swap(state[a * 3 + b], state[x * 3 + y]);       // 回溯

            }
        }

    }
    string res;
    while (end != start) {
        res += prev[end].second;
        end = prev[end].first;
    }
    reverse(res.begin(), res.end());
    return res;

}

int main()
{
    string s, c, seq;
    while (cin >> c) {
        s += c;
        if (c != "x") seq += c;
    }
    int t = 0;
    for (int i = 0; i < seq.size(); ++i)
        for (int j = i + 1; j < seq.size(); ++j)
            if (seq[i] > seq[j]) ++t;

    if (t & 1) cout << "unsolvable" << endl;
    else cout << bfs(s) << endl;
    return 0;
}
