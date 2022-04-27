//-------------------------------------------------------------------------------------------------

//蓄水池算法

//假设给你一个袋子，只能装十个球，现在有一台机器，不断吐出球，从1号开始吐，假设吐到第n号球，让每个球留在袋子中的概率都为10/n
//算法流程：现在有个随机数生成器，能等概率生成指定范围的数字，假设为随机器为f(n），功能为等概率生成1到n的数字，
//			1到10号球直接入袋，之后第i号球，调用f(i)若，f(i）生成的数字为1到10之间，则把某个球扔掉，i号球入袋子，
//			再调用f(10),此前扔掉的某个球就是f(10）生成的号数。这样只要吐出了n号球，那么1——n号球入袋子的概率就为等概率为10/n


//给你一个等概率生成1-7的随机器f()，求等概率生成1-10;
// 封装一函数g(),用生成器f()= 1-3的话标记为1 ，4-6标记为0, 生成7的话就再来一次，直到生成非7,这样就做到了0，1等概率生成
// 利用二进制位，1到10的话最多只需4位二进制位，依次调用g()为每一位赋值，得到数字num，若num>10,则重新再来一次，直到生成的数字在0到9间，最后返回num+1，
// 即可等概率生成1-10

// 现有一个生成器f() 可生成两个数字设为0和1,概率分别固定为p和1-p，利用它等概率生成17-38的数字
// 现在要封装一函数，g()实现等概率生成0和1。可调用两次f()，可能如下 00 10 01 11，生成01和10的概率相等，都为p*(1-p)，
// 因此，可利用这个特点，调用两次f()，若生成01表示生成0，生成10表示1，若生成00或11,再来一次，直到生成01或10,
// 至此，可利用01和10来等概率变相实现1和0的等概率生成器，随后利用二进制仿照上一问题生成数字




//---------------------------------------------------------------------------------------------

//KMP

class KMP {
public:
	int getIndexof(const string& str, const string& match) {
		if (match.size() < 1 || str.size() < 1 || str.size() < match.size()) {
			return -1;
		}
		int x = 0;	// str中当前对比到的位置
		int y = 0;	// match中当前对比到的位置

		// next[i] match中i之前的字符串match[0...i-1]相同的前缀和后缀数
		vector<int> next = getNextArray(match);

		// O(N)	设两变量 x(最大值N) x-y(最大值N)  以下的三个分支互斥的，x和x-y都是非递减的，所以总体循环次数不超所2N
		while (x < str.size() && y < match.size()) {
			if (str[x] == match[y]) {
				// 两位置比较相同，向后移，比较下一个
				++x; ++y;
			} else if (next[y] == -1) {	//条件等价 y==0
				// match往前没得比了，说明str[i]比不了，下一个
				++x;
			} else {
				// 往前跳
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
		next[0] = -1;	//人为规定
		next[1] = 0;
		int i = 2;	//从下标为2的开始算
		// cn代表，cn位置的字符，是当前和i-1位置比较的字符
		int cn = 0;	//从下标2开始，设为0
		// O(M)  设两变量 i(最大值M) i-cn(最大值M)  以下的三个分支互斥的，i和i-cn都是非递减的，所以总体循环次数不超所2M
		while (i < next.size()) {
			if (match[i - 1] == match[cn]) {
				// i++是因为当前字符结算完后，继续下一个字符
				// ++cn是因为 next[i]=cn+1,当计算i+1位置的字符时，cn=next[i],于是在当前一起自增
				next[i++] = ++cn;
			} else if (cn > 0) {
				// 往前跳
				cn = next[cn];
			} else {
				// match没得比了，i位置只能为0
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


//给你一个字符串。如“1234”,它有很多旋转词，如“1234，“2341”，“3412”，“4123”
// 现给你两个字符串，str1和str2，请你判断他是否互为选择词

// 将str1追加自身，再用KMP进行匹配
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



// 给你两颗二叉树 T1和T2 ,请问 T2的结构关系是否对应于T1中的某颗子树
class TreeEqual {
public:
	class Node {
	public:
		int value;
		Node* left;
		Node* right;
		Node(int v) :value(v), left(nullptr), right(nullptr) {}
	};


	// big做头节点的树，其中是否有某颗子树的结构，是和small为头的树，是完全一样的
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

	// head1为头的树，是否在结构上，完全和head2一样
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
		int x = 0;	// str中当前对比到的位置
		int y = 0;	// match中当前对比到的位置

		vector<int> next = getNextArray(match);

		while (x < str.size() && y < match.size()) {
			if (str[x] == match[y]) {
				++x; ++y;
			} else if (next[y] == -1) {	//条件等价 y==0
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
		next[0] = -1;	//人为规定
		next[1] = 0;
		int i = 2;	//从下标为2的开始算
		int cn = 0;	//从下标2开始，设为0
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

