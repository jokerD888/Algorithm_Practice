// class02------------------------------------------------------------------------------------------

//给定数组hard和money，长度都为N
//hard[i]表示i号的难度， money[i]表示i号工作的收入
//给定数组ability，长度都为M，ability[j]表示j号人的能力
//每一号工作，都可以提供无数的岗位，难度和收入都一样
//但是人的能力必须 >= 这份工作的难度，才能上班
//返回一个长度为M的数组ans，ans[j]表示j号人能获得的最好收入
class Code01_ChooseWork {
public:
	class Job {
	public:
		int money;
		int hard;
		Job(int m, int h) :money(m), hard(h) {}
		bool operator<(const Job& b) const {
			return hard == b.hard ? money > b.money : hard < b.money;
		}
	};
	// 先按难度从小到大排，难度相同按报酬从大到小排， 排完后再挑选出相同难度中报酬最大且难度越大的报酬越多的，这样选出的数组即时递增序列，可用二分查找
	// 整体时间O(NlogN)
	vector<int> getMoneys(vector<Job>& job, vector<int>& ability) {
		sort(job.begin(), job.end());
		// key 难度		value 报酬
		vector<Job> m;
		m.push_back({ 0,0 });
		// pre 上一份进入map的工作
		Job pre = job[0];
		for (int i = 1; i < job.size(); ++i) {
			if (job[i].hard != pre.hard && job[i].money > pre.money) {
				pre = job[i];
				m.push_back({ pre.hard,pre.money });
			}
		}
		vector<int> ans(ability.size());
		for (int i = 0; i < ability.size(); ++i) {
			// ability[i] 当前人的能力  查<= ability[i]  且离它最近的
			// 若调用系统API,第三个参数不能直接传入ability,传入的比较值必须和容器元素类型一致
			auto kv = lower_bound(m.begin(), m.end(), Job{ 0,ability[i] }, [](const Job& a, const Job& b) {return a.hard < b.hard; });
			ans[i] = kv != m.end() ? kv->money : 0;
		}
		return ans;
	}
};
//贩卖机只支持硬币支付，且收退都只支持10 ，50，100三种面额 一次购买只能出一瓶可乐，且投钱和找零都遵循优先使用大钱的原则
//需要购买的可乐数量是m， 其中手头拥有的10、50、100的数量分别为a、b、c 可乐的价格是x(x是10的倍数) 请计算出需要投入硬币次数？
class Code02_Cola {
public:
	/*
	 * 买饮料 时间限制： 3000MS 内存限制： 589824KB 题目描述：
	 * 游游今年就要毕业了，和同学们在携程上定制了日本毕业旅行。愉快的一天行程结束后大家回到了酒店房间，这时候同学们都很口渴，
	 * 石头剪刀布选出游游去楼下的自动贩卖机给大家买可乐。 贩卖机只支持硬币支付，且收退都只支持10 ，50，100
	 * 三种面额。一次购买行为只能出一瓶可乐，且每次购买后总是找零最小枚数的硬币。（例如投入100圆，可乐30圆，则找零50圆一枚，10圆两枚）
	 * 游游需要购买的可乐数量是 m，其中手头拥有的 10,50,100 面额硬币的枚数分别是 a,b,c，可乐的价格是x(x是10的倍数)。
	 * 如果游游优先使用大面额购买且钱是够的情况下,请计算出需要投入硬币次数？ 输入描述 依次输入， 需要可乐的数量为 m 10元的张数为 a 50元的张数为 b
	 * 100元的张树为 c 1瓶可乐的价格为 x 输出描述 输出当前金额下需要投入硬币的次数
	 * 例如需要购买2瓶可乐，每瓶可乐250圆，手里有100圆3枚，50圆4枚，10圆1枚。 购买第1瓶投递100圆3枚，找50圆 购买第2瓶投递50圆5枚
	 * 所以是总共需要操作8次金额投递操作 样例输入 2 1 4 3 250 样例输出 8
	 */
	 // 时间复杂度为O(N^2),N为硬币的种类数，本题为3，可视为O（1）
	int putTimes(int m, int a, int b, int c, int x) {
		int qian[]{ 100,50,10 };
		int zhang[]{ c,b,a };
		// 总共需要多少次投币
		int puts = 0;
		// 之前面值的钱还剩下多少总钱数
		int preQianRest = 0;
		// 之前面值的钱还剩下多少总张数
		int preQianZhang = 0;
		for (int i = 0; i < 3; ++i) {
			// 要用之前剩下的钱、当前面值的钱，共同买第一瓶可乐
			// 之前的面值剩下多少钱，是preQianRest
			// 之前的面值剩下多少张，是preQianZhang
			// 之所以之前的面值会剩下来，一定是剩下的钱，一直攒不出一瓶可乐的单价
			// 当前的面值付出一些钱+之前剩下的钱，此时有可能凑出一瓶可乐来
			// 那么当前面值参与搞定第一瓶可乐，需要掏出多少张呢？就是curQianFirstBuyZhang
			int curQianFirstBuyZhang = (x - preQianRest + qian[i] - 1) / qian[i];	//+qian[i]-1是为了先上取整
			if (zhang[i] >= curQianFirstBuyZhang) { // 如果之前的钱和当前面值的钱，能凑出第一瓶可乐
				// 凑出来了一瓶可乐也可能存在找钱的情况，
				giveRest(qian, zhang, i + 1, (preQianRest + qian[i] * curQianFirstBuyZhang) - x, 1);
				puts += curQianFirstBuyZhang + preQianZhang;
				zhang[i] -= curQianFirstBuyZhang;
				m--;
			} else { // 如果之前的钱和当前面值的钱，不能凑出第一瓶可乐
				preQianRest += qian[i] * zhang[i];
				preQianZhang += zhang[i];
				continue;
			}
			// 凑出第一瓶可乐之后，当前的面值有可能能继续买更多的可乐
			// 以下过程就是后续的可乐怎么用当前面值的钱来买
			// 用当前面值的钱，买一瓶可乐需要几张
			int curQianBuyOneColaZhang = (x + qian[i] - 1) / qian[i];	//向上取整
			// 用当前面值的钱，一共可以搞定几瓶可乐
			int curQianBuyColas = min(zhang[i] / curQianBuyOneColaZhang, m);
			// 用当前面值的钱，每搞定一瓶可乐，收货机会吐出多少零钱
			int oneTimeRest = qian[i] * curQianBuyOneColaZhang - x;
			// 每次买一瓶可乐，吐出的找零总钱数是oneTimeRest
			// 一共买的可乐数是curQianBuyColas，所以把零钱去提升后面几种面值的硬币数，
			// 就是giveRest的含义
			giveRest(qian, zhang, i + 1, oneTimeRest, curQianBuyColas);
			// 当前面值去搞定可乐这件事，一共投了几次币
			puts += curQianBuyOneColaZhang * curQianBuyColas;
			// 还剩下多少瓶可乐需要去搞定，继续用后面的面值搞定去吧
			m -= curQianBuyColas;
			// 当前面值可能剩下若干张，要参与到后续买可乐的过程中去，
			// 所以要更新preQianRest和preQianZhang
			zhang[i] -= curQianBuyOneColaZhang * curQianBuyColas;
			preQianRest = qian[i] * zhang[i];
			preQianZhang = zhang[i];
		}
		return m == 0 ? puts : -1;
	}

	void giveRest(int qian[], int zhang[], int i, int oneTimeRest, int times) {
		for (; i < 3; i++) {
			zhang[i] += (oneTimeRest / qian[i]) * times;
			oneTimeRest %= qian[i];
		}
	}

};


//一种消息接收并打印的结构设计
//已知一个消息流会不断地吐出整数 1~N，但不一定按照顺序吐出。
//如果上次打印的数为 i， 那么当 i + 1 出现时，请打印 i + 1 及其之后接收过的并且连续的所有数，直到 1~N 全部接收 并打印完
// 请设计这种接收并打印的结构。初始时默认i == 0(类似于从网络中接受分组数据包进行拼接）
class Code03_ReceiveAndPrintOrderLine {
public:
	class Node {
	public:
		string info;
		Node* next;
		Node(string str) :info(str), next(nullptr) {}
	};
	class MessageBox {
	public:
		unordered_map<int, Node*> headMap;
		unordered_map<int, Node*> tailMap;
		int waitPoint;
		MessageBox() :waitPoint(1) {}
		// 消息的编号，info消息的内容, 消息一定从1开始
		void receive(int num, string info) {
			if (num < 1)
				return;
			Node* cur = new Node(info);
			headMap[num] = cur;
			tailMap[num] = cur;
			// 建立了num~num这个连续区间的头和尾
			// 查询有没有某个连续区间以num-1结尾
			if (tailMap.count(num - 1)) {
				tailMap[num - 1]->next = cur;
				tailMap.erase(num - 1);
				headMap.erase(num);
			}
			// 查询有没有某个连续区间以num+1开头的
			if (headMap.count(num + 1)) {
				cur->next = headMap[num + 1];
				tailMap.erase(num);
				headMap.erase(num + 1);
			}
			if (num == waitPoint)
				print();
		}
		void print() {
			Node* del;
			Node* node = headMap[waitPoint];
			headMap.erase(waitPoint);
			while (node) {
				cout << node->info << " ";
				del = node;
				node = node->next;
				delete del;
				++waitPoint;
			}
			tailMap.erase(waitPoint - 1);
			cout << endl;
		}
		void test() {
			// MessageBox only receive 1~N
			MessageBox box;
			// 1....
			box.receive(2, "B"); // - 2"
			box.receive(1, "A"); // 1 2 -> print, trigger is 1
			box.receive(4, "D"); // - 4
			box.receive(5, "E"); // - 4 5
			box.receive(7, "G"); // - 4 5 - 7
			box.receive(8, "H"); // - 4 5 - 7 8
			box.receive(6, "F"); // - 4 5 6 7 8
			box.receive(3, "C"); // 3 4 5 6 7 8 -> print, trigger is 3
			box.receive(9, "I"); // 9 -> print, trigger is 9
			box.receive(10, "J"); // 10 -> print, trigger is 10
			box.receive(12, "L"); // - 12
			box.receive(13, "M"); // - 12 13
			box.receive(11, "K"); // 11 12 13 -> print, trigger is 11
		}
	};
};


//现有司机N * 2人，调度中心会将所有司机平分给A、B两个区域
//第 i 个司机去A可得收入为income[i][0]，
//第 i 个司机去B可得收入为income[i][1]，
//返回所有调度方案中能使所有司机总收入最高的方案，是多少钱
class Code04_Drive {
public:
	// income -> N * 2 的矩阵 N是偶数！
	// 0 [9, 13]
	// 1 [45,60]
	int maxMoney1(vector<vector<int>> income) {
		if (income.empty() || (income.size() & 1) != 0) {
			return 0;
		}
		int N = income.size(); // 司机数量一定是偶数，所以才能平分，A N /2 B N/2
		int M = N >> 1; // M = N / 2 要去A区域的人
		return process1(income, 0, M);
	}

	// index.....所有的司机，往A和B区域分配！
	// A区域还有rest个名额!
	// 返回把index...司机，分配完，并且最终A和B区域同样多的情况下，index...这些司机，整体收入最大是多少！
	int process1(vector<vector<int>>& income, int index, int rest) {
		if (index == income.size()) {
			return 0;
		}
		// 还剩下司机！
		if (income.size() - index == rest) {
			return income[index][0] + process1(income, index + 1, rest - 1);
		}
		if (rest == 0) {
			return income[index][1] + process1(income, index + 1, rest);
		}
		// 当前司机，可以去A，或者去B
		int p1 = income[index][0] + process1(income, index + 1, rest - 1);
		int p2 = income[index][1] + process1(income, index + 1, rest);
		return max(p1, p2);
	}
	// 再根据以上版本修改为傻缓存即可AC

	// 严格位置依赖的动态规划版本
	int maxMoney2(vector<vector<int>> income) {
		int N = income.size();
		int M = N >> 1;
		vector<vector<int>> dp(N + 1, vector<int>(M + 1));
		//每个位置都依赖于其正下方和左下方
		for (int i = N - 1; i >= 0; i--) {
			for (int j = 0; j <= M; j++) {
				if (N - i == j) {
					dp[i][j] = income[i][0] + dp[i + 1][j - 1];
				} else if (j == 0) {
					dp[i][j] = income[i][1] + dp[i + 1][j];
				} else {
					int p1 = income[i][0] + dp[i + 1][j - 1];
					int p2 = income[i][1] + dp[i + 1][j];
					dp[i][j] = max(p1, p2);
				}
			}
		}
		return dp[0][M];
	}

	//贪心
	//假设一共有10个司机，思路是先让所有司机去A，得到一个总收益
	// 然后看看哪5个司机改换门庭(去B)，可以获得最大的额外收益
	// 根据数据量猜解法可以省去大量的多余分析，节省时间
	int maxMoney3(vector<vector<int>> income) {
		int N = income.size();
		vector<int> arr(N);
		int sum = 0;
		for (int i = 0; i < N; i++) {
			arr[i] = income[i][1] - income[i][0];
			sum += income[i][0];
		}
		sort(arr.begin(), arr.end());
		int M = N >> 1;
		for (int i = N - 1; i >= M; i--) {
			sum += arr[i];
		}
		return sum;
	}
};



// 实现一个哈希表，有put get setAll 功能，且时间复杂度皆为O（1）
//思路为：增加一1个时间戳变量，每次put或setAll 自加，get时比较时间戳的先后进行返回

class Code05_SetAll {
public:
	template<typename V>
	class MyValue {
	public:
		V value;
		long time;
		MyValue() = default;
		MyValue(V v, long t) :value(v), time(t) {}
		bool operator<(const MyValue& a)const {
			return value < a.value;
		}
	};
	template<typename K, typename V>
	class MyHashMap {
	public:
		unordered_map<K, MyValue<V>> m;
		long time;
		MyValue<V> all;

		MyHashMap() :time(0), all({ -1,-1 }) {}
		void put(K key, V value) {
			m[key] = { value,time++ };
		}
		void setAll(V value) {
			all = { value,time++ };
		}
		V get(K key) {
			if (m.find(key) == m.end()) {
				return (V)nullptr;
			}
			if (m[key].time > all.time) {
				return m[key].value;
			} else {
				return all.value;
			}
		}
	};
};
//581. 最短无序连续子数组
class Code06_MinLengthForSort {
public:
	int findUnsortedSubarray(vector<int> nums) {
		if (nums.empty() || nums.size() < 2) {
			return 0;
		}
		int N = nums.size();
		int right = -1;		//答案的右边界
		int left_max = INT_MIN;
		// 从左往右寻找最后一个最大的递增序列的下标
		for (int i = 0; i < N; i++) {
			if (left_max > nums[i]) {	//左边的最大 大于当前数， 更新
				right = i;
			}
			left_max = max(left_max, nums[i]);
		}
		int right_min = INT_MAX;
		int left = N;		// 答案的左边界
		// 从右往左寻找最后一个最小的递减序列的下标
		for (int i = N - 1; i >= 0; i--) {
			if (right_min < nums[i]) {		// 右边的最小 小于当前数， 更新
				left = i;
			}
			right_min = min(right_min, nums[i]);
		}
		return max(0, right - left + 1);
	}
};


void class02() {

	//Code05_SetAll::MyHashMap<int, int> map;
	//map.put(1, 2);
	//cout << map.get(1) << endl;
	//map.setAll(3);
	//cout << map.get(1) << endl;
	//cout << map.get(2);

	Code03_ReceiveAndPrintOrderLine::MessageBox mes;
	mes.test();
}