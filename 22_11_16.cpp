
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


// AcWing 180. 排书

// IDA*算法
// 把估计函数与迭代加深的DFS算法结合，形成IDA*算法
// 以迭代加深DFS的框架为基础，把原来简单的深度的限制加强为:若当前深度+未来估计步数 > 深度限制，则立即从当前分支回溯

// 在目标状态下，第i本书后面是第i+1本书，称i+1是i的正确后续
// 在某个状态下，错误后续总个数为tot,在最理想的情况下，每次操作都能把某3个错误后续全部改对，消除所有错误后续的操作次数也至少需要tot/3上取整次
//      所有可以将这个值作为每个状态的估计函数

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 15;
int seq[N];
int tmp[5][N];
int n;

int f() {
    int tot = 0;
    for (int i = 0; i < n - 1; ++i)
        if (seq[i] + 1 != seq[i + 1])
            ++tot;
    return (tot + 2) / 3;
}
bool check() {
    for (int i = 0; i < n; ++i)
        if (seq[i]!=i+1 ) return false;
    return true;
}
bool dfs(int depth, int limit) {
    if (depth + f() > limit) return false;
    if (check()) return true;

    for (int len = 1; len < n; ++len) {       // 长度
        for (int l = 0; l + len - 1 < n; ++l) {     // 左端点
            int r = l + len - 1;        // 右端点
            for (int i = r + 1; i < n; ++i) {       // 插入的位置
                memcpy(tmp[depth], seq, sizeof seq);
                int x, y;
                for (x = r + 1, y = l; x <= i; ++x, ++y) seq[y] = tmp[depth][x];
                for (x = l; x <= r; ++x, ++y) seq[y] = tmp[depth][x];
                if (dfs(depth + 1, limit)) return true;
                memcpy(seq, tmp[depth], sizeof seq);

            }
        }
    }
    return false;
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> seq[i];
        int depth = 0;
        while (depth < 5 && !dfs(0, depth)) ++depth;
        if (depth < 5)
            cout << depth << endl;
        else
            cout << "5 or more" << endl;

    }
    return 0;
}