
//92. 递归实现指数型枚举

//// 思路：依次递归每个点，分要和不要两个分支
//#include <iostream>
//using namespace std;
//
//const int N = 20;
//int n;
//bool st[N];
//void dfs(int u) {
//	if (u > n) {
//		for (int i = 1; i <= n; ++i)
//			if (st[i])
//				printf("%d ",i);
//		printf("\n");
//		return;
//	}
//	st[u] = true;	// 选择当前点
//	dfs(u + 1);
//
//	st[u] = false;	// 不选择当前点
//	dfs(u + 1);
//}
//int main()
//{
//	scanf("%d", &n);
//	dfs(1);
//	return 0;
//}
//
//



// 93. 递归实现组合型枚举

// C(n,m) 从n个数中任取m个 C(n,m)=n!/m!*(n-m)!
// 思路：从前往后，取数字，每个数分取和不取,但途中rest为0，终止打印，当走完了，rest还有剩下，直接return	，递归深度最多为n层
//#include <iostream>
//using namespace std;
//const int N = 30;
//
//bool st[N];
//int n,m;
//void dfs(int u, int rest) {
//	if (u > n && rest > 0)
//		return;
//	if (rest == 0) {
//		for (int i = 1; i <= n; ++i)
//			if (st[i])
//				printf("%d ", i);
//		printf("\n");	
//		return;
//	}
//	st[u] = true;
//	dfs(u + 1,rest-1);
//	st[u] = false;
//	dfs(u + 1,rest);
//}
//int main()
//{
//	scanf("%d%d", &n,&m);
//	dfs(1,m);
//	return 0;
//}

// 或
// 思路：一共选m个数，依次从小到大枚举选出这m个数,也就是递归深度最多为m层
//#include <iostream>
//using namespace std;
//const int N = 30;
//
//int path[N];
//int n, m;
//void dfs(int u, int start) {
//	if (u > m) {
//		for (int i = 1; i <= m; ++i)
//			printf("%d ", path[i]);
//		printf("\n");
//	} else {
//		for (int i = start; i <= n; ++i) {
//			path[u] = i;
//			dfs(u + 1, i + 1);
//		}
//	}
//}
//int main()
//{
//	scanf("%d%d", &n, &m);
//	dfs(1,1);
//	return 0;
//}

// 94. 递归实现排列型枚举
//
//#include <iostream>
//using namespace std;
//const int N = 12;
//int n;
//int path[N];
//bool st[N];
//void dfs(int level) {
//	if (level > n) {
//		for (int i = 1; i <= n; ++i)
//			printf("%d ", path[i]);
//		printf("\n");
//	} else {
//		for (int i = 1; i <= n; ++i) {
//			if (!st[i]) {	// i 没被选过，选择
//				st[i] = true;
//				path[level] = i;
//				dfs(level + 1);
//				st[i] = false; // 回溯
//			}
//		}
//	}
//}
//int main()
//{
//	scanf("%d", &n);
//	dfs(1);
//	return 0;
//}


//95. 费解的开关

// 思路：类似n*n的矩阵摆法1*2的积木的问题，上一层的缺口只能由本层竖着摆放来解决
//		思想类型，每一行的暗灯都由下面一行去点亮，同时需要枚举第一行的所有按法，因为第一行我们无法判断最优解的按法是否在第一行中出现过

//#include <iostream>
//using namespace std;
//#include <cstring>
//#include <climits>
//const int N = 6;
//int dir[] = { -1,0,1,0,-1 };
//char g[N][N], backup[N][N];
//
//
//int n;
//// 将（x,y)及其上下左右反转
//void turn(int x, int y) {
//	g[x][y] ^= 1;
//	for (int i = 0; i < 4; ++i) {
//		int a = x + dir[i], b = y + dir[i + 1];
//		if (a >= 0 && a < 5 && b >= 0 && b < 5)
//			g[a][b] ^= 1;
//	}
//}
//int check() {
//	int res = INT_MAX;
//	memcpy(backup, g, sizeof g);
//
//	// 枚举第一行的32中按法，共5个
//	for (int op = 0; op < 32; ++op) {
//		int step = 0;
//		// 处理首行
//		for (int i = 0; i < 5; ++i) {
//			if (op >> i & 1) {
//				++step;
//				turn(0, i);
//			}
//		}
//		for (int i = 1; i < 5; ++i)
//			for (int j = 0; j < 5; ++j)
//				if (g[i - 1][j] == '0') {
//					++step;
//					turn(i, j);
//				}
//		// 检测最后一行是否全亮
//		int i = 0;
//		for (; i < 5; ++i)
//			if (g[4][i] == '0') break;
//
//		if (i == 5) res = min(res, step);
//		memcpy(g, backup, sizeof backup);
//	}
//
//	return res > 6 ? -1 : res;
//
//}
//int main()
//{
//	scanf("%d", &n);
//	while (n--) {
//		for (int i = 0; i < 5; ++i)
//			cin >> g[i];
//		cout << check() << endl;
//	}
//	return 0;
//}


//AcWing 96. 奇怪的汉诺塔

// 传统汉诺塔，对于n盘3塔问题，移动的最小步数就是，把前n-1个盘子从A柱移到B柱，然后把第n个盘子移到C柱，
// 最后再把前n-1个盘子移动到C柱。可以得出递推式d[n]=d[n−1]∗2+1 。

// 对于四个柱子，考虑把前n个盘子移动到B柱子上，然后把n-i个盘子在三柱模式下移动到D柱子（因为不能覆盖到B柱上，就等于只剩下A、C、D柱可以用）
// 最后把i个盘子在4塔模式下移动到D柱,考虑所有可能的i取最小值，即得到上述递推公式
// f[i]含义：把源塔上i个盘子通过两个辅助塔放到目标塔的方法数
//#include <iostream>
//#include <cstring>
//#include <algorithm>
//using namespace std;
//
//int d[20], f[20];
//
//int main() {
//	d[1] = 1;
//	for (int i = 2; i <= 12; i++)	// 3塔
//		d[i] = 2 * d[i - 1] + 1;
//	memset(f, 0x3f, sizeof(f));
//	f[1] = 1;
//	for (int i = 2; i <= 12; i++)
//		for (int j = 1; j < i; j++)
//			f[i] = min(f[i], 2 * f[j] + d[i - j]);
//	for (int i = 1; i <= 12; i++)
//		cout << f[i] << endl;
//	return 0;
//}

// 97. 约数之和
//
//// 任意一个正整数 X 都可以表示成若干个质数乘积的形式
//// 如果 N = p1^c1 * p2^c2 * ... *pk^ck	// p为质因数
////      N^B=p1^(c1+B) * p2^(c2+B) *...*pk^(ck+B)
//// 约数个数： (c1 + 1) * (c2 + 1) * ... * (ck + 1)	c个数共有不选和选i个(1~c) c+1种选择
//// 约数之和： (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)
//
//#include <iostream>
//using namespace std;
//const int mod = 9901;
//
//int qmi(int a, int k) {
//	a %= mod;
//	int res = 1;
//	while (k) {
//		if (k & 1)
//			res = res * a % mod;
//		a = a * a % mod;
//		k >>= 1;
//	}
//	return res;
//}
//
//// sum(p, c) = 1 + p + p2 + … + pc
//// 对于偶数个数 sum(p,k)=(1+p^(k/2+1))*sum(p,k/2)
//// 奇数个数		sum(p,k)=p^k+sum(p,k-1)=p*sum(p,k-1)+1, *p是相当于前k个*怕，错开一位，后再加上p^0=1
//int sum(int p, int k) {
//	if (k == 0)
//		return 1;
//	if (k % 2 == 0)	//因为是0~k ,k是偶数的话，总数奇数
//		return (p % mod * sum(p, k - 1) + 1) % mod;	// 简单理解 qmi(p,k)*sum(p,k-1)%mod
//	else			// 偶数个数
//		return (1 + qmi(p, k / 2 + 1)) * sum(p, k / 2) % mod;
//}
//int main()
//{
//	int a, b;
//	cin >> a >> b;
//	int res = 1;
//	for (int i = 2; i <= a; ++i) {
//		int s = 0;	// s是这个质因数有几个
//		while (a % i == 0) {
//			++s;
//			a /= i;
//		}
//		if (s)	// 个数不为0
//			res = res * sum(i, s*b) % mod;
//	}
//	if (!a)
//		res = 0;
//	cout << res << endl;
//	return 0;
//}
//

// AcWing 98. 分形之城 

#include <iostream>
using namespace std;
#include <cmath>
typedef long long LL;
typedef pair<LL, LL> PLL;

// 利用坐标的旋转公式得出相应的坐标转换
PLL calc(LL n, LL m) {
	if (n == 0) return{ 0,0 };
	LL len = 1ll << n - 1, cnt = 1ll << 2 * n - 2;	// len是4个子块的长度，cnt是子块中总个数
	auto pos = calc(n - 1, m % cnt);
	auto x = pos.first, y = pos.second;
	auto z = m / cnt;
	if (z == 0) return { y,x };		// 顺时针旋转90°，再按y轴翻转	
	if (z == 1)return { x,y + len };	//平移
	if (z == 2) return{ x + len,y + len };	//平移
	return { 2 * len - 1 - y,len - 1 - x };		// 顺时针旋转270°，再按y轴翻转，再平移

}
int main()
{
	int T;
	cin >> T;
	while (T--) {
		LL n, a, b;
		cin >> n >> a >> b;
		auto pa = calc(n, a - 1);	// -1 是认为从0开始计数
		auto pb = calc(n, b - 1);
		auto x = pa.first - pb.first, y = pa.second - pb.second;
		printf("%.0lf\n", sqrt(x * x + y * y) * 10);	// printf .0可以四舍五入，cout (int)没有
	}
	return 0;
}