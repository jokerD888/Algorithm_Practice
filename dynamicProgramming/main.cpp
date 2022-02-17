#define _CRT_SECURE_NO_WARNINGS 1

//��̬�滮ѧϰ

#include<iostream>
using namespace std;
#include<algorithm>
#include<vector>
#include<map>
//��Ŀһ
//�������ų�һ�е�N��λ�ã���Ϊ1~N��Nһ�����ڻ����2��ʼʱ�����������е�Mλ����(Mһ����1~N�е�һ��)
// �������������1λ�ã���ô��һ��ֻ����������2λ��;�������������Nλ�ã���ô��һ��ֻ����������N-1λ��;
// ��������������м�λ�ã���ô��һ�����������߻���������;
//�涨�����˱�����K��������������Pλ��(PҲ��1~N�е�һ��)�ķ����ж����ָ����ĸ�����N��M��K��P�����ط�������

class RobotWalk {
public:
	//�����ݹ�
	int way1(int N, int M, int K, int P) {
		if (N < 2 || K < 1 || M<1 || M>N || P<1 || P>N) {
			return 0;
		}
		return walk1(N, M, K, P);
	}
	//cur��ǰλ�ã�restʣ��λ��
	int walk1(int N, int cur, int rest, int P) {
		if (rest == 0) {
			return cur == P ? 1 : 0;
		}
		if (cur == 1) {
			return walk1(N, 2, rest - 1, P);
		}
		if (cur == N) {
			return walk1(N, N - 1, rest - 1, P);
		}
		return walk1(N, cur + 1, rest - 1, P) + walk1(N, cur - 1, rest - 1, P);
	}


	//��̬�滮��������仯���������ö�ά����������
	int way2(int N, int M, int K, int P) {
		if (N < 2 || K < 1 || M<1 || M>N || P<1 || P>N) {
			return 0;
		}
		vector<vector<int>> dp(N + 1, vector<int>(K + 1,-1));
		return walk2(N, M, K, P,dp);
	}
	//cur��ǰλ�ã�restʣ��λ��
	int walk2(int N, int cur, int rest, int P, vector<vector<int>>& dp) {
		if (rest == 0) {
			dp[cur][rest] = cur == P ? 1 : 0;
			return dp[cur][rest];
		}
		if (cur == 1) {
			dp[cur][rest] = walk2(N, 2, rest - 1, P, dp);
			return dp[cur][rest];
		}
		if (cur == N) {
			dp[cur][rest] = walk2(N, N - 1, rest - 1, P, dp);
			return dp[cur][rest];
		}
		dp[cur][rest] = walk2(N, cur + 1, rest - 1, P, dp) + walk2(N, cur - 1, rest - 1, P, dp);
		return dp[cur][rest];
	}


	//��ʵ���ϲ��ÿ���ô������飬�����������õ��ľ�ֻ������״̬
	//walk�����ĵ���Ҳֻ�ı�cur��rest������״̬����
	int way3(int N, int M, int K, int P) {
		if (N < 2 || K < 1 || M<1 || M>N || P<1 || P>N) {
			return 0;
		}
		return walk3(N, M, K, P);
	}
	//cur��ǰλ�ã�restʣ��λ��
	int walk3(int N, int M, int K, int P) {
		vector<int> newdp(N + 1);
		vector<int> olddp(N + 1);
		olddp[P] = 1;
		for (int i = 0; i < K; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (j == 1) {
					newdp[j] = olddp[j + 1];
				} else if (j == N) {
					newdp[j] = olddp[j - 1];
				} else {
					newdp[j] = olddp[j + 1] + olddp[j - 1];
				}
			}
			olddp = newdp;
		}
		return olddp[M];
	}

};

void testRRobotWalk() {
	RobotWalk r;
	cout << r.way1(7, 2, 5, 3) << endl;
	cout << r.way2(7, 2, 5, 3) << endl;
	cout << r.way3(7, 2, 5, 3) << endl;
}



//��Ŀ������������
class Knapsack {
public:
	//�����ݹ�
	int way1(const vector<int>& w, const vector<int>& v, const int bag) {
		return process2(w, v, 0, bag);
	}
	int process2(const vector<int>& w, const vector<int>& v, int index, int rest) {

		if (rest < 0) {	//����������Ч
			return -1;
		}
		if (index == w.size()) {
			return 0;
		}
		//�л�Ҳ�пռ�

		int p1 = process2(w, v, index + 1, rest);	//��Ҫindex����ʱ�����������ļ�ֵ
		int p2next = process2(w, v, index + 1, rest - w[index]);

		int p2 = -1;
		if (p2next != -1) {	//����������Ч
			p2 = v[index] + p2next;
		}
		return max(p1, p2);
	}

	//��̬�滮,���ձ����ݹ飬�Ӻ���ǰ��
	int dpWay(const vector<int>& w,const vector<int>& v, int bag) {
		int N = w.size();	
		vector<vector<int>> dp(N + 1, vector<int>(bag + 1));
		//dp[N][...]���Զ���ʼ��0

		for (int index = N - 1; index >= 0; --index) {	
			for (int rest = 1; rest <= bag; ++rest) {
				int p1 = dp[index + 1][rest];	//��Ҫ��ǰ����
				int p2 = -1;
				if (rest - w[index] >= 0) {	//Ҫ��ǰ����
					p2 = v[index] + dp[index + 1][rest - w[index]];
				}
				dp[index][rest] = max(p1, p2);
			}
		}

		return dp[0][bag];
	}

	//��ǰ�����ƣ��������Ϸ������ݹ�
	int dpWay1(const vector<int>& w, const vector<int>& v, int bag) {
		int N = w.size();
		vector<vector<int>> dp(N + 1, vector<int>(bag + 1));
		//dp[0][...]���Զ���ʼ��0

		for (int index = 0; index < N; ++index) {
			for (int rest = 1; rest <= bag; ++rest) {
				int p1 = dp[index][rest];	//��Ҫ��ǰ
				int p2 = -1;
				if (rest - w[index] >= 0) {		//Ҫ
					p2 = v[index] + dp[index][rest - w[index]];
				}
				dp[index+1][rest] = max(p1, p2);
			}
			
		}
		return dp[N][bag];

	}
};

void testKnapsack() {
	Knapsack k;
	vector<int> w = { 3,2,4,7 };
	vector<int> v = { 5,6,3,19 };
	int bag = 11;
	cout << k.way1(w, v, bag) << endl;
	cout << k.dpWay(w, v, bag) << endl;
	cout << k.dpWay1(w, v, bag) << endl;

}


//��������
//����1��ӦA,2��ӦB,3��ӦC,��������
//�硰111������תΪ��AAA������KA��,��AK��
//����һ��ֻ�������ַ���ɵ��ַ���str,�����ж�����ת�����
class ConvertToLetterString {
public:
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
			if (i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '6') {	//��Ϊֻ��26����ĸ
				ret += process(str, i + 2);	//(i��i+1����Ϊ�����Ĳ��֣����غ����ж����ַ���
			}
			return ret;
		}
		//str[i]='3'~'9'ʱ��ֻ�ܵ�����Ϊһ���ֽ���ת��
		return process(str, i + 1);
	}

	int dpWay(string str) {
		if (str.size() == 0) {
			return 0;
		}
		int n = str.size();
		vector<int> dp(n + 1);
		dp[n] = 1;
		for (int i = n - 1; i >= 0; --i) {

			if (str[i] == '0') {	//��ʱ���������ַ���0ʱ��0����Ч�ģ��޷�ת��
				dp[i] = 0;
			} else if ('1' == str[i]) {
				dp[i] = dp[i + 1];	//��ǰ�ַ�i����ת�������غ����ж����ַ���
				if (i + 1 < str.size()) {
					dp[i] += dp[i + 2];	//(i��i+1����Ϊ�����Ĳ��֣����غ����ж����ַ���
				}
			}else if ('2' == str[i]) {
				dp[i] = dp[i + 1];	//��ǰ�ַ�i����ת�������غ����ж����ַ���
				if (i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '6') {	//��Ϊֻ��26����ĸ
					dp[i] += dp[i + 2];	//(i��i+1����Ϊ�����Ĳ��֣����غ����ж����ַ���
				}
			} else {
				//str[i]='3'~'9'ʱ��ֻ�ܵ�����Ϊһ���ֽ���ת��
				dp[i] = dp[i + 1];
			}
		}
		return dp[0];
	}
};


void testConvertToLetterString() {
	ConvertToLetterString c;
	cout << c.number("9192911919") << endl;
	cout << c.dpWay("9192911919") << endl;
}


//�����ģ�
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
		if (i == j) {
			return 0;
		}
		//��Ϊ����û��ѡ��ֻ�ܷ�����һ���Լ���Ϊ���ֵķ��������Լ��Ǻ��֣����ֿ϶�����������С�ĸ��Լ���������min
		return min(f(arr, i + 1, j), f(arr, i, j - 1));
	}

	int dpWay(const vector<int>& arr) {
		if (arr.size() == 0) {
			return 0;
		}
	
		int N = arr.size();
		vector<vector<int>> f(N, vector<int>(N));
		vector<vector<int>> s(N, vector<int>(N));
		
		for (int i = 0; i < N; ++i) {
			f[i][i] = arr[i];
		} 
		//s[i][i]=0;
		for (int i = 1; i < N; ++i) {
			int L = 0;
			int R = i;
			while(L < N&& R < N) {
				f[L][R] = max(arr[L] + s[L + 1][R], arr[R] + s[L][R - 1]);
				s[L][R] = min(f[L + 1][R], f[L][R - 1]);
				++L; ++R;
			}
		}
		return max(f[0][N - 1], s[0][N - 1]);
		 
	}
	 
};
void testCardsInLine() {
	vector<int> arr = { 100};
	CardsInLine c;
	cout << c.win1(arr) << endl;
	cout << c.dpWay(arr) << endl;

}



//�����壺arr�������в�ͬ�����ظ���ֵ��Ӳ�ң�����aim��ֵĿ�꣬���ж�������Ϸ���
class CoinsWay {
public:
	//�����ݹ�
	int way1(vector<int> arr, int aim) {
		if (arr.size() == 0 || aim < 0) {
			return 0;
		}
		return process1(arr, 0, aim);
	}
	int process1(vector<int>& arr, int index, int rest) {
		if (index == arr.size()) {
			return rest == 0 ? 1 : 0;
		}
		int ways = 0;
		for (int z=0; z * arr[index] <= rest; ++z) {
			ways += process1(arr, index + 1, rest - (z * arr[index]));
		}
		return ways;
	}

	//���仯����
	int way2(vector<int> arr, int aim) {
		if (arr.size() == 0 || aim < 0) {
			return 0;
		}
		vector<vector<int>> dp(arr.size() + 1, vector<int>(aim + 1, -1));
		//����һ�Ź�ϣ�������ݷ�Χʮ�ַ�ɢ��ϸ��Ȼ��ֿ��ܻᵼ��dp[][]�кܶ�λ��û���õ�
		return process2(arr, 0, aim,dp);
	}
	int process2(vector<int>& arr, int index, int rest, vector<vector<int>>& dp) {
		if (dp[index][rest] != -1) {
			return dp[index][rest];
		}
		if (index == arr.size()) {
			dp[index][rest] = rest == 0 ? 1 : 0;
			return dp[index][rest];
		}
		int ways = 0;
		for (int z=0; z * arr[index] <= rest; ++z) {
			ways += process1(arr, index + 1, rest - (z * arr[index]));
		}
		dp[index][rest] = ways;
		return ways;

	}

	//���䶯̬�滮
	int way3(vector<int> arr, int aim) {
		if (arr.size() == 0 || aim < 0) {
			return 0;
		}
		int N = arr.size();
		vector<vector<int>> dp(N + 1, vector<int>(aim + 1));
		dp[N][0] = 1;

		for (int index = N - 1; index >= 0; --index) {
			for (int rest = 0; rest <= aim; ++rest) {
				int ways = 0;
				for (int z = 0; z * arr[index] <= rest; ++z) {
					ways += dp[index + 1][rest - (z * arr[index])];
				}
				dp[index][rest] = ways;
			}
		} 
		return dp[0][aim];
	}

	//���䶯̬�滮�Ż�
	int way4(vector<int> arr, int aim) {
		if (arr.size() == 0 || aim < 0) {
			return 0;
		}
		int N = arr.size();
		vector<vector<int>> dp(N + 1, vector<int>(aim + 1));
		dp[N][0] = 1;

		for (int index = N - 1; index >= 0; --index) {
			dp[index][0] = dp[index + 1][0];
			for (int rest = 1; rest <= aim; ++rest) {
				dp[index][rest] = dp[index + 1][rest];
				if (rest - arr[index] >= 0) {
					dp[index][rest] += dp[index][rest - arr[index]];
				}
			}
		}
		return dp[0][aim];
	}
};

void testCoinsWay() {
	CoinsWay c;
	vector<int> arr{ 5,10,50,100 };
	int aim = 1000;
	cout << c.way1(arr, aim) << endl;
	cout << c.way2(arr, aim) << endl;
	cout << c.way3(arr, aim) << endl;
	cout << c.way4(arr, aim) << endl;


}





//��������
//����һ���ַ���str������һ���ַ������͵�����arr��
//arr���ÿһ���ַ���������һ����ֽ������԰ѵ����ַ�����ʹ�ã�Ŀ����ƴ��str����������Ҫ���ٶ�������ֽ��������������
//���� : str = "babac", arr = { "ba","c","abcd" }
//������Ҫ������ֽ"ba"��"abcd"����Ϊʹ����������ֽ����ÿһ���ַ���������������2��a��2��b��1��c���ǿ���ƴ��str�ġ����Է���2��

class StickersToSpellWord {
public:
	int minStickers1(vector<string> stickers, string target) {
		int n = stickers.size();
		vector<vector<int>> mapS(n, vector<int>(26));
		//��ÿ����ֽ��ÿ���Է�����mapS�У�����ÿһ�ж���һ����ֽ
		for (int i = 0; i < n; ++i) {
			for (auto c : stickers[i]) {
				++mapS[i][c - 'a'];
			}
		}

		map<string, int> dp;
		dp[""] = 0;
		//���򣬿ɱ��ⲻ��Ҫ�ĵݹ�
		sort(target.begin(), target.end());
		return process1(dp, mapS, target);
	}
	//ɵ���棬����ѽ������ֱ�ӷ���
	//����ֵ��-1��restʣ���ַ�������������ֽ���㲻��
	int process1(map<string, int>& dp, vector<vector<int>>& mapS, string rest) {
		if (dp.find(rest) != dp.end()) {
			return dp[rest];
		}

		int ans = INT_MAX;
		int n = mapS.size();
		vector<int> tmap(26);	//restʣ����ֽ�Ĵ�Ƶ
		for (auto c : rest) {
			++tmap[c - 'a']; 
		}

		for (int i = 0; i < n; ++i) {
			//ö�ٵ�ǰ��һ����ֽ��˭

			//����������ݹ飬�涨rest��ǰ����һ��һ���㶨
			if (mapS[i][rest[0] - 'a'] == 0) {
				continue;
			}

			//����ֽ�����Ӵ�Ƶ�ָ�Ϊ�ַ���
			string str;
			for (int j = 0; j < 26; ++j) {
				if (tmap[j] > 0) {
					for (int k = 0; k < max(0, tmap[j] - mapS[i][j]); ++k) {
						str += ('a' + j);
					}
				}
			}

			int tmp = process1(dp, mapS, str);
			if (tmp != -1) {
				ans = min(ans, 1 + tmp);
			} 
		}
		//-1��ʾ��restʣ���ַ�������������ֽ���㲻��
		dp[rest] = ans == INT_MAX ? -1 : ans;
		return dp[rest];
	}

};

void testStickersToSpellWord() {
	StickersToSpellWord s;
	vector<string> strArr = { "caggggac","acpxat","vc","ceagrhvarg" };
	string str = "cagagxpptavecceacagagxppcpxatavecacagcagagxpptaveeccepptaveccegrhvaacagagxpptavecceaagxpptaveccea";
	//int begin = clock();
	//cout << s.minStickers1(strArr, str) << endl;
	//int end = clock();
	//cout << "time:" << end - begin << endl;
	 
}


//�����������
class longestCommonSubsequence {
public:
	int lcse(string str1, string str2) {
		int len1 = str1.size(), len2 = str2.size();
		vector<vector<int>> dp(len1, vector<int>(len2));
		//dp[i][j] ��ʾstr1[0...i],str2[0...j]����������еĳ���
		//ÿ��dp[i][j]�µ�����������й������������
		// 1) ����������в���str1[i]��str2[j]��β
		// 2������������в���str1[i]��β����str2[j]��β
		// 3������������в���str2[j]��β����str1[i]��β
		// 4) �������������str1[i]��str2[j]��β
		dp[0][0] = str1[0] == str2[0] ? 1 : 0;
		//���0��
		for (int i = 1; i < len1; ++i) {
			dp[i][0] = max(dp[i - 1][0], str1[i] == str2[0] ? 1 : 0);
		}
		//���0��
		for (int i = 1; i < len2; ++i) {
			dp[0][i] = max(dp[0][i - 1], str2[i] == str1[0] ? 1 : 0);
		}

		for (int i = 1; i < len1; ++i) {
			for (int j = 1; j < len2; ++j) {
				//���2��3
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				//���4�����������Һ����1��⣬��������Ϊ���4
				if (str1[i] == str2[j]) {
					dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
				}
				//�������������1,�����������֮ǰdp[i][j-1]�����Լ�dp[i-1][j]�����ѱ����ǣ�����ʡ��
				/*else {
					dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
				}*/

			}
		}
		return dp[len1 - 1][len2 - 1];
	}
};


//��Ŀ
//����һ���������飬����ÿ���˺��꿧��׼��ˢ���ӵ�ʱ��
//ֻ��һ̨���Ȼ���һ��ֻ��ϴһ�����ӣ�ʱ��ķ�a��ϴ�����ϴ��һ��ÿ�����ȱ�Ҳ�����Լ��ӷ��ɾ���ʱ��ķ�b��
//���ȱ����Բ��лӷ����������п��ȱ���ɾ����������ʱ��
//�������� : int[] arr��int a��int b

class WashCoffeeCup {
public:

	//a ϴһ����ʱ�� �̶�����
	//b �Լ��ӷ���ɵ�ʱ��	�̶�����
	//drinks ÿһ��Ա�������ʱ��  �̶�����
	//drinks[0..index-1]���Ѿ��ɾ��ˣ������������
	//drinks[index..]�����ɾ��������Ҳ��ĵģ�washLine��ʾϴ�Ļ�����ʱ����
	//drinks[index..]��ɾ������ٵ�ʱ�䷵��
	int process(vector<int>& drinks, int a, int b, int index, int washLine) {

		if (index == drinks.size() - 1) {
			return min(max(washLine, drinks[index] + a), drinks[index] + b);
		}
		//ʣ�²�ֹһ�����ȱ�
		//wash���ҵ�ǰ�ı���ϴ���ʱ��
		int wash = max(washLine, drinks[index])+a;	//ϴ��indexһ����������ʱ���
		//index+1...��ɾ���ʱ��
		int next1 = process(drinks, a, b, index + 1, wash);
		//index...	
		int p1 = max(wash, next1);	//����ı��ӿ��ܱ�ǰ��ɾ��ĸ��죬ȡ�ɾ�������

		int dry = drinks[index] + b;//�ӷ���indexһ����������ʱ���
		int next2 = process(drinks, a, b, index + 1, washLine);
		int p2 = max(dry, next2);

		return min(p1, p2);
	}

	//�Ϸ��Ľ��ɶ�̬�滮��
	int dp(vector<int>& drinks, int a, int b) {
		if (a >= b) {
			return drinks[drinks.size() - 1] + b;
		}

		int limit = 0;//���Ȼ�ʲôʱ�����
		int N = drinks.size();
		for (int i = 0; i < N; ++i) {
			limit = max(limit, drinks[i])+a;
		}
		vector<vector<int>> dp(N, vector<int>(limit + 1));
		//N-1�У����е�ֵ
		for (int washLine = 0; washLine <= limit; ++washLine) {
			dp[N - 1][washLine] = min(max(washLine, drinks[N - 1]) + a, drinks[N - 1] + b);
		}

		for (int index = N - 2; index >= 0; --index) {
			for (int washLine = 0; washLine <= limit; ++washLine) {
				int p1 = INT_MAX;
				int wash = max(washLine, drinks[index]) + a;
				if (wash <= limit) {	//wash���ܻ�Խ�磬��Ҫ�ж�
					p1 = max(wash, dp[index + 1][wash]);
				}
				int p2 = max(drinks[index] + b, dp[index + 1][washLine]);
				dp[index][washLine] = min(p1, p2);
			}
		}
		return dp[0][0];
	}
};

void testWashCoffeeCup() {
	WashCoffeeCup w;
	vector<int> arr = { 1,1,5,5,7,10,12,12,12,12,12,12,15 };
	int a = 3;
	int b = 10;
	cout << w.process(arr, a, b, 0, 0) << endl;
	cout << w.dp(arr, a, b) << endl;

}

int main()
{
	testRRobotWalk();
	testKnapsack();
	testConvertToLetterString();
	testCardsInLine();
	testCoinsWay();
	testStickersToSpellWord();
	testWashCoffeeCup();
	return 0;
}