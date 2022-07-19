// bfprt----------------------------------------------------------------

// 给定n个无序元素，请找出第K小的
class FindMinKthP {
public:
	// 时间O（N）
	int minKth2(vector<int> array, int k) {
		return process2(array, 0, array.size() - 1, k - 1);
	}
	// arr[L...R]范围上，如果排序的话，找位于index的数
	int process2(vector<int>& arr, int L, int R, int index) {
		if (L == R) {
			return arr[L];
		}

		int pivot = arr[L + rand() % (R - L + 1)];
		//cout << "rand:" << pivot << endl;
		vector<int> rge = partition(arr, L, R, pivot);	// 荷兰国旗问题
		if (index >= rge[0] && index <= rge[1]) {
			return arr[index];
		} else if (index < rge[0]) {
			return process2(arr, L, rge[0] - 1, index);
		} else {
			return process2(arr, rge[1] + 1, R, index);
		}
	}

	vector<int> partition(vector<int>& arr, int L, int R, int pivot) {
		int less = L - 1;
		int more = R + 1;
		int cur = L;
		while (cur < more) {
			if (arr[cur] < pivot) {
				swap(arr[++less], arr[cur++]);
			} else if (arr[cur] > pivot) {
				swap(arr[cur], arr[--more]);
			} else {
				++cur;
			}
		}
		return { less + 1,more - 1 };
	}

	// 利用bfprt算法，时间O（N）
	// bfprt算法：arr[L..R] 如果排序的话，位于index位置的是什么
	// 1）五个五个的划分
	// 2) 五个数内部进行排序，取出中间值
	// 3）取出的中间值作为一个数组marr，再调用bfprt(marr,0, marr.size() - 1, marr.size() / 2)取出marr的中位数
	//这样每次可固定舍掉10/3的范围
	int minKth3(vector<int> array, int k) {
		return bfprt(array, 0, array.size() - 1, k - 1);
	}
	// arr[L..R] 如果排序的话，位于index位置的是什么（index一定再arr范围中）
	int bfprt(vector<int>& arr, int L, int R, int index) {
		if (L == R) {
			return arr[L];
		}
		int pivot = medianOfMedians(arr, L, R);
		vector<int> rge = partition(arr, L, R, pivot);
		if (index >= rge[0] && index <= rge[1]) {
			return arr[index];
		} else if (index < rge[0]) {
			return bfprt(arr, L, rge[0] - 1, index);
		} else {
			return bfprt(arr, rge[1] + 1, R, index);
		}
	}

	// arr[L...R] 五个数一组
	// 每个小组内部排序
	// 每个小组中位数拎出来，组成marr
	// marr中的中位数，返回
	int medianOfMedians(vector<int> arr, int L, int R) {
		int size = R - L + 1;
		// 有没有多余的一组（不够五个数）
		int offset = size % 5 == 0 ? 0 : 1;
		vector<int> marr(size / 5 + offset);
		for (int team = 0; team < marr.size(); ++team) {
			int teamFirst = L + team * 5;
			marr[team] = getMedian(arr, teamFirst, min(R, teamFirst + 4));
		}
		return bfprt(marr, 0, marr.size() - 1, marr.size() / 2);
	}
	int getMedian(vector<int>& arr, int L, int R) {
		insertionSort(arr, L, R);
		return arr[(L + R) / 2];
	}
	void insertionSort(vector<int>& arr, int L, int R) {
		for (int i = L + 1; i <= R; ++i) {
			for (int j = i - 1; j >= L && arr[j] > arr[j + 1]; --j) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}



	void test() {
		srand(time(NULL));
		vector<int> arr = { 3,6,1,6,3,8,9,0,4,22,11,5,6,8,2,73,34,66,26,26 };
		vector<int> ret1 = arr;
		sort(ret1.begin(), ret1.end());
		//cout << process2(arr, 0, arr.size() - 1, 10) << " " << ret1[10] << endl;
		cout << minKth2(arr, 10) << " " << minKth3(arr, 10) << " " << ret1[9] << endl;
	}
};


// Manacher-------------------------------------------------------------------------------------------------------------
// 线性时间内解决最大回文字串
// 先了解下变量含义，pArr[i] 表示以i为中心的最长回文串的半径，R是目前最长的回文串的右边界，C是目前最长的回文串的中点。R,C初始时均为-1
// 步骤：原串前后中间间隙插入字符，
//	   从左往右枚举回文中心i，
//		1).若i在R外，暴力扩
//		2).若i在R内（设i关于C的对称点为i1）
//			a. i1的回文区域全在在L,R内，pArr[i]=pArr[i1]
//			b. i1的回文区域在L,R外部，pArr[i]=R-i
//			c. i1的回文区域左边界和L压线，从R开始往外扩
//    R整体最多到N,而a,b分支是O(1)，所以算法整体O(N)
class Manacher {
public:
	int manacher(const string& s) {
		if (s.size() == 0) {
			return 0;
		}
		//"12321" -> "#1#2#3#2#1#"
		string str = manacherString(s);
		// 回文半径的大小
		vector<int> pArr(str.size());	// 回文半径数组
		// C是让R扩张的回文中心
		int C = -1;
		// 讲述中R代表最右的扩成功的位置，在这里，最右的扩张成功位置，在下一个位置
		int R = -1;
		int ret = INT_MIN;	//返回值，记录半径
		// 以i为回文中心共有四中情况
		// 1)i在R外
		// （i在R内，设i1为i关于C的对称点）
		// 2）i1的回文半径 i1在L..R内
		// 3）i1回文半径的左边界在L..R外
		// 4）i1回文半径和L重合
		for (int i = 0; i < str.size(); ++i) {
			// i位置扩出来的答案，i位置扩的区域，至少是多少
			// 如果i在R外，即i>=R(R是第一个违规的位置）  (pArr[2*C-i]是i的对称点）
			pArr[i] = R > i ? min(pArr[2 * C - i], R - i) : 1;	//不用查验的位置先设置到pArr[i]
			//上面一行直接攘括了4种情况不用验的区域


			//情况2,3一进循环就会break
			while (i + pArr[i]<str.size() && i - pArr[i]>-1) {	//循环条件是防止扩的过程种超出左右边界
				// if就是以i为中心，左右扩，否则不能扩了
				if (str[i + pArr[i]] == str[i - pArr[i]]) {
					++pArr[i];
				} else {
					break;
				}

			}

			// i位置扩出来的答案超过了R
			if (i + pArr[i] > R) {
				R = i + pArr[i];
				C = i;
			}
			ret = max(ret, pArr[i]);
		}

		return ret - 1;	//ret记录的是manacherString中的最大回文半径，还需-1，得到原本的长度
	}
	string manacherString(const string& s) {
		string res(s.size() * 2 + 1, '0');
		int index = 0;
		for (int i = 0; i != res.size(); ++i) {
			res[i] = (i & 1) == 0 ? '#' : s[index++];
		}
		return res;
	}
};

// 给你一个字符串str,只能在其后添加字符串，要求添加最少符串使其整体成为回文串
// 解：找出必须包含最后一个字符的最大回文字串，让后将前面的部分逆序追加到字符串后
//     从左到右，找到第一个包含最后一个字符，即是包含最后一个字符的最大回文字串

class AddShortestEnd {
public:
	string shortestEnd(string s) {
		if (s.size() == 0) {
			return string();
		}
		string str = manacherString(s);
		vector<int> pArr(str.size());
		int C = -1;
		int R = -1;
		int maxCntEnd = -1;	//记录包含最后一个字符的回文字串的半径
		for (int i = 0; i < str.size(); ++i) {
			pArr[i] = R > i ? min(pArr[2 * C - i], R - i) : 1;	//不用查验的位置先设置到pArr[i]
			while (i + pArr[i]<str.size() && i - pArr[i]>-1) {	//循环条件是防止扩的过程种超出左右边界
				if (str[i + pArr[i]] == str[i - pArr[i]]) {
					++pArr[i];
				} else {
					break;
				}
			}
			if (i + pArr[i] > R) {
				R = i + pArr[i];
				C = i;
			}
			if (R == str.size()) {
				maxCntEnd = pArr[i];
				break;
			}
		}

		auto ret = s.substr(0, s.size() - maxCntEnd + 1);
		reverse(ret.begin(), ret.end());
		return ret;
	}

	string manacherString(const string& s) {
		string res(s.size() * 2 + 1, '0');
		int index = 0;
		for (int i = 0; i != res.size(); ++i) {
			res[i] = (i & 1) == 0 ? '#' : s[index++];
		}
		return res;
	}

	void test() {
		Manacher m;
		string s = "abcd123321";

		cout << m.manacher(s) << " " << shortestEnd(s) << endl;
	}
};
