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
	// 含义：来到了第index位置，之前的index物品已做好决定，背包剩余rest，所能产生的最大价值
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
	// 二维数组状态转移方程，f[i,j]=max(f[i-1,j],f[i-1,j-wi]+vi)
	// 由于对fi有影响的只有f[i-1],所以可以去掉一维,直接用f[i]来表示处理到当前物品时背包容量为i的最大价值
	// 滚动数组：f[j]=max(f[j],f[j-wi]+vi)

	int dpWay2(const vector<int>& w, const vector<int>& v, int bag) {
		int N = w.size();
		vector<int> dp(bag + 1);
		for (int i = 0; i < N; ++i) {
			for (int rest = bag; rest >= w[i]; --rest) {
				dp[rest] = max(dp[rest], dp[rest - w[i]] + v[i]);
			}
		}

	
		return dp[bag];
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
	cout << k.dpWay2(w, v, bag) << endl;
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

//跳马问题
// 10*9棋盘，马从起点（0，0）出发，恰好走k步到达（x,y)的不同走法有几种
class VaultingHorse {
public:

	int way1(int x, int y, int k) {
		return f(x, y, k);
	}

	// 马从（0，0）出发，有K步要走，并且一定要走完，最终来到（x,y)位置的方法数是多少
	int f(int x, int y, int k) {
		if (k == 0) {
			//要到达的点是(0,0)且k==0,你不会动，方法数为1，如要到达的点不是（0，0）你又不能动，则无法到达最终位置，返回0 
			return x == 0 && y == 0 ? 1 : 0;
		}
		//越界情况
		if (x < 0 || x>9 || y < 0 || y>8) {
			return 0;
		}
		//即步数要走，x和y也是棋盘上的位置
		return f(x + 2, y - 1, k - 1) + f(x + 2, y + 1, k - 1) + f(x + 1, y + 2, k - 1) + f(x - 1, y + 2, k - 1) +
			f(x - 2, y + 1, k - 1) + f(x - 2, y - 1, k - 1) + f(x - 1, y - 2, k - 1) + f(x + 1, y - 2, k - 1);

	}


	int way2(int x, int y, int k) {
		vector<vector<vector<int>>> dp(10, vector<vector<int>>(9, vector<int>(k + 1))); //[x] [y] [k]
		//第0层	
		dp[0][0][0] = 1;	// dp[...][...][0]==0;

		for (int level = 1; level <= k; ++level) {	//枚举层数
			// level层,x,y
			for (int i = 0; i < 10; ++i) {	//x的可能性
				for (int j = 0; j < 9; ++j) {		//y的可能性 
					dp[i][j][level] = getValue(dp, i + 2, j - 1, level - 1) +
						getValue(dp, i + 2, j + 1, level - 1) +
						getValue(dp, i + 1, j + 2, level - 1) +
						getValue(dp, i - 1, j + 2, level - 1) +
						getValue(dp, i - 2, j + 1, level - 1) +
						getValue(dp, i - 2, j - 1, level - 1) +
						getValue(dp, i - 1, j - 2, level - 1) +
						getValue(dp, i + 1, j - 2, level - 1);
				}
			}
		}

		return dp[x][y][k];

	}

	int getValue(vector<vector<vector<int>>>& dp, int x, int y, int k) {
		if (x < 0 || x>9 || y < 0 || y>8) {
			return 0;
		}
		return dp[x][y][k];
	}

	void test() {
		int x = 6, y = 8, k = 10;
		cout << way1(x, y, k) << " " << way2(x, y, k) << endl;
	}
};

//状态压缩的状态方程-----------------------------------------------------------------------------

//464. 我能赢吗


class Solution {
public:
	//法一：暴力尝试(超时）===============================================
	//时间O(n!)	,空间O(n)
	//1-choose 拥有的数字
	bool canIWin0(int choose, int total) {
		if (total == 0)
			return true;
		if ((choose * (choose + 1) >> 1) < total)
			return false;
		vector<int> arr(choose);
		for (int i = 0; i < choose; ++i) {
			arr[i] = i + 1;
		}
		// arr[i] != -1 表示arr[i]这个数字还没被拿走
		// arr[i] == -1 表示arr[i]这个数字已经被拿走
		return process(arr, total);
	}
	// 当前轮到先手拿，
	// 先手只能选择在arr中还存在的数字，
	// 还剩rest这么值，
	// 返回先手会不会赢
	bool process(vector<int>& arr, int rest) {
		if (rest <= 0)
			return false;
		//先手去尝试所有的情况
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] != -1) {
				int cur = arr[i];
				arr[i] = -1;
				bool next = process(arr, rest - cur);
				arr[i] = cur;	//回溯得放在这里，不能放在next的判断之后，不然一旦return之后就无法回溯了

				if (!next)
					return true;
			}
		}
		return false;
	}


	// 法二：暴力超时==========================================================
//时间O(n!)	,空间O(1)
// 因choose<=20,可利用位信息可省去数组开销，相当于把一个线性结果转为了int，但实际还是线性结构
	bool canIWin1(int choose, int total) {
		if (total == 0) {
			return true;
		}
		if ((choose * (choose + 1) >> 1) < total) {
			return false;
		}
		return process1(choose, 0, total);
	}

	// 当前轮到先手拿，
	// 先手可以拿1~choose中的任何一个数字
	// status   i位如果为0，代表没拿，当前可以拿
	//          i位为1，代表已经拿过了，当前不能拿
	// 还剩rest这么值，
	// 返回先手会不会赢
	bool process1(int choose, int status, int rest) {
		if (rest <= 0) {
			return false;
		}
		for (int i = 1; i <= choose; i++) {
			if (((1 << i) & status) == 0) { // i 这个数字，是此时先手的决定！
				if (!process1(choose, (status | (1 << i)), rest - i)) {
					return true;
				}
			}
		}
		return false;
	}


	//法三：缓存(状态压缩）====================================================
	// 时间O(N*N^2)，空间（2^N)
	// 可能对于同一组数据，不同的拿数顺序，所导致的后续操作都是相同的，为此可以使用缓存进行规避
	bool canIWin2(int choose, int total) {
		if (total == 0) {
			return true;
		}
		if ((choose * (choose + 1) >> 1) < total) {
			return false;
		}
		vector<int> dp(1 << (choose + 1));
		// dp[status] == 1  true
		// dp[status] == -1  false
		// dp[status] == 0  process(status) 没算过！去算！
		return process2(choose, 0, total, dp);
	}

	// 为什么明明status和rest是两个可变参数，却只用status来代表状态(也就是dp)
	// 因为选了一批数字之后，得到的和一定是一样的，所以rest是由status决定的，所以rest不需要参与记忆化搜索
	bool process2(int choose, int status, int rest, vector<int>& dp) {
		if (dp[status] != 0) {	//缓存有
			return dp[status] == 1 ? true : false;
		}
		//无缓存，正常算
		bool ans = false;
		if (rest > 0) {
			for (int i = 1; i <= choose; i++) {
				if (((1 << i) & status) == 0) {
					if (!process2(choose, (status | (1 << i)), rest - i, dp)) {
						ans = true;
						break;
					}
				}
			}
		}
		//存入缓存
		dp[status] = ans ? 1 : -1;
		return ans;
	}
};



//TSP----------------------------------------------------------------------------------
class TSP {
public:
	//法一：暴力=============================================================

	int t1(vector<vector<int>>& matrix) {
		int N = matrix.size(); // 0...N-1
		// set
		// set.get(i) == true i这座城市在集合里
		// set.get(i) == false i这座城市不在集合里
		vector<bool> se(N, true);
		return func1(matrix, se, 0);
	}

	// 任何两座城市之间的距离，可以在matrix里面拿到
	// set中表示着哪些城市的集合，
	// start这座城一定在se里，
	// 从start出发，要把set中所有的城市过一遍，最终回到0这座城市，最小距离是多少
	int func1(vector<vector<int>>& matrix, vector<bool>& se, int start) {
		int cityNum = 0;
		for (int i = 0; i < se.size(); i++) {
			if (se[i]) {
				cityNum++;
			}
		}
		if (cityNum == 1) {
			return matrix[start][0];
		}
		// cityNum > 1  不只start这一座城
		se[start] = false;
		int min_path = INT_MAX;
		for (int i = 0; i < se.size(); i++) {
			if (se[i]) {
				// start -> i i... -> 0
				int cur = matrix[start][i] + func1(matrix, se, i);
				min_path = min(min_path, cur);
			}
		}
		se[start] = true;	//回溯
		return min_path;
	}

	//法二：暴力+位运算======================================================
	int t2(vector<vector<int>>& matrix) {
		int N = matrix.size(); // 0...N-1
		// 7座城 1111111
		int allCity = (1 << N) - 1;
		return f2(matrix, allCity, 0);
	}

	// 任何两座城市之间的距离，可以在matrix里面拿到
	// cityStatus的位信息中表示着哪些城市的集合，
	// start这座城一定在cityStatus第start位为1，
	// 从start出发，要把set中所有的城市过一遍，最终回到0这座城市，最小距离是多少
	int f2(vector<vector<int>>& matrix, int cityStatus, int start) {
		// cityStatus == cityStatux & (~cityStaus + 1)
		//~cityStatus + 1 把cityStatus最右侧的1拿出来
		if (cityStatus == (cityStatus & (~cityStatus + 1))) {
			return matrix[start][0];
		}

		// 把start位的1去掉，
		cityStatus &= (~(1 << start));
		int min_path = INT_MAX;
		// 枚举所有的城市
		for (int move = 0; move < matrix.size(); move++) {
			if ((cityStatus & (1 << move)) != 0) {
				int cur = matrix[start][move] + f2(matrix, cityStatus, move);
				min_path = min(min_path, cur);
			}
		}
		cityStatus |= (1 << start);	//回溯
		return min_path;
	}

	//法三：缓存=======================================================
	int t3(vector<vector<int>>& matrix) {
		int N = matrix.size(); // 0...N-1
		// 7座城 1111111
		int allCity = (1 << N) - 1;
		vector<vector<int>> dp(1 << N, vector<int>(N, -1));
		return f3(matrix, allCity, 0, dp);
	}

	int f3(vector<vector<int>>& matrix, int cityStatus, int start, vector<vector<int>> dp) {
		if (dp[cityStatus][start] != -1) {
			return dp[cityStatus][start];
		}
		if (cityStatus == (cityStatus & (~cityStatus + 1))) {
			dp[cityStatus][start] = matrix[start][0];
		} else {
			// 把start位的1去掉，
			cityStatus &= (~(1 << start));
			int min_path = INT_MAX;
			// 枚举所有的城市
			for (int move = 0; move < matrix.size(); move++) {
				if ((cityStatus & (1 << move)) != 0) {
					int cur = matrix[start][move] + f3(matrix, cityStatus, move, dp);
					min_path = min(min_path, cur);
				}
			}
			cityStatus |= (1 << start);		//回溯
			dp[cityStatus][start] = min_path;	//存入缓存
		}
		return dp[cityStatus][start];
	}
	//法四：dp================================================
	int t4(vector<vector<int>>& matrix) {
		int N = matrix.size(); // 0...N-1
		int statusNums = 1 << N;
		vector<vector<int>> dp(statusNums, vector<int>(N));

		for (int status = 0; status < statusNums; status++) {
			for (int start = 0; start < N; start++) {
				if ((status & (1 << start)) != 0) {
					if (status == (status & (~status + 1))) {
						dp[status][start] = matrix[start][0];
					} else {
						int min_path = INT_MAX;
						// start 城市在status里去掉之后，的状态
						int preStatus = status & (~(1 << start));
						// start -> i
						for (int i = 0; i < N; i++) {
							if ((preStatus & (1 << i)) != 0) {
								int cur = matrix[start][i] + dp[preStatus][i];
								min_path = min(min_path, cur);
							}
						}
						dp[status][start] = min_path;
					}
				}
			}
		}
		return dp[statusNums - 1][0];
	}

};

//问题三---------------------------------------------------------------------------
//你有无限的1*2的砖块,要铺满M*N的区域,工不同的铺法有多少种?
class PavingTile {
public:
	/*
	 * 2*M铺地的问题非常简单，这个是解决N*M铺地的问题
	 */
	 //法一：暴力===================================================
	int ways1(int N, int M) {
		if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
			return 0;
		}
		if (N == 1 || M == 1) {
			return 1;
		}
		vector<int> pre(M, 1); // pre代表-1行的状况
		return process(pre, 0, N);
	}

	// pre 表示level-1行的状态
	// level表示，正在level行做决定
	// N 表示一共有多少行 固定的
	// level-2行及其之上所有行，都摆满砖了
	// level做决定，让所有区域都满，方法数返回
	int process(vector<int>& pre, int level, int N) {
		if (level == N) { // base case,且上一行必须被填满
			for (int i = 0; i < pre.size(); i++) {
				if (pre[i] == 0) {
					return 0;
				}
			}
			return 1;
		}

		// 没到终止行，可以选择在当前的level行摆瓷砖
		vector<int> op = getOp(pre);
		return dfs(op, 0, level, N);
	}

	// op[i] == 0 可以考虑摆砖
	// op[i] == 1 只能竖着向上
	int dfs(vector<int>& op, int col, int level, int N) {
		// 在列上自由发挥，玩深度优先遍历，当col来到终止列，i行的决定做完了
		// 轮到i+1行，做决定
		if (col == op.size()) {
			return process(op, level + 1, N);
		}
		int ans = 0;
		// col位置不横摆
		ans += dfs(op, col + 1, level, N); // col位置上不摆横转
		// col位置横摆, 向右
		if (col + 1 < op.size() && op[col] == 0 && op[col + 1] == 0) {
			op[col] = 1;
			op[col + 1] = 1;
			//向右摆，col+1,自然被占用，直接从col+2开始
			ans += dfs(op, col + 2, level, N);
			//回溯
			op[col] = 0;
			op[col + 1] = 0;
		}
		return ans;
	}

	vector<int> getOp(vector<int>& pre) {
		vector<int> cur(pre.size());
		for (int i = 0; i < pre.size(); i++) {
			cur[i] = pre[i] ^ 1;
		}
		return cur;
	}

	//法二：暴力+位信息=========================================================
	// Min (N,M) 不超过 32
	int ways2(int N, int M) {
		if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
			return 0;
		}
		if (N == 1 || M == 1) {
			return 1;
		}
		// 由于利用到位信息，所以N,M的最小值最为位信息，某些情况相当于N*M转为M*N
		int maxN = max(N, M);
		int minN = min(N, M);
		int pre = (1 << minN) - 1;
		return process2(pre, 0, maxN, minN);
	}

	// 上一行的状态，是pre，limit是用来对齐的，固定参数不用管
	// 当前来到i行，一共N行，返回填满的方法数
	int process2(int pre, int i, int N, int M) {
		if (i == N) { // base case
			//pre的M列是否被填满
			return pre == ((1 << M) - 1) ? 1 : 0;
		}
		//根据上一行得出当前行可操作得位信息，0表可任意操作，1表不可操作
		int op = ((~pre) & ((1 << M) - 1));
		return dfs2(op, M - 1, i, N, M);
	}

	int dfs2(int op, int col, int level, int N, int M) {
		if (col == -1) {	//此处得终止条件为-1对于的是二进制位的摆放顺序，低位在右边
			return process2(op, level + 1, N, M);
		}
		int ans = 0;
		ans += dfs2(op, col - 1, level, N, M);
		//col列为0 && 还有下一列 &&  下一列也为0
		if ((op & (1 << col)) == 0 && col - 1 >= 0 && (op & (1 << (col - 1))) == 0) {
			//op | (3 << (col - 1))表示第将3的二进制00000011，左移col-1,即可将op的第col和col-1位置为1
			ans += dfs2((op | (3 << (col - 1))), col - 2, level, N, M);
		}
		return ans;
	}


	//法三：缓存=====================================================================
	// 记忆化搜索的解
	// Min(N,M) 不超过 32
	int ways3(int N, int M) {
		if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
			return 0;
		}
		if (N == 1 || M == 1) {
			return 1;
		}
		int maxN = max(N, M);
		int minN = min(N, M);
		int pre = (1 << minN) - 1;
		vector<vector<int>> dp(1 << minN, vector<int>(maxN + 1, -1));
		return process3(pre, 0, maxN, minN, dp);
	}

	int process3(int pre, int i, int N, int M, vector<vector<int>>& dp) {
		if (dp[pre][i] != -1) {
			return dp[pre][i];
		}
		int ans = 0;
		if (i == N) {
			ans = pre == ((1 << M) - 1) ? 1 : 0;
		} else {
			int op = ((~pre) & ((1 << M) - 1));
			ans = dfs3(op, M - 1, i, N, M, dp);
		}
		dp[pre][i] = ans;
		return ans;
	}

	int dfs3(int op, int col, int level, int N, int M, vector<vector<int>>& dp) {
		if (col == -1) {
			return process3(op, level + 1, N, M, dp);
		}
		int ans = 0;
		ans += dfs3(op, col - 1, level, N, M, dp);
		if (col > 0 && (op & (3 << (col - 1))) == 0) {
			ans += dfs3((op | (3 << (col - 1))), col - 2, level, N, M, dp);
		}
		return ans;
	}
	// 法四：严格位置依赖的动态规划解（感兴趣了解）
	int ways4(int N, int M) {
		if (N < 1 || M < 1 || ((N * M) & 1) != 0) {
			return 0;
		}
		if (N == 1 || M == 1) {
			return 1;
		}
		int big = N > M ? N : M;
		int small = big == N ? M : N;
		int sn = 1 << small;
		int limit = sn - 1;
		vector<int> dp(sn);
		dp[limit] = 1;
		vector<int> cur(sn);
		for (int level = 0; level < big; level++) {
			for (int status = 0; status < sn; status++) {
				if (dp[status] != 0) {
					int op = (~status) & limit;
					dfs4(dp[status], op, 0, small - 1, cur);
				}
			}
			for (int i = 0; i < sn; i++) {
				dp[i] = 0;
			}
			vector<int> tmp = dp;
			dp = cur;
			cur = tmp;
		}
		return dp[limit];
	}

	void dfs4(int way, int op, int index, int end, vector<int>& cur) {
		if (index == end) {
			cur[op] += way;
		} else {
			dfs4(way, op, index + 1, end, cur);
			if (((3 << index) & op) == 0) { // 11 << index 可以放砖
				dfs4(way, op | (3 << index), index + 1, end, cur);
			}
		}
	}

	void test() {
		int N = 8;
		int M = 6;
		cout << (ways1(N, M)) << endl;
		cout << (ways2(N, M)) << endl;
		cout << (ways3(N, M)) << endl;
		cout << (ways4(N, M)) << endl;

		N = 10;
		M = 10;
		cout << "=========" << endl;;
		cout << (ways3(N, M)) << endl;
		cout << (ways4(N, M)) << endl;
	}


};

void testAC() {
	ACAutomation ac;
	ac.insert("dhe");
	ac.insert("he");
	ac.insert("abcdzheks");
	// 设置fail指针
	ac.build();

	auto contains = ac.containWords("abcdhekskdjfafhasldkflskdjhwqaeruv");
	for (string word : contains) {
		cout << word << endl;
	}
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
