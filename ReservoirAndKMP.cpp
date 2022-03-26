//-------------------------------------------------------------------------------------------------

//��ˮ���㷨

//�������һ�����ӣ�ֻ��װʮ����������һ̨�����������³��򣬴�1�ſ�ʼ�£������µ���n������ÿ�������ڴ����еĸ��ʶ�Ϊ10/n
//�㷨���̣������и���������������ܵȸ�������ָ����Χ�����֣�����Ϊ�����Ϊf(n��������Ϊ�ȸ�������1��n�����֣�
//			1��10����ֱ�������֮���i���򣬵���f(i)����f(i�����ɵ�����Ϊ1��10֮�䣬���ĳ�����ӵ���i��������ӣ�
//			�ٵ���f(10),��ǰ�ӵ���ĳ�������f(10�����ɵĺ���������ֻҪ�³���n������ô1����n��������ӵĸ��ʾ�Ϊ�ȸ���Ϊ10/n


//����һ���ȸ�������1-7�������f()����ȸ�������1-10;
// ��װһ����g(),��������f()= 1-3�Ļ����Ϊ1 ��4-6���Ϊ0, ����7�Ļ�������һ�Σ�ֱ�����ɷ�7,������������0��1�ȸ�������
// ���ö�����λ��1��10�Ļ����ֻ��4λ������λ�����ε���g()Ϊÿһλ��ֵ���õ�����num����num>10,����������һ�Σ�ֱ�����ɵ�������0��9�䣬��󷵻�num+1��
// ���ɵȸ�������1-10

// ����һ��������f() ����������������Ϊ0��1,���ʷֱ�̶�Ϊp��1-p���������ȸ�������17-38������
// ����Ҫ��װһ������g()ʵ�ֵȸ�������0��1���ɵ�������f()���������� 00 10 01 11������01��10�ĸ�����ȣ���Ϊp*(1-p)��
// ��ˣ�����������ص㣬��������f()��������01��ʾ����0������10��ʾ1��������00��11,����һ�Σ�ֱ������01��10,
// ���ˣ�������01��10���ȸ��ʱ���ʵ��1��0�ĵȸ�����������������ö����Ʒ�����һ������������




//---------------------------------------------------------------------------------------------

//KMP

class KMP {
public:
	int getIndexof(const string& str, const string& match) {
		if (match.size() < 1 || str.size() < 1 || str.size() < match.size()) {
			return -1;
		}
		int x = 0;	// str�е�ǰ�Աȵ���λ��
		int y = 0;	// match�е�ǰ�Աȵ���λ��

		// next[i] match��i֮ǰ���ַ���match[0...i-1]��ͬ��ǰ׺�ͺ�׺��
		vector<int> next = getNextArray(match);

		// O(N)	�������� x(���ֵN) x-y(���ֵN)  ���µ�������֧����ģ�x��x-y���Ƿǵݼ��ģ���������ѭ������������2N
		while (x < str.size() && y < match.size()) {
			if (str[x] == match[y]) {
				// ��λ�ñȽ���ͬ������ƣ��Ƚ���һ��
				++x; ++y;
			} else if (next[y] == -1) {	//�����ȼ� y==0
				// match��ǰû�ñ��ˣ�˵��str[i]�Ȳ��ˣ���һ��
				++x;
			} else {
				// ��ǰ��
				y = next[y];
			}
		}
		return y == match.size() ? x - y : -1;
	}
private:

	// O(M)
	vector<int> getNextArray(const string& match) {
		if (match.size() == 1) {
			return { -1 };
		}
		vector<int> next(match.size());
		next[0] = -1;	//��Ϊ�涨
		next[1] = 0;
		int i = 2;	//���±�Ϊ2�Ŀ�ʼ��
		// cn����cnλ�õ��ַ����ǵ�ǰ��i-1λ�ñȽϵ��ַ�
		int cn = 0;	//���±�2��ʼ����Ϊ0
		// O(M)  �������� i(���ֵM) i-cn(���ֵM)  ���µ�������֧����ģ�i��i-cn���Ƿǵݼ��ģ���������ѭ������������2M
		while (i < next.size()) {
			if (match[i - 1] == match[cn]) {
				// i++����Ϊ��ǰ�ַ�������󣬼�����һ���ַ�
				// ++cn����Ϊ next[i]=cn+1,������i+1λ�õ��ַ�ʱ��cn=next[i],�����ڵ�ǰһ������
				next[i++] = ++cn;
			} else if (cn > 0) {
				// ��ǰ��
				cn = next[cn];
			} else {
				// matchû�ñ��ˣ�iλ��ֻ��Ϊ0
				next[i++] = 0;
			}
		}
		return next;
	}

public:
	void test() {
		string s = "aabcctaabcctaabcctd";
		string m = "aabcctd";
		cout << getIndexof(s, m) << endl;

	}
};


//����һ���ַ������硰1234��,���кܶ���ת�ʣ��硰1234����2341������3412������4123��
// �ָ��������ַ�����str1��str2�������ж����Ƿ�Ϊѡ���

// ��str1׷����������KMP����ƥ��
class RotatingWord {
public:
	bool way(string str1, string str2) {
		str1 += str2;
		KMP k;
		return k.getIndexof(str1, str2) == -1 ? false : true;
	}

	void test() {
		cout << way("1234456", "4456123") << endl;
	}
};



// �������Ŷ����� T1��T2 ,���� T2�Ľṹ��ϵ�Ƿ��Ӧ��T1�е�ĳ������
class TreeEqual {
public:
	class Node {
	public:
		int value;
		Node* left;
		Node* right;
		Node(int v) :value(v), left(nullptr), right(nullptr) {}
	};


	// big��ͷ�ڵ�����������Ƿ���ĳ�������Ľṹ���Ǻ�smallΪͷ����������ȫһ����
	bool containsTree1(Node* big, Node* small) {
		if (small == nullptr) {
			return true;
		}
		if (big == nullptr) {
			return false;
		}
		if (isSameValueStructure(big, small)) {
			return true;
		}
		return containsTree1(big->left, small) || containsTree1(big->right, small);
	}

	// head1Ϊͷ�������Ƿ��ڽṹ�ϣ���ȫ��head2һ��
	bool isSameValueStructure(Node* head1, Node* head2) {
		if (head1 == nullptr && head2 != nullptr) {
			return false;
		}
		if (head1 != nullptr && head2 == nullptr) {
			return false;
		}
		if (head1 == nullptr && head2 == nullptr) {
			return true;
		}
		if (head1->value != head2->value) {
			return false;
		}
		return isSameValueStructure(head1->left, head2->left) && isSameValueStructure(head1->left, head2->right);
	}

	bool containsTree2(Node* big, Node* small) {
		if (small == nullptr) {
			return true;
		}
		if (big == nullptr) {
			return false;
		}
		vector<string> str = preSerial(big);
		vector<string> match = preSerial(small);
		return getIndexof(str, match) != -1;
	}

	vector<string> preSerial(Node* head) {
		vector<string> ans;
		pres(head, ans);
		return ans;
	}
	void pres(Node* head, vector<string>& ans) {
		if (head == nullptr) {
			ans.push_back("NULL");
		} else {
			ans.push_back(to_string(head->value));
			pres(head->left, ans);
			pres(head->right, ans);
		}

	}

	//KMP
	int getIndexof(vector<string>& str, vector<string>& match) {
		if (match.size() < 1 || str.size() < 1 || str.size() < match.size()) {
			return -1;
		}
		int x = 0;	// str�е�ǰ�Աȵ���λ��
		int y = 0;	// match�е�ǰ�Աȵ���λ��

		vector<int> next = getNextArray(match);

		while (x < str.size() && y < match.size()) {
			if (str[x] == match[y]) {
				++x; ++y;
			} else if (next[y] == -1) {	//�����ȼ� y==0
				++x;
			} else {
				y = next[y];
			}
		}
		return y == match.size() ? x - y : -1;
	}
	vector<int> getNextArray(vector<string>& match) {
		if (match.size() == 1) {
			return { -1 };
		}
		vector<int> next(match.size());
		next[0] = -1;	//��Ϊ�涨
		next[1] = 0;
		int i = 2;	//���±�Ϊ2�Ŀ�ʼ��
		int cn = 0;	//���±�2��ʼ����Ϊ0
		while (i < next.size()) {
			if (match[i - 1] == match[cn]) {
				next[i++] = ++cn;
			} else if (cn > 0) {
				cn = next[cn];
			} else {
				next[i++] = 0;
			}
		}
		return next;
	}

};

