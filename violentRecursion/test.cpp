#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<queue>
#include<stack>
#include<vector>
#include<set>
#include<map>
#include<unordered_set>
//�������������ݽṹ������ʹ�õݹ麯������������ջ��Ԫ�صߵ�----------------------------------------------------
class ReverseStackUsingRecursive {
public:
	void reverse(stack<int>& st) {
		if (st.empty()) {
			return;
		}
		int i = f(st);	//ȡ��ջ�͵�Ԫ��
		reverse(st);	
		st.push(i);		//��ջ
	}

	//ȥ��������ջ�׵�Ԫ��
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


//��ӡһ���ַ�����ȫ�������У�--------------------------------------
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

//��ӡһ���ַ�����ȫ�������У�Ҫ�󲻳����ظ�����ֵ��������(����Ҫ������ͬ�������У�----------------------------------
//����set�Զ�ȥ���ظ�������
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

//��ӡ�ַ�������������--------------------------------------------
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

	//str[0....i-1]�Ѿ����þ�����
	//str[i....]���л�������iλ��
	//��������β�ͣ�i��ֹ��str��ʱ�����Ӽ�Ϊ���е�һ��
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

//��ӡ�ַ������������У�Ҫ�󲻳����ظ�����------------------------------------
//��һ�����Ը����������һ������setȥ��
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

	//str[0....i-1]�Ѿ����þ�����
	//str[i....]���л�������iλ��
	//��������β�ͣ�i��ֹ��str��ʱ�����Ӽ�Ϊ���е�һ��
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

//��������֧�޽磬���ڷ�һ��ֱ���ڵݹ�����п����ޱ�Ҫ�ĵݹ��֧
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

	//str[0....i-1]�Ѿ����þ�����
	//str[i....]���л�������iλ��
	//��������β�ͣ�i��ֹ��str��ʱ�����Ӽ�Ϊ���е�һ��
	void process(string& str, int i, vector<string>& res) {
		if (i == str.size()) {
			res.push_back(str);
		}
		bool visit[26] = { false };		//�����Ŀ������26��Сд��ĸ�����Բ���set����¼��λ���Ƿ��ѱ�ĳ���ַ�ռ�ù�
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

//����1��ӦA,2��ӦB,3��ӦC,��������
//�硰111������תΪ��AAA������KA��,��AK��
//����һ��ֻ�������ַ���ɵ��ַ���str,�����ж�����ת�����
class ConvertToLetterString {
public:
	int cnt = 0;
	int number(string str) {
		if (str.size() == 0) {
			return 0;
		}
		return process(str, 0);
		
	}
	//str[0...i-1]�Ѿ�ת�����ˣ��̶��ˣ�i֮ǰ���Ѿ������ˣ����ٹ���
	//����i...�����ж�����ת�����
	int process(string& str, int i) {
		if (i == str.size()) {	
			return 1;		//����1�����ͣ��ӿ�ʼ�������ߵ�����·Ϊ��Чת������1����Чת��
		}
		if (str[i] == '0') {	//��ʱ���������ַ���0ʱ��0����Ч�ģ��޷�ת��
			return 0;
		}

		if ('1' == str[i]) {
			int ret = process(str, i + 1);	//��ǰ�ַ�i����ת�������غ����ж����ַ���
			if (i + 1 < str.size()) {
				ret += process(str, i + 2);	//(i��i+1����Ϊ�����Ĳ��֣����غ����ж����ַ���
			}
			return ret;
		}

		if ('2' == str[i]) {
			int ret = process(str, i + 1);	//��ǰ�ַ�i����ת�������غ����ж����ַ���
			if (i + 1 < str.size() && str[i+1] >='0' && str[i+1]<='6') {	//��Ϊֻ��26����ĸ
				ret += process(str, i + 2);	//(i��i+1����Ϊ�����Ĳ��֣����غ����ж����ַ���
			}
			return ret;
		}
		//str[i]='3'~'9'ʱ��ֻ�ܵ�����Ϊһ���ֽ���ת��
		return process(str, i + 1);
	}
};
//��ֱ�Ӳ�ȡ��Ա��������ʽ��¼
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
		if (str[i] == '0') {	//��ʱ���������ַ���0ʱ��0����Ч�ģ��޷�ת��
			return ;
		}

		if ('1' == str[i]) {
			process(str, i + 1);	//��ǰ�ַ�i����ת�������غ����ж����ַ���
			if (i + 1 < str.size()) {
				process(str, i + 2);	//(i��i+1����Ϊ�����Ĳ��֣����غ����ж����ַ���
			}
			return ;
		}

		if ('2' == str[i]) {
			process(str, i + 1);	//��ǰ�ַ�i����ת�������غ����ж����ַ���
			if (i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '6') {	//��Ϊֻ��26����ĸ
				process(str, i + 2);	//(i��i+1����Ϊ�����Ĳ��֣����غ����ж����ַ���
			}
			return ;
		}
		//str[i]='3'~'9'ʱ��ֻ�ܵ�����Ϊһ���ֽ���ת��
		process(str, i + 1);
	}
};

void testConvertToLetterString() {
	string s = "11245";	//1 1 2 4 5 ,1 12 4 5 ,11 2 4 5,11 24 5,1 1 24 5	//5��ת����ʽ
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
	cout << "����:"<<ans.size() << endl;
	delete(&ans);		//����Ķ������ڶ��Ͽ��ٵģ�������ͷ�

	cout << "------------subSquencesNoRepeat------------" << endl;
	PrintAllSubsquencesNoRepeat pn;
	auto& ans1=pn.subsNoRepeat(s);
	for (auto v : ans1) {
		cout << v << endl;
	}
	cout << "����:" << ans1.size() << endl;
	delete(&ans1);
}

void testPrintAllPermutations() {
	string s = "abcde";
	PrintAllPermutations p;
	auto& ans=p.permutation(s);
	for (auto v : ans) {
		cout << v << endl;
	}
	cout << "����:" << ans.size() << endl;
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
	cout << "����:" << ans.size() << endl;
	delete(&ans);


	PrintAllPermutationsNoRepeat2 p2;
	auto& ans1 = p2.permutation(s);
	for (auto v : ans1) {
		cout << v << endl;
	}
	cout << "����:" << ans1.size() << endl;
	delete(&ans1);

	//�����ͬ

}



//��������------------------------------------------------------------------
class Knapack {
public:
	int getMaxValue(const vector<int>& w,const vector<int>& v, const int bag) {
		//return process1(w, v, 0, 0, bag);
		return process2(w, v, 0, bag);

	}

	//���䣺���������ͼ�ֵ����������
	//index....֮��Ļ�������ѡ��
	//0...index-1֮ǰ�Ļ����ѽ��������ˣ����˴�ʱ������װ��alreadyW������
	//�������أ���index֮��Ļ������ܱ�װ�²���������ֵ
	int process1(const vector<int>& w, const vector<int>& v, int index,int alreadyW,const int bag) {
		if (alreadyW > bag) {	//����
			return -1;
		}
		//û����
		if (index == w.size()) {
			return 0;
		}
		int p1 = process1(w, v, index + 1, alreadyW, bag);	//��Ҫindex����ʱ�����������ļ�ֵ
		int p2next = process1(w, v, index + 1, alreadyW + w[index], bag);	

		int p2 = -1;
		if (p2next != -1) {
			p2 = v[index] + p2next;
		}
		return max(p1, p2);
	}
	//��
	//ʡȥ�˱�����ǰ�Ѿ�װ�˶��ٵĲ����ͱ�������������rest��ʾ����ʣ������������
	int process2(const vector<int>& w, const vector<int>& v, int index ,int rest) {

		if (rest < 0) {	//����������Ч
			return -1;
		}
		if (index == w.size()) {
			return 0;
		}
		//�л�Ҳ�пռ�

		int p1 = process2(w, v, index + 1,  rest);	//��Ҫindex����ʱ�����������ļ�ֵ
		int p2next = process2(w, v, index + 1, rest-w[index]);

		int p2 = -1;
		if (p2next != -1) {	//����������Ч
			p2 = v[index] + p2next;
		}
		return max(p1, p2);
	}
};

//����һ��ֽ�����飬�ų�һ�ţ������е�ֵ����ֽ�Ƶ�ֵ��ֽ������ѡ��Aѡ��B,�涨һ��һ����һ���ƣ���ֻ�ܴ�����߻�����ұ���һ�ţ����涨A���֣�B���֣�
//A.B˭��ֽ����ֵ�ۼ���ߣ���Ϊʤ�ߣ� ֽ��������ֵ���ɼ�,A��B����������,���ʤ�ߵķ���
//�����������г��˿�ʼ����ȷA�����֣�B�Ǻ��֣�֮������ֺ��־���ĳ���ӽ��ϵ������ˣ�
class CardsInLine {
public:
	int win1(const vector<int>& arr) {
		if (arr.size() == 0) {
			return 0;
		}
		//�������ֺͺ���֮������ֵ���ڵ�ǰλ�ã�������A��������B
		return max(f(arr, 0, arr.size() - 1), s(arr, 0, arr.size() - 1));
	}
	//��ѡһ��ѡ�Ƶ�ʱ�򣬶��������֣����֣���ʱҪѡ�Ƶ���Ϊ���֣���һ�ξ��ֵ��Լ�����ѡ��

	//f�����֣���Ϊ���֣�һ����ѡ����Լ���������
	int f(const vector<int>& arr, int i, int j) {
		if (i == j) {
			return arr[i];
		}
		//���أ�max(arr[i]+�Լ���һ�¹�������Ϊ���ֵķ���,arr[j]+�Լ���һ�¹�������Ϊ���ֵķ���)
		return max(arr[i] + s(arr, i + 1, j), arr[j] + s(arr, i, j - 1));
	}
	//s�Ǻ��֣���Ϊ���֣�����ֻ������ѡ��������С��
	int s(const vector<int>& arr, int i, int j) {
		if(i==j){
			return 0;
		}
		//��Ϊ����û��ѡ��ֻ�ܷ�����һ���Լ���Ϊ���ֵķ��������Լ��Ǻ��֣����ֿ϶�����������С�ĸ��Լ���������min
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
