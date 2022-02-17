#define _CRT_SECURE_NO_WARNINGS 1

//动态规划学习

#include<iostream>
using namespace std;
#include<algorithm>
#include<vector>
#include<map>
//题目一
//假设有排成一行的N个位置，记为1~N，N一定大于或等于2开始时机器人在其中的M位置上(M一定是1~N中的一个)
// 如果机器人来到1位置，那么下一步只能往右来到2位置;如果机器人来到N位置，那么下一步只能往左来到N-1位置;
// 如果机器人来到中间位置，那么下一步可以往左走或者往右走;
//规定机器人必须走K步，最终能来到P位置(P也是1~N中的一个)的方法有多少种给定四个参数N、M、K、P，返回方法数。

class RobotWalk {
public:
	//暴力递归
	int way1(int N, int M, int K, int P) {
		if (N < 2 || K < 1 || M<1 || M>N || P<1 || P>N) {
			return 0;
		}
		return walk1(N, M, K, P);
	}
	//cur当前位置，rest剩余位置
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


	//动态规划或叫做记忆化搜索，利用二维数组做缓存
	int way2(int N, int M, int K, int P) {
		if (N < 2 || K < 1 || M<1 || M>N || P<1 || P>N) {
			return 0;
		}
		vector<vector<int>> dp(N + 1, vector<int>(K + 1,-1));
		return walk2(N, M, K, P,dp);
	}
	//cur当前位置，rest剩余位置
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


	//但实际上不用开那么大的数组，整个过程中用到的就只有两组状态
	//walk函数的调用也只改变cur和rest，其他状态不变
	int way3(int N, int M, int K, int P) {
		if (N < 2 || K < 1 || M<1 || M>N || P<1 || P>N) {
			return 0;
		}
		return walk3(N, M, K, P);
	}
	//cur当前位置，rest剩余位置
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



//题目二：背包问题
class Knapsack {
public:
	//暴力递归
	int way1(const vector<int>& w, const vector<int>& v, const int bag) {
		return process2(w, v, 0, bag);
	}
	int process2(const vector<int>& w, const vector<int>& v, int index, int rest) {

		if (rest < 0) {	//后续货物无效
			return -1;
		}
		if (index == w.size()) {
			return 0;
		}
		//有货也有空间

		int p1 = process2(w, v, index + 1, rest);	//不要index货物时，后续产生的价值
		int p2next = process2(w, v, index + 1, rest - w[index]);

		int p2 = -1;
		if (p2next != -1) {	//后续货物有效
			p2 = v[index] + p2next;
		}
		return max(p1, p2);
	}

	//动态规划,依照暴力递归，从后往前推
	int dpWay(const vector<int>& w,const vector<int>& v, int bag) {
		int N = w.size();	
		vector<vector<int>> dp(N + 1, vector<int>(bag + 1));
		//dp[N][...]以自动初始化0

		for (int index = N - 1; index >= 0; --index) {	
			for (int rest = 1; rest <= bag; ++rest) {
				int p1 = dp[index + 1][rest];	//不要当前货物
				int p2 = -1;
				if (rest - w[index] >= 0) {	//要当前货物
					p2 = v[index] + dp[index + 1][rest - w[index]];
				}
				dp[index][rest] = max(p1, p2);
			}
		}

		return dp[0][bag];
	}

	//从前往后推，不基于上法暴力递归
	int dpWay1(const vector<int>& w, const vector<int>& v, int bag) {
		int N = w.size();
		vector<vector<int>> dp(N + 1, vector<int>(bag + 1));
		//dp[0][...]已自动初始化0

		for (int index = 0; index < N; ++index) {
			for (int rest = 1; rest <= bag; ++rest) {
				int p1 = dp[index][rest];	//不要当前
				int p2 = -1;
				if (rest - w[index] >= 0) {		//要
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


//问题三：
//假如1对应A,2对应B,3对应C,依次类推
//如“111”可以转为“AAA”，“KA”,“AK”
//给定一个只有数字字符组成的字符串str,返回有多少种转换结果
class ConvertToLetterString {
public:
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
			if (i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '6') {	//因为只有26个字母
				ret += process(str, i + 2);	//(i和i+1）作为单独的部分，返回后续有多少种方法
			}
			return ret;
		}
		//str[i]='3'~'9'时，只能单独作为一部分进行转换
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

			if (str[i] == '0') {	//此时遇到的是字符是0时，0是无效的，无法转换
				dp[i] = 0;
			} else if ('1' == str[i]) {
				dp[i] = dp[i + 1];	//当前字符i单独转换，返回后续有多少种方法
				if (i + 1 < str.size()) {
					dp[i] += dp[i + 2];	//(i和i+1）作为单独的部分，返回后续有多少种方法
				}
			}else if ('2' == str[i]) {
				dp[i] = dp[i + 1];	//当前字符i单独转换，返回后续有多少种方法
				if (i + 1 < str.size() && str[i + 1] >= '0' && str[i + 1] <= '6') {	//因为只有26个字母
					dp[i] += dp[i + 2];	//(i和i+1）作为单独的部分，返回后续有多少种方法
				}
			} else {
				//str[i]='3'~'9'时，只能单独作为一部分进行转换
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


//问题四：
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
		if (i == j) {
			return 0;
		}
		//作为后手没得选，只能返回下一步自己作为先手的分数，而自己是后手，先手肯定留下利益最小的给自己，所以用min
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



//问题五：arr数组中有不同的无重复面值的硬币，给你aim面值目标，共有多少种组合方法
class CoinsWay {
public:
	//暴力递归
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

	//记忆化搜索
	int way2(vector<int> arr, int aim) {
		if (arr.size() == 0 || aim < 0) {
			return 0;
		}
		vector<vector<int>> dp(arr.size() + 1, vector<int>(aim + 1, -1));
		//或建立一张哈希表，若数据范围十分分散，细腻度划分可能会导致dp[][]中很多位置没有用到
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

	//经典动态规划
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

	//经典动态规划优化
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





//问题六：
//给定一个字符串str，给定一个字符串类型的数组arr。
//arr里的每一个字符串，代表一张贴纸，你可以把单个字符剪开使用，目的是拼出str来。返回需要至少多少张贴纸可以完成这个任务。
//例子 : str = "babac", arr = { "ba","c","abcd" }
//至少需要两张贴纸"ba"和"abcd"，因为使用这两张贴纸，把每一个字符单独剪开，含有2个a、2个b、1个c。是可以拼出str的。所以返回2。

class StickersToSpellWord {
public:
	int minStickers1(vector<string> stickers, string target) {
		int n = stickers.size();
		vector<vector<int>> mapS(n, vector<int>(26));
		//把每张贴纸的每个自符存在mapS中，数组每一行对于一张贴纸
		for (int i = 0; i < n; ++i) {
			for (auto c : stickers[i]) {
				++mapS[i][c - 'a'];
			}
		}

		map<string, int> dp;
		dp[""] = 0;
		//排序，可避免不必要的递归
		sort(target.begin(), target.end());
		return process1(dp, mapS, target);
	}
	//傻缓存，如果已近算过，直接返回
	//返回值是-1，rest剩余字符无论用那张贴纸都搞不定
	int process1(map<string, int>& dp, vector<vector<int>>& mapS, string rest) {
		if (dp.find(rest) != dp.end()) {
			return dp[rest];
		}

		int ans = INT_MAX;
		int n = mapS.size();
		vector<int> tmap(26);	//rest剩余贴纸的词频
		for (auto c : rest) {
			++tmap[c - 'a']; 
		}

		for (int i = 0; i < n; ++i) {
			//枚举当前第一张贴纸是谁

			//避免出现死递归，规定rest从前往后一批一批搞定
			if (mapS[i][rest[0] - 'a'] == 0) {
				continue;
			}

			//将贴纸试完后从词频恢复为字符串
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
		//-1表示，rest剩余字符无论用那张贴纸都搞不定
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


//最长公共子序列
class longestCommonSubsequence {
public:
	int lcse(string str1, string str2) {
		int len1 = str1.size(), len2 = str2.size();
		vector<vector<int>> dp(len1, vector<int>(len2));
		//dp[i][j] 表示str1[0...i],str2[0...j]最长公共子序列的长度
		//每种dp[i][j]下的最长公共子序列共有四种情况，
		// 1) 最长公共子序列不以str1[i]和str2[j]结尾
		// 2）最长公共子序列不以str1[i]结尾，以str2[j]结尾
		// 3）最长公共子序列不以str2[j]结尾，以str1[i]结尾
		// 4) 最长公共子序列以str1[i]和str2[j]结尾
		dp[0][0] = str1[0] == str2[0] ? 1 : 0;
		//求第0列
		for (int i = 1; i < len1; ++i) {
			dp[i][0] = max(dp[i - 1][0], str1[i] == str2[0] ? 1 : 0);
		}
		//求第0行
		for (int i = 1; i < len2; ++i) {
			dp[0][i] = max(dp[0][i - 1], str2[i] == str1[0] ? 1 : 0);
		}

		for (int i = 1; i < len1; ++i) {
			for (int j = 1; j < len2; ++j) {
				//情况2和3
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				//情况4是有条件的且和情况1相斥，条件成立为情况4
				if (str1[i] == str2[j]) {
					dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
				}
				//条件不成立情况1,但这种情况在之前dp[i][j-1]往上以及dp[i-1][j]往左已被考虑，可以省略
				/*else {
					dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
				}*/

			}
		}
		return dp[len1 - 1][len2 - 1];
	}
};


//题目
//给定一个有序数组，代表每个人喝完咖啡准备刷杯子的时间
//只有一台咖啡机，一次只能洗一个杯子，时间耗费a，洗完才能洗下一杯每个咖啡杯也可以自己挥发干净，时间耗费b，
//咖啡杯可以并行挥发返回让所有咖啡杯变干净的最早完成时间
//三个参数 : int[] arr、int a、int b

class WashCoffeeCup {
public:

	//a 洗一杯的时间 固定变量
	//b 自己挥发风干的时间	固定变量
	//drinks 每一个员工喝完的时间  固定变量
	//drinks[0..index-1]都已经干净了，不用你操心了
	//drinks[index..]都想变干净，这是我操心的，washLine表示洗的机器何时能用
	//drinks[index..]变干净，最少的时间返回
	int process(vector<int>& drinks, int a, int b, int index, int washLine) {

		if (index == drinks.size() - 1) {
			return min(max(washLine, drinks[index] + a), drinks[index] + b);
		}
		//剩下不止一个咖啡杯
		//wash是我当前的杯子洗完的时间
		int wash = max(washLine, drinks[index])+a;	//洗，index一杯，结束的时间点
		//index+1...变干净的时间
		int next1 = process(drinks, a, b, index + 1, wash);
		//index...	
		int p1 = max(wash, next1);	//后面的杯子可能比前面干净的更快，取干净最慢的

		int dry = drinks[index] + b;//挥发，index一杯，结束的时间点
		int next2 = process(drinks, a, b, index + 1, washLine);
		int p2 = max(dry, next2);

		return min(p1, p2);
	}

	//上法改进成动态规划版
	int dp(vector<int>& drinks, int a, int b) {
		if (a >= b) {
			return drinks[drinks.size() - 1] + b;
		}

		int limit = 0;//咖啡机什么时候可用
		int N = drinks.size();
		for (int i = 0; i < N; ++i) {
			limit = max(limit, drinks[i])+a;
		}
		vector<vector<int>> dp(N, vector<int>(limit + 1));
		//N-1行，所有的值
		for (int washLine = 0; washLine <= limit; ++washLine) {
			dp[N - 1][washLine] = min(max(washLine, drinks[N - 1]) + a, drinks[N - 1] + b);
		}

		for (int index = N - 2; index >= 0; --index) {
			for (int washLine = 0; washLine <= limit; ++washLine) {
				int p1 = INT_MAX;
				int wash = max(washLine, drinks[index]) + a;
				if (wash <= limit) {	//wash可能会越界，需要判断
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