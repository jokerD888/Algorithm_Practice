
// AcWing 99. 激光炸弹

//#include <iostream>
//using namespace std;
//
//const int N = 5e3 + 10; //不能开 1e5+10, 内存限制比较严格
//
//int s[N][N];
//int n, r;
//
//int main() {
//	cin >> n >> r;
//	r = min(5001, r); // 因为r最大可以取 10^9,但目标范围是5000*5000
//	for (int i = 0; i < n; i++) {
//		int x, y, w;
//		cin >> x >> y >> w;
//		s[++x][++y] += w; //右移一位, 就不需要考虑边界了, 并且必须是+=, 不能是=, 因为1个位置可能有多个目标
//	}
//	// 计算二维数组前缀和
//	for (int i = 1; i <= 5001; i++)
//		for (int j = 1; j <= 5001; j++)
//			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
//
//	int ans = 0;
//	// 枚举爆炸可能的每个点,以爆炸范围右下角为准
//	for (int i = r; i <= 5001; i++)
//		for (int j = r; j <= 5001; j++)
//			ans = max(ans, s[i][j] - s[i - r][j] - s[i][j - r] + s[i - r][j - r]);
//
//	cout << ans << endl;
//	return 0;
//}



// AcWing 100. IncDec序列

// 差分
// b[1]=a[1] , b[i]=a[i]-a[i-1]	(2<=i<=n)
// 对a数组[l,r]范围上所有数加上某个数c等同于在差分序列中b[l]+=c b[r+1]-=c
// 题目要求最后a数组中所有数都要一样，即要求差分序列除b[1]外，其他都为0,即要求b[i] (2<=i<=n)都为0
// 要求操作次数最小，而每次对a数组[l.r]上加上或者减去某个数，即要对b[l]和b[r+1]减去或加上某个数，即为b数组的一次操作为一正一负
// 利用贪心，每次操作b数组 i,j (2<=i<=n) 上的两个数，若b数组中正数的和和负数的和相同（绝对值），那么就操作 和的次数
// 如果不同，即在区间[2,n]中无法找到配对的一正一负了,可以选取b[1]和b[n+1]两个不受影响的数进行配对。
// 最后所问的是最种得到的a数组有多少种可能的结果，取决于b[1]取值的可能，共有无法配对的数n + 1，因为对于[1,j]的操作可能会有0~n;
//#include <iostream>
//using namespace std;
//
//const int N = 1e5 + 10;
//int a[N];
//
//
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
//	for (int i = n; i > 1; --i) a[i] -= a[i - 1];
//
//	long long pos = 0, neg = 0;
//	for (int i = 2; i <= n; ++i)
//		a[i] > 0 ? pos += a[i] : neg -= a[i];	// 负数再减就变正
//
//	cout << min(pos, neg) + abs(pos - neg) << endl; // 配的上的对+配不上的对
//	cout << abs(pos - neg) + 1 << endl;				// 配不上的对才可以进行两者任意的操作，i=1 或 j=n+1
//
//	return 0;
//}


//101. 最高的牛

// 贪心：一开始认为全部的牛全都是最高身高，对每一对关系，l,r 使其[l-1,r-1]的牛升高都减1
// 为避免重复的关系，使用哈希表检测去重
#include <iostream>
using namespace std;
#include <unordered_set>
#include <string>
const int N = 5000 + 10;
int a[N];

int main()
{
	int n, p, h, m;
	cin >> n >> p >> h >> m;
	a[1] = h;
	int l, r;
	unordered_set<string> check;
	while (m--) {
		cin >> l >> r;
		if (l > r) swap(l, r);
		string s = to_string(l) + '-' + to_string(r);
		if (!check.count(s)) {
			a[l + 1]++, a[r]--;
			check.emplace(s);
		}
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		cout << (res += a[i]) << endl;
	}
	return 0;
}

