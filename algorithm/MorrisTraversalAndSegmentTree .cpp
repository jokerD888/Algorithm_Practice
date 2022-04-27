// MorrisTraversal------------------------------------------------------------------------------------

class MorrisTraversal {
public:
	class Node {
	public:
		int value;
		Node* left;
		Node* right;
		Node(int data) :value(data), left(nullptr), right(nullptr) {}
	};


	// 当前节点cur,一开始cur来到整颗树头
	// 1） cur无左树，cur=cur.right
	// 2) cur有左树，找到左树最右节点，mostRight
	//      1.mostRight的右指针指向null, 则 mostRight.right=cur,cur=cur.left
	//      2.mostRight的右指针指向cur,  则 mostRight.right=nullptr,cur=cur.right
	void morris(Node* head) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		while (cur) {
			// cur有没有左树
			mostRight = cur->left;
			if (mostRight) {	// 有左树的情况下
				// 找到cur左树上，真实的最右
				while (mostRight->right && mostRight->right != cur) {
					mostRight = mostRight->right;
				}
				// 从while中出来，mostRight一定是cur左树上的最后节点
				if (!mostRight->right) {
					mostRight->right = cur;
					cur = cur->left;
					continue;
				} else {	//mostRight->right==cur
					mostRight->right = nullptr;
				}
			}
			// 中序遍历
			//cout << cur.value << " "; 
			cur = cur->right;

		}
	}
	// 先序遍历是第一次遇到就打印（对于有左子树的），中序遍历是第二次遇到才打印，对于没有左子树的直接打印即可

	// 中序遍历
	void morrisIn(Node* head) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		while (cur) {
			// cur有没有左树
			mostRight = cur->left;
			if (mostRight) {	// 有左树的情况下
				// 找到cur左树上，真实的最右
				while (mostRight->right && mostRight->right != cur) {
					mostRight = mostRight->right;
				}
				// 从while中出来，mostRight一定是cur左树上的最后节点
				if (!mostRight->right) {
					mostRight->right = cur;
					cur = cur->left;
					continue;
				} else {	//mostRight->right==cur
					mostRight->right = nullptr;
				}
			}
			// 中序遍历
			cout << cur->value << " ";
			cur = cur->right;

		}
	}
	// 先序
	void morrisPre(Node* head) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		while (cur) {
			mostRight = cur->left;
			if (mostRight) {	// 有左树的情况下
				while (mostRight->right && mostRight->right != cur) {
					mostRight = mostRight->right;
				}
				if (!mostRight->right) {
					mostRight->right = cur;
					cout << cur->value << " ";
					cur = cur->left;
					continue;
				} else {	//mostRight->right==cur
					mostRight->right = nullptr;
				}
			} else {
				cout << cur->value << " ";
			}
			cur = cur->right;
		}
	}
	// 后序,利用每个子二叉树的右边界可以划分整个二叉树，每遍历到了第二次，就逆序打印其左子树的右边界，最后再打印整棵树的右边界
	void morrisPos(Node* head) {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		while (cur) {
			// cur有没有左树
			mostRight = cur->left;
			if (mostRight) {	// 有左树的情况下
				// 找到cur左树上，真实的最右
				while (mostRight->right && mostRight->right != cur) {
					mostRight = mostRight->right;
				}
				// 从while中出来，mostRight一定是cur左树上的最后节点
				if (!mostRight->right) {
					mostRight->right = cur;
					cur = cur->left;
					continue;
				} else {	//mostRight->right==cur
					mostRight->right = nullptr;
					printEdge(cur->left);	//逆序打印一颗树的右边界
				}
			}
			cur = cur->right;
		}
		printEdge(head);	//逆序打印一颗树的右边界
	}

	void printEdge(Node* head) {
		Node* tail = reverseEdge(head);
		Node* cur = tail;
		while (cur) {
			cout << cur->value << " ";
			cur = cur->right;
		}
		reverseEdge(tail);
	}
	Node* reverseEdge(Node* from) {
		Node* pre = nullptr;
		Node* next = nullptr;
		while (from) {
			next = from->right;
			from->right = pre;
			pre = from;
			from = next;
		}
		return pre;
	}

	void test() {
		Node a(1), b(2), c(3), d(4), e(5), f(6), g(7);
		a.left = &b;
		b.right = &c;
		a.right = &d;
		d.left = &e;
		e.right = &f;
		f.right = &g;
		morrisIn(&a);
		cout << endl;
		morrisPre(&a);
		cout << endl;
		morrisPos(&a);
		cout << endl;
	}
};


// 给你一个二叉树，请你返回整棵树的最小高度
class MinHeight {
public:
	class Node {
	public:
		int value;
		Node* left;
		Node* right;
		Node(int data) :value(data), left(nullptr), right(nullptr) {}
	};

	int minHeight1(Node* head) {
		if (head == nullptr) {
			return 0;
		}
		return p(head);
	}
	int p(Node* head) {
		if (!head->left && !head->right) {
			return 1;
		}
		// 左右子树起码一个不为空
		int leftH = INT_MAX;
		if (head->left) {
			leftH = p(head->left);
		}
		int rightH = INT_MAX;
		if (head->right) {
			rightH = p(head->right);
		}
		return 1 + min(leftH, rightH);
	}

	// 根据morris遍历改写
	int minHeight2(Node* head) {
		if (!head) {
			return 0;
		}
		Node* cur = head;
		Node* mostRight = nullptr;
		int curLevel = 0;	//上一步节点所在的层数
		int minHeight = INT_MAX;
		while (cur) {
			mostRight = cur->left;
			if (mostRight) {
				int leftHight = 1;	//左树上右边界的个数
				while (mostRight->right && mostRight->right != cur) {
					++leftHight;
					mostRight = mostRight->right;
				}
				if (!mostRight->right) {	// 第一次到达
					mostRight->right = cur;
					cur = cur->left;
					++curLevel;
					continue;
				} else {	// 第二次到达
					if (!mostRight->left) {
						minHeight = min(minHeight, curLevel);
					}
					curLevel -= leftHight;
					mostRight->right = nullptr;
				}
			} else {
				++curLevel;
			}
			cur = cur->right;
		}
		int finalRight = 1;
		cur = head;
		while (cur->right) {
			++finalRight;
			cur = cur->right;
		}
		if (!cur->left && !cur->right) {
			minHeight = min(minHeight, finalRight);
		}
		return minHeight;
	}

	void test() {
		Node a(1), b(2), c(3), d(4), e(5), f(6), g(7);
		a.left = &b;
		b.right = &c;
		a.right = &d;
		d.left = &e;
		e.right = &f;
		f.right = &g;

		cout << minHeight1(&a) << " " << minHeight2(&a) << endl;
	}

};

//Segment tree----------------------------------------------------------------------------------------

class SegmentTree {
public:
	int MAXN;
	vector<int> arr;
	vector<int> sum;	// sum[]模拟线段树维护区间和
	vector<int> lazy;	// lazy[]为累加懒惰标记
	vector<int> change;	// change[]为更新的值
	vector<bool> update;// update[]为更新懒惰标记

	SegmentTree(const vector<int>& origin) {
		MAXN = origin.size() + 1;
		arr.resize(MAXN);	// arr[0]不用，从下标1开始
		for (int i = 1; i < MAXN; ++i) {
			arr[i] = origin[i - 1];
		}
		sum.resize(MAXN << 2);
		lazy.resize(MAXN << 2);
		change.resize(MAXN << 2);
		update.resize(MAXN << 2);
	}

	// 初始化阶段，先把sum数组填好
	// 在arr[l..r]范围上，去build,1~N;
	// rt:这个范围在sum中的下标 
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
	// 之前所有的懒增加和懒更新，从父范围，发给左右两个子范围
	// ln表示左子树元素节点个数，rn表示右子树节点个数
	void pushDown(int rt, int ln, int rn) {
		if (update[rt]) {
			update[rt << 1] = true;
			update[rt << 1 | 1] = true;

			change[rt << 1] = change[rt];
			change[rt << 1 | 1] = change[rt];

			lazy[rt << 1] = 0;
			lazy[rt << 1 | 1] = 0;

			sum[rt << 1] = change[rt] * ln;
			sum[rt << 1 | 1] = change[rt] * rn;
			update[rt] = false;

		}

		if (lazy[rt] != 0) {
			lazy[rt << 1] += lazy[rt];
			sum[rt << 1] += lazy[rt] * ln;
			lazy[rt << 1 | 1] += lazy[rt];
			sum[rt << 1 | 1] += lazy[rt] * rn;
			lazy[rt] = 0;
		}
	}

	void pushUp(int rt) {
		sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	}

	// L...R 为任务范围，所有的值累加上C
	// l...r 为表达的范围， rt 为去哪里找l...r范围上的信息
	void add(int L, int R, int C, int l, int r, int rt) {
		// 任务的范围彻底覆盖了当前表达的范围
		if (L <= l && R >= r) {
			sum[rt] += C * (r - l + 1);
			lazy[rt] += C;
			return;
		}
		// 任务并没有把l...r全包，要把当前任务下发
		int mid = (l + r) >> 1;
		// 下发之前的攒的所有懒任务
		pushDown(rt, mid - l + 1, r - mid);
		// 左孩子是否需要接受任务
		if (L <= mid) {
			add(L, R, C, l, mid, rt << 1);
		}
		if (R > mid) {
			add(L, R, C, mid + 1, r, rt << 1 | 1);
		}
		// 左右孩子做完任务后，我更新我的sum信息
		pushUp(rt);
	}

	void upDate(int L, int R, int C, int l, int r, int rt) {
		if (L <= l && R >= r) {
			update[rt] = true;
			change[rt] = C;
			sum[rt] = C * (r - l + 1);
			lazy[rt] = 0;
			return;
		}
		// 当前任务懒不住，先下发
		int mid = (l + r) >> 1;
		pushDown(rt, mid - l + 1, r - mid);
		if (L <= mid) {
			upDate(L, R, C, l, mid, rt << 1);
		}
		if (R > mid) {
			upDate(L, R, C, mid + 1, r, rt << 1 | 1);
		}
		pushUp(rt);
	}

	long long query(int L, int R, int l, int r, int rt) {
		if (L <= l && R >= r) {
			return sum[rt];
		}
		int mid = (l + r) >> 1;
		pushDown(rt, mid - l + 1, r - mid);
		long long ans = 0;
		if (L <= mid) {
			ans += query(L, R, l, mid, rt << 1);
		}
		if (R > mid) {
			ans += query(L, R, mid + 1, r, rt << 1 | 1);
		}
		return ans;
	}
};

// 比较器，测试线段树算法是否正确
class Right {
public:
	vector<int> arr;
	Right(const vector<int>& orgin) {
		arr.resize(orgin.size() + 1);
		for (int i = 0; i < orgin.size(); ++i) {
			arr[i + 1] = orgin[i];
		}
	}
	void update(int L, int R, int C) {
		for (int i = L; i <= R; ++i) {
			arr[i] = C;
		}
	}

	void add(int L, int R, int C) {
		for (int i = L; i <= R; ++i) {
			arr[i] += C;
		}
	}
	long long query(int L, int R) {
		long long ans = 0;
		for (int i = L; i <= R; ++i) {
			ans += arr[i];
		}
		return ans;
	}
};
vector<int> genarateRandomArray(int len, int maxN) {
	int size = (int)(rand() % len) + 1;
	vector<int> orgin(size);
	for (int i = 0; i < size; ++i) {
		orgin[i] = (int)(rand() % maxN) - (int)(rand() % maxN);
	}
	return orgin;
}
bool testSegmentTree() {

	srand(time(NULL));
	int len = 100;
	int maxN = 1000;
	int testTimes = 5000;
	int addOrUpdateTimes = 1000;
	int queryTimes = 500;
	for (int i = 0; i < testTimes; ++i) {
		vector<int> orgin = genarateRandomArray(len, maxN);
		SegmentTree seg(orgin);
		int S = 1;
		int N = orgin.size();
		int root = 1;
		seg.build(S, N, root);
		Right rig(orgin);
		for (int j = 0; j < addOrUpdateTimes; ++j) {
			int num1 = (int)(rand() % N) + 1;
			int num2 = (int)(rand() % N) + 1;
			int L = min(num1, num2);
			int R = max(num1, num2);
			int C = (int)(rand() % maxN) - (int)(rand() % maxN);
			if (rand() % 10 < 5) {
				seg.add(L, R, C, S, N, root);
				rig.add(L, R, C);
			} else {
				seg.upDate(L, R, C, S, N, root);
				rig.update(L, R, C);
			}

		}

		for (int k = 0; k < queryTimes; ++k) {
			int num1 = (int)(rand() % N) + 1;
			int num2 = (int)(rand() % N) + 1;
			int L = min(num1, num2);
			int R = max(num1, num2);
			long long ans1 = seg.query(L, R, S, N, root);
			long long ans2 = rig.query(L, R);
			if (ans1 != ans2) {
				return false;
			}
		}
	}
	return true;
}

// 想象一下标准的俄罗斯方块游戏，X轴是积木最终下落到底的轴线下面是这个游戏的简化版:
// 1)只会下落正方形积木
// 2)[a, b]->代表一个边长为b的正方形积木，积木左边缘沿着× = a这条线从上方掉落3)认为整个X轴都可能接住积木，也就是说简化版游戏是没有整体的左右边界的4）没有整体的左右边界，所以简化版游戏不会消除积木，因为不会有哪一层被填满。
// 给定一个N * 2的二维数组matrix，可以代表N个积木依次掉落，
// 返回每一次掉落之后的最大高度


class FallingSquares {
public:
	class SegmentTree {
		vector<int> maxH;
		vector<int> change;
		vector<bool> update;

		void pushUp(int rt) {
			maxH[rt] = max(maxH[rt << 1], maxH[rt << 1 | 1]);
		}

		void pushDown(int rt, int ln, int rn) {
			if (update[rt]) {
				update[rt << 1] = true;
				update[rt << 1 | 1] = true;
				change[rt << 1] = change[rt];
				change[rt << 1 | 1] = change[rt];
				maxH[rt << 1] = change[rt];
				maxH[rt << 1 | 1] = change[rt];
				update[rt] = false;
			}
		}
	public:
		SegmentTree(int size) {
			int N = size + 1;
			maxH.resize(N << 2);
			change.resize(N << 2);
			update.resize(N << 2);
		}
		int query(int L, int R, int l, int r, int rt) {
			if (L <= l && r <= R) {
				return maxH[rt];
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			int left = 0, right = 0;
			if (L <= mid) {
				left = query(L, R, l, mid, rt << 1);
			}
			if (R > mid) {
				right = query(L, R, mid + 1, r, rt << 1 | 1);
			}
			return max(left, right);
		}
		void upDate(int L, int R, int C, int l, int r, int rt) {
			if (L <= l && r <= R) {
				update[rt] = true;
				change[rt] = C;
				maxH[rt] = C;
				return;
			}
			int mid = (l + r) >> 1;
			pushDown(rt, mid - l + 1, r - mid);
			if (L <= mid) {
				upDate(L, R, C, l, mid, rt << 1);
			}
			if (R > mid) {
				upDate(L, R, C, mid + 1, r, rt << 1 | 1);
			}
			pushUp(rt);
		}

	};
	unordered_map<int, int> index(const vector<vector<int>>& positions) {
		set<int> pos;
		for (auto arr : positions) {
			pos.insert(arr[0]);
			pos.insert(arr[0] + arr[1] - 1);
		}
		unordered_map<int, int> map;
		int cnt = 0;
		for (auto index : pos) {
			map[index] = ++cnt;
		}
		return map;
	}


	vector<int> fallingSquares(const vector<vector<int>>& positions) {
		unordered_map<int, int> m = index(positions);
		int N = m.size();
		SegmentTree seg(N);
		int maxH = 0;
		vector<int> res;
		for (auto arr : positions) {
			int L = m[arr[0]];
			int R = m[arr[0] + arr[1] - 1];
			int H = seg.query(L, R, 1, N, 1) + arr[1];
			maxH = max(maxH, H);
			res.push_back(maxH);
			seg.upDate(L, R, H, 1, N, 1);
		}
		return res;
	}
};


// 给你x轴上不同范围的线段，求线段重叠的最多条数
class CoverMax {
public:

	// 暴力，重叠的区间最小为1，单位枚举每次个区间
	int maxCover1(const vector<vector<int>>& lines) {
		int left = INT_MAX;
		int right = INT_MIN;
		for (int i = 0; i < lines.size(); ++i) {
			left = min(left, lines[i][0]);
			right = max(right, lines[i][1]);
		}
		int cover = 0;
		for (double p = left + 0.5; p < right; p += 1) {
			int cur = 0;
			for (int i = 0; i < lines.size(); ++i) {
				if (lines[i][0]<p && lines[i][1]>p) {
					++cur;
				}
			}
			cover = max(cover, cur);
		}
		return cover;
	}

	// 先给所有线段排序，起点小的排在前面，终点无所谓。再遍历每条线段，堆中小于当前线段的start的pop,再把当前线段的end入堆
	// 当前堆中元素的个数即为当前面可能的最大值
	int maxCover2(vector<vector<int>>& m) {
		sort(m.begin(), m.end(), [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
		/*auto cmp = [](const vector<int>& a, const vector<int>& b) { return a[1] > b[1]; };
		priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> heap(cmp);
		int res = 0;
		for (int i = 0; i < m.size(); ++i) {
			while (!heap.empty() && heap.top()[1] <= m[i][0]) {
				heap.pop();
			}
			heap.push(m[i]);
			res = max(res, (int)heap.size());
		}*/

		priority_queue<int, vector<int>, greater<int>> heap;
		int res = 0;
		for (int i = 0; i < m.size(); ++i) {
			while (!heap.empty() && heap.top() <= m[i][0]) {
				heap.pop();
			}
			heap.push(m[i][1]);
			res = max(res, (int)heap.size());
		}
		return res;
	}

	bool test() {
		srand(time(NULL));
		int maxRight = 50;
		int minLeft = 0;
		int testTime = 100;
		int maxLength = 50;
		for (int i = 0; i < testTime; ++i) {
			vector<vector<int>> arr;
			for (int j = 0; j < maxLength; ++j) {
				int a = rand() % maxRight;
				int b = rand() % maxRight;
				auto ret = minmax(a, b);
				arr.push_back({ ret.first, ret.second + 1 });
			}
			auto brr = arr;
			if (maxCover1(arr) != maxCover2(brr)) {
				return false;
			}
		}

		return true;
	}
};

// 给定一些矩形，用两点来表示（左上角，右下角）,求最多重叠矩形的个数
class CoverRectangleMax {
public:
	class Rectangle {
	public:
		int up, down, left, right;
		Rectangle(int u, int d, int l, int r) :up(u), down(d), left(l), right(r) {}
	};
	class CmpLeft {
	public:
		bool cmp(const Rectangle& a, const Rectangle& b) { return a.left < b.left; }
	};
	class CmpRight {
	public:
		bool cmp(const Rectangle& a, const Rectangle& b) { return a.right < b.right; }
	};
	// O(N^2*logN)
	int maxCover(vector<Rectangle> recs) {
		if (recs.size() == 0) {
			return 0;
		}
		// 根据down(底）进行排序 O(N*LogN)
		sort(recs.begin(), recs.end(), [](const Rectangle& a, const Rectangle& b) {return a.down < b.down; });
		// 可能会对当前底边的公共区域，产生影响的矩形
		set<Rectangle,CmpLeft> leftOrdered;
		int ans = 0;

		// 依次考察每个矩形的边
		for (int i = 0; i < recs.size();) {	//O(N)
			do {
				leftOrdered.insert(recs[i++]);
			} while (i < recs.size() && recs[i].down == recs[i - 1].down);
			// 清除顶<=当前底的矩形  O(N)
			removeLowerOnCurDown(leftOrdered, recs[i - 1].down);	
			// 维持了右边界排序的容器
			set<Rectangle, CmpRight> rightOrdered;
			// O(N *LogN)
			for (auto rec : leftOrdered) {
				removeLeftOnCurLeft(rightOrdered, rec.left);
				rightOrdered.insert(rec);
				ans = max(ans, (int)rightOrdered.size());
			}
		}
		return ans;
	}

	void removeLowerOnCurDown(set<Rectangle, CmpLeft>& se, int curDown) {
		vector<Rectangle> removes;
		for (auto& rec : se) {
			if (rec.up <= curDown) {
				removes.push_back(rec);
			}
		}
		for (auto rec : removes) {
			se.erase(rec);
		}
	}

	void removeLeftOnCurLeft(set<Rectangle,CmpRight>& rightOrdered, int curLeft) {
		vector<Rectangle> removes;
		for (auto& rec : rightOrdered) {
			if (rec.right <= curLeft) {
				removes.push_back(rec);
			}
		}
		for (auto rec : removes) {
			rightOrdered.erase(rec);
		}
	}
};
