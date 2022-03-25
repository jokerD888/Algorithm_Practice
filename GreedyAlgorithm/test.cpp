#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstdlib>
//会议安排
class Program {
public:
	int startTime;	//会议开始时间
	int endTime;		//会议结束时间
	Program(int st, int en) :startTime(st), endTime(en) {}
	bool operator<(Program& a) {
		return this->endTime < a.endTime;
	}
};
class BestArrange {
public:

	int bestArrange(vector<Program>& program, int timePoint) {
		sort(program.begin(), program.end());
		int res = 0;
		for (int i = 0; i < program.size(); ++i) {
			if (timePoint <= program[i].startTime) {
				++res;
				timePoint = program[i].endTime;
			}
		}
		return res;
	}
};



//分金块(哈夫曼编码问题）
class LessMoneySplitGold {
public:
	int lessMoney(const vector<int> arr) {
		priority_queue<int,vector<int>,greater<int>> pQ;	//建小根堆,升序，开头为小，less降序，开头为大
		for (int i = 0; i < arr.size(); ++i) {
			pQ.push(arr[i]);
		}

		int sum = 0;
		int cur = 0;
		while (pQ.size() > 1) {	
			cur = pQ.top();
			pQ.pop();
			cur += pQ.top();
			pQ.pop();
			sum += cur;
			pQ.push(cur);
		} 
		return sum;
	}
};


//给定起始资金和最多完成的项目个数，选择不同的项目找出最大利润
class FindMaximizedCapital {
public:

	class Node {
	public:
		int p;
		int c;

		Node(int p, int c) :p(p), c(c) {}
	};
	class minConstCompatator {
	public:
		bool operator()(const Node* a, const Node* b) {	//以花费为主的小根堆,
			return a->c > b->c;
		}
	};
	class maxProfitsCompatator {
	public:
		bool operator()(const Node* a, const Node* b) {	  //以利润为主的大根堆
			return a->p < b->p;
		}
	};
	int findMaximizedCapital(int k, int w, const vector<int>& Profits, const vector<int>& Capital) {
		priority_queue<Node*, vector<Node*>, minConstCompatator> minCostQ;
		priority_queue<Node*, vector<Node*>, maxProfitsCompatator> maxProfitsQ;

		//所有项目仍到被锁中，花费组织的小跟堆
		for (int i = 0; i < Profits.size(); ++i) {
			minCostQ.emplace(new Node(Profits[i], Capital[i]));
		}


		for (int i = 0; i < k; ++i) {	//进行K轮
			//能力所及的项目，全解锁
			while (!minCostQ.empty() && minCostQ.top()->c <= w) {
				maxProfitsQ.push(minCostQ.top());
				minCostQ.pop();
			}

			//目前能力无法再进行项目
			if (maxProfitsQ.empty()) {
				return w;
			}

			w += maxProfitsQ.top()->p;
			maxProfitsQ.pop();

		}
		return w;
	}
};


//N皇后问题
//DFS
class NQueens {
public:
	int num1(int n) {
		if (n < 1) {
			return 0;
		}
		vector<int> record(n);	//一行放一个，record[i]表示第i个皇后放在了第record[i]列
		return process1(0, record, n);
	}

	//目前来到了第i行
	//record[0....i-1]表示之前的行，放了的皇后的位置,任何两个皇后都不共行，不公列，不公斜线
	//n表示整体一共又多少行
	//返回值是，摆完所有的皇后后，合理的摆法有多少种
	int process1(int i, vector<int>& record, int n) {
		if (i == n) {
			return 1;
		}
		int res;
		for (int j = 0; j < n; ++j) {
			//当前在i行，尝试i行所有的列
			if (isValid(record, i, j)) {
				record[i] = j;
				res += process1(i + 1, record, n);
			}
		}
		return res;
	}

	bool isValid(vector<int> record, int i, int j) {
		for (int k = 0; k < i; ++k) {
			if (j == record[k] || abs(record[k] - j) == abs(i - k)) {	//若行差等于列差，说明连线成45°角，成斜线	
				return false;
			}
		}
		return true;
	}

	//常系数时间优化
	int num2(int n) {	//不要超过32皇后问题,若要超过32,int 改为long
		if (n < 1 || n>32) {
			return 0;
		}
		int limit = n == 32 ? -1 : (1 << n) - 1;	//利用位信息，数本身无特别意义，假如n皇后问题，后n位是1，前面为0
		return process2(limit, 0, 0, 0);
	}

	//colLim列的限制，1的位置不能放皇后，0的位置可以
	//leftDiaLim左斜线的限制，1的位置不能放皇后，0的位置可以
	//rgihtDiaLim右斜线的限制，1的位置不能放皇后，0的位置可以
	int process2(int limit, int colLim, int leftDiaLim, int rightDiaLim) {
		if (colLim == limit) {		//说明n皇后已填满
			return 1;
		}
		int pos = 0;
		int mostRightOne = 0;
		pos = limit & (~(colLim | leftDiaLim | rightDiaLim));	//得出的pos的1的位置为可以填皇后的位置
		int res = 0;
		while (pos != 0) {
			mostRightOne = pos & (~pos + 1);	//依次找出最右边的1
			pos = pos - mostRightOne;	//减去上步已填的位置1
			//得到下一步的位置，colLim加上刚填位置的1，leftDiaLim加上刚填位置的左边的位置的1，rightDiaLim加上刚填位置的右 边的位置的1，
			res += process2(limit, colLim | mostRightOne, (leftDiaLim | mostRightOne) << 1, (rightDiaLim | mostRightOne) >> 1);
		}
		return res;
	}

};



//一个数据流中，随时可以取得中位数
//利用大小堆
class FindMedian {
public:

	priority_queue<int> maxHeap;	//大根堆
	priority_queue<int, vector<int>, greater<int>> minHeap;		//小根堆

	void push(int x) {
		if (maxHeap.empty()) {
			maxHeap.push(x);
			return;
		}
		if (x <= maxHeap.top()) {
			maxHeap.push(x);
		} else {
			minHeap.push(x);
		}

		if (abs((int)maxHeap.size() - (int)minHeap.size()) == 2) {
			if (maxHeap.size() > minHeap.size()) {
				minHeap.push(maxHeap.top());
				maxHeap.pop();
			} else {
				maxHeap.push(minHeap.top());
				minHeap.pop();
			}
		}
	}
	int findMedianFromArray(const vector<int>& nums) {
		//清空堆
		priority_queue<int, vector<int>, greater<int>> emptyMin;
		minHeap.swap(emptyMin);
		priority_queue<int> emptyMax;
		maxHeap.swap(emptyMax);

		for (auto i : nums) {
			push(i);
		}
		return findMedian();
	}

	int findMedian() {
		//return maxHeap.size() > minHeap.size() ? maxHeap.top() : (maxHeap.size() == minHeap.size() ? (maxHeap.top() + minHeap.top()) / 2:minHeap.top());
		//纯属娱乐，等同于
		if (maxHeap.size() == minHeap.size()) {
			return (maxHeap.size() + minHeap.size()) >> 1;
		} else if (maxHeap.size() > minHeap.size()) {
			return maxHeap.top();
		} else {
			return minHeap.top();
		}

	}
};

void test01() {
	vector<int> c{ 3,1,4,9,9 };
	vector<int> p{ 1,2,3,7,4 };
	FindMaximizedCapital a;
	cout << a.findMaximizedCapital(4, 1, p, c);

}


void test02() {
	FindMedian a;
	a.push(2);
	a.push(2);

	a.push(5);
	a.push(1);
	a.push(1);
	a.push(4);
	a.push(7);
	cout << a.findMedian() << endl;

	cout << a.findMedianFromArray({ 2,1,4,8,6,9,6,10,4,5,1 });

}
int main()
{
	//test01();
	test02();
	NQueens n;
	cout<<n.num1(6)<<" "<<n.num2(6);
	return 0;
}