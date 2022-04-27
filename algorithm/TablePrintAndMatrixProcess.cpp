//Table printing and matrix processing
//���;�����

//���
//1�������������ֵ��̫�࣬������hardcode�ķ�ʽ�г�����Ϊ�����һ����
//2)һ����������ʱ�ײ�Ƶ��ʹ�ù�ģ�����С����Ľ⣬���С����ķ���ֵ��������1)�����԰�С����Ľ��г�һ�ű���Ϊ�����һ����
//3)����ҹ���

//����
//��������򵥣�����ֻ��һ��ʵ�ʲ���
//Ҫ��ķ�������Ҳ�򵥣�Ҳֻ��һ��
//�ñ��������������������Ӧ�ķ���ֵ����ӡ�����ҹ��ɣ������Ż�code

//����һ��
//С��ȥ��ƻ�����̵�ֻ�ṩ�������͵����ϴ���ÿ�����Ͷ�������������
//1)��װ��6��ƻ���Ĵ���
//2)��װ��8��ƻ���Ĵ���
//С����������ʹ�����ִ�����װƻ��������С����ǿ��֢����Ҫ���Լ�ʹ�õĴ��������������٣���ʹ�õ�ÿ�����ӱ���װ����
//����һ��������N����������ʹ�ö��ٴ��ӡ����N�޷���ʹ�õ�ÿ�����ӱ���װ��, ���� - 1

class AppleMinBags {
	int minBags(int apple) {
		if (apple < 0) {
			return -1;
		}

		int bag6 = -1;
		//�ȼ���ȫʹ��8�Ŵ��ӣ�ʣ�༸������󲻶�--8�Ŵ��ӵ���������6�Ŵ����Ƿ�������װ����ֱ��8�ô��Ӽ�Ϊ0��ʣ�µĴ��ڵ���24�˳�
		int bag8 = apple / 8;
		int rest = apple - 8 * bag8;
		while (bag8 >= 0 && rest < 24) {
			//��rest>=24˵������rest���е�24��������3��8�Ŵ��ӣ�ʵ����Ļ���ʣ��rest-24�����⣬��û��Ҫ����ȥ�ˣ��ض��޷��ɹ�
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
	//ͨ��print�����۲���ɵã���18֮��8��Ϊһ����й��������
	int minBagAwesome(int apple) {
		//���������������-1
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


//�������
//����һ��������N����ʾ��N�����ͳһ�ѷ��ڲֿ�����һֻţ��һֻ��ţ�ȳԣ����ԣ����������Բݲ�����ţ������ÿһ���ܳԵĲ���������:
//1��4��16��64��(4��ĳ�η�)
//˭���ȰѲݳ��꣬˭��ʤ
//����ţ���򶼾�������������Ӯ�������������Եľ���������Ψһ�Ĳ���N������˭��Ӯ

class EatGress {
public:
	
	string winner1(int n) {
		// 0 1  2  3  4
		//�� �� �� �� ��
		if (n < 5) {
			return (n == 0 || n == 2) ? "����" : "����";
		}
		int base = 1;
		while (base <= n) {
			//��ǰһ��n�ݲݣ����ֳԵ�����base�ݣ�n-base���������ֵ�
			if (winner1(n - base) == "����") {
				//��n-base�Ĺ����У��Լ���Ϊ�˺��֣�����n-base�����к���Ӯ�ˣ����Լ����ѡ��ͻ�Ӯ
				return "����";
			}
			//��ֹ���
			if (base > n / 4) {
				break;
			}
			base *= 4;
		}

		//����ʼ���޷�Ӯ������Ӯ
		return "����";
	}
	//ͨ����ӡ����ᷢ�֣������Ǻ��Ⱥ����ȣ�ѭ����ȥ
	void print() {
		for (int i = 0; i < 50; ++i) {
			cout << i << ": " << winner1(i) << endl;;
		}
	}

	string winner2(int n) {
		if (n % 5 == 0 || n % 5 == 2) {
			return "����";
		}
		return "����";
	}
};

//��������
//����һ����:���Ա�ʾ�����ɣ�����>1)���������͵�������:
//5 = 2 + 3��5������������
//12 = 3 + 4 + 5, 12������������
//1����������������ΪҪ����������1��������������2 = 1 + 1��2Ҳ���ǣ���Ϊ�Ⱥ��ұ߲�����������
//����һ������N, �����ǲ��ǿ��Ա�ʾ���������������͵���

class MsumToN {
public:
	//����
	bool isMSum1(int num) {
		for (int i = 1; i < num; ++i) {//��ͷ����i
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
	//ͨ����ӡ�۲�ã�ֻҪ��2���ݶ���false
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
		//��nums&(nums-1))�ж�num�ǲ���2��ĳ�η������Ƿ���0�����Ƿ���1 
		return (num & (num - 1)) != 0;
	}
};


//��֤������

//����һ��
//zigzag��ӡ��֤
class ZigZagPrintMatrix {
public:
	void printMatrixZigZag(vector<vector<int>>& matrix) {
		int Arow = 0, Acol = 0;
		int Brow = 0, Bcol = 0;
		int EndRow = matrix.size() - 1;
		int EndCol = matrix[0].size() - 1;
		bool fromUp = false;	//�ǲ��Ǵ����������´�ӡ
		//һ��ʼA��B���ڣ�0��0)λ�ã�A�����ߣ��ߵ�ͷ�Ļ������ߣ�B�����ߣ��ߵ�ͷ�Ļ�������
		while (Arow != EndRow + 1) {
			//��֪б�ߵ����ˣ�A��B������Ҳ��֪��ȥ��ӡ
			printLevel(matrix, Arow, Acol, Brow, Bcol, fromUp);

			//���´����в��ɻ���������֮�����Ͻǵ�Ԫ�غ����½ǵ�Ԫ�ؽ�������

			//���A�����ߵ�ͷ�ˣ���ô��+1,��ʼ������
			Arow = Acol == EndCol ? Arow + 1 : Arow;
			//���A�����ߵ�ͷ��,�в��䣬������+1,��������
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


//�������תȦ��ӡ����

class PrintMatrixSpiralOrder {
public:
	//ֻ��Ҫ���Ͻǣ�a,b)�����½�(c,d)����ȷ��һ������
	void printEdge(vector<vector<int>>& m, int a, int b, int c, int d) {
		//���ֻ��һ��
		if (a == c) {
			for (int i = b; i <= d; ++i) {
				cout << m[a][i] << " ";
			}
		} else if (b == d) {	//���ֻ��һ��
			for (int i = a; i < c; ++i) {
				cout << m[i][b] << " ";
			}
		} else {
			int curC = b;
			int curR = a;
			//�ϱ�
			while (curC != d) {
				cout << m[a][curC] << " ";
				curC++;
			}
			//�ұ�
			while (curR != c) {
				cout << m[curR][d] << " ";
				curR++;
			}
			//�±�
			while (curC != b) {
				cout << m[c][curC] << " ";
				curC--;
			}
			//���
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



//ԭ����ת�����ξ���
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
