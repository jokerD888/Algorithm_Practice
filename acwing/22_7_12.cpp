//116. 飞行员兄弟

// 暴力枚举，从16个格子，一个格子最多翻转一次，因为两次的话相当于白弄
// 所以共0~2^16种状态，而每种状态需要枚举16位，所以总时间规模位16*2^16,可以满足题目要求
// 需要先预处理每个位置的操作状态，根据异或的特性有结合律，可以先算出来操作每个位置后需要异或的值，即可O(1）时间内完成整行整列的操作

//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//typedef pair<int, int> PII;
//int change[4][4];
//
//int get(int x, int y) { return 4 * x + y; }
//
//int main()
//{
//	int state = 0;
//	// 得出初始状态
//	for (int i = 0; i < 4; ++i) {
//		string line;
//		cin >> line;
//		for (int j = 0; j < 4; ++j)
//			if (line[j] == '+')
//				state += 1 << get(i, j);
//	}
//
//	// 预处理
//	for (int i = 0; i < 4; ++i)
//		for (int j = 0; j < 4; ++j) {
//			for (int k = 0; k < 4; ++k) {
//				change[i][j] += 1 << get(i, k);
//				change[i][j] += 1 << get(k, j);
//			}
//			change[i][j] -= 1 << get(i, j);
//		}
//
//
//	vector<PII> res;
//	// 枚举
//	for (int k = 0; k < 1 << 16; ++k) {
//		int now = state;
//		vector<PII> path;
//		for (int i = 0; i < 16; ++i)
//			if (k >> i & 1) {
//				int x = i / 4, y = i % 4;
//				now ^= change[x][y];
//				path.emplace_back(x, y);
//			}
//		if (!now && (res.empty() || res.size() > path.size())) res = path;
//	}
//	cout << res.size() << endl;
//	for (auto& p : res)cout << p.first + 1 << " " << p.second + 1 << endl;
//
//	return 0;
//}
//

// 117. 占卜DIY

// 模拟
//// 每一堆最多只会抽4次，不会抽完，每堆高度也不会超过4张
//#include <iostream>
//#include <deque>
//using namespace std;
//
//deque<int> a[14];
//int ans[14];
//int get(char c) {
//	if (c == '0')return 10;
//	if (isdigit(c)) return c - '0';
//	if (c == 'A')return 1;
//	if (c == 'J') return 11;
//	if (c == 'Q')return 12;
//	return 13;
//}
//int main()
//{
//	char c;
//	for (int i = 1; i <= 13; ++i)
//		for (int j = 0; j < 4; ++j) {
//			cin >> c;
//			getchar();
//			a[i].push_back(get(c));
//		}
//	int kn = -1;
//	int num = 13;
//	while(kn!=4){
//		if (num == 13) {
//			++kn;
//			if (4==kn) break;		// 这里=4了要立刻退出，否则下面的取头操作可能会失败，因为a[13]此时可能会为空
//			num = a[13].front();
//			a[13].pop_front();
//			continue;
//		}
//		++ans[num];
//
//		a[num].push_front(num);
//		int tmp = num;
//		num = a[num].back();	// 此时num已变，需要tmp临时存储
//		a[tmp].pop_back();
//	}
//	int res = 0;
//	for (int i = 1; i <= 13; ++i)
//		if (ans[i] == 4) ++res;
//	cout << res << endl;
//
//	return 0;
//}
//
////你会发现，其实正面超上的牌根本不用再存储下来，即插入的操作是多余的
//#include <iostream>
//#include <vector>
//using namespace std;
//
//vector<int> cards[14];
//int open[14];
//
//int get(char c) {
//	if (c == '0')return 10;
//	if (isdigit(c)) return c - '0';
//	if (c == 'A')return 1;
//	if (c == 'J') return 11;
//	if (c == 'Q')return 12;
//	return 13;
//}
//
//int main()
//{
//
//	for (int i = 1; i <= 13; ++i) {
//		for (int j = 0; j < 4; ++j) {
//			// 用长度为2的字符串来读会自动过滤到回车或空格
//			char s[2];
//			cin >> s;
//			cards[i].push_back(get(*s));
//		}
//	}
//	for (int i = 0; i < 4; ++i) {
//		int t = cards[13][i];
//		while (t != 13) {
//			++open[t];
//			int r = cards[t].back();
//			cards[t].pop_back();
//			t = r;
//		}
//	}
//
//	int res = 0;
//	for (int i = 1; i <= 12; ++i) res += open[i] >= 4;
//
//	cout << res << endl;
//	return 0;
//}


// 118. 分形

// 每一级相当于5个低一级的图形，复制到五个不同位置
// 所以我们模拟这种操作，开一个足够大的正方形矩性模拟复制操作

//#include <iostream>
//#include <cmath>
//using namespace std;
//
//const int N = 1000;
//char g[N][N];
//
//void dfs(int n) {
//	if (n == 1) {
//		g[0][0] = 'X';
//		return;
//	}
//	dfs(n - 1);
//	int len = pow(3, n - 2);
//
//	int sx[]{ 0,1,2,2 }, sy[]{ 2,1,0,2 };
//	for (int k = 0; k < 4; ++k)
//		for (int i = 0; i < len; ++i)
//			for (int j = 0; j < len; ++j)
//				g[sx[k] * len + i][sy[k] * len + j] = g[i][j];
//}
//int main()
//{
//	dfs(7);
//
//	int n;
//	while (cin >> n && n != -1) {
//		int len = pow(3, n - 1);
//		for (int i = 0; i < len; ++i) {
//			for (int j = 0; j < len; ++j)
//				if (g[i][j])cout << "X";
//				else cout << " ";
//			cout << endl;
//		}
//		cout << "-" << endl;
//	}
//	return 0;
//}
//
//// 或纯递归形式
//
//#include <iostream>
//#include <cmath>
//using namespace std;
//
//const int N = 1000;
//char g[N][N];
//
//void dfs(int n,int x,int y) {
//	if (n == 1) {
//		g[x][y] = 'X';
//		return;
//	}
//	int len = pow(3, n - 2);
//
//	int sx[]{ 0,0,1,2,2 }, sy[]{ 0,2,1,0,2 };
//	for (int i = 0; i < 5; ++i) dfs(n - 1, x + len * sx[i], y + len * sy[i]);
//
//}
//int main()
//{
//	dfs(7,0,0);
//
//	int n;
//	while (cin >> n && n != -1) {
//		int len = pow(3, n - 1);
//		for (int i = 0; i < len; ++i) {
//			for (int j = 0; j < len; ++j)
//				if (g[i][j])cout << "X";
//				else cout << " ";
//			cout << endl;
//		}
//		cout << "-" << endl;
//	}
//	return 0;
//}

// 迭代形式
//
//#include <iostream>
//#include <cmath>
//using namespace std;
//
//void calc(int n) {
//	int len = pow(3, n - 1);
//	for (int i = 0; i < len; ++i) {
//		string s = "X";
//		int line = i;
//		int cur_len = 1;
//		for (int j = 0; j < n - 1; ++j) {
//			int level = line % 3;	// level 是算出当前行是当前级的第几部分，后续的/=3是算上一级的第几部分
//			if (level == 1) s = string(cur_len, ' ') + s + string(cur_len, ' ');
//			else s = s + string(cur_len, ' ') + s;
//			cur_len *= 3;
//			line /= 3;
//		}
//		cout << s << endl;
//	}
//}
//int main()
//{
//
//	int n;
//	while (cin >> n && n != -1) {
//		calc(n);
//		cout << "-" << endl;
//	}
//	return 0;
//}



// 119. 袭击

// 思路：先按x轴坐标排序，若x坐标相同，按随机因子排序（为了防止一些特殊数据,但靠x排序后，A组的在一边，B组的在一边）
// 最小距离的两个点，可能在同一侧，也可能不在同一侧，先归并二分出左右两边的最小值mi，在考虑中间的情况，我们枚举左边的点，那么右边的点离他的距离不会超过mi

//#include <iostream>
//#include <algorithm>
//#include <cmath>
//#include <climits>
//using namespace std;
//const double INF = 1e10;
//const int N = 200010;
//struct Point {
//	int x, y, rd;
//	bool type;
//	bool operator<(const Point& a)const {
//		if (x == a.x)return rd < a.rd;
//		return x < a.x;
//	}
//}points[N], temp[N];
//
//double dist(Point a, Point b) {
//	if (a.type == b.type) return INF;
//	double dx = a.x - b.x, dy = a.y - b.y;
//	return sqrt(dx * dx + dy * dy);
//}
//
//double dfs(int l, int r) {
//	if (l >= r) return INF;
//	int mid = l + r >> 1;
//	double mid_x = points[mid].x;
//	double res = min(dfs(l, mid), dfs(mid + 1, r));
//
//	{
//		int k = 0, i = l, j = mid + 1;
//		while (i <= mid && j <= r)
//			temp[k++] = points[i].y <= points[j].y ? points[i++] : points[j++];
//		while (i <= mid)temp[k++] = points[i++];
//		while (j <= r)temp[k++] = points[j++];
//		for (i = 0, j = l; i < k; ++i, ++j) points[j] = temp[i];
//	}
//
//	// 筛出区间的点
//	int k = 0;
//	for (int i = l; i <= r; ++i)
//		if (points[i].x >= mid_x - res && points[i].x <= mid_x + res)
//			temp[k++] = points[i];
//
//	for (int i = 0; i < k; ++i)
//		for (int j = i - 1; j >= 0 && temp[i].y - temp[j].y < res; --j)
//			res = min(res, dist(temp[i], temp[j]));
//	return res;
//
//}
//
//
//int main()
//{
//	int t, n;
//	cin >> t;
//	srand(0);
//	while (t--) {
//		cin >> n;
//		for (int i = 0; i < n; ++i) {
//			cin >> points[i].x >> points[i].y;
//			points[i].type = 0;
//			points[i].rd = rand();
//		}
//		for (int i = n; i < n * 2; ++i) {
//			cin >> points[i].x >> points[i].y;
//			points[i].type = 1;
//			points[i].rd = rand();
//		}
//		sort(points, points + 2 * n);
//
//		printf("%.3f\n", dfs(0, n * 2 - 1));
//	}
//	return 0;
//}



// 120. 防线

// 二分
// 对于等差数列的性质，可以在O（1）时间内求出某个序列小于x的个数 = (min(seqs[i].e, x) - seqs[i].s) / seqs[i].d + 1
// 然后利用最多只有一个奇数，可以进行二分，若左边区间小于mid的个数为奇数就继续在左半区间二分，否则在右半区间二分

//#include <iostream>
//using namespace std;
//typedef long long LL;
//const int N = 200010;
//
//struct Seq {
//	int s, e, d;
//}seqs[N];
//
//int n;
//LL get_sum(int x) {
//	LL res = 0;
//	for (int i = 0; i < n; ++i)
//		if (seqs[i].s <= x)
//			res += (min(seqs[i].e, x) - seqs[i].s) / seqs[i].d + 1;
//	return res;
//}
//int main()
//{
//	int T;
//	scanf("%d", &T);
//	while (T--) {
//		int l = 0, r = 0;
//		scanf("%d", &n);
//		for (int i = 0; i < n; ++i) {
//			int s, e, d;
//			scanf("%d%d%d", &s, &e, &d);
//			seqs[i] = { s,e,d };
//			r = max(r, e);
//		}
//
//		while (l < r) {
//			int mid = (LL)l + r >> 1;
//			if (get_sum(mid) & 1) r = mid;
//			else l = mid + 1;
//		}
//		auto sum = get_sum(r) - get_sum(r - 1);
//		if (sum % 2)printf("%d %lld\n", r, sum);
//		else puts("There's no weakness.");
//	}
//
//	return 0;
//}


// 121. 赶牛入圈

//// 暴力 超时，虽然也可以用前缀和，但明显空间会爆
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//const int N = 510;
//typedef pair<int, int> PII;
//PII a[N];
//int c, n;
//int maxLen;
//bool check(int now) {
//	// 这里我本想枚举这n个点，以每个点作为边长为now的矩形的左下角，但实际上这n个点，横纵坐标并不是逐级递增的，思维固化了
//	// 即在这里我认为答案矩形的坐下角必定有点，这是错误的，故导致得出的结果偏大。实际上最小的矩形至少有一对对边上都有点。
//	//--now;
//	//for (int i = 0; i < n; ++i) {
//	//	int ans = 0;
//	//	int x = a[i].first, y = a[i].second;
//	//	if (x + now >= 10000 && y + now >= 10000)continue;
//	//	for (int j = 0; j < n; ++j)
//	//		if (a[j].first >= x && a[j].first <= x + now && a[j].second >= y && a[j].second <= y + now)
//	//			++ans;
//	//	if (ans >= c)return true;
//	//}
//	//return false;
//
//	--now;
//	for (int i = 1; i <= maxLen; ++i)
//		for (int j = 1; j <= maxLen; ++j) {
//			int ans = 0;
//			for (int k = 0; k < n; ++k)
//				if (a[k].first >= i && a[k].first <= i + now && a[k].second >= j && a[k].second <= j + now)
//					++ans;
//			if (ans >= c) return true;
//		}
//
//	return false;
//
//
//}
//int main()
//{
//	cin >> c >> n;
//	for (int i = 0; i < n; ++i) {
//		cin >> a[i].first >> a[i].second;
//		maxLen = max({ maxLen, a[i].first, a[i].second });
//	}
//	sort(a, a + n);
//	int l = 0, r = 10000;
//	while (l < r) {
//		int mid = l + r >> 1;
//		// 如果边长为mid的矩阵中草的个数>=c
//		if (check(mid)) r = mid;
//		else l = mid + 1;
//
//	}
//	cout << l << endl;
//	return 0;
//}
//
//
//// 二分答案边长，对于如何检测二分出来的边长构成的矩形是否满足条件，我们可以进行双指针判定，枚举点集
//
//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//const int N = 510;
//typedef pair<int, int> PII;
//PII a[N];
//int c, n;
//
//bool check(int now) {
//	--now;
//	for (int i = 0; i < n; ++i) {
//		int j = i;
//		// 先筛出x轴符合要求的
//		while (j < n && a[j].first - a[i].first <= now)++j;
//		if (j - i < c) return false;	//如果所剩下的草个数不够了，false
//		// [i,j)是满足x轴要求的，即现在确定了左右边界
//
//		// 再枚举y轴边界
//		for (int k = i; k < j; ++k) {
//			// l,r 即为枚举的上下边界
//			int l = a[k].second, r = a[k].second + now, ans = 0;
//			for (int u = i; u < j; ++u)
//				if (a[u].second >= l && a[u].second <= r) ++ans;;
//			// 如果这四个边界围成的矩形草的数量>=c,true
//			if (ans >= c) return true;
//		}
//	}
//	return false;
//}
//int main()
//{
//	cin >> c >> n;
//	for (int i = 0; i < n; ++i)cin >> a[i].first >> a[i].second;
//	sort(a, a + n);
//	int l = 0, r = 10000;
//	while (l < r) {
//		int mid = l + r >> 1;
//		// 如果边长为mid的矩阵中草的个数>=c
//		if (check(mid)) r = mid;
//		else l = mid + 1;
//	}
//	cout << l << endl;
//	return 0;
//}
//
//
//// 离散化+前缀和+二分
//
//// 最小边长的正方形，它有一对对边上都有点，我们假设是左右两条对边，那么我们可以上下移动使得底边上也有点存在
//// 这样的正方形的边长一定可以满足条件。点都个数只有500个，但x,y范围却在10000，进行离散化，即可将数据范围缩小到1000，这样矩阵规模1e6
//// 在利用前缀和进行O（1）的单点查询。整体达到O(log10000*M^2)M是不同横纵坐标值的个数
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//using namespace std;
//
//typedef pair<int, int> PII;
//const int N = 1010;
//
//int n, c;
//PII points[N];
//vector<int> nums;
//int sum[N][N];
//
//int get(int x) {
//	int l = 0, r = nums.size() - 1;
//	while (l < r) {
//		int mid = l + r >> 1;
//		if (nums[mid] >= x) r = mid;
//		else l = mid + 1;
//	}
//	return l;
//}
//bool check(int len) {
//	// x1,y2为矩阵左上角，x2,y2为矩阵右下角
//	for (int x1 = 0, x2 = 1; x2 < nums.size(); ++x2) {
//		while (nums[x2] - nums[x1 + 1] + 1 > len) ++x1;
//		for (int y1 = 0, y2 = 1; y2 < nums.size(); ++y2) {
//			while (nums[y2] - nums[y1 + 1] + 1 > len) ++y1;
//			if (sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1] >= c)
//				return true;
//		}
//	}
//	return false;
//}
//int main()
//{
//	cin >> c >> n;
//	nums.push_back(0);
//	for (int i = 0; i < n; ++i) {
//		int x, y;
//		cin >> x >> y;
//		points[i] = { x,y };
//		nums.push_back(x);
//		nums.push_back(y);
//	}
//	sort(nums.begin(), nums.end());
//	// 去重，unique对相邻的重复元素，通过覆盖进“删除”，返回一个迭代器，指向不重复元素的尾后位置；
//	nums.erase(unique(nums.begin(), nums.end()), nums.end());
//
//	for (int i = 0; i < n; ++i) {
//		int x = get(points[i].first), y = get(points[i].second);
//		++sum[x][y];
//	}
//	for (int i = 1; i < nums.size(); ++i)
//		for (int j = 1; j < nums.size(); ++j)
//			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
//
//	int l = 1, r = 10000;
//	while (l < r) {
//		int mid = l + r >> 1;
//		if (check(mid))r = mid;
//		else l = mid + 1;
//	}
//	cout << l << endl;
//	return 0;
//}


// 122. 糖果传递

//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//// 实际上本题就是环形均分纸牌问题
//// 对于普通均分纸牌问题，解法就是，先求平均值，每个元素再减去平均值，然后求前缀和，对与每个前缀和取绝对值进行累加即可
//// 如果成环的化，最优解一定满足环上有相邻的两个人之间没有发生交换
//// 则解法为，对前缀和数组进行排序，取中位数作为断点，即答案就是每个前缀-中位数取绝对值进行累加
//typedef long long LL;
//const int N = 1000010;
//int candys[N],sum[N];
//int n;
//
//int main()
//{
//	scanf("%d", &n);
//	LL avg=0;
//	for (int i = 1; i <= n; ++i) {
//		scanf("%d", candys + i);
//		avg += candys[i];
//	}
//	avg /= n;
//	
//	for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + candys[i] - avg;
//
//	sort(sum + 1, sum + n + 1);
//
//	LL res = 0;
//	int mid = sum[n+1 >> 1];
//	for (int i = 1; i <= n; ++i)
//		res += abs(sum[i] - mid);
//	printf("%lld\n", res);
//
//	
//	return 0;
//}


// 123. 士兵

// 可以发现，每个士兵最终放置的x和y坐标是相互独立的，
// 对于y坐标，就相当于，每个y点到某一点的距离之和最小，解法即 排序后的中位数即所求的点
// 对于x坐标，假设最终排成的一条线起点为a,那么每个士兵x点到其最终应处位置的距离为|x1-a|,|x1-a-1|,...,|xn-a-n+1|
// 可以发现 每个式子的形式为|xi-a-ci| ci为第i项等差数列，公差为1,首项无要求，即先预处理，使得每个x点先减去c后，问题就化为了y点的相同问题
//
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//const int N = 10010;
//int x[N], y[N];
//
//int n;
//
//int work(int* a) {
//	int res = 0;
//	sort(a, a + n);
//	for (int i = 0; i < n; ++i) res += abs(a[i] - a[n >> 1]);
//
//	return res;
//}
//int main()
//{
//	cin >> n;
//	for (int i = 0; i < n; ++i)cin >> x[i] >> y[i];
//
//	sort(x, x + n);
//	for (int i = 0; i < n; ++i)x[i] -= i;
//
//	cout << work(x) + work(y) << endl;
//}


//124. 数的进制转换

// 普通做法，是将a进制的转为10进制，再将10进制的转为b进制，需要高精度运算，代码量大
// 简便做法是将a进制直接转为b进制，利用短除法，不断取模，整除。

//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//int n;
//int a, b;
//string s;
//
//string work() {
//	vector<int> numbers;
//	// 字母转为数字存储
//	for (auto c : s) {
//		int num;
//		if (c >= '0' && c <= '9') num = c - '0';
//		else if (c >= 'A' && c <= 'Z') num = c - 'A' + 10;
//		else num = c - 'a' + 36;
//		numbers.push_back(num);
//	}
//	reverse(numbers.begin(), numbers.end());	// 使得数字从低位到高位存
//
//	vector<int> res;
//	while (numbers.size()) {
//		int rest = 0;	// 上一剩下的数
//		for (int i = numbers.size() - 1; i >= 0; --i) {
//			numbers[i] += rest * a;		// 上一位剩下的加上
//			rest = numbers[i] % b;		// 求余
//			numbers[i] /= b;			// 商
//		}
//		res.push_back(rest);
//		// 去除前导0
//		while (numbers.size() && numbers.back() == 0) numbers.pop_back();
//	}
//
//	reverse(res.begin(), res.end());
//	string ret;
//	// 转为字符串
//	for (auto x : res) {
//		char c;
//		if (x <= 9) c = x + '0';
//		else if (x >= 10 && x <= 35)c = 'A' + x - 10;
//		else c = 'a' + x - 36;
//		ret += c;
//	}
//	return ret;
//}
//int main()
//{
//	cin >> n;
//	while (n--) {
//		cin >> a >> b >> s;
//		cout << a << " " << s << endl;
//		cout << b << " " << work() << endl<<endl;
//	}
//	return 0;
//}



// 125. 耍杂技的牛

// 解法：以每头牛的体重和强壮度相加进行排序，排完后这样的顺序就是最优解的顺序
// 证明：先记前i头牛的体重前缀和sum[i]
//  牛		交换前				交换后
//  i		sum[i-1]-s[i]		sum[i-1]+w[i+1]-s[i]
//  i+1		sum[i]-s[i+1]		sum[i-1]-s[i+1]
//  每个式子再减去sum[i-1]得：
//  牛		交换前				交换后
//  i		-s[i]		  <		w[i+1]-s[i]
//  i+1		w[i]-s[i+1]	  >		-s[i+1]
// 现在我们只需要对比 w[i]-s[i+1] 和w[i+1]-s[i] 的大小关系
// 当 w[i]-s[i+1] >= w[i+1]-s[i] , 即w[i]+s[i] >= w[i+1]+s[i+1]，所以交换后更优，两头牛的风险值的最大值变小了
// 当 w[i]-s[i+1] <= w[i+1]-s[i] , 即w[i]+s[i] >= w[i+1]+s[i+1]，所以交换前更优。
// 证毕！



//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//const int N = 50010;
//typedef pair<int, int> PII;
//typedef long long LL;
//PII cows[N];
//int sum[N];
//int n;
//
//int main()
//{
//	cin >> n;
//	for (int i = 0; i < n; ++i)cin >> cows[i].first >> cows[i].second;
//	sort(cows, cows + n, [](const PII a, const PII b) { return a.first + a.second <b.first+ b.second; });
//	int res = -1e9,sum=0;
//	for (int i = 0; i < n; ++i) {
//		res = max(res, sum - cows[i].second);
//		sum += cows[i].first;
//	}
//	cout << res << endl;
//
//	return 0;
//}



// 126. 最大的和

//// 前缀和+枚举起点终点
//// O(n^4)勉强能过
//#include <iostream>
//using namespace std;
//
//const int N = 110;
//int n;
//int a[N][N];
//
//int get(int x1, int y1, int x2, int y2) {
//	return a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1];
//}
//int work() {
//	int res = -1e9;
//	for (int x1 = 1; x1 <= n; ++x1)
//		for (int x2 = x1; x2 <= n; ++x2)
//			for (int y1 = 1; y1 <= n; ++y1)
//				for (int y2 = y1; y2 <= n; ++y2)
//					res = max(res, get(x1, y1, x2, y2));
//	return res;
//}
//int main()
//{
//	cin >> n;
//	for (int i = 1; i <= n; ++i)
//		for (int j = 1; j <= n; ++j) {
//			cin >> a[i][j];
//			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
//
//		}
//
//	cout << work() << endl;
//	return 0;
//}
//
//
//// 对于一位的序列求子序列的最大值，可以O(N)解决，用f[i] 表示以a[i]结尾的向左延申的子序列的最大值
//// 对于f[i]  1)若f[i-1]<=0 ,则f[i]=a[i]  2)若f[i-1]>0 ,则f[i]=f[i-1]+a[i]
//
//// 所以对于二维的我们可以枚举矩形的上下边界，上下边界固定后，利用前缀和，可以化简为一位的问题
//// 做到O(N^3)
//
//#include <iostream>
//using namespace std;
//
//const int N = 110;
//int n;
//int a[N][N];
//
//int work() {
//	int res = -1e9;
//	for(int i=1;i<=n;++i)
//		for (int j = i; j <= n; ++j) {
//			int last = 0;
//			for (int k = 1; k <= n; ++k) {
//				last = max(last, 0) + a[j][k] - a[i - 1][k];
//				res = max(res, last);
//			}
//		}
//
//	return res;
//}
//int main()
//{
//	cin >> n;
//	for (int i = 1; i <= n; ++i)
//		for (int j = 1; j <= n; ++j) {
//			cin >> a[i][j];
//			a[i][j] += a[i - 1][j];
//		}
//
//	cout << work() << endl;
//	return 0;
//}



// 127. 任务

// 思路：对机器和任务从大到小排序，从大到小遍历任务，机器也从大到小遍历，只要机器的time>=当前任务的time,就加入集合中。
// 直到加无可加，然后从集合中找到最小的大于当前任务级别的机器，此任务就交个这个机器。

// 对于价值的计算我们可以发现，最小的x值*500>最大的y值*2,即说明x值对价值的贡献战主导，只有x相同，再考虑y值，所有根据x值进行排序
// 对于为什么要从集合中找到最小的大于当前任务级别的机器，感性来说,是因为没必要，找个最小的满足就可以了，后续可能会有对大的有要求，
// 自己尽可能选择小的，更多的选择留给别人。


#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

typedef pair<int, int> PII;
const int N = 100010;
int n, m;

PII mchs[N], task[N];

int main()
{
	while (cin >> n >> m) {
		for (int i = 0; i < n; ++i)cin >> mchs[i].first >> mchs[i].second;
		for (int i = 0; i < m; ++i) cin >> task[i].first >> task[i].second;

		sort(mchs, mchs + n);
		sort(task, task + m);

		long long res = 0,cnt=0;
		multiset<int> ys;
		for (int i = m - 1, j = n - 1; i >= 0; --i) {
			int x = task[i].first, y = task[i].second;
			while (j >= 0 && mchs[j].first >= x)
				ys.insert(mchs[j--].second);
			// 当前集合中的机器都是time>=x的
			auto it = ys.lower_bound(y);	// 选出满足的最小的y值
			if (it != ys.end()) {
				++cnt;
				res += 500 * x + 2 * y;
				ys.erase(it);
			}
		}
		cout << cnt << " " << res << endl;
	}
	
	return 0;
}

