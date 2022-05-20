#include<iostream>
using namespace std;
#include <vector>
#include <set>
#include <filesystem>
#include <unordered_map>
#include <cstring>
#include <stack>
using namespace std::filesystem;
// 给定一个有序数组arr，从左到右依次表示X轴上从左往右点的位置
// 给定一个正整数K，返回如果有一根长度为K的绳子，最多能盖住几个点
// 绳子的边缘点碰到X轴上的点，也算盖住

class Code01_CordCoverMaxPoint {
public:
	// L为绳子的长度
	//O(nlogn)
	int maxPoint1(vector<int>& arr, int L) {
		int res = 1;
		// 枚举绳子的每一个结尾
		for (int i = 0; i < arr.size(); i++) {
			int nearest = nearestIndex(arr, i, arr[i] - L);
			res = max(res, i - nearest + 1);
		}
		return res;
	}
	// 二分查找，查找第一个大于value的位置
	int nearestIndex(vector<int>& arr, int R, int value) {
		int L = 0;
		int index = R;
		while (L <= R) {
			int mid = L + ((R - L) >> 1);
			if (value <= arr[mid]) {
				R = mid - 1;
			} else {
				L = mid + 1;
			}
		}
		return L;
	}
	// 滑动窗口，O（n)
	int maxPoint2(vector<int>& arr, int L) {
		int left = 0;
		int right = 0;
		int N = arr.size();
		int ans = 0;
		while (left < N) {
			while (right < N && arr[right] - arr[left] <= L) {
				++right;
			}
			ans = max(ans, right - (left++));
		}
		return ans;
	}

};


class Code02_CountFiles {
public:
	// 注意这个函数也会统计隐藏文件
	int getFileNumber(string folderPath) {
		if (!exists(folderPath))		// 如果目录不存在
			return 0;
		path root(folderPath);
		//如果路径不是目录也不是文件 
		if (!is_directory(root) && is_regular_file(root)) {
			return 0;
		}
		// 如果只是单个文件，返回1
		if (is_regular_file(root)) {
			return 1;
		}
		// DFS
		stack<path> st;
		st.push(root);
		int files = 0;
		while (!st.empty()) {
			path folder = st.top();
			st.pop();
			directory_entry entry(folder);	//文件入口
			directory_iterator list(entry);	//文件入口容器
			for (auto& it : list) {
				if (is_regular_file(it)) {	//文件的话，文件数++
					++files;
				}
				if (is_directory(it)) {	//目录的话，入栈
					st.push(it);
				}
			}
		}
		return files;
	}

};

class Code03_Near2Power {
public:
	// n是正数，返回大于等于，且最接近2的某次方的值
	int tableSizeFor(unsigned int n) {
		// n是无符号，采用的是逻辑右移
		n--;		//-1是为了考虑n正好是2的某次方的情况
		n |= n >> 1;
		n |= n >> 2;
		n |= n >> 4;
		n |= n >> 8;
		n |= n >> 16;	//32位做到16即可，64为到32
		//做完之后，最高位的1及其右边所有位都变为1
		return n + 1;
	}
	void test() {
		cout << tableSizeFor(158984) << endl;
	}
};

class Code04_MinSwapStep {
public:
	// 一个数组中只有两种字符'G'和'B'，
	// 可以让所有的G都放在左侧，所有的B都放在右侧
	// 或者可以让所有的G都放在右侧，所有的B都放在左侧
	// 但是只能在相邻字符之间进行交换操作，请问请问至少需要交换几次，

	int minStep1(string s) {
		if (s.empty())
			return 0;
		int step1 = 0, step2 = 0;
		int gi = 0, bi = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == 'G') {	//当前的G，去左边   方案1
				step1 += (i - gi++);
			} else {	// 当前的B，去左边   方案2
				step2 += (i - bi++);
			}
		}
		return min(step1, step2);
	}
	void test() {
		cout << minStep1("GGBGBBGGG") << endl;
	}
};


//329.矩阵中的最长递增路径
class Code05_LongestIncreasingPath {
public:
	//法一：暴力，尝试每个点作为起点，看其四周是否有递增路径
	// 超时
	int longestIncreasingPath1(vector<vector<int>>& matrix) {
		int ans = 0;
		int N = matrix.size();
		int M = matrix[0].size();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				ans = max(ans, process1(matrix, i, j));
			}
		}
		return ans;
	}

	// 从m[i][j]开始走，走出来的最长递增链，返回！
	int process1(vector<vector<int>>& m, int i, int j) {
		int up = i > 0 && m[i][j] < m[i - 1][j] ? process1(m, i - 1, j) : 0;
		int down = i < (m.size() - 1) && m[i][j] < m[i + 1][j] ? process1(m, i + 1, j) : 0;
		int left = j > 0 && m[i][j] < m[i][j - 1] ? process1(m, i, j - 1) : 0;
		int right = j < (m[0].size() - 1) && m[i][j] < m[i][j + 1] ? process1(m, i, j + 1) : 0;
		return max(max(up, down), max(left, right)) + 1;
	}

	//法二:缓存
	int longestIncreasingPath2(vector<vector<int>>& matrix) {
		int ans = 0;
		int N = matrix.size();
		int M = matrix[0].size();
		vector<vector<int>> dp(N, vector<int>(M));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				ans = max(ans, process2(matrix, i, j, dp));
			}
		}
		return ans;
	}

	// 从m[i][j]开始走，走出来的最长递增链，返回！
	int process2(vector<vector<int>>& m, int i, int j, vector<vector<int>>& dp) {
		if (dp[i][j] != 0) {
			return dp[i][j];
		}
		// (i,j)不越界
		int up = i > 0 && m[i][j] < m[i - 1][j] ? process2(m, i - 1, j, dp) : 0;
		int down = i < (m.size() - 1) && m[i][j] < m[i + 1][j] ? process2(m, i + 1, j, dp) : 0;
		int left = j > 0 && m[i][j] < m[i][j - 1] ? process2(m, i, j - 1, dp) : 0;
		int right = j < (m[0].size() - 1) && m[i][j] < m[i][j + 1] ? process2(m, i, j + 1, dp) : 0;
		int ans = max(max(up, down), max(left, right)) + 1;
		dp[i][j] = ans;
		return ans;
	}
};


/*
 * 给定两个数组x和hp，长度都是N。
 * x数组一定是有序的，x[i]表示i号怪兽在x轴上的位置
 * hp数组不要求有序，hp[i]表示i号怪兽的血量
 * 为了方便起见，可以认为x数组和hp数组中没有负数。
 * 再给定一个正数range，表示如果法师释放技能的范围长度(直径！)
 * 被打到的每只怪兽损失1点血量。
 * 返回要把所有怪兽血量清空，至少需要释放多少次aoe技能？
 * 三个参数：int[] x, int[] hp, int range
 * 返回：int 次数
 * */
class Code06_AOE {
public:
	// 法一：暴力尝试在每个位置释放技能，只能过小样例测试
	int minAoe1(vector<int> x, vector<int> hp, int range) {
		bool allClear = true;
		for (int i = 0; i < hp.size(); i++) {
			if (hp[i] > 0) {
				allClear = false;
				break;
			}
		}
		if (allClear) {
			return 0;
		} else {
			int ans = INT_MAX;
			for (int left = 0; left < x.size(); left++) {
				if (hasHp(x, hp, left, range)) {	//检查left到left+range范围上是否有怪兽
					minusOneHp(x, hp, left, range);	//该范围怪兽hp--
					ans = min(ans, 1 + minAoe1(x, hp, range));	//DFS
					addOneHp(x, hp, left, range);	// 回溯
				}
			}
			return ans;
		}
	}

	bool hasHp(vector<int>& x, vector<int>& hp, int left, int range) {
		for (int index = left; index < x.size() && x[index] - x[left] <= range; index++) {
			if (hp[index] > 0) {
				return true;
			}
		}
		return false;
	}

	void minusOneHp(vector<int>& x, vector<int>& hp, int left, int range) {
		for (int index = left; index < x.size() && x[index] - x[left] <= range; index++) {
			hp[index]--;
		}
	}

	void addOneHp(vector<int>& x, vector<int>& hp, int left, int range) {
		for (int index = left; index < x.size() && x[index] - x[left] <= range; index++) {
			hp[index]++;
		}
	}


	// 法二；贪心
	// 为了验证
	// 不用线段树，但是贪心的思路，和课上一样
	// 1) 总是用技能的最左边缘刮死当前最左侧的没死的怪物
	// 2) 然后向右找下一个没死的怪物，重复步骤1)
	int minAoe2(vector<int>& x, vector<int>& hp, int range) {
		int n = x.size();
		vector<int> cover(n);
		// cover[i] 记录以i位置为技能为左边缘，右边缘所能覆盖到的位置
		///cover[i] : 如果i位置是技能的最左侧，技能往右的range范围内，最右影响到哪
		int r = 0;
		for (int i = 0; i < n; i++) {
			while (r < n && x[r] - x[i] <= range) {
				r++;
			}
			cover[i] = r;
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			// 找最左边没死的怪兽为技能左边缘进行技能释放
			if (hp[i] > 0) {
				int minus = hp[i];
				for (int index = i; index < cover[i]; index++) {
					hp[index] -= minus;
				}
				ans += minus;
			}
		}
		return ans;
	}

	//法三：因为AOE是区间伤害，可用线段树快速修改查询
	int minAoe3(vector<int> x, vector<int> hp, int range) {
		int n = x.size();
		vector<int> cover(n);
		int r = 0;
		// cover[i] : 如果i位置是技能的最左侧，技能往右的range范围内，最右影响到哪
		for (int i = 0; i < n; i++) {
			while (r < n && x[r] - x[i] <= range) {
				r++;
			}
			cover[i] = r - 1;
		}
		SegmentTree st(hp);
		st.build(1, n, 1);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int leftHP = st.query(i, i, 1, n, 1);
			if (leftHP > 0) {	//血量为正的话
				ans += leftHP;
				st.add(i, cover[i - 1] + 1, -leftHP, 1, n, 1);
			}
		}
		return ans;
	}

	class SegmentTree {
	public:
		int MAXN;
		vector<int> arr;
		vector<int> sum;
		vector<int> lazy;
		SegmentTree(vector<int> orgin) {
			MAXN = orgin.size() + 1;
			arr.resize(MAXN);
			for (int i = 1; i < MAXN; ++i) {
				arr[i] = orgin[i - 1];
			}
			sum.resize(MAXN << 2);
			lazy.resize(MAXN << 2);
		}
		void pushUp(int rt) {
			sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
		}

		void build(int l, int r, int rt) {
			if (l == r) {
				sum[rt] = arr[l];
				return;
			}
			int mid = (l + r) >> 1;
			build(l, mid, rt << 1);
			build(mid + 1, r, rt << 1 | 1);
			pushUp(rt);
		}
		void add(int L, int R, int C, int l, int r, int rt) {
			if (L <= l && r <= R) {
				sum[rt] += C * (r - l + 1);
				lazy[rt] += C;
				return;
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			if (L <= mid) {
				add(L, R, C, l, mid,rt << 1);
			}

		}
		void pushDown(int rt, int ln, int rn) {
			if (lazy[rt] != 0) {
				lazy[rt << 1] += lazy[rt];
				sum[rt << 1] += lazy[rt] * ln;
				lazy[rt << 1 | 1] += lazy[rt];
				sum[rt << 1 | 1] += lazy[rt] * rn;
			}
		}
		int query(int L, int R, int l, int r, int rt) {
			if (L <= l && r <= R) {
				return sum[rt];
			}
			int mid = (l + r) >> 1;
			// 先下发
			pushDown(rt, mid - 1 + 1, r - mid);
			int ans = 0;
			if (L <= mid) {
				ans += query(L, R, l, mid, rt << 1);
			}
			if (R > mid) {
				ans += query(L, R, mid + 1, r, rt << 1 | 1);
			}
			return ans;
		}
	};
};

//494. 目标和
class Code07_TargetSum {
public:
	// 法一：暴力尝试，每个数要么正要么负
	int findTargetSumWays1(vector<int>& arr, int s) {
		return process1(arr, 0, s);
	}
	// 可以自由使用arr[index....]所有的数字！
	// 搞出rest这个数，方法数是多少？返回
	// index == 7 rest = 13
	// map "7_13" 256
	int process1(vector<int>& arr, int index, int rest) {
		if (index == arr.size()) { // 没数了！
			return rest == 0 ? 1 : 0;
		}
		// 还有数！arr[index] arr[index+1 ... ]
		return process1(arr, index + 1, rest - arr[index]) + process1(arr, index + 1, rest + arr[index]);
	}

	// 法二：缓存 哈希表形式，因为rest变量可为负数，用数组形式较麻烦
	int findTargetSumWays2(vector<int>& arr, int s) {
		unordered_map<int, unordered_map<int, int>> m;
		return process2(arr, 0, s, m);
	}

	int process2(vector<int>& arr, int index, int rest, unordered_map<int, unordered_map<int, int>>& dp) {
		if (dp.find(index) != dp.end() && dp[index].find(rest) != dp[index].end()) {
			return dp[index][rest];
		}
		// 否则，没命中！
		int ans = 0;
		if (index == arr.size()) {
			ans = rest == 0 ? 1 : 0;
		} else {
			ans = process2(arr, index + 1, rest - arr[index], dp) + process2(arr, index + 1, rest + arr[index], dp);
		}
		dp[index][rest] = ans;
		return ans;
	}



	// 优化点一 :
   // 你可以认为arr中都是非负数
   // 因为即便是arr中有负数，比如[3,-4,2]
   // 因为你能在每个数前面用+或者-号
   // 所以[3,-4,2]其实和[3,4,2]达成一样的效果
   // 那么我们就全把arr变成非负数，不会影响结果的
   // 优化点二 :
   // 如果arr都是非负数，并且所有数的累加和是sum
   // 那么如果target<sum，很明显没有任何方法可以达到target，可以直接返回0
   // 优化点三 :
   // arr内部的数组，不管怎么+和-，最终的结果都一定不会改变奇偶性
   // 所以，如果所有数的累加和是sum，
   // 并且与target的奇偶性不一样，没有任何方法可以达到target，可以直接返回0
   // 优化点四 :
   // 比如说给定一个数组, arr = [1, 2, 3, 4, 5] 并且 target = 3
   // 其中一个方案是 : +1 -2 +3 -4 +5 = 3
   // 该方案中取了正的集合为P = {1，3，5}
   // 该方案中取了负的集合为N = {2，4}
   // 所以任何一种方案，都一定有 sum(P) - sum(N) = target
   // 现在我们来处理一下这个等式，把左右两边都加上sum(P) + sum(N)，那么就会变成如下：
   // sum(P) - sum(N) + sum(P) + sum(N) = target + sum(P) + sum(N)
   // 2 * sum(P) = target + 数组所有数的累加和
   // sum(P) = (target + 数组所有数的累加和) / 2
   // 也就是说，任何一个集合，只要累加和是(target + 数组所有数的累加和) / 2
   // 那么就一定对应一种target的方式
   // 也就是说，比如非负数组arr，target = 7, 而所有数累加和是11
   // 求有多少方法组成7，其实就是求有多少种达到累加和(7+11)/2=9的方法
   // 优化点五 :
   // 二维动态规划的空间压缩技巧
	int findTargetSumWays(vector<int> arr, int target) {
		int sum = 0;
		for (int n : arr) {
			sum += n;
		}
		// 如果 最大和<target，那么凑不齐，或奇偶性不同，return 0
		return sum < target || ((target & 1) ^ (sum & 1)) != 0 ? 0 : subset2(arr, (target + sum) >> 1);
	}

	// 求非负数组nums有多少个子集，累加和是s
	// 二维动态规划
	// 不用空间压缩
	int subset1(vector<int> nums, int s) {
		if (s < 0) {
			return 0;
		}
		int n = nums.size();
		// dp[i][j] : nums前缀长度为i的所有子集，有多少累加和是j？
		vector<vector<int>> dp(n + 1, vector<int>(s + 1));
		// nums前缀长度为0的所有子集，有多少累加和是0？一个：空集
		dp[0][0] = 1;	//第0行的其他自动初始化为0
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= s; j++) {
				dp[i][j] = dp[i - 1][j];
				if (j - nums[i - 1] >= 0) {
					dp[i][j] += dp[i - 1][j - nums[i - 1]];
				}
			}
		}
		return dp[n][s];
	}

	// 求非负数组nums有多少个子集，累加和是s
	// 二维动态规划
	// 用空间压缩:
	// 核心就是for循环里面的：for (int i = s; i >= n; i--) {
	// 为啥不枚举所有可能的累加和？只枚举 n...s 这些累加和？
	// 因为如果 i - n < 0，dp[i]怎么更新？和上一步的dp[i]一样！所以不用更新
	// 如果 i - n >= 0，dp[i]怎么更新？上一步的dp[i] + 上一步dp[i - n]的值，这才需要更新
	int subset2(vector<int>& nums, int s) {
		if (s < 0) {
			return 0;
		}
		vector<int> dp(s + 1);
		dp[0] = 1;
		for (int n : nums) {
			for (int i = s; i >= n; i--) {
				dp[i] += dp[i - n];
			}
		}
		return dp[s];
	}

};

//699. 掉落的方块
class Solution {
public:
	class SegmentTree {
	public:
		vector<int> maxN;
		vector<int> change;
		vector<bool> update;
		SegmentTree(int size) {
			int N = size + 1;
			maxN.resize(N << 2);
			change.resize(N << 2);
			update.resize(N << 2);
		}
		void pushUp(int rt) {
			maxN[rt] = max(maxN[rt << 1], maxN[rt << 1 | 1]);
		}
		void pushDown(int rt, int ln, int rn) {
			if (update[rt]) {
				update[rt << 1] = true;
				update[rt << 1 | 1] = true;
				change[rt << 1] = change[rt];
				change[rt << 1 | 1] = change[rt];
				maxN[rt << 1] = change[rt];
				maxN[rt << 1 | 1] = change[rt];
				update[rt] = false;
			}
		}
		void UpDate(int L, int R, int C, int l, int r, int rt) {
			if (L <= l && r <= R) {
				update[rt] = true;
				change[rt] = C;
				maxN[rt] = C;
				return;
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			if (L <= mid) {
				UpDate(L, R, C, l, mid, rt << 1);
			}
			if (R > mid) {
				UpDate(L, R, C, mid + 1, r, rt << 1 | 1);
			}
			pushUp(rt);
		}
		
		int query(int L, int R, int l, int r, int rt) {
			if (L <= l && r <= R) {
				return maxN[rt];
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			int left = 0;
			int right = 0;
			if (L <= mid) {
				left = query(L, R, l, mid, rt << 1);
			}
			if (R > mid) {
				right = query(L, R, mid + 1, r, rt << 1 | 1);
			}
			return max(left, right);
		}
	};
	// 坐标压缩
	unordered_map<int, int> index(vector<vector<int>>& positions) {
		set<int> pos;
		for (auto& arr : positions) {
			pos.insert(arr[0]);
			pos.insert(arr[0]+arr[1]-1);
		}
		unordered_map<int, int> ret;
		int count = 0;
		for (int index : pos) {
			ret[index] = ++count;
		}
		return ret;
	}
	vector<int> fallingSquares(vector<vector<int>>& positions) {
		unordered_map<int, int> m = index(positions);
		int N = m.size();
		SegmentTree segmentTree(N);
		int maxN = 0;
		vector<int> res;
		for (auto& arr : positions) {
			int L = m[arr[0]];
			int R = m[arr[0] + arr[1] - 1];
			int height = segmentTree.query(L, R, 1, N, 1) + arr[1];
			maxN = max(maxN, height);
			res.push_back(maxN);
			segmentTree.UpDate(L, R, height, 1, N, 1);
		}
		return res;
	}
};


int main()
{
	Code02_CountFiles code2;
	//cout << code2.getFileNumber("E:\\c语言截图\\") << endl;
	Code03_Near2Power code3;
	code3.test();
	Code04_MinSwapStep code4;
	code4.test();
	Code07_TargetSum code7;
	return 0;
}