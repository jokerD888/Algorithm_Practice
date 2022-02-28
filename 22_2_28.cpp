////844. �ȽϺ��˸���ַ���
////��һ��ģ���ع�
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
////������˫ָ��
////�Ӻ���ǰ������������#'��˵����Ҫɾ��һ���ַ�
//class Solution {
//public:
//    bool backspaceCompare(string S, string T) {
//        int i = S.length() - 1, j = T.length() - 1;
//        int skipS = 0, skipT = 0;
//
//        while (i >= 0 || j >= 0) {
//            //���������һ��while��ȷ��һ���ַ�
//            while (i >= 0) {
//                if (S[i] == '#') {
//                    //��¼�����ĸ�����ͬʱ������#��
//                    skipS++, i--;
//                } else if (skipS > 0) {
//                    //�����ǡ�#������ʼ����skipS���ַ�
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
////986. �����б�Ľ���
////�鲢����
//class Solution {
//public:
//    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
//        vector<vector<int>> ret;
//        int i = 0, j = 0;
//        while (i < firstList.size() && j < secondList.size()) {
//            //Ϊ��������Ľ�����[low,high]
//            //lowΪ����������߽�����ֵ
//            //highΪ���������ұ߽����Сֵ
//            int low = max(firstList[i][0], secondList[j][0]);
//            int high = min(firstList[i][1], secondList[j][1]);
//            if (low <= high) {
//                ret.push_back({ low,high });
//            }
//            //���������е�����ұ߽���ܻ����һ���������һ�������ཻ��
//            //���������ұ߽�������Ȼ����������һ�������������һ������
//            if (firstList[i][1] < secondList[j][1]) {
//                ++i;
//            } else {
//                ++j;
//            }
//        }
//        return ret;
//    }
//};



////11. ʢ���ˮ������
////��һ��ö��(��ʱ��
////ʱ��O��N^2)
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
////������
////˫ָ��
////��������ڵ׺͸ߣ���ʼ�ȴ���������ҿ�ʼ����ʱ�ĵ�����������������ֻ�и��̵ı߱䳤�ſ��ܣ����������ҿ��ܵĸ����ı�
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
//			//��߸�
//			if (height[left] < height[right]) {
//				while (++left < height.size() && height[left] <= height[x]) {}
//			} else {
//				//�ұ߸�
//				while (--right >= 0 && height[right] <= height[y]) {}
//			}
//		}
//		return ret;
//	}
//};
////��
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


//438. �ҵ��ַ�����������ĸ��λ��
//��һ������ƥ��(��ʱ��
//�����p������ȫ���У������α���s�Ա�
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
		//p��ȫ����
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


//������ͳ�ƴ�Ƶ+��������
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

//��
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

//�������Ż��Ļ�������
//���ٷֱ�ͳ�ƻ������ں��ַ��� p��ÿ����ĸ������������ͳ�ƻ������ں��ַ��� p ��ÿ����ĸ�����Ĳ
// ��������� differ ����¼��ǰ�������ַ��� p ��������ͬ����ĸ�ĸ��������ڻ������ڵĹ�����ά������
//���жϻ���������ÿ����ĸ���������ַ��� p ��ÿ����ĸ�������Ƿ���ͬʱ��ֻ��Ҫ�ж�differ �Ƿ�Ϊ�㼴�ɡ�

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
			if (count[s[i] - 'a'] == 1) {  // ��������ĸ s[i] ���������ַ��� p �е������Ӳ�ͬ�����ͬ
				--differ;
			} else if (count[s[i] - 'a'] == 0) {  // ��������ĸ s[i] ���������ַ��� p �е���������ͬ��ò�ͬ
				++differ;
			}
			--count[s[i] - 'a'];

			if (count[s[i + pLen] - 'a'] == -1) {  // ��������ĸ s[i+pLen] ���������ַ��� p �е������Ӳ�ͬ�����ͬ
				--differ;
			} else if (count[s[i + pLen] - 'a'] == 0) {  // ��������ĸ s[i+pLen] ���������ַ��� p �е���������ͬ��ò�ͬ
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
