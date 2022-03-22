
//滑动窗口


//假设一个固定大小为W的窗口，依次划过arr, 返回每一次滑出状况的最大值
//例如, arr = [4, 3,5,4, 3, 3, 6, 7], W = 3返回: [5,5, 5, 4, 6, 7]

class SlidingWindowMaxArray {
public:
	vector<int> getMaxWindow(const vector<int>& arr, int w) {
		if (arr.size() < w || w < 1) {
			return {};
		}
		//其中放的是位置，头代表（大 ->小）  
		list<int> qmax;
		vector<int> ans;
		int index = 0;
		for (int i = 0; i < arr.size(); ++i) {
			//当前让i->arr[i]进窗口，i就是R

			while (!qmax.empty() && arr[qmax.back()] <= arr[i]) {
				qmax.pop_back();
			}
			qmax.push_back(i);
			//如果双端队列头值等于窗口左边界的过期下标的话
			if (qmax.front() == i - w) {
				qmax.pop_front();
			}
			if (i >= w - 1) {
				ans.push_back(arr[qmax.front()]);
			}

		}
		return ans;
	}
	void test() {
		vector<int> arr = { 4, 3,5,4, 3, 3, 6, 7 };

		auto ret = getMaxWindow(arr, 3);
		for (auto i : ret) {
			cout << i << " ";
		}
		cout << endl;
	}

};


//给定一个整型数组arr，和一个整数num
//某个arr中的子数组sub，如果想达标，必须满足 : sub中最大值 - sub中最小值 <= num,
//返回arr中达标子数组的数量

//窗口内最最大值和最小值的更新结构
class AllLessNumSubArray {
public:
	//暴力O（N^3)
	int getNumBao(const vector<int>& arr, int num) {
		if (arr.size() == 0) {
			return 0;
		}
		int ans = 0;
		for (int L = 0; L < arr.size(); ++L) {
			for (int R = L; R < arr.size(); ++R) {
				auto ret = minmax_element(arr.begin() + L, arr.begin() + R + 1);
				if (*ret.second - *ret.first <= num) {
					++ans;
				}

			}
		}
		return ans;
	}

	//滑动窗口O（N)
	//数组中的所有元素最多只有两次次入队列和出队列
	int getNum(const vector<int>& arr, int num) {
		if (arr.size() == 0) {
			return 0;
		}
		list<int> qmin, qmax;
		int ans = 0, L = 0, R = 0;
		//[L,R)左闭右开区间
		while (L < arr.size()) {
			//L是开头位置，尝试每一个开头
			// 如果此时窗口的开头是L，下面的while工作：R向右扩到违规为止
			while (R < arr.size()) {	// R是最后一个达标位置的再下一个
				while (!qmin.empty() && arr[qmin.back()] >= arr[R]) {
					qmin.pop_back();
				}
				qmin.push_back(R);

				while (!qmax.empty() && arr[qmax.back() <= arr[R]]) {
					qmax.pop_back();
				}
				qmax.push_back(R);

				if (arr[qmax.front()] - arr[qmin.front()] > num) {
					//此时的窗口范围的最大最小值已近不满足<=num的要求，也就不必要在向右扩张
					break;
				}
				++R;
			}
			ans += R - L;

			if (L == qmax.front()) {
				qmax.pop_front();
			}
			if (L == qmin.front()) {
				qmin.pop_front();
			}

			++L;
		}
		return ans;
	}


	void test() {
		vector<int> arr = { 1,2,4,3,5 };
		cout << getNum(arr, 3) << " " << getNumBao(arr, 3);
	}
};


//优化：
//数据状况	（此题，若一范围达标，缩小的必打表，扩大的必不达标）
//问题本身	问题和范围建立单调性，首尾指针同理 



//单调栈
//问题：在一个数组中，返回每一个位置的数，离它左边最近的比它小的数和离它右边最近的比他小的数

//在栈中要维持从下往上是从小到大的顺序（入栈的是下标，下标对应的数字应维持从小到大）
class MonotonousStack {
public:
	//数组中没有重复值,如果要入栈的值不能按照大小顺序入栈，那么要弹出，弹出的数字的右边答案为要入栈的，左边答案为弹出的数字下方的数字
	vector<vector<int>> getNearLessNoRepeat(const vector<int>& arr) {
		vector<vector<int>> res(arr.size(), vector<int>(2));
		stack<int> st;
		for (int i = 0; i < arr.size(); ++i) {
			while (!st.empty() && arr[st.top()] > arr[i]) {
				int popIndex = st.top();
				st.pop();
				int leftLessIndex = st.empty() ? -1 : st.top();	//如果栈不为空，左边的答案即为当期栈顶（因为被求答案的数字已近被弹出）
				res[popIndex][0] = leftLessIndex;
				res[popIndex][1] = i;
			}
			st.push(i);
		}

		while (!st.empty()) {
			int popIndex = st.top();
			st.pop();
			int leftLessIndex = st.empty() ? -1 : st.top();
			res[popIndex][0] = leftLessIndex;
			res[popIndex][1] = -1;	//因为此时的数字并不是因为新数字的进入而出栈，所以栈中右边的答案即为-1,表示找不到这样的数字
		}
		return res;
	}

	//数组中有重复元素
	vector<vector<int>> getNearLess(const vector<int>& arr) {
		vector<vector<int>> res(arr.size(), vector<int>(2));
		// list<int> 放的是位置（下标）同样值的东西，位置压在一起
		stack<list<int>> st;
		for (int i = 0; i < arr.size(); ++i) {	// i->arr[i]进栈
			//同样的 栈中从底到顶的顺序是从小到大
			while (!st.empty() && arr[st.top().front()] > arr[i]) {
				list<int> popLs = st.top();
				st.pop();
				//取决于下面位置的列表中，最晚加入的那个
				int leftLessIndex = st.empty() ? -1 : st.top().back();
				for (auto popi : popLs) {
					res[popi][0] = leftLessIndex;
					res[popi][1] = i;
				}
			}
			//相等的、比你小的
			if (!st.empty() && arr[st.top().front()] == arr[i]) {
				st.top().push_back(i);
			} else {
				list<int> li;
				li.push_back(i);
				st.emplace(li);
			}
		}
		while (!st.empty()) {
			list<int> popLs = st.top();
			st.pop();
			// 取决于下面位置的链表中，最晚加入的那个
			int leftLessIndex = st.empty() ? -1 : st.top().back();
			for (auto i : popLs) {
				res[i][0] = leftLessIndex;
				res[i][1] = -1;
			}
		}
		return res;
	}

	void test() {
		vector<int> arr = { 3,4,2,5,6,0,1 };
		auto ret1 = getNearLessNoRepeat(arr);

		vector<int> arr1 = { 3,3,4,2,5,5,6,0,1 };

		auto ret2 = getNearLess(arr1);

	}
};
//单调性，发现它的范围和它要求解的问题的指标之间存不存在，范围变大，指标变大，或范围变大，指标变小






//问题三：
//给定一个只包含正整数的数组arr, arr中任何一个子数组sub,一定都可以算出(sub累加和)* (sub中的最小值)是什么
//那么所有子数组中，这个值最大是多少 ?

//首先做预处理求前缀和，再枚举以i位置为最小值的 累加和*最小值 的最大值
class Solution {
public:
	int getMaxSubArray(const vector<int>& arr) {
		int n = arr.size();
		//前缀和
		vector<int> prefix(n);
		prefix[0] = arr[0];
		for (int i = 1; i < n; ++i) {
			prefix[i] = prefix[i - 1] + arr[i];
		}

		//单调栈
		vector<vector<int>> res(arr.size(), vector<int>(2));
		// list<int> 放的是位置（下标）同样值的东西，位置压在一起
		stack<list<int>> st;
		for (int i = 0; i < arr.size(); ++i) {	// i->arr[i]进栈
			//同样的 栈中从底到顶的顺序是从小到大
			while (!st.empty() && arr[st.top().front()] > arr[i]) {
				list<int> popLs = st.top();
				st.pop();
				//取决于下面位置的列表中，最晚加入的那个
				int leftLessIndex = st.empty() ? -1 : st.top().back();
				for (auto popi : popLs) {
					res[popi][0] = leftLessIndex;
					res[popi][1] = i;
				}
			}
			//相等的、比你小的
			if (!st.empty() && arr[st.top().front()] == arr[i]) {
				st.top().push_back(i);
			} else {
				list<int> li;
				li.push_back(i);
				st.emplace(li);
			}
		}
		while (!st.empty()) {
			list<int> popLs = st.top();
			st.pop();
			// 取决于下面位置的链表中，最晚加入的那个
			int leftLessIndex = st.empty() ? -1 : st.top().back();
			for (auto i : popLs) {
				res[i][0] = leftLessIndex;
				res[i][1] = -1;
			}
		}

		int ret = 0;
		//枚举子数组最小值
		for (int i = 0; i < n; ++i) {
			//子数组左右边界，左开右闭
			int left = res[i][0] == -1 ? 0 : prefix[res[i][0]];
			int right = res[i][1] == -1 ? prefix[n - 1] : prefix[res[i][1] - 1];
			ret = max(ret, arr[i] * (right - left));
		}
		return ret;
	}
	void test() {
		vector<int> arr = { 3,4,5,6,2,7 };
		cout << getMaxSubArray(arr) << endl;
	}
};