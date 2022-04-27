#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include<map>
#include<unordered_set>
//不借助其他数据结构，仅可使用递归函数，将给定的栈中元素颠倒----------------------------------------------------
class ReverseStackUsingRecursive {
public:
	void reverse(stack<int>& st) {
		if (st.empty()) {
			return;
		}
		int i = f(st);	//取出栈低的元素
		reverse(st);	
		st.push(i);		//入栈
	}

	//去除并返回栈底的元素
	int f(stack<int>& st) {
		int res = st.top();
		st.pop();
		if (st.empty()) {
			return res;
		} else {
			int last = f(st);
			st.push(res);
			return last;
		}
	}
};


//打印一个字符串的全部子序列，--------------------------------------
class PrintAllSubsquences {
public:
	vector<string>& subs(string s) {
		string path;
		vector<string>* ans=new vector<string>;
		process1(s, 0, *ans, path);
		return *ans;
	}

	void process1(string& str, int index, vector<string>& ans, string& path) {
		if (index == str.size()) {
			ans.push_back(path);
			return;
		}
		process1(str, index + 1, ans, path);
		path += str[index];
		process1(str, index + 1, ans, path);
		path.pop_back();
	}
};

//打印一个字符串的全部子序列，要求不出现重复字面值的子序列(即不要出现相同的子序列）----------------------------------
//利用set自动去除重复子序列
class PrintAllSubsquencesNoRepeat {
public:
	unordered_set<string>& subsNoRepeat(string s) {
		string path;
		unordered_set<string>* setString=new unordered_set<string>;
		process1(s, 0, *setString, path);
		return *setString;
	}

	void process1(string& str, int index, unordered_set<string>& setString, string& path) {
		if (index == str.size()) {
			setString.insert(path);
			return;
		}
		process1(str, index + 1, setString, path);
		path += str[index];
		process1(str, index + 1, setString, path);
		path.pop_back();
	}
};

//打印字符串的所有排列--------------------------------------------
class PrintAllPermutations {
public:
	vector<string>& permutation(string str) {
		vector<string>* res = new vector<string>;
		if (str.size() == 0) {
			return *res;
		}
		process(str, 0, *res);
		return *res;
	}

	//str[0....i-1]已经做好决定的
	//str[i....]都有机会来到i位置
	//当遍历到尾巴，i终止，str此时的样子即为排列的一种
	void process(string& str, int i, vector<string>& res) {
		if (i == str.size()) {
			res.push_back(str);
		}
		for (int j = i; j < str.size(); ++j) {
			swap(str[i], str[j]);
			process(str, i + 1, res);
			swap(str[i], str[j]);
		}
	}
};

//打印字符串的所有排列，要求不出现重复排列------------------------------------
//法一：可以跟上面的做法一样，用set去重
class PrintAllPermutationsNoRepeat1 {
public:
	unordered_set<string>& permutation(string str) {
		unordered_set<string>* res = new unordered_set<string>;
		if (str.size() == 0) {
			return *res;
		}
		process(str, 0, *res);

		return *res;
	}

	//str[0....i-1]已经做好决定的
	//str[i....]都有机会来到i位置
	//当遍历到尾巴，i终止，str此时的样子即为排列的一种
	void process(string& str, int i, unordered_set<string>& res) {
		if (i == str.size()) {
			res.insert(str);
		}
		for (int j = i; j < str.size(); ++j) {
			swap(str[i], str[j]);
			process(str, i + 1, res);
			swap(str[i], str[j]);
		}
	}
};

//法二：分支限界，快于法一，直接在递归过程中砍掉无必要的递归分支
class PrintAllPermutationsNoRepeat2 {
public:
	vector<string>& permutation(string str) {
		vector<string>* res = new vector<string>;
		if (str.size() == 0) {
			return *res;
		}
		process(str, 0, *res);
		return *res;
	}

	//str[0....i-1]已经做好决定的
	//str[i....]都有机会来到i位置
	//当遍历到尾巴，i终止，str此时的样子即为排列的一种
	void process(string& str, int i, vector<string>& res) {
		if (i == str.size()) {
			res.push_back(str);
		}
		bool visit[26] = { false };		//如果题目不光是26个小写字母，可以采用set来记录此位置是否已被某个字符占用过
		for (int j = i; j < str.size(); ++j) {
			if (!visit[str[j] - 'a']) {
				visit[str[j] - 'a'] = true;
				swap(str[i], str[j]);
				process(str, i + 1, res);
				swap(str[i], str[j]);
			}
		}
	}
};

//假如1对应A,2对应B,3对应C,依次类推
//如“111”可以转为“AAA”，“KA”,“AK”
//给定一个只有数字字符组成的字符串str,返回有多少种转换结果
class ConvertToLetterString {
public:
	int cnt = 0;
	int number(string str) {
		if (str.size() == 0) {
			return 0;
		}
		return process(str, 0);
		
	}
	//str[0...i-1]已经转化完了，固定了，i之前的已经决定了，不再关心
	//关心i...往后有多少种转化结果
	int process(string& str, int i) {
		if (i == str.size()) {	
			return 1;		//返回1，解释：从开始到结束走的这条路为有效转化，是1条有效转化
		}
		if (str[i] == '0') {	//此时遇到的是字符是0时，0是无效的，无法转换
			return 0;
		}

		if ('1' == str[i]) {
			int ret = process(str, i + 1);	//当前字符i单独转换，返回后续有多少种方法
			if (i + 1 < str.size()) {
				ret += process(str, i + 2);	//(i和i+1）作为单独的部分，返回后续有多少种方法
			}
			return ret;
		}

		if ('2' == str[i]) {
			int ret = process(str, i + 1);	//当前字符i单独转换，返回后续有多少种方法
			if (i + 1 < str.size() && str[i+1] >='0' && str[i+1]<='6') {	//因为只有26个字母
				ret += process(str, i + 2);	//(i和i+1）作为单独的部分，返回后续有多少种方法
			}
			return ret;
		}
		//str[i]='3'~'9'时，只能单独作为一部分进行转换
		return process(str, i + 1);
	}
};
//或直接采取成员变量的形式记录
class ConvertToLetterString1 {
public:
	int cnt = 0;
	int number(string str) {
		if (str.size() == 0) {
			return 0;
		}
		process(str, 0);
		return cnt;

	}
	void process(string& str, int i) {
		if (i == str.size()) {
			++cnt;
			return ;
		}
		if (str[i] == '0') {	//此时遇到的是字符是0时，0是无效的，无法转换
			return ;
		}

		if ('1' == str[i]) {
			process(str, i + 1);	//当前字符i单独转换，返回后续有多少种方法
			if (i + 1 < str.size()) {
				process(str, i + 2);	//(i和i+1）作为单独的部分，返回后续有多少种方法
			}
			return ;
		}

		if ('2' == str[i]) {
			process(str, i + 1);	//当前字符i单独转换，返回后续有多少种方法
			if (i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '6') {	//因为只有26个字母
				process(str, i + 2);	//(i和i+1）作为单独的部分，返回后续有多少种方法
			}
			return ;
		}
		//str[i]='3'~'9'时，只能单独作为一部分进行转换
		process(str, i + 1);
	}
};

void testConvertToLetterString() {
	string s = "11245";	//1 1 2 4 5 ,1 12 4 5 ,11 2 4 5,11 24 5,1 1 24 5	//5种转换方式
	ConvertToLetterString c;
	cout << c.number(s) << endl;
}

void testReverse() {
	stack<int> a;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);

	ReverseStackUsingRecursive s;
	s.reverse(a);
	while (!a.empty()) {
		cout << a.top() << endl;
		a.pop();
	}
}

void testPrintAllSubsquences(){
	string s = "123442";
	PrintAllSubsquences p;
	auto &ans=p.subs(s);
	cout << "------------subSquences------------" << endl;
	for (auto v : ans) {
		cout << v << endl;
	}
	cout << "总数:"<<ans.size() << endl;
	delete(&ans);		//返会的对象是在堆上开辟的，用完后释放

	cout << "------------subSquencesNoRepeat------------" << endl;
	PrintAllSubsquencesNoRepeat pn;
	auto& ans1=pn.subsNoRepeat(s);
	for (auto v : ans1) {
		cout << v << endl;
	}
	cout << "总数:" << ans1.size() << endl;
	delete(&ans1);
}

void testPrintAllPermutations() {
	string s = "abcde";
	PrintAllPermutations p;
	auto& ans=p.permutation(s);
	for (auto v : ans) {
		cout << v << endl;
	}
	cout << "总数:" << ans.size() << endl;
	delete(&ans);
}

void testPrintAllPermutationsNoRepeat() {
	string s = "aabcdc";
	PrintAllPermutationsNoRepeat1 p;
	cout << "test1-----------------------" << endl;
	auto& ans = p.permutation(s);
	for (auto v : ans) {
		cout << v << endl;
	}
	cout << "总数:" << ans.size() << endl;
	delete(&ans);


	PrintAllPermutationsNoRepeat2 p2;
	auto& ans1 = p2.permutation(s);
	for (auto v : ans1) {
		cout << v << endl;
	}
	cout << "总数:" << ans1.size() << endl;
	delete(&ans1);

	//结果相同

}



//背包问题------------------------------------------------------------------
class Knapack {
public:
	int getMaxValue(const vector<int>& w,const vector<int>& v, const int bag) {
		//return process1(w, v, 0, 0, bag);
		return process2(w, v, 0, bag);

	}

	//不变：货物重量和价值，背包承重
	//index....之后的货物自由选择
	//0...index-1之前的货物已近决定过了，至此此时背包已装了alreadyW的重量
	//函数返回：从index之后的货物所能被装下产生的最大价值
	int process1(const vector<int>& w, const vector<int>& v, int index,int alreadyW,const int bag) {
		if (alreadyW > bag) {	//超重
			return -1;
		}
		//没超重
		if (index == w.size()) {
			return 0;
		}
		int p1 = process1(w, v, index + 1, alreadyW, bag);	//不要index货物时，后续产生的价值
		int p2next = process1(w, v, index + 1, alreadyW + w[index], bag);	

		int p2 = -1;
		if (p2next != -1) {
			p2 = v[index] + p2next;
		}
		return max(p1, p2);
	}
	//或
	//省去了背包当前已经装了多少的参数和背包的容量，用rest表示背包剩余的重量来替代
	int process2(const vector<int>& w, const vector<int>& v, int index ,int rest) {

		if (rest < 0) {	//后续货物无效
			return -1;
		}
		if (index == w.size()) {
			return 0;
		}
		//有货也有空间

		int p1 = process2(w, v, index + 1,  rest);	//不要index货物时，后续产生的价值
		int p2next = process2(w, v, index + 1, rest-w[index]);

		int p2 = -1;
		if (p2next != -1) {	//后续货物有效
			p2 = v[index] + p2next;
		}
		return max(p1, p2);
	}
};

//给定一个纸牌数组，排成一排，数组中的值代表纸牌的值，纸牌现有选手A选手B,规定一人一次拿一张牌，且只能从最左边或从最右边拿一张，若规定A先手，B后手，
//A.B谁的纸牌数值累计最高，即为胜者， 纸牌所有数值都可见,A和B都绝顶聪明,算出胜者的分数
//（整个过程中除了开始有明确A是先手，B是后手，之后的先手后手就是某种视角上的区别了）
class CardsInLine {
public:
	int win1(const vector<int>& arr) {
		if (arr.size() == 0) {
			return 0;
		}
		//返回先手和后手之间的最大值，在当前位置，先手是A，后手是B
		return max(f(arr, 0, arr.size() - 1), s(arr, 0, arr.size() - 1));
	}
	//在选一次选牌的时候，都会有先手，后手，此时要选牌的人为先手，下一次就轮到自己后手选了

	//f是先手，作为先手，一定是选择对自己利益最大的
	int f(const vector<int>& arr, int i, int j) {
		if (i == j) {
			return arr[i];
		}
		//返回：max(arr[i]+自己在一下过程中作为后手的分数,arr[j]+自己在一下过程中作为后手的分数)
		return max(arr[i] + s(arr, i + 1, j), arr[j] + s(arr, i, j - 1));
	}
	//s是后手，作为后手，先手只会让你选择利益最小的
	int s(const vector<int>& arr, int i, int j) {
		if(i==j){
			return 0;
		}
		//作为后手没得选，只能返回下一步自己作为先手的分数，而自己是后手，先手肯定留下利益最小的给自己，所以用min
		return min(f(arr, i + 1, j), f(arr, i, j - 1));
	}


};


void testCrads() {
	CardsInLine c;
	vector<int> arr = { 4,7,9,5 };
	cout << "A:" << c.f(arr, 0, 3) << endl;
	cout << "B:" << c.s(arr, 0, 3) << endl;
	cout << "win:" << c.win1(arr);

}


int main(void)
{
	//testReverse();
	//testPrintAllSubsquences();
	//testPrintAllPermutations();
	//testPrintAllPermutationsNoRepeat();
	//testConvertToLetterString();
	//testCrads();

	/*auto ret=testClass();
	cout << ret.str << endl;*/

	return 0;

}
