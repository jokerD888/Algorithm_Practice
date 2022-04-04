//22. 括号生成
// 根据左右括号匹配的原理，一开始设左括号和右括号的数值都为n，left=right=n;
// （1）如果left==right,那么此时只能先选择左括号
// （2）如果left<right,那么此时可选择左括号也可以选择右括号
// （3）如果left已近为0，那么只能把剩余的右括号补上即可
// 最优解：
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
			// 剩余左右括号数相等，下一个只能用左括号
			getParenthesis(str += '(', left - 1, right);
			str.pop_back();
		} else if (left < right) {
			// 剩余左括号小于右括号，下一个可以用左括号也可以用右括号
			if (left > 0) {
				getParenthesis(str += '(', left - 1, right);
				str.pop_back();
			}
			getParenthesis(str += ')', left, right - 1);
			str.pop_back();
		}
	}
};

// 暴力
// 生成所有 2^(2n)个 '(' 和 ')' 字符构成的序列，然后我们检查每一个是否有效即可
class Solution {
	bool valid(const string& str) {
		int balance = 0;	//遇见左括号+1，右括号-1，如果<0，去掉所有之前以匹配的括号的化，开头就是右括号，违规
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


//回溯法
//方法一还有改进的余地：我们可以只在序列仍然保持有效时才添加 '(' or ')'，而不是像 方法一 那样每次添加。我们可以通过跟踪到目前为止放置的左括号和右括号的数目来做到这一点，
//如果左括号数量不大于 n，我们可以放一个左括号。如果右括号数量小于左括号的数量，我们可以放一个右括号。
//在方法一的基础上做出限制判断，如果剩余左括号的数量大于右括号，违规，如果已经没有左括号了，违规。
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

//按括号序列的长度递归
//任何一个括号序列都一定是由 ( 开头，并且第一个 ( 一定有一个唯一与之对应的 )。
//这样一来，每一个括号序列可以用 (a)b 来表示，其中 a 与 b 分别是一个合法的括号序列（可以为空）。
//1.我们需要枚举与第一个 ( 对应的 ) 的位置 2 * i + 1；
//2.递归调用 generate(i) 即可计算 a 的所有可能性；
//3.递归调用 generate(n - i - 1) 即可计算 b 的所有可能性；
//4.遍历 a 与 b 的所有可能性并拼接，即可得到所有长度为 2 * n 的括号序列。
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
// 类似：上面是把n-1插入（）里，这里把（）插入到n-1的结果里然后去重
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


//53. 最大子数组和
//动态规划
// 我们用 f(i) 代表以第 i 个数结尾的「连续子数组的最大和」
// 因此我们只需要求出每个位置的 f(i)，然后返回 f数组中的最大值即可
// 如何求 f(i) 呢？我们可以考虑 nums[i] 单独成为一段还是加入 f(i-1)对应的那一段，
// 这取决于nums[i] 和 f(i-1) +nums[i] 的大小，我们希望获得一个比较大的
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


//分治，线段树
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

