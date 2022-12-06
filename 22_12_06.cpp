
// 237. 程序自动分析

// 并查集，由于数据范围太大，做离散化。先处理相等关系，将其合并，再处理不等关系，若不等关系中，两者处于同一集合，false

#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100010,M=200010;
int num[M],fa[M],cnt;
int a[N], b[N];
bool st[N];
// 找到x在fa中的下标
int cast(int x) {
    return lower_bound(num, num + cnt, x)-num;
}
int get(int x) {
    if (x != fa[x])
        fa[x] = get(fa[x]);
    return fa[x];
}
int merge(int x, int y) {
    fa[get(x)] = get(y);
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        cnt = 0;
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a[i] >> b[i] >> st[i];
            num[cnt++] = a[i], num[cnt++] = b[i];
        }
        // 去重
        sort(num, num + cnt);
        cnt = unique(num, num + cnt) - num;
        
        for (int i = 0; i < cnt; ++i) fa[i] = i;

        bool success = true;

        /*for (int i = 0; i < n; ++i) {
            int x = cast(a[i]), y = cast(b[i]);
            int x1 = get(x), x2 = get(y);
            if (st[i]) {
                merge(x, y);
            } else {
                if (x1 == x2) {
                    success = false;
                    break;
                }
            }
        }*/
        // 烫烫！！ 注意不能向上面一样边遍历边构建，需要先将所有相等的合并，再检查不相等的，若不相等得在一个集合，false
        for (int i = 0; i < n; ++i) 
            if (st[i]) 
                merge(cast(a[i]), cast(b[i]));
            
       
        for (int i = 0; i < n; ++i) {
            if (!st[i]) {
                int x = get(cast(a[i])), y = get(cast(b[i]));
                if (x == y) {
                    success = false;
                    break;
                }
            }
        }

        if (success) cout << "YES" << endl;
        else cout << "NO" << endl;


    }
    return 0;
}



// 238. 银河英雄传说

// 带边权并查集
// 当接收到一个Cxy指令时，分别执行get(x) 和get(y)完成查询和路径压缩。若二者的返回值相同，则说明x和y处于同一列中。因为x和y此时都已经指向
// 树根，所以d[x]保存了位于x之前的战舰数量，d[y] 保存了位于y之前的战舰数量。二者之差的绝对值再减1, 就是x和y之间间隔的战舰数量。

// 当接收到一个Mxy指令时，把x的树根作为y的树根的子节点，连接的新边的权值应该设为合并之前集合y的大小(根据题意，集合y中的全部战舰都排在集
// 合x之前)。因此，我们还需要一个size 数组在每个树根上记录集合大小

#include <iostream>
using namespace std;

const int N = 300010;
int fa[N], d[N],sz[N];

int get(int x) {
    if (x == fa[x]) return x;
    int root = get(fa[x]);
    d[x] += d[fa[x]];
    return fa[x] = root;
}
void merge(int x, int y) {
    x = get(x), y = get(y);
    fa[x] = y, d[x] = sz[y];
    sz[y] += sz[x];
}

int main()
{
    int n;
    cin >> n;
    
    for (int i = 0; i < N; ++i) fa[i] = i,sz[i]=1;

    char opr[2];
    int a, b;
    for (int i = 0; i < n; ++i) {
        cin >> opr >> a >> b;
        int x = get(a), y = get(b);
        if (opr[0] == 'M') {
            if(x!=y)
                merge(a, b);
        } else {
            if (x == y) {
                cout << max(abs(d[a] - d[b])-1,0) << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}