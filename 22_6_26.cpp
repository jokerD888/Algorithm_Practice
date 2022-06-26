// 710. 黑名单中的随机数
// 若所有黑名单数全部在区间 [n-m,n) 范围内。此时我们可以直接在 [0,n-m) 范围内取随机整数。
// 所以我们可以对于在 [0,n-m) 范围内的黑名单数，我们可以将其映射到 [n-m,n)范围内的非黑名单数（白名单数）上。
class Solution {
	unordered_map<int, int> b2w;
	int bound;

public:
	Solution(int n, vector<int>& blacklist) {
		int m = blacklist.size();
		bound = n - m;
		// 先将 [n-m,n) 范围内的黑名单数存入一个哈希集合black；
		unordered_set<int> black;
		for (int b : blacklist) {
			if (b >= bound) {
				black.emplace(b);
			}
		}
		// 对于每个 [0,n-m)范围内的黑名单数 b，首先不断增加 w 直至其不在黑名单中，然后将 b 映射到 w 上，并将 w 增加一。
		int w = bound;
		for (int b : blacklist) {
			if (b < bound) {
				// 直到w不在黑名单
				while (black.count(w)) {
					++w;
				}
				// 映射
				b2w[b] = w++;
			}
		}
	}

	int pick() {
		// int x = rand() % bound;  // 在这里rand()生成的随机数最大范围RAND_MAX为32767，不适用
		static default_random_engine e;
		int x = e() % bound;
		// 若x在黑名单，返回映射的白名单中的数，否则直接返回x
		return b2w.count(x) ? b2w[x] : x;
	}
};

// 8. 字符串转换整数 (atoi)

// 模拟
class Solution {
public:
	int myAtoi(string s) {
		long long res = 0;
		int index = -1, n = s.size();
		bool neg = false;
		while (++index < n && s[index] == ' ');	//跳过前导空格
		if (index == n)
			return 0;
		if (!isdigit(s[index])) {
			if (s[index] == '-')	// -号
				neg = true;
			else if (s[index] != '+')	// 非正负号 ，return 0
				return 0;
		} else {
			res = s[index] - '0';	// 数字，默认正数
		}
		for (int i = index + 1; i < n; ++i) {
			if (res > INT_MAX || !isdigit(s[i]))
				break;
			res = res * 10 + s[i] - '0';
		}
		if (neg) {
			if (res > INT_MAX)
				return INT_MIN;
			else
				return -res;
		} else {
			if (res > INT_MAX)
				return INT_MAX;
			return res;
		}

	}
};

//或

class Solution {
public:
	int myAtoi(string s) {
		int res = 0;
		int i = -1, n = s.size();
		bool neg = false;
		while (++i < n && s[i] == ' ');
		if (s[i] == '-')
			neg = true;
		if (s[i] == '-' || s[i] == '+')
			++i;
		while (i < n && isdigit(s[i])) {
			int r = s[i] - '0';
			if (res > INT_MAX / 10 || (res == INT_MAX / 10 && r > 7))
				return neg ? INT_MIN : INT_MAX;
			res = res * 10 + r;
			++i;
		}
		return neg ? -res : res;
	}
};


// 自动机
class Automaton {
	string state = "start";
	unordered_map<string, vector<string>> table = {
		{"start", {"start", "signed", "in_number", "end"}},
		{"signed", {"end", "end", "in_number", "end"}},
		{"in_number", {"end", "end", "in_number", "end"}},
		{"end", {"end", "end", "end", "end"}}
	};

	int get_col(char c) {
		if (isspace(c)) return 0;
		if (c == '+' or c == '-') return 1;
		if (isdigit(c)) return 2;
		return 3;
	}
public:
	int sign = 1;
	long long ans = 0;

	void get(char c) {
		state = table[state][get_col(c)];
		if (state == "in_number") {
			ans = ans * 10 + c - '0';
			ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
		} else if (state == "signed")
			sign = c == '+' ? 1 : -1;
	}
};

class Solution {
public:
	int myAtoi(string str) {
		Automaton automaton;
		for (char c : str)
			automaton.get(c);
		return automaton.sign * automaton.ans;
	}
};