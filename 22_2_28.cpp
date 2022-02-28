////844. 比较含退格的字符串
////法一：模拟重构
//class Solution {
//public:
//	bool backspaceCompare(string s, string t) {
//		string ret1, ret2;
//		for (auto c : s) {
//
//			if (c != '#') {
//				ret1.push_back(c);
//			} else if (!ret1.empty()) {
//				ret1.pop_back();
//			}
//
//		}
//
//		for (auto c : t) {
//			if (c != '#') {
//				ret2.push_back(c);
//			} else if (!ret2.empty()) {
//				ret2.pop_back();
//			}
//		}
//
//		if (ret1 == ret2) {
//			return true;
//		}
//		return false;
//	}
//};
//
////法二：双指针
////从后往前遍历，遇到‘#'就说明需要删除一个字符
//class Solution {
//public:
//    bool backspaceCompare(string S, string T) {
//        int i = S.length() - 1, j = T.length() - 1;
//        int skipS = 0, skipT = 0;
//
//        while (i >= 0 || j >= 0) {
//            //下面这里的一个while是确定一个字符
//            while (i >= 0) {
//                if (S[i] == '#') {
//                    //记录跳过的个数，同时跳过‘#’
//                    skipS++, i--;
//                } else if (skipS > 0) {
//                    //遇到非‘#’，开始跳过skipS个字符
//                    skipS--, i--;
//                } else {
//                    break;
//                }
//            }
//            while (j >= 0) {
//                if (T[j] == '#') {
//                    skipT++, j--;
//                } else if (skipT > 0) {
//                    skipT--, j--;
//                } else {
//                    break;
//                }
//            }
//            if (i >= 0 && j >= 0) {
//                if (S[i] != T[j]) {
//                    return false;
//                }
//            } else {
//                if (i >= 0 || j >= 0) {
//                    return false;
//                }
//            }
//            i--, j--;
//        }
//        return true;
//    }
//};
//
//
//
////986. 区间列表的交集
////归并区间
//class Solution {
//public:
//    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
//        vector<vector<int>> ret;
//        int i = 0, j = 0;
//        while (i < firstList.size() && j < secondList.size()) {
//            //为求两区间的交区间[low,high]
//            //low为两个区间左边界的最大值
//            //high为两个区间右边界的最小值
//            int low = max(firstList[i][0], secondList[j][0]);
//            int high = min(firstList[i][1], secondList[j][1]);
//            if (low <= high) {
//                ret.push_back({ low,high });
//            }
//            //两个区间中的最大右边界可能会和另一个区间的下一个区间相交，
//            //所以最大的右边界区间依然是其自身，另一个区间迭代其下一个区间
//            if (firstList[i][1] < secondList[j][1]) {
//                ++i;
//            } else {
//                ++j;
//            }
//        }
//        return ret;
//    }
//};



////11. 盛最多水的容器
////法一：枚举(超时）
////时间O（N^2)
//class Solution {
//public:
//	int maxArea(vector<int>& height) {
//		int ret = 0;
//		for (int i = 0; i < height.size(); ++i) {
//			for (int j = i; j < height.size(); ++j) {
//				ret = max(ret, (j - i) * min(height[i], height[j]));
//			}
//		}
//		return ret;
//	}
//};
//
////法二：
////双指针
////面积受限于底和高，开始先从最左和最右开始，此时的底最大，若想让面积更大，只有更短的边变长才可能，所以向内找可能的更长的边
//class Solution {
//public:
//	int maxArea(vector<int>& height) {
//		int left = 0, right = height.size() - 1;
//		int x = 0, y = 0;
//		int ret = 0;
//		while (left <= right) {
//			int tmp = min(height[left], height[right]) * (right - left);
//			if (tmp > ret) {
//				ret = tmp;
//				x = left;
//				y = right;
//			}
//			//左边高
//			if (height[left] < height[right]) {
//				while (++left < height.size() && height[left] <= height[x]) {}
//			} else {
//				//右边高
//				while (--right >= 0 && height[right] <= height[y]) {}
//			}
//		}
//		return ret;
//	}
//};
////或
//class Solution {
//public:
//	int maxArea(vector<int>& height) {
//		int l = 0, r = height.size() - 1;
//		int ans = 0;
//		while (l < r) {
//			int area = min(height[l], height[r]) * (r - l);
//			ans = max(ans, area);
//			if (height[l] <= height[r]) {
//				++l;
//			} else {
//				--r;
//			}
//		}
//		return ans;
//	}
//};
//


//438. 找到字符串中所有字母异位词
//法一：暴力匹配(超时）
//先算出p的所有全排列，再依次遍历s对比
class Solution {
public:

	void dfs(string p, vector<bool> vis, int index, string& tmp, vector<string>& comb) {
		if (index == p.size()) {
			if (tmp.size() != p.size()) {
				return;
			}
			comb.push_back(tmp);
			return;
		}
		for (int i = 0; i < p.size(); ++i) {
			if (vis[i]) {
				continue;
			}
			tmp += p[i];
			vis[i] = true;
			dfs(p, vis, index + 1, tmp, comb);
			tmp.pop_back();
			vis[i] = false;
		}
	}
	vector<int> findAnagrams(string s, string p) {
		//p的全排列
		vector<string> comb;
		vector<int> ret;
		int lenP = p.size();
		vector<bool> vis(lenP);
		string tmp;
		dfs(p, vis, 0, tmp, comb);
		for (int i = 0; i <= s.size() - lenP; ++i) {
			for (int j = 0; j < comb.size(); ++j) {
				if (s.substr(i, lenP) == comb[j]) {
					ret.push_back(i);
					break;
				}
			}
		}
		return ret;
	}
};


//法二：统计词频+滑动窗口
class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		map<char, int> m,comp;
		for (auto c : p) {
			++m[c];
		}
		vector<int> ret;
		int lenP = p.size();
		for (int i = 0; i < lenP; ++i) {
			++comp[s[i]];
		}
		if (m == comp) {
			ret.push_back(0);
		}
		for (int i = lenP; i < s.size(); ++i) {
			if (comp.find(s[i - lenP]) != comp.end()) {
				--comp[s[i - lenP]];
				if (comp[s[i - lenP]] == 0) {
					comp.erase(s[i - lenP]);
				}
			}
			++comp[s[i]];
			if (comp == m) {
				ret.push_back(i - lenP+1);
			}
		}
		return ret;
	}
};

//或
class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		int sLen = s.size(), pLen = p.size();

		if (sLen < pLen) {
			return vector<int>();
		}

		vector<int> ans;
		vector<int> sCount(26);
		vector<int> pCount(26);
		for (int i = 0; i < pLen; ++i) {
			++sCount[s[i] - 'a'];
			++pCount[p[i] - 'a'];
		}

		if (sCount == pCount) {
			ans.emplace_back(0);
		}

		for (int i = 0; i < sLen - pLen; ++i) {
			--sCount[s[i] - 'a'];
			++sCount[s[i + pLen] - 'a'];

			if (sCount == pCount) {
				ans.emplace_back(i + 1);
			}
		}

		return ans;
	}
};

//法三：优化的滑动窗口
//不再分别统计滑动窗口和字符串 p中每种字母的数量，而是统计滑动窗口和字符串 p 中每种字母数量的差；
// 并引入变量 differ 来记录当前窗口与字符串 p 中数量不同的字母的个数，并在滑动窗口的过程中维护它。
//在判断滑动窗口中每种字母的数量与字符串 p 中每种字母的数量是否相同时，只需要判断differ 是否为零即可。

class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		int sLen = s.size(), pLen = p.size();

		if (sLen < pLen) {
			return vector<int>();
		}

		vector<int> ans;
		vector<int> count(26);
		for (int i = 0; i < pLen; ++i) {
			++count[s[i] - 'a'];
			--count[p[i] - 'a'];
		}

		int differ = 0;
		for (int j = 0; j < 26; ++j) {
			if (count[j] != 0) {
				++differ;
			}
		}

		if (differ == 0) {
			ans.emplace_back(0);
		}

		for (int i = 0; i < sLen - pLen; ++i) {
			if (count[s[i] - 'a'] == 1) {  // 窗口中字母 s[i] 的数量与字符串 p 中的数量从不同变得相同
				--differ;
			} else if (count[s[i] - 'a'] == 0) {  // 窗口中字母 s[i] 的数量与字符串 p 中的数量从相同变得不同
				++differ;
			}
			--count[s[i] - 'a'];

			if (count[s[i + pLen] - 'a'] == -1) {  // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从不同变得相同
				--differ;
			} else if (count[s[i + pLen] - 'a'] == 0) {  // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从相同变得不同
				++differ;
			}
			++count[s[i + pLen] - 'a'];

			if (differ == 0) {
				ans.emplace_back(i + 1);
			}
		}

		return ans;
	}
};
