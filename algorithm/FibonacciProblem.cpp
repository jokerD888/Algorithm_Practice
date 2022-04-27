//斐波那契数列

class FibonacciProblem {
public:

	//暴力递归 O(2^n)
	int f1(int n) {
		if (n < 1) {
			return 0;
		}
		if (n == 1 || n == 2) {
			return 1;
		}
		return f1(n - 1) + f1(n - 2);
	}

	//线性求解 O（N）
	int f2(int n) {
		int res = 0, pre = 1, tmp = 0;
		for (int i = 1; i <= n; ++i) {
			tmp = res;
			res = res + pre;
			pre = tmp;
		}
		return res;
	}

	// 矩阵求解O(logN)
	// fib(n)代表第n个斐波那契数，矩阵关系如下
	// |fib(n) fib(n-1)| =|fib(n-1) fib(n-2)| * | 1 1|
	//											| 1 0|
	// 可化为	|fib(n) fib(n-1)| = |fib(2) fib(1)| * | 1 1|^(n-2)
	//												  | 1 0|
	int f3(int n) {
		if (n < 1) {
			return 0;
		}
		if (n == 1 || n == 2) {
			return 1;
		}
		vector<vector<int>> base = { {1,1},
									 {1,0} };
		vector<vector<int>> res=matrixPower(base, n - 2);
		return res[0][0] + res[1][0];

	}
	vector<vector<int>> matrixPower(vector<vector<int>>& m, int p) {
		vector<vector<int>> res(m.size(), vector<int>(m[0].size()));;
		// 初始为单位矩阵
		for (int i = 0; i < res.size(); ++i) {
			res[i][i] = 1;
		}
		vector<vector<int>> tmp = m;	// 矩阵1次方
		for (; p != 0; p >>= 1) {
			if ((p & 1) != 0) {
				res = muliMatrix(res, tmp);
			}
			tmp=muliMatrix(tmp, tmp);
		}
		return res;
	}
	//俩个矩阵乘完之后的结果返回
	vector<vector<int>> muliMatrix(vector<vector<int>> m1, vector<vector<int>> m2) {
		//相乘得到的矩阵大小为 m1的行*m2的列
		vector<vector<int>> res(m1.size(), vector<int>(m2[0].size()));
		for (int i = 0; i < m1.size(); ++i) {			
			for (int j = 0; j < m2[0].size(); ++j) {
				for (int k = 0; k < m2.size(); ++k) {
					res[i][j] += m1[i][k] * m2[k][j];
				}
			}
		}
		return res;
	}



	void test() {
		int n = 19;
		cout << f1(n) << " " << f2(n) << " " << f3(n) << endl;
	}
};
// 只要 f(n)=c1*f(n-1)+c2*f(n-2)+c3*f(n-3)+...+ck*f(n-k) 这种严格递推的形式都可以优化为O(logN)
// 如 行列式| f(n) f(n-1) ... f(n-k+1)| =  行列式 |f(1)f(2)..f(k)| * |k*k的矩阵|^k

//奶牛问题：
//第一年只有一只母牛，假设每只母牛每年只会生一只母牛，刚出生的牛经历过3年才能生育，求第n年的母牛个数
class Cow {
public:
	int f(int n) {
		if (n < 1) {
			return 0;
		}
		if (n == 1 || n == 2 || n == 3) {
			return n;
		}
		vector<vector<int>> base = {
			{1,1,0},
			{0,0,1},
			{1,0,0} };
		vector<vector<int>> res = matrixPower(base, n - 3);
		return 3 * res[0][0] + 2 * res[1][0] + res[2][0];
	}
	vector<vector<int>> matrixPower(vector<vector<int>>& m, int p) {
		vector<vector<int>> res(m.size(), vector<int>(m[0].size()));;
		// 初始为单位矩阵
		for (int i = 0; i < res.size(); ++i) {
			res[i][i] = 1;
		}
		vector<vector<int>> tmp = m;	// 矩阵1次方
		for (; p != 0; p >>= 1) {
			if ((p & 1) != 0) {
				res = muliMatrix(res, tmp);
			}
			tmp = muliMatrix(tmp, tmp);
		}
		return res;
	}
	//俩个矩阵乘完之后的结果返回
	vector<vector<int>> muliMatrix(vector<vector<int>> m1, vector<vector<int>> m2) {
		//相乘得到的矩阵大小为 m1的行*m2的列
		vector<vector<int>> res(m1.size(), vector<int>(m2[0].size()));
		for (int i = 0; i < m1.size(); ++i) {
			for (int j = 0; j < m2[0].size(); ++j) {
				for (int k = 0; k < m2.size(); ++k) {
					res[i][j] += m1[i][k] * m2[k][j];
				}
			}
		}
		return res;
	}
};

