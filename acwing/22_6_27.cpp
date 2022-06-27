//89. a ^ b
//#include <iostream>
//using namespace std;
//int Pow(long long a, int b, int p) {		// a是long long
//	int res = 1%p;	//注意mod p是应对p为1
//	while (b) {
//		if (b & 1)
//			res = res * a % p;
//		b >>= 1;
//		a = a * a % p;
//	}
//	return res;
//}
//int main()
//{
//	int a, b, p;
//	cin >> a >> b >> p;
//	cout<<Pow(a, b, p);
//	return 0;
//}

//90. 64位整数乘法
//#include <iostream>
//using namespace std;
//
//int main()
//{
//	long long a, b, p;
//	cin >> a >> b >> p;
//	// 注意此题为乘法了，不再求幂
//	long long res = 0;
//	while (b) {
//		if (b & 1)
//			res = (res + a) % p;
//		a = a * 2 % p;
//		b >>= 1;
//	}
//	cout << res;
//	return 0;
//}

//91. 最短Hamilton路径
// 若直接暴力dfs,最多有18!种路径，不可取
// 但实际我们只关心当前有哪些点走过了和当前处于那个点，所有有 2^20*20种状态，大约为2*1e7，可满足
// 思想：过程只于当前走过的点和当前处于那个点，若state集合中的点已走过，且当前来到点j(j一定在state集合中），
// 那么就等于state集合去除点j的集合得state_k，在集合state中任一个点k 即 f[state_k][k]再加上k点到j点的权重
// 即状态转移 f[state][j]=f[state_k][k]+weight[k][j]，state_k=state 除掉j之后的集合,state_k要包含k
//#include <iostream>
//#include <cstring>
//using namespace std;
//
//const int N = 20, M = 1 << 20;
//
//int n;
//int f[M][N], weight[N][N];
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	for (int i = 0; i < n; ++i)
//		for (int j = 0; j < n; ++j)
//			scanf("%d", &weight[i][j]);
//	memset(f, 0x3f, sizeof f);
//	f[1][0] = 0;	// 一开始在0这个点，第0位二进制位1，用1来表示
//
//	for (int i = 0; i < 1 << n; ++i)	// state
//		for (int j = 0; j < n; ++j)		// j
//			if (i >> j & 1)	//判断i的第j位是否为1
//				for (int k = 0; k < n; ++k)
//					if (i - (1 << j) >> k & 1)	// i从除去j后，且第k位在集合
//						f[i][j] = min(f[i][j], f[i - (1 << j)][k] + weight[k][j]);
//	cout << f[(1 << n) - 1][n - 1];
//	return 0;
//}


// 998. 起床困难综合症
// 暴力的话就是每个攻击值都试一下，但时间1e14

//注意到 按位与、按位或、按位异或 共有的一个性质：每次运算只有关该位上的数，不影响其它位上的数
// 如果该位可以填 u，并且填 u 之后答案的该位是 1，那么在该位填 u，否则填 !u

// 思路：从高到低枚举每一位，如果该位置的数大于m,则此位置只能填0，
// 否则，如果第i为填0的结果大于等于填1的结果，那么该位置填0，否则该位置填1，且将m减去该二进制位上对应的数，使得攻击在m范围内


#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int n, m;
int t[N];
short op[N];

//calc 用于计算 x 经过所有数的第 j 位操作后所得到的结果
bool calc(bool x, int j) {
	for (int i = 0; i < n; ++i) {
		if (op[i] == 1) x |= t[i] >> j & 1;
		else if (op[i] == 2) x ^= t[i] >> j & 1;
		else x &= t[i] >> j & 1;
	}
	return x;
}
int main()
{
	cin >> n >> m;
	string s;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		cin >> s >> t[i];
		if (s[0] == 'O') op[i] = 1;
		else if (s[0] == 'X') op[i] = 2;
		else op[i] = 3;
	}

	for (int i = 29; ~i; i--) {		//~i是当i=-1是得0，终止循环
		// 因为本题中 m 最大是 10 ^ 9，log2(10 ^ 9) = 3log2(10 ^ 3) < 3 * 10 = 30，所以每次 i 从 29 往后枚举就可以了
		if (1 << i <= m)                         // 如果填 1 后小于等于 m，要看填完后对答案的影响来填
		{
			bool x = calc(0, i), y = calc(1, i); // 先分别处理出该位填 0 的结果和该位填 1 的结果
			if (x >= y) ans |= x << i;            // 如果该位填 1 并不比该位填 0 更优，那么为了让剩下能填的数更大，在该位填 0
			else ans |= y << i, m -= 1 << i;     // 否则在该位填 1，填完后让 m 减去该位填 1 的结果，这样在后面填数的时候只用考虑是否大于 m 就可以了
		} else ans |= calc(0, i) << i;             // 否则该位只能填 0,
	}
	cout << ans << endl;
	return 0;

}
