#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstdlib>
//���鰲��
class Program {
public:
	int startTime;	//���鿪ʼʱ��
	int endTime;		//�������ʱ��
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



//�ֽ��(�������������⣩
class LessMoneySplitGold {
public:
	int lessMoney(const vector<int> arr) {
		priority_queue<int,vector<int>,greater<int>> pQ;	//��С����,���򣬿�ͷΪС��less���򣬿�ͷΪ��
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


//������ʼ�ʽ�������ɵ���Ŀ������ѡ��ͬ����Ŀ�ҳ��������
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
		bool operator()(const Node* a, const Node* b) {	//�Ի���Ϊ����С����,
			return a->c > b->c;
		}
	};
	class maxProfitsCompatator {
	public:
		bool operator()(const Node* a, const Node* b) {	  //������Ϊ���Ĵ����
			return a->p < b->p;
		}
	};
	int findMaximizedCapital(int k, int w, const vector<int>& Profits, const vector<int>& Capital) {
		priority_queue<Node*, vector<Node*>, minConstCompatator> minCostQ;
		priority_queue<Node*, vector<Node*>, maxProfitsCompatator> maxProfitsQ;

		//������Ŀ�Ե������У�������֯��С����
		for (int i = 0; i < Profits.size(); ++i) {
			minCostQ.emplace(new Node(Profits[i], Capital[i]));
		}


		for (int i = 0; i < k; ++i) {	//����K��
			//������������Ŀ��ȫ����
			while (!minCostQ.empty() && minCostQ.top()->c <= w) {
				maxProfitsQ.push(minCostQ.top());
				minCostQ.pop();
			}

			//Ŀǰ�����޷��ٽ�����Ŀ
			if (maxProfitsQ.empty()) {
				return w;
			}

			w += maxProfitsQ.top()->p;
			maxProfitsQ.pop();

		}
		return w;
	}
};


//N�ʺ�����
//DFS
class NQueens {
public:
	int num1(int n) {
		if (n < 1) {
			return 0;
		}
		vector<int> record(n);	//һ�з�һ����record[i]��ʾ��i���ʺ�����˵�record[i]��
		return process1(0, record, n);
	}

	//Ŀǰ�����˵�i��
	//record[0....i-1]��ʾ֮ǰ���У����˵Ļʺ��λ��,�κ������ʺ󶼲����У������У�����б��
	//n��ʾ����һ���ֶ�����
	//����ֵ�ǣ��������еĻʺ�󣬺���İڷ��ж�����
	int process1(int i, vector<int>& record, int n) {
		if (i == n) {
			return 1;
		}
		int res;
		for (int j = 0; j < n; ++j) {
			//��ǰ��i�У�����i�����е���
			if (isValid(record, i, j)) {
				record[i] = j;
				res += process1(i + 1, record, n);
			}
		}
		return res;
	}

	bool isValid(vector<int> record, int i, int j) {
		for (int k = 0; k < i; ++k) {
			if (j == record[k] || abs(record[k] - j) == abs(i - k)) {	//���в�����в˵�����߳�45��ǣ���б��	
				return false;
			}
		}
		return true;
	}

	//��ϵ��ʱ���Ż�
	int num2(int n) {	//��Ҫ����32�ʺ�����,��Ҫ����32,int ��Ϊlong
		if (n < 1 || n>32) {
			return 0;
		}
		int limit = n == 32 ? -1 : (1 << n) - 1;	//����λ��Ϣ�����������ر����壬����n�ʺ����⣬��nλ��1��ǰ��Ϊ0
		return process2(limit, 0, 0, 0);
	}

	//colLim�е����ƣ�1��λ�ò��ܷŻʺ�0��λ�ÿ���
	//leftDiaLim��б�ߵ����ƣ�1��λ�ò��ܷŻʺ�0��λ�ÿ���
	//rgihtDiaLim��б�ߵ����ƣ�1��λ�ò��ܷŻʺ�0��λ�ÿ���
	int process2(int limit, int colLim, int leftDiaLim, int rightDiaLim) {
		if (colLim == limit) {		//˵��n�ʺ�������
			return 1;
		}
		int pos = 0;
		int mostRightOne = 0;
		pos = limit & (~(colLim | leftDiaLim | rightDiaLim));	//�ó���pos��1��λ��Ϊ������ʺ��λ��
		int res = 0;
		while (pos != 0) {
			mostRightOne = pos & (~pos + 1);	//�����ҳ����ұߵ�1
			pos = pos - mostRightOne;	//��ȥ�ϲ������λ��1
			//�õ���һ����λ�ã�colLim���ϸ���λ�õ�1��leftDiaLim���ϸ���λ�õ���ߵ�λ�õ�1��rightDiaLim���ϸ���λ�õ��� �ߵ�λ�õ�1��
			res += process2(limit, colLim | mostRightOne, (leftDiaLim | mostRightOne) << 1, (rightDiaLim | mostRightOne) >> 1);
		}
		return res;
	}

};



//һ���������У���ʱ����ȡ����λ��
//���ô�С��
class FindMedian {
public:

	priority_queue<int> maxHeap;	//�����
	priority_queue<int, vector<int>, greater<int>> minHeap;		//С����

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
		//��ն�
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
		//�������֣���ͬ��
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