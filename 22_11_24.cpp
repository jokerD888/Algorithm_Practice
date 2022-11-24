

// 190. 字串变换

// 迭代加深，超时，过一半用例，时间最多每层最少N个分支，最深10层，N^10,N是每层可以进行转换的个数
// 字符串最长20个，最多可变换20个字符串，共6组规则，所以最高是120^10,导致超时


#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 22;

string a, b;
string tfa[7], tfb[7];
int n;
int cnt = 0;
bool dfs(int depth, string s) {
    if (++cnt <= 10000) return false;

    if (s == b) return true;
    if (!depth) return false;

    for (int i = 0; i < n; ++i) {   // 枚举每一种转化规则
        int pos, t = 0;;
        while (pos = s.find(tfa[i], t++), pos != s.npos) {
            int len = tfa[i].size();
            string ss = s.substr(0, pos) + tfb[i] + s.substr(pos + len);
            if (dfs(depth - 1, ss)) return true;
        }
    }

    return false;
}
int main()
{
    cin >> a >> b;
    while (cin >> tfa[n] >> tfb[n])++n;
    int depth = 0;
    while (depth <= 10 && !dfs(depth, a)) ++depth;
    if (depth <= 10) cout << depth << endl;
    else cout << "NO ANSWER!";
    return 0;
}


// 普通bfs,加上计数操作即可AC,当搜索个数达到一定数量，直接判否


#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
using namespace std;

typedef pair<string, int> PSI;
const int N = 10;
int cnt;
string a, b, from[N], to[N];
unordered_map<string, bool> exist;

int bfs() {
    int res = -1, cal = 0;
    if (a == b) return 0;
    queue<PSI> q;
    q.push({ a,0 });
    exist[a] = true;
    while (q.size() && res == -1 && ++cal <= 10000) {
        auto t = q.front();
        q.pop();
        a = t.first;
        if (t.second >= 10) break;
        for (int i = 0; i < cnt; ++i) {
            for (int st = 0; st + from[i].size() - 1 < a.size(); ++st) {
                bool success = true;
                for (int j = 0; j < from[i].size(); ++j) {
                    if (a[st + j] != from[i][j]) {
                        success = false;
                        break;
                    }
                }
                if (!success) continue;
                string c = a;
                a.replace(a.begin() + st, a.begin() + st + from[i].size(), to[i]);
                if (!exist.count(a)) {
                    exist[a] = true;
                    q.push({ a,t.second + 1 });
                    if (a == b) {
                        res = t.second + 1;
                        break;
                    }
                }
                a = c;
            }
        }
    }
    return res;
}

int main()
{
    cin >> a >> b;
    while (cin >> from[cnt] >> to[cnt]) ++cnt;
    int res = bfs();
    if (res == -1)
        cout << "NO ANSWER!" << endl;
    else
        cout << res << endl;
    return 0;
}


// 双向搜索，使得搜索空间大幅减小，k^5,k是每层的分支数


#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <queue>
using namespace std;

const int N = 6;
int n;
string A, B;
string a[N], b[N];

int extend(queue<string>& q, unordered_map<string, int>& da, unordered_map<string, int>& db,
    string a[N], string b[N])
{
    int d = da[q.front()];  // 取出对头深度
    while (q.size() && da[q.front()] == d) {    // 搜索完d深度的空间
        auto t = q.front();
        q.pop();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < t.size(); ++j) {
                if (t.substr(j, a[i].size()) == a[i]) {
                    string r = t.substr(0, j) + b[i] + t.substr(j + a[i].size());
                    if (db.count(r)) return da[t] + db[r] + 1;  // db中有r的记录，返回深度只和
                    if (da.count(r)) continue;      // r出现过
                    da[r] = da[t] + 1;
                    q.push(r);
                }
            }
        }
    }
    return 11;

}
int bfs() {
    if (A == B) return 0;
    queue<string> qa, qb;
    unordered_map<string, int> da, db;

    qa.push(A); qb.push(B);
    da[A] = db[B] = 0;

    int step = 0;
    while (qa.size() && qb.size()) {
        int t;
        if (qa.size() < qb.size()) t = extend(qa, da, db, a, b);
        else t = extend(qb, db, da, b, a);

        if (t <= 10) return t;
        if (++step == 10) return -1;
    }
    return -1;
}

int main()
{
    cin >> A >> B;
    while (cin >> a[n] >> b[n]) ++n;

    int t = bfs();
    if (t == -1) puts("NO ANSWER!");
    else cout << t << endl;
    return 0;
}




