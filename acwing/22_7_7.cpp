
// 110. 防晒

// 思路
// 按照minSPF递减的顺序把奶牛排序，依次考虑每头奶牛。
// 对于每头奶牛，扫描一遍所有的防晒霜，
// 在这头奶牛能用(能用指的是该防晒霜的强度符合这头奶牛的范围，并且瓶数还有剩余）的防晒霜里找SPF值最大的使用。

// 以上算法的贪心策略是在满足条件的前提下每次选 SPF最大的防晒霜。这个策略为什么是正确的呢?我们考虑这一步策略的作用范围扩展到后续其他奶牛之后产生的影响。
// 每瓶防晒霜是否可用，会被minSPF与maxSPF 两个条件限制。因为奶牛已被按照minSPF 递减排序，所以每一个不低于当前奶牛 minSPF值的防晒霜，都不会低于后面其他奶牛的minSPF。也就是说，
// 对于当前奶牛可用的任意两瓶防晒霜x与y，如果SPF[x]<SPF[y]，那么后面其他奶牛只可能出现“x,y都能用”“x,y 都不能用”或者“x能用，y不能用”这三种情况之一。
// 因此当前奶牛选择maxSPF较大的y去使用，对于整体问题的影响显然比选择maxSPF较小的x更好。
// 另外，每头奶牛对答案的贡献至多是1。即使让当前这头奶牛放弃日光浴，留下防晒霜给后面的某一头奶牛用，对答案的贡献也不会变得更大。综上所述，尽量满足当前的奶牛，并选择SPF值尽量大的防晒霜是一个正确的贪心策略。
// 以上摘自《算法竞赛进阶指南》



//#include <cstring>
//#include <iostream>
//#include <algorithm>
//#include <map>
//
//using namespace std;
//
//typedef pair<int, int> PII;
//const int N = 2510;
//
//int n, m;
//PII cows[N];
//
//int main()
//{
//	cin >> n >> m;
//	map<int, int> spfs;
//	for (int i = 0; i < n; i++) cin >> cows[i].first >> cows[i].second;
//	for (int i = 0; i < m; i++)
//	{
//		int spf, cover;
//		cin >> spf >> cover;
//		spfs[spf] += cover; // 注意这里要写 +=，因为数据中存在spf值相同的防晒霜
//	}
//	sort(cows, cows + n);	// sort默认排升序，所以后续是从后往前遍历
//	int res = 0;
//	spfs[0] = spfs[1001] = n;	// 两个哨兵，便于处理查找结果，因为map查找失败返回的是end迭代器
//	for (int i = n - 1; i >= 0; i--)
//	{
//		auto spf = spfs.upper_bound(cows[i].second);	// 大于cows[i].second
//		spf--;	// 小于等于
//		if (spf->first >= cows[i].first)
//		{
//			res++;
//			if (--spf->second == 0)
//				spfs.erase(spf);
//		}
//	}
//	cout << res << endl;
//	return 0;
//}


// 111. 畜栏预定

// 将所有牛按开始时间从小到大排序
// 用小根堆维护当前所有畜栏的最后一头牛的吃草结束时间
// 如果当前牛的吃草时间大于堆顶牛的结束时间，那么当前牛继承堆顶牛的畜栏

// 大致原理是尽量使得畜栏都能够被及时利用，一旦有畜栏空位了，就接着使用

//#include <iostream>
//#include <algorithm>
//#include <queue>
//using namespace std;
//
//const int N = 50000 + 10;
//struct cow {
//	int start, end;
//	int index, res;
//	bool operator<(const cow& a)const { return end > a.end; }
//}cows[N];
//int n;
//
//int main()
//{
//	cin >> n;
//	for (int i = 0; i < n; ++i)cin >> cows[i].start >> cows[i].end, cows[i].index = i;
//	sort(cows, cows + n, [](const cow& a, const cow& b) {return a.start < b.start; });
//	priority_queue<cow> qu;
//	int cnt = 0;
//	for (int i = 0; i < n; ++i) {
//		if (!qu.empty() && qu.top().end < cows[i].start) {
//			cows[i].res = qu.top().res;
//			qu.pop();
//			qu.emplace(cows[i]);
//		} else {
//			cows[i].res = ++cnt;
//			qu.emplace(cows[i]);
//		}
//	}
//	sort(cows, cows + n, [](const cow& a, const cow& b) {return a.index < b.index; });
//	cout << cnt << endl;
//	for (int i = 0; i < n; ++i)cout << cows[i].res << endl;
//
//	return 0;
//}


// 112. 雷达设备

// 起初想法是，将小岛从左往右排序，再从左往右，卡着雷达的边界放置雷达，使得当前小岛在雷达的最左边界内，但由于雷达是圆形，
// 若当前小岛的下一个小岛离当前小岛很近，但y轴方向较远，就导致得再在附近新建一雷达，显然无法最优


// 思路：对于x轴上方得每个建筑物，可以计算出x轴上得一段能管辖它的区间l[i]~r[i],那么问题就转化为：
// 给定N个区间，在x轴上放置最少的雷达，使得每个区间包含至少一个点
// 先按照每个区间的左端点从小到大排序，用一个变量维护已经安放的最后一个雷达的位置pos,起初pos为负无穷。
// 依次考虑每个区间。如果当前区间i的左端点l[i]大于最后一台监控设备的坐标pos，则新增一台设备，令 pos = r[i]。
// 否则就让最后一台已经安放的监控设备来管辖当前区间，并令pos = min(r[i], pos)。
// 因为当前段的右边界可能小于最后一个雷达可以放置的最右位置，所以为了让当前小岛也被最后一个雷达管理，所以雷达最右放在min(r[i], pos)位置
// 依此类推，直至所有区间被管辖，输出安放的设备个数即可。


// 证明：来自《算法竞赛进阶指南》
// 这个贪心算法可以用“决策包容性”来证明。首先，对于每个区间l[i~r[i]，有两种选择:
// 1.使用已有的监控设备管辖它。
// 2.新建一台监控设备管辖它。
// 我们的贪心策略是，当选择1可行时，不会选择2。选择1之后，未来可以在任意位置新建一台监控设备，而选择2则需要在l[i]~r[i]之间新建设备，
// 也就是说，第1项选择未来可能到达的状态包含了第2项选择未来可能到达的状态。
// 其次，在选择1之后，我们把上一台设备调整到min(r[i], pos）的位置，也就是在能管辖i的前提下尽量往后放，
// “尽量往后放”这个策略未来的可达状态显然也包含了“放在更靠前的位置”未来的可达状态。最后，因为所有区间已经按照[i]排序所以这个调整不会影响到已经被管辖的区间，证毕。

//#include <iostream>
//#include <cmath>
//#include <algorithm>
//using namespace std;
//
//const int N = 1000 + 10;
//typedef pair<double, double> PDD;
//
//PDD a[N];
//int n, d, res;
//double pos = -2010;
//bool ok = true;
//int main()
//{
//	cin >> n >> d;
//	int x, y;
//	for (int i = 0; i < n; ++i) {
//		cin >> x >> y;
//		if (d * d < y * y) ok = false;
//		double k = sqrt(d * d - y * y);
//		a[i].first = x - k, a[i].second = x + k;
//	}
//	sort(a, a + n);
//	for (int i = 0; i < n; ++i) {
//		if (pos < a[i].first)
//			pos = a[i].second,++res;
//		else
//			pos = min(a[i].second, pos);	// 因为当前段的右边界可能小于最后一个雷达可以放置的最右位置
//	}
//	cout << (ok ? res : -1) << endl;
//	return 0;
//}


// 或
// 1.将所有区间按右端点从小到大排序；
// 2.依次考虑每个区间：
//		1）如果当前区间包含最后一个选择的点，则直接跳过；
//		2）如果当前区间不包含最后一个选择的点，则在当前区间的右端点的位置选一个新的点；

//#include <cstring>
//#include <iostream>
//#include <algorithm>
//#include <cmath>
//
//using namespace std;
//
//typedef pair<double, double> PDD;
//const int N = 1010;
//const double eps = 1e-6, INF = 1e10;
//// 关于double问题，一般定义一个精确值，认为两个点的差值在eps内，就认为两点相同
//int n, d;
//PDD seg[N];
//
//int main()
//{
//	cin >> n >> d;
//
//	bool success = true;
//
//	for (int i = 0; i < n; i++)
//	{
//		int x, y;
//		cin >> x >> y;
//		if (y > d)
//		{
//			success = false;
//			break;
//		}
//		auto len = sqrt(d * d - y * y);
//		seg[i] = { x + len, x - len };	// 这里存的是r,l,便于后续排序，因为要按终点排序
//	}
//
//	if (!success) puts("-1");
//	else
//	{
//		sort(seg, seg + n);
//		int res = 0;
//		double last = -INF;
//		for (int i = 0; i < n; i++)
//		{
//			if (seg[i].second > last + eps)
//			{
//				res++;
//				last = seg[i].first;
//			}
//		}
//		cout << res << endl;
//	}
//	return 0;
//}

//
//#include <iostream>
//using namespace std;
//
//int main()
//{
//	
//	return 0;
//}


// 114. 国王游戏


// 思路：直接将所有大臣按左右手上的数的乘积从小到大排序，得到的序列就是最优排队方案。
// 假设有相邻两个不递增，那么交换后两个数的最大值不大于交换前两个数的最大值。
// 而且交换相邻两个数不会对其他人的奖金产生影响，所以如果存在逆序，则将其交换，得到的结果一定不会比原来更差。

//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//const int N = 1000 + 10;
//typedef pair<int, int> PII;
//PII a[N];
//int n;
//
//// 模拟竖式乘法
//vector<int> mul(vector<int>& a, int b) {
//	vector<int> c;
//	int t = 0;
//	for (int i = 0; i < a.size(); ++i) {
//		t += a[i] * b;
//		c.push_back(t % 10);
//		t /= 10;
//	}
//	while (t)c.push_back(t % 10), t /= 10;
//	return c;
//}
//// 模拟除法
//vector<int> div(vector<int>& a, int b) {
//	vector<int> c;
//	bool is_first = false;
//	for (int i = a.size() - 1,t=0; i >= 0; --i) {
//		t = t * 10 + a[i];
//		int x = t / b;
//		if (x || is_first) {
//			is_first = true;
//			c.push_back(x);
//		}
//		t %= b;
//	}
//	return vector<int>(c.rbegin(), c.rend());
//}
//vector<int> max_vec(vector<int>& a, vector<int> b) {
//	if (a.size() > b.size()) return a;
//	if (b.size() > a.size()) return b;
//	if (vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend()))
//		return a;
//	return b;
//
//}
//void print(vector<int>& a) {
//	for (int i = a.size() - 1; i >= 0; --i) cout << a[i];
//	cout << endl;
//}
//int main()
//{
//	cin >> n;
//	for (int i = 0; i <= n; ++i)cin >> a[i].first >> a[i].second;
//	sort(a + 1, a + n + 1, [](PII a, PII b) {return a.first * a.second < b.first* b.second; });
//
//	vector<int> product(1, 1),res(1,0);
//
//	for (int i = 0; i <= n; ++i) {
//		if (i)res = max_vec(res, div(product, a[i].second));
//		product = mul(product, a[i].first);
//	}
//	print(res);
//	return 0;
//}

// 115. 给树染色


// 思路：如果染色没有限制，那么由排序不等式，我们应该先染权值最大的节点，再染权值第二大的节点，依此类推。
// 假设权值最大的节点是 b，它的父节点是 a，那么当染色有限制时，如果 a 被染色了，我们应该立即给 b 染色。所以我们就找到了在染色顺序上相邻的两个点。
// 对于两组点需要合并时，可以将这两组点分别当成两个点，其权值分别是两组内所有点权值的平均值。
// 最终做法是：每次找出当前权值最大的非根节点，将其染色顺序排在紧随父节点之后的位置，然后将该点合并进父节点中，更新父节点的权值。直到将所有点都合并进根节点为止。
// 但这样最终的分值不好算，们可以在将点合并的时候，实时更新当前的权值和，
// 假设a组（a1,a2,...,an)要合并到b组（b1,b2,...bm)后,那么b组的分值不受影响，而a组每个权值的T(时间戳）将增加m,即整体增加了 m * a组权值的和
// 整体时间复杂度O(N^2)
#include <iostream>
using namespace std;

const int N = 1010;
struct Node
{
	int father, size, sum;
	double avg;
}nodes[N];
int n, root;

// 找最大权值
int find() {
	double avg = 0;
	int res = -1;
	for(int i=1;i<=n;++i)
		if (i != root && nodes[i].avg > avg) {
			avg = nodes[i].avg;
			res = i;
		}
	return res;
}
int main()
{
	cin >> n >> root;
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		auto& nd = nodes[i];
		cin >> nd.sum;
		nd.size = 1;
		nd.avg = nd.sum;
		res += nodes[i].sum;
	}
	// 建立父节点关系
	for (int i = 0, a, b; i < n - 1; ++i) {
		cin >> a >> b;
		nodes[b].father = a;
	}
	// 每次合并会少一个点，直到剩下根节点即可，共循环n-1次
	for (int i = 0; i < n - 1; ++i) {	// O（N)
		int ver = find();				// O（N)
		int f = nodes[ver].father;
		res += nodes[ver].sum * nodes[f].size;	// ver中的节点集合追加到f中去，ver中每个点的权值被提高f.size个单位
		nodes[ver].avg = -1; // ver合并到父节点中去，置为-1,避免之后被选到
		for (int j = 1; j <= n; ++j)	// ver低下的节点的父亲修改为ver的父亲		O(N)
			if (nodes[j].father == ver) nodes[j].father = f;
		nodes[f].sum += nodes[ver].sum;
		nodes[f].size += nodes[ver].size;
		nodes[f].avg = (double)nodes[f].sum / nodes[f].size;
	}

	cout << res;

	return 0;
}