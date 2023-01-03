// 284. 金字塔

// 一棵树的每棵子树都对应着这棵树 DFS 序中的一个区间
// 本题中记录的序列虽然不是 DFS 序，但仍然满足这条性质。因此，这道题目在“树形结构”与“字符串”之间通过“子树”和“区间”建立了联系。
// 不难想到用 F[L,r] 表示子串 S[l~r] 对应着多少种可能的金字塔结构(树形结构)。
//     我们的决策就是区间上最后一个树开始的位置

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;
const int N = 310,MOD=1e9;

string str;
int f[N][N];

int main()
{   
    cin >> str;
    int n = str.size();
    if (n % 2 == 0) puts("0");     // 因为n个节点，n-1个边，每个边一进一出各打印一个点，再加上最开始的根节点，所以长度为2*n-1,一定为奇数
    else {
        for (int len = 1; len <= n; len += 2)      // 长度一定是奇数
            for (int l = 0; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                if (len == 1) f[l][r] = 1;          
                else if(str[l]==str[r]) {               
                    for (int k = l; k < r; k += 2) {     
                        if (str[k] == str[l]) {
                            f[l][r] = (f[l][r] +(LL)f[l][k] * f[k + 1][r - 1]) % MOD;
                        }
                    }
                }
            }
        cout << f[0][n - 1] << endl;
    }
    return 0;
}

