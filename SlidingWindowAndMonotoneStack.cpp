
//��������


//����һ���̶���СΪW�Ĵ��ڣ����λ���arr, ����ÿһ�λ���״�������ֵ
//����, arr = [4, 3,5,4, 3, 3, 6, 7], W = 3����: [5,5, 5, 4, 6, 7]

class SlidingWindowMaxArray {
public:
	vector<int> getMaxWindow(const vector<int>& arr, int w) {
		if (arr.size() < w || w < 1) {
			return {};
		}
		//���зŵ���λ�ã�ͷ������ ->С��  
		list<int> qmax;
		vector<int> ans;
		int index = 0;
		for (int i = 0; i < arr.size(); ++i) {
			//��ǰ��i->arr[i]�����ڣ�i����R

			while (!qmax.empty() && arr[qmax.back()] <= arr[i]) {
				qmax.pop_back();
			}
			qmax.push_back(i);
			//���˫�˶���ͷֵ���ڴ�����߽�Ĺ����±�Ļ�
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


//����һ����������arr����һ������num
//ĳ��arr�е�������sub��������꣬�������� : sub�����ֵ - sub����Сֵ <= num,
//����arr�д�������������

//�����������ֵ����Сֵ�ĸ��½ṹ
class AllLessNumSubArray {
public:
	//����O��N^3)
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

	//��������O��N)
	//�����е�����Ԫ�����ֻ�����δ�����кͳ�����
	int getNum(const vector<int>& arr, int num) {
		if (arr.size() == 0) {
			return 0;
		}
		list<int> qmin, qmax;
		int ans = 0, L = 0, R = 0;
		//[L,R)����ҿ�����
		while (L < arr.size()) {
			//L�ǿ�ͷλ�ã�����ÿһ����ͷ
			// �����ʱ���ڵĿ�ͷ��L�������while������R��������Υ��Ϊֹ
			while (R < arr.size()) {	// R�����һ�����λ�õ�����һ��
				while (!qmin.empty() && arr[qmin.back()] >= arr[R]) {
					qmin.pop_back();
				}
				qmin.push_back(R);

				while (!qmax.empty() && arr[qmax.back() <= arr[R]]) {
					qmax.pop_back();
				}
				qmax.push_back(R);

				if (arr[qmax.front()] - arr[qmin.front()] > num) {
					//��ʱ�Ĵ��ڷ�Χ�������Сֵ�ѽ�������<=num��Ҫ��Ҳ�Ͳ���Ҫ����������
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


//�Ż���
//����״��	�����⣬��һ��Χ��꣬��С�ıش������ıز���꣩
//���Ȿ��	����ͷ�Χ���������ԣ���βָ��ͬ�� 



//����ջ
//���⣺��һ�������У�����ÿһ��λ�õ����������������ı���С�����������ұ�����ı���С����

//��ջ��Ҫά�ִ��������Ǵ�С�����˳����ջ�����±꣬�±��Ӧ������Ӧά�ִ�С����
class MonotonousStack {
public:
	//������û���ظ�ֵ,���Ҫ��ջ��ֵ���ܰ��մ�С˳����ջ����ôҪ���������������ֵ��ұߴ�ΪҪ��ջ�ģ���ߴ�Ϊ�����������·�������
	vector<vector<int>> getNearLessNoRepeat(const vector<int>& arr) {
		vector<vector<int>> res(arr.size(), vector<int>(2));
		stack<int> st;
		for (int i = 0; i < arr.size(); ++i) {
			while (!st.empty() && arr[st.top()] > arr[i]) {
				int popIndex = st.top();
				st.pop();
				int leftLessIndex = st.empty() ? -1 : st.top();	//���ջ��Ϊ�գ���ߵĴ𰸼�Ϊ����ջ������Ϊ����𰸵������ѽ���������
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
			res[popIndex][1] = -1;	//��Ϊ��ʱ�����ֲ�������Ϊ�����ֵĽ������ջ������ջ���ұߵĴ𰸼�Ϊ-1,��ʾ�Ҳ�������������
		}
		return res;
	}

	//���������ظ�Ԫ��
	vector<vector<int>> getNearLess(const vector<int>& arr) {
		vector<vector<int>> res(arr.size(), vector<int>(2));
		// list<int> �ŵ���λ�ã��±꣩ͬ��ֵ�Ķ�����λ��ѹ��һ��
		stack<list<int>> st;
		for (int i = 0; i < arr.size(); ++i) {	// i->arr[i]��ջ
			//ͬ���� ջ�дӵ׵�����˳���Ǵ�С����
			while (!st.empty() && arr[st.top().front()] > arr[i]) {
				list<int> popLs = st.top();
				st.pop();
				//ȡ��������λ�õ��б��У����������Ǹ�
				int leftLessIndex = st.empty() ? -1 : st.top().back();
				for (auto popi : popLs) {
					res[popi][0] = leftLessIndex;
					res[popi][1] = i;
				}
			}
			//��ȵġ�����С��
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
			// ȡ��������λ�õ������У����������Ǹ�
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
//�����ԣ��������ķ�Χ����Ҫ���������ָ��֮��治���ڣ���Χ���ָ���󣬻�Χ���ָ���С






//��������
//����һ��ֻ����������������arr, arr���κ�һ��������sub,һ�����������(sub�ۼӺ�)* (sub�е���Сֵ)��ʲô
//��ô�����������У����ֵ����Ƕ��� ?

//������Ԥ������ǰ׺�ͣ���ö����iλ��Ϊ��Сֵ�� �ۼӺ�*��Сֵ �����ֵ
class Solution {
public:
	int getMaxSubArray(const vector<int>& arr) {
		int n = arr.size();
		//ǰ׺��
		vector<int> prefix(n);
		prefix[0] = arr[0];
		for (int i = 1; i < n; ++i) {
			prefix[i] = prefix[i - 1] + arr[i];
		}

		//����ջ
		vector<vector<int>> res(arr.size(), vector<int>(2));
		// list<int> �ŵ���λ�ã��±꣩ͬ��ֵ�Ķ�����λ��ѹ��һ��
		stack<list<int>> st;
		for (int i = 0; i < arr.size(); ++i) {	// i->arr[i]��ջ
			//ͬ���� ջ�дӵ׵�����˳���Ǵ�С����
			while (!st.empty() && arr[st.top().front()] > arr[i]) {
				list<int> popLs = st.top();
				st.pop();
				//ȡ��������λ�õ��б��У����������Ǹ�
				int leftLessIndex = st.empty() ? -1 : st.top().back();
				for (auto popi : popLs) {
					res[popi][0] = leftLessIndex;
					res[popi][1] = i;
				}
			}
			//��ȵġ�����С��
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
			// ȡ��������λ�õ������У����������Ǹ�
			int leftLessIndex = st.empty() ? -1 : st.top().back();
			for (auto i : popLs) {
				res[i][0] = leftLessIndex;
				res[i][1] = -1;
			}
		}

		int ret = 0;
		//ö����������Сֵ
		for (int i = 0; i < n; ++i) {
			//���������ұ߽磬���ұ�
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