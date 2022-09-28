// 01背包问题
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
int n, m;
int f[N][N];    // f[i][j] 定义：前i个物品，背包容量为j，所能拥有的最大收益
int v[N], w[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            f[i][j] = f[i - 1][j];
            if (j >= v[i])
                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
        }
    }

    cout << f[n][m] << endl;
    return 0;
}

// 滚动数组
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=1010;
int n,m;
int f[N];       // f[i]定义：容量为i的背包所能装下的最大价值
int v[N],w[N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i) cin>>v[i]>>w[i];

    for(int i=1;i<=n;++i){
        for(int j=m;j>=v[i];--j){       // 从后往前
            f[j]=max(f[j],f[j-v[i]]+w[i]);
        }
    }

    cout<<f[m]<<endl;
    return 0;
}


// 完全背包问题
#include <iostream>
using namespace std;

const int N = 1010;
int v[N], w[N];
int dp[N];  // dp[i] 表容量为i的背包所能装下的最大价值
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    for (int i = 1; i <= n; ++i)
        for (int j = v[i]; j <= m; ++j)
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);

    cout << dp[m];

    return 0;
}


// 多重背包问题 I
#include <iostream>
using namespace std;


const int N = 110;
int dp[N];
int main()
{
    int n, m;
    int v, w, s;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> v >> w >> s;
        for (int j = m; j >= v; --j)
            for (int k = 1; k <= s && k * v <= j; ++k)
                dp[j] = max(dp[j], dp[j - k * v] + k * w);
    }
    cout << dp[m];
    return 0;
}


// 多重背包问题 II
#include <iostream>
using namespace std;

#include <vector>

const int N = 2010;
int dp[N];
struct Good {
    int v, w;
};
int main()
{
    int n, m;
    cin >> n >> m;
    vector<Good> goods;
    for (int i = 0; i < n; ++i) {
        int v, w, s;
        cin >> v >> w >> s;
        // 二进制拆分，化为01背包问题
        for (int k = 1; k <= s; k *= 2) {
            s -= k;
            goods.push_back({ v * k,w * k });
        }
        if (s > 0) goods.push_back({ v * s,w * s });
    }
    for (auto good : goods) {
        for (int j = m; j >= good.v; --j) {
            dp[j] = max(dp[j], dp[j - good.v] + good.w);
        }
    }
    cout << dp[m];
    return 0;
}


// 二维费用的背包问题
#include <iostream>
using namespace std;

const int N = 1010;
int dp[N][N];

int main()
{
    int N, V, M;
    cin >> N >> V >> M;
    for (int i = 0; i < N; ++i) {
        int n, m, w;
        cin >> n >> m >> w;
        for (int j = V; j >= n; --j) {  // 体积
            for (int k = M; k >= m; --k) {  // 重量
                dp[j][k] = max(dp[j][k], dp[j - n][k - m] + w);
            }
        }
    }
    cout << dp[V][M];
    return 0;
}