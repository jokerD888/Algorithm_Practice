//// 103. 电影
//
//// 定义movie结构体，内有id记录第几个电影，sound为语音编号，word为字幕编号，sn为多少人的语言与语音相同，wn为多少人的语言与字幕相同
//// 自定义排序规则，sn大的排前面，sn一样的按wn大的排前面
//// 对于语音和字幕编号生成哈希表，使得n个人可以快速映射到movies上
//
//#include <iostream>
//using namespace std;
//#include <algorithm>
//#include <unordered_map>
//const int N = 200000 + 10;
//int a[N];
//unordered_map<int, vector<int>> hs, hw;
//int n, m;
//struct movie {
//	int id;
//	int sound, word;
//	int sn, wn;
//	bool operator<(const movie& a) {
//		return sn == a.sn ? wn > a.wn:sn > a.sn;
//	}
//}movies[N];
//
//int main()
//{
//	cin >> n;
//	for (int i = 1; i <= n; ++i) cin >> a[i];
//	cin >> m;
//	for (int i = 1; i <= m; ++i) {
//		cin >> movies[i].sound;
//		hs[movies[i].sound].push_back(i);
//		movies[i].id = i;
//	}
//	for (int i = 1; i <= m; ++i) {
//		cin >> movies[i].word;
//		hw[movies[i].word].push_back(i);
//	}
//	for (int i = 1; i <= n; ++i) {
//		if (hs.count(a[i]))
//			for (auto j : hs[a[i]])
//				++movies[j].sn;
//		if (hw.count(a[i]))
//			for (auto j : hw[a[i]])
//				++movies[j].wn;
//	}
//	sort(movies + 1, movies + m + 1);
//	cout << movies[1].id << endl;
//	// 实际上不排也ok,遍历一遍找最大即可
//	//int res = 1, s = 0, w = 0;
//	//for (int i = 1; i <= m; ++i) {
//	//	if (movies[i].sn > s || (movies[i].sn == s && movies[i].wn > w))
//	//		res = i, s = movies[i].sn, w = movies[i].wn;
//	//}
//	//cout << res << endl;
//
//	return 0;
//}
//
//
//
//// 离散化，数据范围在1e9但最多3*200000 个
//#include <cstdio>
//#include <algorithm>
//using namespace std;
//int n, m, k = 0, tot = 0;
//const int N = 2e5 + 50;
////3*N是因为语言的来源有3个地方，假设都不相同，则有3*N种语言
//int lang[3 * N], uni[3 * N], a[N], b[N], c[N], ans[3 * N];
////find作用是把稀疏编号转为稠密编号
//int find(int x) {
//	return lower_bound(uni + 1, uni + 1 + k, x) - uni;
//}
//
//int main() {
//	//保存科学家会的语言，并用lang记录
//	scanf("%d", &n);
//	for (int i = 1; i <= n; i++) {
//		scanf("%d", &a[i]);
//		lang[++tot] = a[i];
//	}
//	//保存电影音频的语言，并用lang记录
//	scanf("%d", &m);
//	for (int i = 1; i <= m; i++) {
//		scanf("%d", &b[i]);
//		lang[++tot] = b[i];
//	}
//	//保存电影字幕的语言，并用lang记录
//	for (int i = 1; i <= m; i++) {
//		scanf("%d", &c[i]);
//		lang[++tot] = c[i];
//	}
//	//排序lang，为了去重复
//	sort(lang + 1, lang + 1 + tot);
//	//把lang数组去重复，保存到uni数组
//	//uni的数组下标做为每种语言(原有的1-10^9的稀疏编号）新的稠密编号
//	for (int i = 1; i <= tot; i++) {
//		if (i == 1 || lang[i] != lang[i - 1]) {
//			uni[++k] = lang[i];
//		}
//	}
//	//a[i]中保存原始的稀疏编号，用find转变成稠密编号，并用ans数组记录每种语言出现的次数。
//	for (int i = 1; i <= n; i++) ans[find(a[i])]++;
//	//遍历所有电影，按要求找到最多科学家会的电影
//	int ans0, ans1, ans2;
//	//ans0保存最终结果，ans1和ans2为中间结果
//	ans0 = ans1 = ans2 = 0;
//	for (int i = 1; i <= m; i++) {
//		//算出第i个电影音频语言的科学家数，和第i个字幕语言的科学家数
//		int anx = ans[find(b[i])], any = ans[find(c[i])];
//		//如果ans大于ans1或者前者相等且any大于ans2时，更新
//		if (anx > ans1 || (anx == ans1 && any > ans2)) {
//			ans0 = i, ans1 = anx, ans2 = any;
//		}
//	}
//	//如果所有的电影的声音和字幕的语言，科学家们都不懂，随便选一个
//	if (ans0 == 0) {
//		printf("%d\n", 1);
//	} else {
//		printf("%d\n", ans0);
//	}
//
//	return 0;
//}


//104. 货仓选址

//// 排序+遍历
//// 先对n个店的位置求和，对n个店进行排序，然后从1开始到a[n-1]尝试每个位置
//// 由于每次递增1，对于每个位置i，我们要使得a[index]>=i ,这样前index个店的位置相当于当前位置i的距离+1，后n-index则相对距离-1
//// 这样一次遍历找出最小值即可，时间复杂度O(NlogN)瓶颈在于排序上
//
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//const int N = 100000 + 10, M = 40000 + 10;
//int a[N];
//int n;
//
//int main()
//{
//	cin >> n;
//	long long sum = 0;
//	for (int i = 0; i < n; ++i)cin >> a[i], sum += a[i];
//	sort(a, a + n);
//
//	int index = 0;
//	long long res = sum;
//	for (int i = 1; i <= a[n - 1]; ++i) {
//		while (i > a[index]) ++index;
//		sum += index, sum -= n - index;
//		res = min(res, sum);
//	}
//	cout << res << endl;
//	return 0;
//}
//
//// 或
//// 直接摆放在中位数的位置即为答案,利用绝对值不等式证明
//// |x-a|+|x-b|>=|a-b|	,即x取[a,b]即可是等式成立
//// 对于a1,a2,...,an,		首尾两两一组不等式
//// （|a1 - x|+|an - x|)+（|a2 - x|+|an-1 - x|)+...
//// 为使等式成立，x需要取在一对的位置中，对于奇数个数，取中间那个即可，对于偶数个数，取中间那两个的任何一个都可
//
//
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//const int N = 100100;
//int a[N], n;
//int main()
//{
//	cin >> n;
//	for (int i = 0; i < n; ++i)cin >> a[i];
//	sort(a, a + n);
//	int res = 0;
//	for (int i = 0; i < n; ++i) res += abs(a[i] - a[n / 2]);
//	cout << res << endl;
//	return 0;
//}



// 105. 七夕祭

// 前置题：均分纸牌
// 题意：有 n 个牌堆，每个牌堆里有 ai 个牌，现在要将每个牌堆的牌数变为相同的，
//      每次操作可以将任意牌堆的任意张牌移动到相邻的牌堆中，请问最少需要多少个操作将所有牌堆的牌数变为相同的。
// 首先我们可以得知总牌数cnt,T=cnt/n既是每个牌堆的牌数，若无法整数，说明无法均分
// 先将每个牌堆的牌数 ai 减去这个 T，就可以得到每个牌堆的牌数距离满足条件的牌数还差多少张牌，
// 每个牌堆想要获得牌只能由相邻的牌堆进行提供，所以我们只需要从第一个牌堆开始考虑，按照多出少补的原则进行递推
// 所以有两种情况：1）给出牌或拿走牌后，第二个牌堆不为0，那么继续操作，2）给出牌或拿走牌后，第二个牌堆为0，那么第二堆牌就不需要任何操作了
// 代码：
//#include <cstdio>
//
//const int N = 105;
//int arr[N];
//
//int main() {
//	int n;
//	scanf("%d", &n);
//	for (int i = 1; i <= n; i++) scanf("%d", &arr[i]);
//
//	int t = 0;
//	for (int i = 1; i <= n; i++) t += arr[i]; 
//	t /= n;
//	for (int i = 1; i <= n; i++) arr[i] -= t;
//
//	int tnt = 0, ans = 0;
//	for (int i = 1; i <= n; i++) {
//		tnt += arr[i];
//		ans++; 
//		if (tnt == 0) ans--;
//	}
//	printf("%d\n", ans);
//	return 0;
//}

// 而此题相当于在上述问题中增加了两个个条件，将链变为环，每次只能移动一个点
// 这道题目有一个非常重要的性质就是，只会改变相邻的两个数的位置，因此我们交换两个数，只会改变一行的喜爱小摊或者一列的喜爱小摊，
// 而不会同时改变行和列的喜爱小摊，既然这样的话，我们就可以将这道题目分成两个部分，一部分是求行的最少次数，一部分是求列的最少次数。
// 所以问题又回到了环形均分纸牌上了，
// 可以发现即使图形为环，为了保证结果最优总会有两个摊点间不会进行交换，那么我们将这个环从这两点间断开当成链处理，就和 均分纸牌 一样了。

// 而每次只能移动一个点，求均分完后最小操作次数，不同于上述问题中的一次可以操作多个
// 那么其实对每个数ai-T后的新数组求前缀和然后累加每个数的绝对值即为所求，注意理解

// 对于环的端点如何寻找呢？假设环在点k断开，那么k+1为新头,k为尾，变为一行
// 那么对于的前缀和序列变为s[k+1]-s[k],s[k+2]-s[k],...,s[N]-s[k],s[1]+s[N]-s[k],...,s[k]+s[N]-s[k]
// 即根据上述讨论的前缀和数组绝对值累加，所需最少步数为，累加|s[i]-s[k]|,k取何值时累加和最小，这不就是上一题的货舱选址问题吗
// s[i]等同于数组上的N家商店位置，s[k]就是仓库的位置

// 此题就是思路难想，代码简单。本题可类比为行，列方向上的两次环形均分纸牌，环形均分纸牌又类比均分纸牌和货仓选址问题
//#include <cstdio>
//#include <iostream>
//#include <algorithm>
//
//const int N = 100005;
//long long xl[N], yl[N], f[N]; //注意long long 会爆int
//
////懂了思路这里就是小模拟
//long long handle(long long arr[N], int n) {
//	for (int i = 1; i <= n; i++) f[i] = f[i - 1] + arr[i] - arr[0] / n;
//
//	std::sort(f + 1, f + 1 + n);
//	long long ans = 0;
//	for (int i = 1; i <= n; i++) {
//		ans += std::abs(f[i] - f[(n + 1) >> 1]);
//	}
//	return ans;
//}
//
//int main() {
//	int n, m, t;
//	scanf("%d %d %d", &n, &m, &t);
//
//	for (int i = 1; i <= t; i++) {
//		int x, y;
//		scanf("%d %d", &x, &y);
//		xl[x]++, yl[y]++;
//	}
//
//	for (int i = 1; i <= n; i++) xl[0] += xl[i];
//	for (int i = 1; i <= m; i++) yl[0] += yl[i];
//
//	if (xl[0] % n == 0 && yl[0] % m == 0) {
//		printf("both %lld", handle(xl, n) + handle(yl, m));
//	} else if (xl[0] % n == 0) {
//		printf("row %lld", handle(xl, n));
//	} else if (yl[0] % m == 0) {
//		printf("column %lld", handle(yl, m));
//	} else puts("impossible");
//	return 0;
//}
//
//
//// 106. 动态中位数
//
//// 看清题意，所有 M 相加之和不超过 5e5,眼拙还以为1e8
//// 为动态维护中位数，可建立两个堆，大根堆和小根堆
//// 对于序列中从小到大，我们始终保持[1,M/2]放入大根堆，[m/2+1,M]放入小根堆，
//// 任何一个时候，如果某一个堆中元素过多，打破了这个限制，就取出该堆的堆顶插入到另一个堆，这样一来，序列的中位数就是小根堆的堆顶
//
//#include <iostream>
//#include <climits>
//#include <queue>
//using namespace std;
//
//int main()
//{
//	int p;
//	cin >> p;
//	int index, m;
//	for (int i = 1; i <= p; ++i) {
//		cin >> index >> m;
//		printf("%d %d\n", index, m / 2 + 1);
//		priority_queue<int> b;	// 默认大根堆
//		priority_queue<int, vector<int>, greater<int>> s;	//小根堆
//		int num;
//		cin >> num;
//		printf("%d ", num);
//		s.emplace(num);
//		for (int j = 2; j <= m; ++j) {
//			cin >> num;
//			if (num < s.top()) b.emplace(num);
//			else s.emplace(num);
//			if (b.size() > j / 2) {
//				s.emplace(b.top());
//				b.pop();
//			} else if (s.size() > j / 2 + 1) {
//				b.emplace(s.top());
//				s.pop();
//			}
//			if (j & 1) {
//				printf("%d ", s.top());
//				if ((j + 1) / 2 % 10 == 0)printf("\n");
//			}
//
//		}
//		if ((m + 1) / 2 % 10) printf("\n");
//
//	}
//	return 0;
//}


// 107. 超快速排序

// 思路：只通过比较和交换相邻两个数值，实际上就是冒泡排序，在排序过程中没找到一对大小颠倒的相邻数值，就将他们交换
// 就会使整个序列的逆序对个数减少1，明显最终排序好后逆序对的个数为0，所以对数组进行冒泡排序的最少交换次数就是其中逆序对数
// 我们可以直接使用归并排序求出数组的逆序对数
// 合并两个有序序列a[l~mid]与a[mid +1~r]可以采用两个指针i与j分别对二者进行扫描的方式，
// 不断比较两个指针所指向数值a[i]和 a[j]的大小，将小的那个加入到排序的结果数组中。
// 若小的那个是α[j]，则a[i~mid]都比a[j]要大，它们都会与a[j]构成逆序对，可以顺便统计到答案中，具体表现为cnt+=mid-i+1

//#include <iostream>
//using namespace std;
//
//const int N = 501000;
//int a[N], b[N];
//long long cnt;
//void merge(int l, int r) {
//	if (l >= r) return;
//	int mid = l + r >> 1;
//	merge(l, mid);
//	merge(mid + 1, r);
//	int i = l, j = mid + 1;
//	for (int k = l; k <= r; ++k)
//		if (j > r || i <= mid && a[i] <= a[j]) b[k] = a[i++];
//		else b[k] = a[j++], cnt += mid - i + 1;
//	for (int k = l; k <= r; ++k)a[k] = b[k];
//}
//int main()
//{
//	int n;
//	while (cin >> n && n) {
//		for (int i = 1; i <= n; ++i)cin >> a[i];
//		cnt = 0;
//		merge(1, n);
//		cout << cnt << endl;
//	}
//	return 0;
//}


// 108. 奇数码问题
// 思路：奇数码游戏若两个局面可达，当且仅当两个局面下网格中的数依次写成1行n * n1个元素的序列后（不考虑空格)，逆序对个数的奇偶性相同。
// 该结论的必要性很容易证明:空格左右移动时，写成的序列显然不变;空格向上(下)移动时，相当于某个数与它后(前)边的n-1个数交换了位置，
// 因为n-1是偶数，所以逆序对数的变化也只能是偶数。
// 上面的结论还可以扩展到n为偶数的情况，此时两个局面可达，当且仅当两个局面对应网格写成序列后，“逆序对数之差”和“两个局面下空格所在的行数之差”奇偶性相同。
// 事实上，在 n* m网格上(n,m ≥2)也服从上述两个结论之一(根据列数奇偶性分情况讨论)。
// 总而言之，n* m数码问题的有解性判定，可以转化为归并排序求逆序对来解决。



#include <iostream>
using namespace std;
const int N = 510;
int a[N * N], b[N * N];
int cnt;	// 逆序对个数，即使爆int，奇偶性也不变
void merge(int l, int r) {
	if (l >= r)return;
	int mid = l + r >> 1;
	merge(l, mid);
	merge(mid + 1, r);
	int i = l, j = mid + 1;
	for (int k = l; k <= r; ++k)
		if (j > r || i <= mid && a[i] <= a[j])b[k] = a[i++];
		else b[k] = a[j++], cnt += mid - i + 1;
	for (int k = l; k <= r; ++k)a[k] = b[k];
}
int main()
{
	int n;
	while (cin >> n) {
		cnt = 0;
		for (int i = 1,j=0; i <= n * n; ++i) {
			cin >> a[++j];
			if (0 == a[j])--j;
		}
		merge(1, n * n - 1);
		int tmp = cnt;
		cnt = 0;
		for (int i = 1,j=0; i <= n * n; ++i) {
			cin >> a[++j];
			if (0 == a[j])--j;
		}
		merge(1, n * n - 1);
		if ((tmp & 1) == (cnt & 1)) cout << "TAK" << endl;
		else cout << "NIE" << endl;
	}
}