// bfprt----------------------------------------------------------------

// ����n������Ԫ�أ����ҳ���KС��
class FindMinKthP {
public:
	// ʱ��O��N��
	int minKth2(vector<int> array, int k) {
		return process2(array, 0, array.size() - 1, k - 1);
	}
	// arr[L...R]��Χ�ϣ��������Ļ�����λ��index����
	int process2(vector<int>& arr, int L, int R, int index) {
		if (L == R) {
			return arr[L];
		}

		int pivot = arr[L + rand() % (R - L + 1)];
		//cout << "rand:" << pivot << endl;
		vector<int> rge = partition(arr, L, R, pivot);	// ������������
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

	// ����bfprt�㷨��ʱ��O��N��
	// bfprt�㷨��arr[L..R] �������Ļ���λ��indexλ�õ���ʲô
	// 1���������Ļ���
	// 2) ������ڲ���������ȡ���м�ֵ
	// 3��ȡ�����м�ֵ��Ϊһ������marr���ٵ���bfprt(marr,0, marr.size() - 1, marr.size() / 2)ȡ��marr����λ��
	//����ÿ�οɹ̶����10/3�ķ�Χ
	int minKth3(vector<int> array, int k) {
		return bfprt(array, 0, array.size() - 1, k - 1);
	}
	// arr[L..R] �������Ļ���λ��indexλ�õ���ʲô��indexһ����arr��Χ�У�
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

	// arr[L...R] �����һ��
	// ÿ��С���ڲ�����
	// ÿ��С����λ������������marr
	// marr�е���λ��������
	int medianOfMedians(vector<int> arr, int L, int R) {
		int size = R - L + 1;
		// ��û�ж����һ�飨�����������
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
// ����ʱ���ڽ���������ִ�
// ���˽��±������壬pArr[i] ��ʾ��iΪ���ĵ�����Ĵ��İ뾶��R��Ŀǰ��Ļ��Ĵ����ұ߽磬C��Ŀǰ��Ļ��Ĵ����е㡣R,C��ʼʱ��Ϊ-1
// ���裺ԭ��ǰ���м��϶�����ַ���
//	   ��������ö�ٻ�������i��
//		1).��i��R�⣬������
//		2).��i��R�ڣ���i����C�ĶԳƵ�Ϊi1��
//			a. i1�Ļ�������ȫ����L,R�ڣ�pArr[i]=pArr[i1]
//			b. i1�Ļ���������L,R�ⲿ��pArr[i]=R-i
//			c. i1�Ļ���������߽��Lѹ�ߣ���R��ʼ������
//    R������ൽN,��a,b��֧��O(1)�������㷨����O(N)
class Manacher {
public:
	int manacher(const string& s) {
		if (s.size() == 0) {
			return 0;
		}
		//"12321" -> "#1#2#3#2#1#"
		string str = manacherString(s);
		// ���İ뾶�Ĵ�С
		vector<int> pArr(str.size());	// ���İ뾶����
		// C����R���ŵĻ�������
		int C = -1;
		// ������R�������ҵ����ɹ���λ�ã���������ҵ����ųɹ�λ�ã�����һ��λ��
		int R = -1;
		int ret = INT_MIN;	//����ֵ����¼�뾶
		// ��iΪ�������Ĺ����������
		// 1)i��R��
		// ��i��R�ڣ���i1Ϊi����C�ĶԳƵ㣩
		// 2��i1�Ļ��İ뾶 i1��L..R��
		// 3��i1���İ뾶����߽���L..R��
		// 4��i1���İ뾶��L�غ�
		for (int i = 0; i < str.size(); ++i) {
			// iλ���������Ĵ𰸣�iλ���������������Ƕ���
			// ���i��R�⣬��i>=R(R�ǵ�һ��Υ���λ�ã�  (pArr[2*C-i]��i�ĶԳƵ㣩
			pArr[i] = R > i ? min(pArr[2 * C - i], R - i) : 1;	//���ò����λ�������õ�pArr[i]
			//����һ��ֱ��������4����������������


			//���2,3һ��ѭ���ͻ�break
			while (i + pArr[i]<str.size() && i - pArr[i]>-1) {	//ѭ�������Ƿ�ֹ���Ĺ����ֳ������ұ߽�
				// if������iΪ���ģ�������������������
				if (str[i + pArr[i]] == str[i - pArr[i]]) {
					++pArr[i];
				} else {
					break;
				}

			}

			// iλ���������Ĵ𰸳�����R
			if (i + pArr[i] > R) {
				R = i + pArr[i];
				C = i;
			}
			ret = max(ret, pArr[i]);
		}

		return ret - 1;	//ret��¼����manacherString�е������İ뾶������-1���õ�ԭ���ĳ���
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

// ����һ���ַ���str,ֻ�����������ַ�����Ҫ��������ٷ���ʹ�������Ϊ���Ĵ�
// �⣺�ҳ�����������һ���ַ����������ִ����ú�ǰ��Ĳ�������׷�ӵ��ַ�����
//     �����ң��ҵ���һ���������һ���ַ������ǰ������һ���ַ����������ִ�

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
		int maxCntEnd = -1;	//��¼�������һ���ַ��Ļ����ִ��İ뾶
		for (int i = 0; i < str.size(); ++i) {
			pArr[i] = R > i ? min(pArr[2 * C - i], R - i) : 1;	//���ò����λ�������õ�pArr[i]
			while (i + pArr[i]<str.size() && i - pArr[i]>-1) {	//ѭ�������Ƿ�ֹ���Ĺ����ֳ������ұ߽�
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
