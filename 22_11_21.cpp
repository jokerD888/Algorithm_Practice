
// 188. 武士风度的牛

// 普通的宽搜

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
const int N = 160;
int n, m;
char s[N][N];
int dist[N][N];

PII st, ed;
int bfs() {
    memset(dist, -1, sizeof dist);
    const int dx[]{ -2,-2, -1,1,2,2,1,-1 }, dy[]{ -1,1,2,2,1,-1,-2,-2 };

    queue<PII> q;
    q.push(st);
    dist[st.first][st.second] = 0;

    while (q.size()) {
        auto t = q.front(); q.pop();
        int x = t.first, y = t.second;
        if (t == ed) return dist[x][y];

        for (int i = 0; i < 8; ++i) {
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < n && b >= 0 && b < m && s[a][b] != '*' && dist[a][b] == -1) {
                dist[a][b] = dist[x][y] + 1;
                q.push({ a,b });
            }
        }

    }
    return -1;
}
int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (s[i][j] == 'K') st = { i,j };
            else if (s[i][j] == 'H') ed = { i,j };

    cout << bfs();
    return 0;
}



// 189. 乳草的入侵

// 普通的bfs,但注意！！！：题目中的坐标是笛卡尔坐标，注意输入时的x和y

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
const int N = 110;
int n, m;
char s[N][N];
PII st;

int dfs() {

    queue<PII> q;
    q.push(st);
    s[st.first][st.second] = '*';
    const int dx[]{ -1,-1,-1,0,1,1,1,0 }, dy[]{ -1,0,1,1,1,0,-1,-1 };

    int t = 0;
    while (q.size()) {
        int size = q.size();
        ++t;
        while (size--) {
            auto t = q.front(); q.pop();
            int x = t.first, y = t.second;
            for (int i = 0; i < 8; ++i) {
                int a = x + dx[i], b = y + dy[i];
                if (a >= 0 && a < n && b >= 0 && b < m && s[a][b] == '.') {
                    s[a][b] = '*';
                    q.push({ a,b });
                }
            }
        }
    }
    return t - 1;
}
int main()
{
    cin >> m >> n;
    cin >> st.second >> st.first;
    for (int i = 0; i < n; ++i) cin >> s[i];
    --st.first, --st.second;

    cout << dfs();
    return 0;
}

