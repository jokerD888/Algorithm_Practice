//Table printing and matrix processing
//打表和矩阵处理

//打表法
//1）问题如果返回值不太多，可以用hardcode的方式列出，作为程序的一部分
//2)一个大问题解决时底层频繁使用规模不大的小问题的解，如果小问题的返回值满足条件1)，可以把小问题的解列成一张表，作为程序的一部分
//3)打表找规律

//步骤
//输入参数简单，并且只有一个实际参数
//要求的返回类型也简单，也只有一个
//用暴力方法，把输入参数对应的返回值，打印出来找规律，进而优化code

//问题一：
//小虎去买苹果，商店只提供两种类型的塑料袋，每种类型都有任意数量。
//1)能装下6个苹果的袋子
//2)能装下8个苹果的袋子
//小虎可以自由使用两种袋子来装苹果，但是小虎有强迫症，他要求自己使用的袋子数量必须最少，且使用的每个袋子必须装满。
//给定一个正整数N，返回至少使用多少袋子。如果N无法让使用的每个袋子必须装满, 返回 - 1

class AppleMinBags {
	int minBags(int apple) {
		if (apple < 0) {
			return -1;
		}

		int bag6 = -1;
		//先假设全使用8号袋子，剩余几个，随后不断--8号袋子的数量，看6号袋子是否能正好装满，直到8好袋子减为0或剩下的大于等于24退出
		int bag8 = apple / 8;
		int rest = apple - 8 * bag8;
		while (bag8 >= 0 && rest < 24) {
			//若rest>=24说明起码rest其中的24个可以用3个8号袋子，实际求的还是剩余rest-24的问题，已没必要算下去了，必定无法成功
			int restUse6 = minBagBase6(rest);
			if (restUse6 != -1) {
				bag6 = restUse6;
				break;
			}
			rest = apple - 8 * (--bag8);
		}
		return bag6 == -1 ? -1 : bag6 + bag8;
	}

	int minBagBase6(int rest) {
		return rest % 6 == 0 ? (rest / 6) : -1;
	}
public:
	//通过print（）观察规律得，从18之后8个为一组进行规律性输出
	int minBagAwesome(int apple) {
		//如果是奇数，返回-1
		if ((apple & 1) != 0) {
			return -1;
		}

		if (apple < 18) {
			return apple == 0 ? 0 : (apple == 6 || apple == 8) ? 1 
				: (apple == 12 || apple == 14 || apple == 16) ? 2 : -1;
		}
		return (apple - 18) / 8 + 3;
	}
	void print() {
		for (int apple = 0; apple < 100; ++apple ) {
			cout << apple << ":" << minBags(apple) << endl;;
		}
	}
};


//问题二：
//给定一个正整数N，表示有N份青草统一堆放在仓库里有一只牛和一只羊，牛先吃，羊后吃，它俩轮流吃草不管是牛还是羊，每一轮能吃的草量必须是:
//1，4，16，64…(4的某次方)
//谁最先把草吃完，谁获胜
//假设牛和羊都绝顶聪明，都想赢，都会做出理性的决定，根据唯一的参数N，返回谁会赢

class EatGress {
public:
	
	string winner1(int n) {
		// 0 1  2  3  4
		//后 先 后 先 先
		if (n < 5) {
			return (n == 0 || n == 2) ? "后手" : "先手";
		}
		int base = 1;
		while (base <= n) {
			//当前一共n份草，先手吃掉的是base份，n-base是留给后手的
			if (winner1(n - base) == "后手") {
				//在n-base的过程中，自己沦为了后手，若在n-base过程中后手赢了，则自己这个选择就会赢
				return "先手";
			}
			//防止溢出
			if (base > n / 4) {
				break;
			}
			base *= 4;
		}

		//先手始终无法赢，后手赢
		return "后手";
	}
	//通过打印，你会发现，规律是后先后先先，循环下去
	void print() {
		for (int i = 0; i < 50; ++i) {
			cout << i << ": " << winner1(i) << endl;;
		}
	}

	string winner2(int n) {
		if (n % 5 == 0 || n % 5 == 2) {
			return "后手";
		}
		return "先手";
	}
};

//问题三：
//定义一种数:可以表示成若干（数量>1)连续正数和的数比如:
//5 = 2 + 3，5就是这样的数
//12 = 3 + 4 + 5, 12就是这样的数
//1不是这样的数，因为要求数量大于1个、连续正数和2 = 1 + 1，2也不是，因为等号右边不是连续正数
//给定一个参数N, 返回是不是可以表示成若干连续正数和的数

class MsumToN {
public:
	//暴力
	bool isMSum1(int num) {
		for (int i = 1; i < num; ++i) {//开头的数i
			int sum = i;
			for (int j = i + 1; j < num; ++j) {
				if (sum + j > num) {
					break;
				}
				if (sum + j == num) {
					return true;
				}
				sum += j;
			}
		}
		return false;
	}
	//通过打印观察得，只要是2的幂都是false
	void print() {
		for (int i = 0; i < 100; ++i) {
			cout << i << ": " << isMSum1(i) << endl;
		 }
		for (int i = 0; i < 1000; ++i) {
			if (isMSum1(i) != isMSum2(i)) {
				cout << "failed!" << endl;
				return;
			}
		}
		cout << "succeed!" << endl;
		return;

	}

	bool isMSum2(int num) {
		if (num < 3) {
			return false;
		}
		//（nums&(nums-1))判断num是不是2的某次方，若是返回0，不是返回1 
		return (num & (num - 1)) != 0;
	}
};


//举证处理技巧

//问题一：
//zigzag打印举证
class ZigZagPrintMatrix {
public:
	void printMatrixZigZag(vector<vector<int>>& matrix) {
		int Arow = 0, Acol = 0;
		int Brow = 0, Bcol = 0;
		int EndRow = matrix.size() - 1;
		int EndCol = matrix[0].size() - 1;
		bool fromUp = false;	//是不是从右上往坐下打印
		//一开始A和B都在（0，0)位置，A往右走，走到头的话往下走，B往下走，走到头的话往右走
		while (Arow != EndRow + 1) {
			//得知斜线的两端，A和B，方向也得知，去打印
			printLevel(matrix, Arow, Acol, Brow, Bcol, fromUp);

			//以下代码行不可互换，换了之后右上角的元素和左下角的元素将被跳过

			//如果A得列走到头了，那么行+1,开始往下走
			Arow = Acol == EndCol ? Arow + 1 : Arow;
			//如果A的列走到头了,列不变，否则，列+1,继续右走
			Acol = Acol == EndCol ? Acol : Acol + 1;

			Bcol = Brow == EndRow ? Bcol + 1 : Bcol;
			Brow = Brow == EndRow ? Brow : Brow + 1;

			fromUp = !fromUp;
		}
		cout << endl;
	}

	void printLevel(vector<vector<int>>& m, int Ar, int Ac, int Br, int Bc, bool f) {
		if (f) {
			while (Ar != Br + 1) {
				cout << m[Ar++][Ac--] << " ";
			}
		} else {
			while (Br != Ar - 1) {
				cout << m[Br--][Bc++] << " ";
			}
		}
	}

	void test() {
		vector<vector<int>> matrix = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
		printMatrixZigZag(matrix);
	}
};


//问题二：转圈打印矩阵

class PrintMatrixSpiralOrder {
public:
	//只需要左上角（a,b)，右下角(c,d)即可确定一个矩阵
	void printEdge(vector<vector<int>>& m, int a, int b, int c, int d) {
		//如果只有一行
		if (a == c) {
			for (int i = b; i <= d; ++i) {
				cout << m[a][i] << " ";
			}
		} else if (b == d) {	//如果只有一列
			for (int i = a; i < c; ++i) {
				cout << m[i][b] << " ";
			}
		} else {
			int curC = b;
			int curR = a;
			//上边
			while (curC != d) {
				cout << m[a][curC] << " ";
				curC++;
			}
			//右边
			while (curR != c) {
				cout << m[curR][d] << " ";
				curR++;
			}
			//下边
			while (curC != b) {
				cout << m[c][curC] << " ";
				curC--;
			}
			//左边
			while (curR != a) {
				cout << m[curR][b] << " ";
				curR--;
			}
		}
	}

	void spiralOrderPrint(vector<vector<int>>& matrix) {
		int tR = 0, tC = 0;
		int dR = matrix.size() - 1, dC = matrix[0].size() - 1;
		while (tR <= dR && tC <= dC) {
			printEdge(matrix, tR++, tC++, dR--, dC--);
		}
		cout << endl;
	}

	void test() {
		vector<vector<int>> matrix = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
		spiralOrderPrint(matrix);
	}
};



//原地旋转正方形矩阵
class RotateMatrix {
public:
	void rotate(vector<vector<int>>& matrix) {
		int a = 0;
		int b = 0;
		int c = matrix.size() - 1;
		int d = matrix[0].size() - 1;
		while (a < c) {
			rotateEdge(matrix, a++, b++, c--, d--);
		}
	}

	void rotateEdge(vector<vector<int>>& m, int a, int b, int c, int d) {
		int tmp = 0;
		for (int i = 0; i < d - b; ++i) {
			tmp = m[a][b + i];
			m[a][b + i] = m[c - i][b];
			m[c - i][b] = m[c][d - i];
			m[c][d - i] = m[a + i][d];
			m[a + i][d] = tmp;
		}
	}

	void printMatrix(vector<vector<int>>& m) {
		for (int i = 0; i != m.size(); ++i) {
			for (int j = 0; j != m[0].size(); ++j) {
				cout << m[i][j] << " ";
			}
		}
		cout << endl;
	}
	void test() {
		vector<vector<int>> matrix = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16} };
		rotate(matrix);
		printMatrix(matrix);
	}

};


int main()
{
	ZigZagPrintMatrix z;
	z.test();

	PrintMatrixSpiralOrder p;
	p.test();

	RotateMatrix r;
	r.test();
	return 0;
}
