//22. ��������
// ������������ƥ���ԭ��һ��ʼ�������ź������ŵ���ֵ��Ϊn��left=right=n;
// ��1�����left==right,��ô��ʱֻ����ѡ��������
// ��2�����left<right,��ô��ʱ��ѡ��������Ҳ����ѡ��������
// ��3�����left�ѽ�Ϊ0����ôֻ�ܰ�ʣ��������Ų��ϼ���
// ���Ž⣺
class Solution {
public:
	vector<string> res;
	vector<string> generateParenthesis(int n) {
		if (n <= 0) {
			return res;
		}
		string s;
		getParenthesis(s, n, n);
		return res;
	}
	void getParenthesis(string& str, int left, int right) {
		if (left == 0 && right == 0) {
			res.push_back(str);
			return;
		}
		if (left == right) {
			// ʣ��������������ȣ���һ��ֻ����������
			getParenthesis(str += '(', left - 1, right);
			str.pop_back();
		} else if (left < right) {
			// ʣ��������С�������ţ���һ��������������Ҳ������������
			if (left > 0) {
				getParenthesis(str += '(', left - 1, right);
				str.pop_back();
			}
			getParenthesis(str += ')', left, right - 1);
			str.pop_back();
		}
	}
};

// ����
// �������� 2^(2n)�� '(' �� ')' �ַ����ɵ����У�Ȼ�����Ǽ��ÿһ���Ƿ���Ч����
class Solution {
	bool valid(const string& str) {
		int balance = 0;	//����������+1��������-1�����<0��ȥ������֮ǰ��ƥ������ŵĻ�����ͷ���������ţ�Υ��
		for (char c : str) {
			if (c == '(') {
				++balance;
			} else {
				--balance;
			}
			if (balance < 0) {
				return false;
			}
		}
		return balance == 0;
	}

	void generate_all(string& current, int n, vector<string>& result) {
		if (n == current.size()) {
			if (valid(current)) {
				result.push_back(current);
			}
			return;
		}
		current += '(';
		generate_all(current, n, result);
		current.pop_back();
		current += ')';
		generate_all(current, n, result);
		current.pop_back();
	}
public:
	vector<string> generateParenthesis(int n) {
		vector<string> result;
		string current;
		generate_all(current, n * 2, result);
		return result;
	}
};


//���ݷ�
//����һ���иĽ�����أ����ǿ���ֻ��������Ȼ������Чʱ����� '(' or ')'���������� ����һ ����ÿ����ӡ����ǿ���ͨ�����ٵ�ĿǰΪֹ���õ������ź������ŵ���Ŀ��������һ�㣬
//������������������� n�����ǿ��Է�һ�������š��������������С�������ŵ����������ǿ��Է�һ�������š�
//�ڷ���һ�Ļ��������������жϣ����ʣ�������ŵ��������������ţ�Υ�棬����Ѿ�û���������ˣ�Υ�档
class Solution {
	void backtrack(vector<string>& ans, string& cur, int open, int close, int n) {
		if (cur.size() == n * 2) {
			ans.push_back(cur);
			return;
		}
		if (open < n) {
			cur.push_back('(');
			backtrack(ans, cur, open + 1, close, n);
			cur.pop_back();
		}
		if (close < open) {
			cur.push_back(')');
			backtrack(ans, cur, open, close + 1, n);
			cur.pop_back();
		}
	}
public:
	vector<string> generateParenthesis(int n) {
		vector<string> result;
		string current;
		backtrack(result, current, 0, 0, n);
		return result;
	}
};

//���������еĳ��ȵݹ�
//�κ�һ���������ж�һ������ ( ��ͷ�����ҵ�һ�� ( һ����һ��Ψһ��֮��Ӧ�� )��
//����һ����ÿһ���������п����� (a)b ����ʾ������ a �� b �ֱ���һ���Ϸ����������У�����Ϊ�գ���
//1.������Ҫö�����һ�� ( ��Ӧ�� ) ��λ�� 2 * i + 1��
//2.�ݹ���� generate(i) ���ɼ��� a �����п����ԣ�
//3.�ݹ���� generate(n - i - 1) ���ɼ��� b �����п����ԣ�
//4.���� a �� b �����п����Բ�ƴ�ӣ����ɵõ����г���Ϊ 2 * n ���������С�
class Solution {
	shared_ptr<vector<string>> cache[100] = { nullptr };
public:
	shared_ptr<vector<string>> generate(int n) {
		if (cache[n] != nullptr)
			return cache[n];
		if (n == 0) {
			cache[0] = shared_ptr<vector<string>>(new vector<string>{ "" });
		} else {
			auto result = shared_ptr<vector<string>>(new vector<string>);
			for (int i = 0; i != n; ++i) {
				auto lefts = generate(i);
				auto rights = generate(n - i - 1);
				for (const string& left : *lefts)
					for (const string& right : *rights)
						result->push_back("(" + left + ")" + right);
			}
			cache[n] = result;
		}
		return cache[n];
	}
	vector<string> generateParenthesis(int n) {
		return *generate(n);
	}
};
// ���ƣ������ǰ�n-1���루�������ѣ������뵽n-1�Ľ����Ȼ��ȥ��
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		if (n == 1) return { "()" };
		unordered_set<string> res;
		string tmp;
		for (auto& s : generateParenthesis(n - 1)) {
			for (int i = 0; i != 2 * (n - 1); ++i) {
				tmp = s.substr(0, i) + "()" + s.substr(i);
				res.insert(tmp);
			}
		}
		return {res.begin(),res.end()};
	}
};


//53. ����������
//��̬�滮
// ������ f(i) �����Ե� i ������β�ġ���������������͡�
// �������ֻ��Ҫ���ÿ��λ�õ� f(i)��Ȼ�󷵻� f�����е����ֵ����
// ����� f(i) �أ����ǿ��Կ��� nums[i] ������Ϊһ�λ��Ǽ��� f(i-1)��Ӧ����һ�Σ�
// ��ȡ����nums[i] �� f(i-1) +nums[i] �Ĵ�С������ϣ�����һ���Ƚϴ��
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int pre = 0, maxAns = nums[0];
		for (const auto& x : nums) {
			pre = max(pre + x, x);
			maxAns = max(maxAns, pre);
		}
		return maxAns;
	}
};


//���Σ��߶���
class Solution {
public:
	struct Status {
		int lSum, rSum, mSum, iSum;
	};

	Status pushUp(Status l, Status r) {
		int iSum = l.iSum + r.iSum;
		int lSum = max(l.lSum, l.iSum + r.lSum);
		int rSum = max(r.rSum, r.iSum + l.rSum);
		int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
		return Status{ lSum, rSum, mSum, iSum };
	};

	Status get(vector<int>& a, int l, int r) {
		if (l == r) {
			return Status{ a[l], a[l], a[l], a[l] };
		}
		int m = (l + r) >> 1;
		Status lSub = get(a, l, m);
		Status rSub = get(a, m + 1, r);
		return pushUp(lSub, rSub);
	}

	int maxSubArray(vector<int>& nums) {
		return get(nums, 0, nums.size() - 1).mSum;
	}
};

